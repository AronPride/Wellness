/*******************************************************************************
 * Copyright (C) 2014 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

/* $Revision: 3015 $ $Date: 2014-08-20 16:52:05 -0600 (Wed, 20 Aug 2014) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "spi.h"
#include "clkman_regs.h"
#include "nvic_table.h"

#ifndef TIMEOUT
#define TIMEOUT      0x5000
#endif

#define SPI_NONE     0x0000
#define SPI_TX       0x0001
#define SPI_RX       0x0002
#define SPI_BOTH     0x0003

static void *spi_slave_state[MXC_CFG_SPI_INSTANCES];

void SPI_Config(spi_slave_t *slave, uint8_t port) {
    memset(slave, 0, sizeof(spi_slave_t));
    slave->port = port;
    slave->gen.spi_mstr_en = 1;
    slave->gen.tx_fifo_en = 1;
    slave->gen.rx_fifo_en = 1;
    slave->mstr.sck_hi_clk = 1;
    slave->mstr.sck_lo_clk = 1;
    slave->mstr.alt_sck_hi_clk = 1;
    slave->mstr.alt_sck_lo_clk = 1;
}

void SPI_ConfigClock(spi_slave_t *slave, uint32_t clk_high, uint8_t clk_low, uint32_t alt_clk_high, uint8_t alt_clk_low, uint8_t polarity, uint8_t phase) {
    slave->mstr.sck_hi_clk = clk_high;
    slave->mstr.sck_lo_clk = clk_low;
    slave->mstr.alt_sck_hi_clk = alt_clk_high;
    slave->mstr.alt_sck_lo_clk = alt_clk_low;
    slave->mstr.spi_mode = (((polarity & 1) << 1) | (phase & 1));
}

void SPI_ConfigSlaveSelect(spi_slave_t *slave, uint8_t slave_select, uint8_t polarity, uint8_t act_delay, uint8_t inact_delay) {
    slave->mstr.slave_sel = slave_select;
    slave->ss_sr.ss_polarity = polarity;
    slave->mstr.act_delay = act_delay;
    slave->mstr.inact_delay = inact_delay;
}

void SPI_ConfigSpecial(spi_slave_t *slave, spi_flow_ctrl_t flow_ctrl, uint8_t polarity, uint8_t ss_sample_mode_en, uint8_t out_val, uint8_t drv_mode) {
    switch (flow_ctrl) {
        case MXC_E_SPI_FLOW_CTRL_SR:
            slave->spcl.miso_fc_en = 0;
            slave->header.flow_ctrl = 1;
            break;
        case MXC_E_SPI_FLOW_CTRL_MISO:
            slave->spcl.miso_fc_en = 1;
            slave->header.flow_ctrl = 1;
            break;
        default:
            slave->spcl.miso_fc_en = 0;
            slave->header.flow_ctrl = 0;
            break;
    }
    slave->ss_sr.fc_polarity = polarity;

    slave->spcl.ss_sample_mode = ss_sample_mode_en;
    slave->spcl.ss_sa_sdio_out = out_val;
    slave->spcl.ss_sa_sdio_dr_en = drv_mode;
}

uint8_t SPI_WaitFlowControl(spi_slave_t *slave) {
    uint32_t timeout = TIMEOUT;
    mxc_spi_gen_ctrl_t gen = MXC_SPI_GET_SPI(slave->port)->gen_ctrl_f;

    while (timeout--)
    {
        gen = MXC_SPI_GET_SPI(slave->port)->gen_ctrl_f;
        if (gen.bb_sr_in) {
            break;
        }
    }
    return gen.bb_sr_in;
}

int32_t SPI_Setup(spi_slave_t *slave) {
    if(BITBAND_GetBit((uint32_t)&slave->lock, 0))
        return -1;

    BITBAND_SetBit((uint32_t)&slave->lock, 0);

    /* clear FIFOs */
    MXC_SPI_GET_SPI(slave->port)->gen_ctrl = 0;

    MXC_SPI_GET_SPI(slave->port)->mstr_cfg_f = slave->mstr;
    MXC_SPI_GET_SPI(slave->port)->ss_sr_polarity_f = slave->ss_sr;
    MXC_SPI_GET_SPI(slave->port)->gen_ctrl_f = slave->gen;
    MXC_SPI_GET_SPI(slave->port)->spcl_ctrl_f = slave->spcl;

    MXC_SPI_GET_SPI(slave->port)->inten = 0;
    MXC_SPI_GET_SPI(slave->port)->intfl = 0x3F;

    /* clock needs to be turned 'on' */
    mxc_clkman_clk_gate_ctrl1_t gater1 = MXC_CLKMAN->clk_gate_ctrl1_f;
    gater1.spi0_clk_gater = MXC_E_CLKMAN_CLK_GATE_ON;
    MXC_CLKMAN->clk_gate_ctrl1_f = gater1;

    /* enable this IRQ */
    NVIC_EnableIRQ(MXC_SPI_GET_IRQ(slave->port));

    return 0;
}

static void cleanup(spi_slave_t *slave)
{
    /* Disable the interrupts after it's done */
    MXC_SPI_GET_SPI(slave->port)->inten = 0;

    BITBAND_ClrBit((uint32_t)&slave->lock, 0);

    /* clock needs to be set back to 'dynamic' */
    mxc_clkman_clk_gate_ctrl1_t gater1 = MXC_CLKMAN->clk_gate_ctrl1_f;
    gater1.spi0_clk_gater = MXC_E_CLKMAN_CLK_GATE_DYNAMIC;
    MXC_CLKMAN->clk_gate_ctrl1_f = gater1;
}

static uint32_t page_to_bytes(spi_size_unit_t unit)
{
    switch(unit)
    {
        case MXC_E_SPI_UNIT_4B_PAGES:
            return 4;
        case MXC_E_SPI_UNIT_8B_PAGES:
            return 8;
        case MXC_E_SPI_UNIT_16B_PAGES:
            return 16;
        case MXC_E_SPI_UNIT_32B_PAGES:
            return 32;
        default:
            return 1;
    }
}

static int32_t receive(spi_slave_t *slave)
{
    volatile uint8_t *rx_fifo = (uint8_t *)(MXC_SPI_GET_BASE_FIFO(slave->port) + 0x800);
    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;

    uint8_t num_fifo = fifo_ctrl.rx_fifo_used;
    uint32_t num_rx = slave->rx_size - slave->rx_index;
    uint32_t num = (num_fifo < num_rx) ? num_fifo : num_rx;

    while (num--) {
        slave->rx_buf[slave->rx_index] = *rx_fifo;
        slave->rx_index++;
        num_rx--;
    };

    if (num_rx > 15) {
        fifo_ctrl.rx_fifo_af_lvl = 15;
    } else {
        fifo_ctrl.rx_fifo_af_lvl = 0;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;

    if (!(slave->header.direction & SPI_RX) || !num_rx) {
        return 1;
    }

    return 0;
}

static int32_t transmit(spi_slave_t *slave)
{
    volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;

    uint8_t num_fifo = 16 - fifo_ctrl.tx_fifo_used;
    uint32_t num_tx = slave->tx_size - slave->tx_index;
    uint32_t num = (num_fifo < num_tx) ? num_fifo : num_tx;

    if (!(slave->header.direction & SPI_TX) || !num_tx) {
        return 1;
    }

    while (num) {
        if (num_tx > 1) {
            *tx_fifo = slave->tx_buf[slave->tx_index] | (slave->tx_buf[slave->tx_index + 1] << 8);
            slave->tx_index += 2;
            num_tx -= 2;
        } else if (num_tx == 1) {
            *tx_fifo = slave->tx_buf[slave->tx_index] | 0xFF00;
            slave->tx_index++;
            num_tx--;
        } else {
            *tx_fifo = 0xFFFF;
        }
        if (num > 1) {
            num -= 2;
        } else {
            num--;
        }
    }

    if (num_tx > 7) {
        fifo_ctrl.tx_fifo_ae_lvl = 7;
    } else {
        fifo_ctrl.tx_fifo_ae_lvl = 15;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;

    return 0;
}

static void prepare(spi_slave_t *slave, \
        const uint8_t *tx_buf, uint32_t tx_size, \
        uint8_t *rx_buf, uint32_t rx_size, \
        spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    spi_slave_state[slave->port] = slave;
    slave->rx_buf = rx_buf;
    slave->rx_index = 0;
    slave->rx_size = rx_size  * page_to_bytes(unit);

    slave->tx_buf = tx_buf;
    slave->tx_index = 0;
    slave->tx_size = tx_size  * page_to_bytes(unit);

    if (!tx_buf && !rx_buf) {
        slave->header.direction = SPI_NONE;
        if (tx_size) {
            slave->header.size = tx_size;
        } else {
            slave->header.size = rx_size;
        }
    } else if ((tx_buf && tx_size) && (rx_buf && rx_size)) {
        slave->header.direction = SPI_BOTH;
        slave->header.size = tx_size;
    } else if (tx_buf && tx_size) {
        slave->header.direction = SPI_TX;
        slave->header.size = tx_size;
    } else if (rx_buf && rx_size) {
        slave->header.direction = SPI_RX;
        slave->header.size = rx_size;
    }

    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;

    if (slave->rx_size  > 15) {
        fifo_ctrl.rx_fifo_af_lvl = 15;
    } else {
        fifo_ctrl.rx_fifo_af_lvl = 0;
    } 
    if ((slave->tx_size) > 7) {
        fifo_ctrl.tx_fifo_ae_lvl = 7;
    } else {
        fifo_ctrl.tx_fifo_ae_lvl = 15;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;

    mxc_spi_mstr_cfg_t mstr_cfg = MXC_SPI_GET_SPI(slave->port)->mstr_cfg_f;
    switch (unit) {
        case MXC_E_SPI_UNIT_BYTES:
            mstr_cfg.page_size = 0;
            slave->header.unit = 1;
            break;
        case MXC_E_SPI_UNIT_4B_PAGES:
            mstr_cfg.page_size = 0;
            slave->header.unit = 2;
            break;
        case MXC_E_SPI_UNIT_8B_PAGES:
            mstr_cfg.page_size = 1;
            slave->header.unit = 2;
            break;
        case MXC_E_SPI_UNIT_16B_PAGES:
            mstr_cfg.page_size = 2;
            slave->header.unit = 2;
            break;
        case MXC_E_SPI_UNIT_32B_PAGES:
            mstr_cfg.page_size = 3;
            slave->header.unit = 2;
            break;
        default:
            mstr_cfg.page_size = 0;
            slave->header.unit = 0;
            break;
    }

    switch (mode) {
        case MXC_E_SPI_MODE_3_WIRE:
            mstr_cfg.three_wire_mode = 1;
            slave->header.width = 0;
            break;
        case MXC_E_SPI_MODE_DUAL:
            mstr_cfg.three_wire_mode = 0;
            slave->header.width = 1;
            break;
        case MXC_E_SPI_MODE_QUAD:
            mstr_cfg.three_wire_mode = 0;
            slave->header.width = 2;
            break;
        default:
            mstr_cfg.three_wire_mode = 0;
            slave->header.width = 0;
            break;
    }
    MXC_SPI_GET_SPI(slave->port)->mstr_cfg_f = mstr_cfg;

    slave->header.alt_clk = alt_clk;
    slave->header.deassert_ss = last;
    slave->last = last;
}

int32_t SPI_TransmitAsync(spi_slave_t *slave, \
                          const uint8_t *tx_buf, uint32_t tx_size, void(*tx_handler)(int32_t ret_status), \
                          uint8_t *rx_buf, uint32_t rx_size, void(*rx_handler)(uint32_t rx_size), \
                          spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    if ((!tx_size && !rx_size) || ((tx_size && rx_size) && (tx_size != rx_size)) || (tx_size > 32 || rx_size > 32)) {
        cleanup(slave);
        return -1;
    }

    mxc_spi_inten_t inten = MXC_SPI_GET_SPI(slave->port)->inten_f;

    prepare(slave, tx_buf, tx_size, rx_buf, rx_size, unit, mode, alt_clk, last);

    slave->rx_handler = rx_handler;
    slave->tx_handler = tx_handler;

    switch (slave->header.direction) {
        case SPI_TX:
            inten.tx_fifo_ae = 1;
            break;
        case SPI_RX:
            inten.rx_fifo_af = 1;
            break;
        case SPI_BOTH:
            inten.tx_fifo_ae = 1;
            inten.rx_fifo_af = 1;
            break;
        default:
            inten.tx_fifo_ae = 1;
            break;
    }

    inten.tx_ready = 1;

    volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
    *tx_fifo = (uint16_t)slave->header.info;

    transmit(slave);

    MXC_SPI_GET_SPI(slave->port)->intfl = 0x3F;
    MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

    return 0;
}

int32_t SPI_Transmit(spi_slave_t *slave, \
                       const uint8_t *tx_buf, uint32_t tx_size, \
                       uint8_t *rx_buf, uint32_t rx_size, \
                       spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    if ((!tx_size && !rx_size) || ((tx_size && rx_size) && (tx_size != rx_size)) || (tx_size > 32 || rx_size > 32)) {
        cleanup(slave);
        return -1;
    }

    uint32_t timeout = TIMEOUT;

    prepare(slave, tx_buf, tx_size, rx_buf, rx_size, unit, mode, alt_clk, last);

    volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
    *tx_fifo = (uint16_t)slave->header.info;

    while (timeout--) {
        if (transmit(slave) && receive(slave)) {
            cleanup(slave);

            return 0;
        }
    }

    cleanup(slave);

    return -1;
}

static void SPI_IRQHandler(uint32_t instance)
{
    spi_slave_t *slave;
    mxc_spi_intfl_t intfl;
    mxc_spi_inten_t inten;

    slave = spi_slave_state[instance];

    intfl = MXC_SPI_GET_SPI(slave->port)->intfl_f;
    MXC_SPI_GET_SPI(slave->port)->intfl_f = intfl;

    inten = MXC_SPI_GET_SPI(slave->port)->inten_f;

    if (inten.rx_fifo_af && intfl.rx_fifo_af) {
        if (receive(slave)) {
            inten = MXC_SPI_GET_SPI(slave->port)->inten_f;
            inten.rx_fifo_af = 0;
            MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

            if(slave->rx_handler) {
                slave->rx_handler(slave->rx_index);
            }
        }
    }

    if (inten.tx_fifo_ae && intfl.tx_fifo_ae) {
        if (transmit(slave)) {
            inten = MXC_SPI_GET_SPI(slave->port)->inten_f;
            inten.tx_fifo_ae = 0;
            MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

            if(slave->tx_handler) {
                slave->tx_handler(slave->tx_index);
            }
        }
    }

    if (inten.tx_ready && intfl.tx_ready) {
        inten = MXC_SPI_GET_SPI(slave->port)->inten_f;
        inten.tx_ready = 0;
        MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

        cleanup(slave);
    }
}

void SPI0_IRQHandler(void)
{
    SPI_IRQHandler(0);
}

void SPI1_IRQHandler(void)
{
    SPI_IRQHandler(1);
}

void SPI2_IRQHandler(void)
{
    SPI_IRQHandler(2);
}

#if (MXC_CFG_SPI_INSTANCES > 3)
#error "SPI driver only supports 2 instances; you should add more IRQ handlers"
#endif
