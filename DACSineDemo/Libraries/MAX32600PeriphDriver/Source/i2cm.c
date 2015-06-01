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

/* $Revision: 4394 $ $Date: 2015-02-17 15:51:27 -0600 (Tue, 17 Feb 2015) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "i2cm.h"

#define I2C_SLAVE_ADDR_READ_BIT     0x0001

#ifndef MXC_I2CM_TX_TIMEOUT
#define MXC_I2CM_TX_TIMEOUT                     0x5000
#endif

#ifndef MXC_I2CM_RX_TIMEOUT
#define MXC_I2CM_RX_TIMEOUT                     0x5000
#endif


typedef struct i2c_master_t {
    uint8_t *buf;
    uint32_t bytes_left;
    uint32_t bytes_index;
    void (*callback_fn)(int32_t);
    uint8_t read;
    uint8_t index;
    uint8_t addr;
    uint8_t stop_bit;
} i2c_master_t;

static i2c_master_t i2c_master_state[MXC_CFG_I2CM_INSTANCES];

static void do_xmit(i2c_master_t *im)
{
    volatile uint16_t *tx_fifo = (uint16_t *)MXC_I2CM_GET_BASE_FIFO(im->index);
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(im->index);

    if(im->bytes_left && im->buf)
    {
        do {
            *tx_fifo = (MXC_S_I2CM_TRANS_TAG_TXDATA_ACK | im->buf[im->bytes_index++]);
            --im->bytes_left;
        } while(im->bytes_left && regs->intfl_f.tx_fifo_3q_empty);
    }
}

inline static int32_t I2CM_WriteToTxFifo(uint8_t index, const uint16_t data)
{
    volatile uint16_t *tx_fifo = (uint16_t *)MXC_I2CM_GET_BASE_FIFO(index);
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    mxc_i2cm_intfl_t intfl;

    while(*tx_fifo) {
        intfl = regs->intfl_f;
        if((intfl.tx_nacked) || (intfl.tx_timeout) || (intfl.tx_lost_arbitr)) {
            return -1;
        }
    }
    *tx_fifo = data;
    return 0;
}

static int32_t I2CM_TxAsync(i2c_master_t *im)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(im->index);
    mxc_i2cm_inten_t inten = regs->inten_f;

    regs->intfl = 0x3FF;
    inten.tx_done = 1;
    regs->inten_f = inten;
    NVIC_EnableIRQ(MXC_I2CM_GET_IRQ(im->index)); 
    
    if(I2CM_WriteToTxFifo(im->index, (MXC_S_I2CM_TRANS_TAG_START | im->addr))) { /* start + addr (write) */
        return -1;
    }

    mxc_i2cm_trans_t trans = regs->trans_f;
    /* start the transaction if it wasn't already started */
    if (!trans.tx_in_progress) {
        trans.tx_start = 1;
        regs->trans_f = trans;
    }

    do_xmit(im);
    return 0;
}

static int32_t I2CM_RxAsync(i2c_master_t *im)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(im->index);
    mxc_i2cm_inten_t inten = regs->inten_f;
    uint32_t i = im->bytes_left;

    regs->intfl = 0x3FF;
    inten.rx_fifo_2q_full = 1;
    inten.rx_fifo_3q_full = 1;
    inten.rx_fifo_full = 1;
    inten.rx_fifo_empty = 1;
    regs->inten_f = inten;
    NVIC_EnableIRQ(MXC_I2CM_GET_IRQ(im->index)); 

    /* start + addr (read) */
    if(I2CM_WriteToTxFifo(im->index, (MXC_S_I2CM_TRANS_TAG_START | (im->addr) | I2C_SLAVE_ADDR_READ_BIT))) { 
        return -1;
    }
    
    while(i > 256) 
    {
        if(I2CM_WriteToTxFifo(im->index, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | 255))) {
            return -1;
        }
        i -= 256;
    }

    if (i > 1) 
    {
        if(I2CM_WriteToTxFifo(im->index, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | (i - 2)))) {
            return -1;
        }
    }

    if(I2CM_WriteToTxFifo(im->index, MXC_S_I2CM_TRANS_TAG_RXDATA_NACK)) { /* NACK last data byte */
        return -1;
    }

    if(I2CM_WriteToTxFifo(im->index, MXC_S_I2CM_TRANS_TAG_STOP)) { /* stop condition */
        return -1;
    }

    mxc_i2cm_trans_t trans = regs->trans_f;
    /* start the transaction if it wasn't already started */
    if (!trans.tx_in_progress) {
        trans.tx_start = 1;
        regs->trans_f = trans;
    }

    return 0;
}

static void I2CM_IRQHandler(uint32_t instance)
{
    i2c_master_t *im = &i2c_master_state[instance];
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(instance);
    mxc_i2cm_intfl_t intfl = regs->intfl_f;
    mxc_i2cm_inten_t inten = regs->inten_f;

    regs->intfl_f = intfl;

    if(intfl.tx_done && inten.tx_done)
    {
        if(!im->bytes_left)
        {
            if(im->stop_bit) {
                I2CM_WriteToTxFifo(im->index, MXC_S_I2CM_TRANS_TAG_STOP);
            }

            inten.tx_done = 0;
            regs->inten_f = inten;

            im->buf = NULL;

            if(im->callback_fn) {
                im->callback_fn(0);
            }
        }
        else {
            do_xmit(im);
        }
    }

    if((intfl.rx_fifo_not_empty || intfl.rx_fifo_full || intfl.rx_fifo_2q_full || intfl.rx_fifo_3q_full ) && inten.rx_fifo_empty)
    {
        volatile uint16_t *rx_fifo = (uint16_t *)(MXC_I2CM_GET_BASE_FIFO(im->index) + 0x800);
        uint8_t bytes_to_read = regs->bb_f.rx_fifo_cnt;
        uint32_t i;

        if(im->bytes_index < im->bytes_left) 
        {
            for(i = 0; i < bytes_to_read; i++) {
                im->buf[im->bytes_index++] = *rx_fifo;
            }
        }

        if(im->bytes_index == im->bytes_left) {
            inten = regs->inten_f;
            inten.rx_fifo_2q_full = 0;
            inten.rx_fifo_3q_full = 0;
            inten.rx_fifo_full = 0;
            inten.rx_fifo_empty = 0;
            regs->inten_f = inten;

            im->buf = NULL;

            if(im->callback_fn) {
                im->callback_fn(im->bytes_index);
            }
        }
    }
}

void I2CM0_IRQHandler(void)
{
    I2CM_IRQHandler(0);
}

void I2CM1_IRQHandler(void)
{
    I2CM_IRQHandler(1);
}

static i2c_master_t i2cm_data;

static void i2cm_cmd_cb(int32_t ret_status) 
{
    if(!i2cm_data.read) {
        I2CM_TxAsync(&i2cm_data);
    }
    else if(i2cm_data.read) {
        I2CM_RxAsync(&i2cm_data);
    }
}

static void i2cm_fill_tx_struct(i2c_master_t *im, uint8_t index, uint8_t addr, const uint8_t *data, uint32_t data_bytes, void(*tx_done)(int32_t ret_status), uint8_t stop_bit)
{
    memset(im, 0, sizeof(i2c_master_t));

    im->index = index;
    im->addr = addr;
    im->stop_bit = stop_bit;
    
    im->buf = (uint8_t *)data;
    im->bytes_index = 0;
    im->bytes_left = data_bytes;
    im->callback_fn = tx_done;
}

static void i2cm_fill_rx_struct(i2c_master_t *im, uint8_t index, uint8_t addr, uint8_t *data, uint32_t data_bytes, void(*rx_handler)(int32_t rx_bytes))
{
    memset(im, 0, sizeof(i2c_master_t));

    im->index = index;
    im->addr = addr;
    im->stop_bit = 1;

    im->buf = data;
    im->bytes_index = 0;
    im->bytes_left = data_bytes;
    im->callback_fn = rx_handler;
}

int32_t I2CM_WriteAsync(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, const uint8_t *data, uint32_t data_bytes, void(*tx_done)(int32_t ret_status))
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    i2c_master_t *im = &i2c_master_state[index];

    if (regs->trans_f.tx_in_progress) {
        return -1;
    }

    if (!cmd_bytes && !data_bytes) {
        return -1;
    }

    regs->intfl = 0x3FF; /* clear all interrupts */

    if(cmd_bytes && cmd) 
    {
        i2cm_fill_tx_struct(im, index, addr, cmd, cmd_bytes, i2cm_cmd_cb, 0);
        I2CM_TxAsync(im);

        i2cm_fill_tx_struct(&i2cm_data, index, addr, data, data_bytes, tx_done, 1);
        I2CM_TxAsync(&i2cm_data);
        return 0;
    }

    if(data_bytes && data)
    {
        i2cm_fill_tx_struct(im, index, addr, data, data_bytes, tx_done, 1);
        I2CM_TxAsync(im);
        return 0;
    }

    return -1;
}

int32_t I2CM_ReadAsync(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, uint8_t *data, uint32_t data_bytes, void(*rx_handler)(int32_t rx_bytes))
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    i2c_master_t *im = &i2c_master_state[index];

    if (regs->trans_f.tx_in_progress) {
        return -1;
    }

    if (!cmd_bytes && !data_bytes) {
        return -1;
    }

    regs->intfl = 0x3FF; /* clear all interrupts */

    if(cmd_bytes && cmd) 
    {
        i2cm_fill_tx_struct(im, index, addr, cmd, cmd_bytes, i2cm_cmd_cb, 0);
        I2CM_TxAsync(im);

        i2cm_fill_rx_struct(&i2cm_data, index, addr, data, data_bytes, rx_handler);
        I2CM_TxAsync(&i2cm_data);
        return 0;
    }

    if(data_bytes && data)
    {
        i2cm_fill_rx_struct(im, index, addr, data, data_bytes, rx_handler);
        I2CM_RxAsync(im);
        return 0;
    }
    return -1;
}

static int32_t I2CM_TxInProgress(uint8_t index)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    int32_t timeout = MXC_I2CM_TX_TIMEOUT;

    while (regs->trans_f.tx_in_progress && --timeout);

    if (!timeout || regs->trans_f.tx_nacked || regs->trans_f.tx_lost_arbitr || regs->trans_f.tx_timeout) {
        /* recover */
        regs->ctrl = MXC_F_I2CM_CTRL_MSTR_RESET;
        regs->intfl = 0x3FF; /* clear all interrupts */
        regs->ctrl = MXC_F_I2CM_CTRL_TX_FIFO_EN | MXC_F_I2CM_CTRL_RX_FIFO_EN;
        return -1;
    }

    return 0;
}

static int32_t I2CM_Rx(uint8_t index, uint8_t addr, uint8_t *data, uint32_t bytes)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    volatile uint16_t *rx_fifo = (uint16_t *)(MXC_I2CM_GET_BASE_FIFO(index) + 0x800);
    uint32_t i = bytes;
    
    /* start + addr (read) */
    if(I2CM_WriteToTxFifo(index, (MXC_S_I2CM_TRANS_TAG_START | addr | I2C_SLAVE_ADDR_READ_BIT))) { 
        return -1;
    }
    
    while(i > 256) 
    {
        if(I2CM_WriteToTxFifo(index, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | 255))) {
            return -1;
        }
        i -= 256;
    }

    if (i > 1) 
    {
        if(I2CM_WriteToTxFifo(index, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | (i - 2)))) {
            return -1;
        }
    }

    mxc_i2cm_trans_t trans = regs->trans_f;
    /* start the transaction if it wasn't already started */
    if (!trans.tx_in_progress) {
        trans.tx_start = 1;
        regs->trans_f = trans;
    }

    if(I2CM_WriteToTxFifo(index, MXC_S_I2CM_TRANS_TAG_RXDATA_NACK)) { /* NACK last data byte */
        return -1;
    }

    if(I2CM_WriteToTxFifo(index, MXC_S_I2CM_TRANS_TAG_STOP)) { /* stop condition */
        return -1;
    }

    int32_t timeout = MXC_I2CM_RX_TIMEOUT;
    uint16_t temp;

    i = 0;
    while(i < bytes)
    {
        while (!regs->intfl_f.rx_fifo_not_empty && (regs->bb_f.rx_fifo_cnt == 0)) {
            if ((timeout-- < 0) || !regs->trans_f.tx_in_progress) {
                return -1;
            }
        }

        timeout = MXC_I2CM_RX_TIMEOUT;
    
        mxc_i2cm_intfl_t intfl = regs->intfl_f;
        intfl.rx_fifo_not_empty = 1;
        regs->intfl_f = intfl;

        temp = *rx_fifo;

        if(temp & MXC_S_I2CM_RSTLS_TAG_EMPTY) {
            continue;
        }
        data[i++] = (uint8_t) temp;
    }
    return i;
}

static int32_t I2CM_Tx(uint8_t index, uint8_t addr, const uint8_t *data, uint32_t bytes, uint8_t stop)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    uint32_t i;

    if(I2CM_WriteToTxFifo(index, (MXC_S_I2CM_TRANS_TAG_START | addr))) { /* start + addr (write) */
        return -1;
    }

    mxc_i2cm_trans_t trans = regs->trans_f;
    /* start the transaction if it wasn't already started */
    if (!trans.tx_in_progress) {
        trans.tx_start = 1;
        regs->trans_f = trans;
    }

    /* load as much of the cmd into the FIFO as possible */
    for (i = 0; i < bytes; i++) {
        if(I2CM_WriteToTxFifo(index, (MXC_S_I2CM_TRANS_TAG_TXDATA_ACK | data[i]))) { /* cmd (expect ACK) */
            return -1;
        }
    }

    if(stop) {
        if(I2CM_WriteToTxFifo(index, MXC_S_I2CM_TRANS_TAG_STOP)) { /* stop condition */
            return -1;
        }
    }
    return i;
}

int32_t I2CM_Read(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, uint8_t *data, uint32_t data_bytes)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    int32_t retval = data_bytes;

    if (regs->trans_f.tx_in_progress) {
        return -1;
    }

    if (!cmd_bytes && !data_bytes) {
        return -1;
    }

    regs->intfl = 0x3FF; /* clear all interrupts */

    if (cmd_bytes) {
        if (I2CM_Tx(index, addr, cmd, cmd_bytes, FALSE) != cmd_bytes) {
            retval = -1;
        }
    }

    /* ACK (count - 1) data bytes */
    if (data_bytes) {
        if (I2CM_Rx(index, addr, data, data_bytes) != data_bytes) {
            retval = -1;
        }
    }

    if(I2CM_TxInProgress(index)) {
        retval = -1;
    }
    return retval;
}

int32_t I2CM_Write(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, const uint8_t *data, uint32_t data_bytes)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    int32_t retval = data_bytes;

    if (regs->trans_f.tx_in_progress) {
        return -1;
    }

    if (!cmd_bytes && !data_bytes) {
        return -1;
    }

    regs->intfl = 0x3FF; /* clear all interrupts */

    if (cmd_bytes) {
        if(I2CM_Tx(index, addr, cmd, cmd_bytes, FALSE) != cmd_bytes) {
            retval = -1;
        }
    }

    if (data_bytes) {
        if(I2CM_Tx(index, addr, data, data_bytes, TRUE) != data_bytes) {
            retval = -1;
        }
    }

    if(I2CM_TxInProgress(index)) {
        retval = -1;
    }
    return retval;
}

int32_t I2CM_Init(uint8_t index, i2cm_speed_t speed)
{
    mxc_i2cm_regs_t *regs = MXC_I2CM_GET_I2CM(index);
    mxc_i2cm_fs_clk_div_t fs_div = regs->fs_clk_div_f;
    mxc_i2cm_hs_clk_div_t hs_div = regs->hs_clk_div_f;
    mxc_i2cm_ctrl_t ctrl = regs->ctrl_f;

    /* reset module */
    ctrl.mstr_reset_en = 1;
    regs->ctrl_f = ctrl;
    regs->ctrl = 0;

    switch(speed)
    {
        case MXC_E_I2CM_SPEED_100KHZ:
            if(SystemCoreClock == 24000000) {
                fs_div.fs_filter_clk_div = 12;
                fs_div.fs_scl_hi_cnt = 38;
                fs_div.fs_scl_lo_cnt = 144;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 16000000) {
                fs_div.fs_filter_clk_div = 8;
                fs_div.fs_scl_hi_cnt = 24;
                fs_div.fs_scl_lo_cnt = 96;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 12000000) {
                fs_div.fs_filter_clk_div = 6;
                fs_div.fs_scl_hi_cnt = 17;
                fs_div.fs_scl_lo_cnt = 72;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 8000000) {
                fs_div.fs_filter_clk_div = 4;
                fs_div.fs_scl_hi_cnt = 10;
                fs_div.fs_scl_lo_cnt = 48;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 6000000) {
                fs_div.fs_filter_clk_div = 3;
                fs_div.fs_scl_hi_cnt = 7;
                fs_div.fs_scl_lo_cnt = 36;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 3000000) {
                fs_div.fs_filter_clk_div = 2;
                fs_div.fs_scl_hi_cnt = 1;
                fs_div.fs_scl_lo_cnt = 18;
                regs->fs_clk_div_f = fs_div;
            }
            break;
        case MXC_E_I2CM_SPEED_400KHZ:
            if(SystemCoreClock == 24000000) {
                fs_div.fs_filter_clk_div = 3;
                fs_div.fs_scl_lo_cnt = 36;
                fs_div.fs_scl_hi_cnt = 5;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 16000000) {
                fs_div.fs_filter_clk_div = 2;
                fs_div.fs_scl_hi_cnt = 2;
                fs_div.fs_scl_lo_cnt = 24;
                regs->fs_clk_div_f = fs_div;
            }
            else if(SystemCoreClock == 12000000) {
                fs_div.fs_filter_clk_div = 2;
                fs_div.fs_scl_hi_cnt = 1;
                fs_div.fs_scl_lo_cnt = 18;
                regs->fs_clk_div_f = fs_div;
            }
            break;
        case MXC_E_I2CM_SPEED_1MHZ:
            if(SystemCoreClock == 24000000) {
                hs_div.hs_filter_clk_div = 1;
                hs_div.hs_scl_lo_cnt = 14;
                hs_div.hs_scl_hi_cnt = 0;
                regs->hs_clk_div_f = hs_div;
            }
            break;
        default:
            return -1;
    }

    /* set timeout to 255 ms and turn on the auto-stop option */
    mxc_i2cm_timeout_t timeout = regs->timeout_f;
    timeout.tx_timeout = 0xFF;
    timeout.auto_stop_en = 1;
    regs->timeout_f = timeout;

    /* enable tx_fifo and rx_fifo */
    ctrl = regs->ctrl_f;
    ctrl.tx_fifo_en = 1;
    ctrl.rx_fifo_en = 1;
    regs->ctrl_f = ctrl;

    return 0;
}
