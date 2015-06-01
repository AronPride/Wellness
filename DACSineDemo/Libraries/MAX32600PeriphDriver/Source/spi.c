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

/* $Revision: 4375 $ $Date: 2015-02-17 12:45:25 -0600 (Tue, 17 Feb 2015) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "spi.h"
#include "nvic_table.h"

#ifndef TIMEOUT
#define TIMEOUT      20000
#endif

#define SPI_NONE     0
#define SPI_TX       1
#define SPI_RX       2
#define SPI_BOTH     3

static spi_slave_t *spi_slaves[MXC_CFG_SPI_INSTANCES] = {NULL};
static uint32_t spi_locks[MXC_CFG_SPI_INSTANCES] = {0};

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

void SPI_ConfigClock(spi_slave_t *slave, uint8_t clk_high, uint8_t clk_low, uint8_t alt_clk_high, uint8_t alt_clk_low, uint8_t polarity, uint8_t phase) {
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

void SPI_ConfigPageSize(spi_slave_t *slave, spi_page_size_t size) {
    slave->mstr.page_size = size;
}

void SPI_ConfigSpecial(spi_slave_t *slave, spi_flow_ctrl_t flow_ctrl, uint8_t polarity, uint8_t ss_sample_mode_en, uint8_t out_val, uint8_t drv_mode, uint8_t three_wire) {
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

    slave->mstr.three_wire_mode = three_wire;
}

static void setup(spi_slave_t *slave) {
    if(BITBAND_GetBit((uint32_t)&spi_locks[slave->port], 0))
        return;

    BITBAND_SetBit((uint32_t)&spi_locks[slave->port], 0);

    spi_slaves[slave->port] = slave;
    MXC_SPI_GET_SPI(slave->port)->gen_ctrl = 0;
    MXC_SPI_GET_SPI(slave->port)->mstr_cfg_f = slave->mstr;
    MXC_SPI_GET_SPI(slave->port)->ss_sr_polarity_f = slave->ss_sr;
    MXC_SPI_GET_SPI(slave->port)->gen_ctrl_f = slave->gen;
    MXC_SPI_GET_SPI(slave->port)->spcl_ctrl_f = slave->spcl;
}

uint8_t SPI_WaitFlowControl(spi_slave_t *slave) {
    uint32_t timeout = TIMEOUT;
    mxc_spi_gen_ctrl_t gen;

    setup(slave);

    while (timeout--)
    {
        gen = MXC_SPI_GET_SPI(slave->port)->gen_ctrl_f;
        if (gen.bb_sr_in) {
            break;
        }
    }
    return gen.bb_sr_in;
}

static void cleanup(spi_slave_t *slave)
{
    BITBAND_ClrBit((uint32_t)&spi_locks[slave->port], 0);
}

static uint8_t page_to_bytes(spi_size_unit_t unit, spi_page_size_t page)
{
    if (unit == MXC_E_SPI_UNIT_PAGES) {
        switch(page)
        {
            case MXC_E_SPI_PAGE_SIZE_4B:
                return 4;
            case MXC_E_SPI_PAGE_SIZE_8B:
                return 8;
            case MXC_E_SPI_PAGE_SIZE_16B:
                return 16;
            case MXC_E_SPI_PAGE_SIZE_32B:
                return 32;
            default:
                return 1;
        }
    }
    return 1;
}

static void set_sizes(spi_slave_t *slave, uint32_t size) {
    if (slave->header.unit) {
        uint8_t bytes = page_to_bytes(MXC_E_SPI_UNIT_PAGES, slave->mstr.page_size);
        if (size >= bytes) {
            uint32_t temp = size / bytes;
            if (temp >= 32) {
                slave->header.size = 0;
                slave->temp_size = 32 * bytes;
            } else {
                slave->header.size = temp;
                slave->temp_size = temp * bytes;
            }
            slave->header.unit = 2;
        } else {
            if (size >= 32) {
                slave->header.size = 0;
                slave->temp_size = 32;
            } else {
                slave->header.size = size;
                slave->temp_size = size;
            }
            slave->header.unit = 1;
        }
    } else {
        if (size >= 32) {
            slave->header.size = 0;
            slave->temp_size = 32;
        } else {
            slave->header.size = size;
            slave->temp_size = size;
        }
        slave->header.unit = 0;
    }

    slave->temp_tx_index = -1;
    slave->temp_rx_index = 0;
}

static int32_t next_header(spi_slave_t *slave) {
    uint32_t tx_size = slave->tx_size - slave->tx_index;
    uint32_t rx_size = slave->rx_size - slave->rx_index;

    if (!tx_size && !rx_size)
        return SPI_BOTH;

    if (slave->tx_buf && slave->tx_size && tx_size) {
        if (slave->rx_buf && slave->rx_size && rx_size) {
            slave->header.direction = SPI_BOTH;
            uint32_t size = (tx_size < rx_size) ? tx_size : rx_size;

            set_sizes(slave, size);

            if (size == slave->temp_size && tx_size == rx_size) {
                slave->header.deassert_ss = slave->last;
            } else {
                slave->header.deassert_ss = 0;
            }
        } else {
            slave->header.direction = SPI_TX;

            set_sizes(slave, tx_size);

            if (tx_size == slave->temp_size) {
                slave->header.deassert_ss = slave->last;
            } else {
                slave->header.deassert_ss = 0;
            }
        }
    } else if (slave->rx_buf && slave->rx_size && rx_size) {
        slave->header.direction = SPI_RX;

        set_sizes(slave, rx_size);

        if (rx_size == slave->temp_size) {
            slave->header.deassert_ss = slave->last;
        } else {
            slave->header.deassert_ss = 0;
        }
    } else {
        slave->header.direction = SPI_NONE;
        uint32_t size = rx_size;
        if (tx_size) {
            if (rx_size) {
                size = (tx_size < rx_size) ? tx_size : rx_size;
            } else {
                size = tx_size;
            }
        }

        set_sizes(slave, size);

        if (size == slave->temp_size) {
            slave->header.deassert_ss = slave->last;
        } else {
            slave->header.deassert_ss = 0;
        }
    }

    if (!tx_size)
        return SPI_TX;

    if (!rx_size)
        return SPI_RX;

    return SPI_NONE;
}

static void prepare(spi_slave_t *slave, \
        const uint8_t *tx_buf, uint32_t tx_size, \
        uint8_t *rx_buf, uint32_t rx_size, \
        spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    slave->rx_buf = rx_buf;
    slave->rx_index = 0;
    slave->rx_size = rx_size * page_to_bytes(unit, slave->mstr.page_size);

    slave->tx_buf = tx_buf;
    slave->tx_index = 0;
    slave->tx_size = tx_size * page_to_bytes(unit, slave->mstr.page_size);

    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;
    if (slave->rx_size > 15) {
        fifo_ctrl.rx_fifo_af_lvl = 15;
    } else {
        fifo_ctrl.rx_fifo_af_lvl = 0;
    } 
    if (slave->tx_size > 7) {
        fifo_ctrl.tx_fifo_ae_lvl = 7;
    } else {
        fifo_ctrl.tx_fifo_ae_lvl = 15;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;

    switch (mode) {
        case MXC_E_SPI_MODE_DUAL:
            slave->header.width = 1;
            break;
        case MXC_E_SPI_MODE_QUAD:
            slave->header.width = 2;
            break;
        default:
            slave->header.width = 0;
            break;
    }

    slave->header.unit = unit;
    slave->header.alt_clk = alt_clk;
    slave->last = last;

    next_header(slave);
}

static void header(spi_slave_t *slave) {
    volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;
    uint8_t num_tx_fifo = 16 - fifo_ctrl.tx_fifo_used;

    if (num_tx_fifo) {
        *tx_fifo = (uint16_t)slave->header.info;
        slave->temp_tx_index = 0;
    }
}

static void transmit(spi_slave_t *slave) {
    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;
    uint8_t num_tx_fifo = 16 - fifo_ctrl.tx_fifo_used;
    uint32_t num_tx_temp = slave->temp_size - slave->temp_tx_index;

    while (num_tx_fifo && num_tx_temp) {
        if (num_tx_fifo >= 2 && num_tx_temp >= 4) {
            volatile uint32_t *tx_fifo = (uint32_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
            *tx_fifo = *((uint32_t *)&slave->tx_buf[slave->tx_index]);
            slave->tx_index += 4;
            slave->temp_tx_index += 4;
            num_tx_fifo -= 2;
            num_tx_temp -= 4;
        } else if (num_tx_temp >= 2) {
            volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
            *tx_fifo = *((uint16_t *)&slave->tx_buf[slave->tx_index]);
            slave->tx_index += 2;
            slave->temp_tx_index += 2;
            num_tx_fifo -= 1;
            num_tx_temp -= 2;
        } else {
            volatile uint16_t *tx_fifo = (uint16_t *)MXC_SPI_GET_BASE_FIFO(slave->port);
            *tx_fifo = *((uint16_t *)&slave->tx_buf[slave->tx_index]);
            slave->tx_index++;
            slave->temp_tx_index++;
            num_tx_fifo -= 1;
            num_tx_temp = 0;
        }
    }

    if (num_tx_temp > 15) {
        fifo_ctrl.tx_fifo_ae_lvl = 7;
    } else {
        fifo_ctrl.tx_fifo_ae_lvl = 15;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;
}

static void receive(spi_slave_t *slave) {
    volatile uint8_t *rx_fifo = (uint8_t *)(MXC_SPI_GET_BASE_FIFO(slave->port) + 0x800);
    mxc_spi_fifo_ctrl_t fifo_ctrl = MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f;
    uint8_t num_rx_fifo = fifo_ctrl.rx_fifo_used;
    uint32_t num_rx_temp = slave->temp_size - slave->temp_rx_index;

    while (num_rx_temp && num_rx_fifo) {
        slave->rx_buf[slave->rx_index] = *rx_fifo;
        slave->rx_index++;
        slave->temp_rx_index++;
        num_rx_temp--;
        num_rx_fifo--;
    }

    if (num_rx_temp > 15) {
        fifo_ctrl.rx_fifo_af_lvl = 15;
    } else {
        fifo_ctrl.rx_fifo_af_lvl = 0;
    }
    MXC_SPI_GET_SPI(slave->port)->fifo_ctrl_f = fifo_ctrl;
}

static int32_t transceive(spi_slave_t *slave) {
    if (slave->temp_tx_index == -1) {
        header(slave);
    } else {
        switch (slave->header.direction) {
            case SPI_BOTH:
                if (slave->temp_tx_index < slave->temp_size) {
                    transmit(slave);
                }
                if (slave->temp_rx_index < slave->temp_size) {
                    receive(slave);
                }
                if (slave->temp_tx_index == slave->temp_size && slave->temp_rx_index == slave->temp_size) {
                    return next_header(slave);
                }
                break;
            case SPI_TX:
                if (slave->temp_tx_index < slave->temp_size) {
                    transmit(slave);
                }
                if (slave->temp_tx_index == slave->temp_size) {
                    return next_header(slave);
                }
                break;
            case SPI_RX:
                if (slave->temp_rx_index < slave->temp_size) {
                    receive(slave);
                }
                if (slave->temp_rx_index == slave->temp_size) {
                    return next_header(slave);
                }
                break;
            default:
                return SPI_BOTH;
        }
    }
    return SPI_NONE;
}

int32_t SPI_TransmitAsync(spi_slave_t *slave, \
                          const uint8_t *tx_buf, uint32_t tx_size, void(*tx_handler)(int32_t ret_status), \
                          uint8_t *rx_buf, uint32_t rx_size, void(*rx_handler)(uint32_t rx_size), \
                          spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    if (!tx_size && !rx_size) {
        cleanup(slave);
        return -1;
    }

    setup(slave);

    prepare(slave, tx_buf, tx_size, rx_buf, rx_size, unit, mode, alt_clk, last);

    slave->rx_handler = rx_handler;
    slave->tx_handler = tx_handler;

    mxc_spi_inten_t inten = {0};
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

    if (transceive(slave) == SPI_BOTH) {
        cleanup(slave);
        return 0;
    }

    MXC_SPI_GET_SPI(slave->port)->intfl = 0x3F;
    MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

    NVIC_EnableIRQ(MXC_SPI_GET_IRQ(slave->port));

    return 0;
}

int32_t SPI_Transmit(spi_slave_t *slave, \
                       const uint8_t *tx_buf, uint32_t tx_size, \
                       uint8_t *rx_buf, uint32_t rx_size, \
                       spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last)
{
    if (!tx_size && !rx_size) {
        cleanup(slave);
        return -1;
    }

    setup(slave);

    prepare(slave, tx_buf, tx_size, rx_buf, rx_size, unit, mode, alt_clk, last);

    uint32_t timeout = TIMEOUT;
    while (timeout--) {
        if (transceive(slave) == SPI_BOTH) {
            if (last) {
                cleanup(slave);
            }
            return 0;
        }
    }

    cleanup(slave);
    return -1;
}

static void SPI_IRQHandler(uint32_t instance)
{
    spi_slave_t *slave = spi_slaves[instance];
    mxc_spi_inten_t inten = MXC_SPI_GET_SPI(slave->port)->inten_f;
    mxc_spi_intfl_t intfl = MXC_SPI_GET_SPI(slave->port)->intfl_f;
    MXC_SPI_GET_SPI(slave->port)->intfl_f = intfl;

    if ((inten.rx_fifo_af && intfl.rx_fifo_af) && (inten.tx_fifo_ae && intfl.tx_fifo_ae)) {
        switch (transceive(slave)) {
            case SPI_TX:
                inten.tx_fifo_ae = 0;
                MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

                if (slave->tx_handler) {
                    slave->tx_handler(slave->tx_index);
                }
                break;
            case SPI_RX:
                inten.rx_fifo_af = 0;
                MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

                if (slave->rx_handler) {
                    slave->rx_handler(slave->rx_index);
                }
                break;
            case SPI_BOTH:
                inten.tx_fifo_ae = 0;
                inten.rx_fifo_af = 0;
                MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

                if (slave->tx_handler) {
                    slave->tx_handler(slave->tx_index);
                }
                if (slave->rx_handler) {
                    slave->rx_handler(slave->rx_index);
                }
                break;
            default:
                break;
        }
    } else if (inten.tx_fifo_ae && intfl.tx_fifo_ae) {
        if (transceive(slave) == SPI_BOTH) {
            inten.tx_fifo_ae = 0;
            MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

            if (slave->tx_handler) {
                slave->tx_handler(slave->tx_index);
            }
        }
    } else if (inten.rx_fifo_af && intfl.rx_fifo_af) {
        if (transceive(slave) == SPI_BOTH) {
            inten.rx_fifo_af = 0;
            MXC_SPI_GET_SPI(slave->port)->inten_f = inten;

            if (slave->rx_handler) {
                slave->rx_handler(slave->rx_index);
            }
        }
    } else if (inten.tx_ready && intfl.tx_ready) {
        NVIC_DisableIRQ(MXC_SPI_GET_IRQ(slave->port));

        MXC_SPI_GET_SPI(slave->port)->inten = 0;
        MXC_SPI_GET_SPI(slave->port)->intfl = 0x3F;

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
