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

/* $Revision: 3928 $ $Date: 2015-01-16 15:49:15 -0600 (Fri, 16 Jan 2015) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "uart.h"

/* device driver specific object (state data) */
typedef struct uart_state_t {
    mxc_uart_regs_t *uart_base;
    const uint8_t *tx_buffer;
    uint8_t *rx_buffer;
    uint16_t tx_index;
    volatile uint16_t tx_left; /* volatile because its accessed in both ISR and user space */
    uint16_t rx_in;
    uint16_t rx_limit;
    void(*rx_handler)(int32_t rx_bytes);
    void(*tx_done)(int32_t ret_status);
} uart_state_t;

static uart_state_t uart_state[MXC_CFG_UART_INSTANCES];

static void set_baudrate(mxc_uart_regs_t *uart_base, int baud)
{
    extern uint32_t SystemCoreClock; /* Global per CMSIS specs */
    uint32_t idiv = 0, ddiv = 0, div = 0;

    div = SystemCoreClock / ((baud / 100) * 128);
    idiv = (div / 100);
    ddiv = (div - idiv * 100) * 128 / 100;
    
    uart_base->baud_int = idiv;
    uart_base->baud_div_128 = ddiv;
}

static int32_t do_xmit(uart_state_t *state, uint8_t block)
{
    volatile mxc_uart_regs_t *my_uart = state->uart_base;
    mxc_uart_status_t status = my_uart->status_f;

    if(block)
    {
        while(state->tx_left) {
            do {
                status = my_uart->status_f;
            } while(status.tx_fifo_full);

            my_uart->tx_rx_fifo = *state->tx_buffer;
            state->tx_left--;
            state->tx_buffer++;
        }
    }
    else 
    {
        status = my_uart->status_f;
        while(state->tx_left && !(status.tx_fifo_full))
        {
            my_uart->tx_rx_fifo = state->tx_buffer[state->tx_index++];
            state->tx_left--;
            status = my_uart->status_f;
        }
    }
    return state->tx_left;
}

static void get_rx_data(mxc_uart_regs_t *my_uart, uart_state_t *state)
{
    mxc_uart_status_t status;
    status = my_uart->status_f;
    
    while(!(status.rx_fifo_empty) && (state->rx_in < state->rx_limit))
    {
        state->rx_buffer[state->rx_in] = my_uart->tx_rx_fifo;
        state->rx_in++;
        status = my_uart->status_f;
    }
    
    if(state->rx_in >= state->rx_limit)
    {
        if(state->rx_handler)
        {
            state->rx_handler(state->rx_in);
            state->rx_in = 0; /* assume the callback cleared the whole buffer */
        }
    }
}

/* this handler, will handle all UART IRQ instances */    
static void UART_IRQHandler(uint32_t instance)
{
    uart_state_t *state;
    mxc_uart_regs_t *my_uart;
    mxc_uart_intfl_t isr_reg;

    state = &uart_state[instance];

    my_uart = state->uart_base;
    isr_reg = my_uart->intfl_f;

    if(isr_reg.tx_almost_empty)
    {
        /* clear the flag we are currently servicing */
        isr_reg.tx_almost_empty = 0;
        my_uart->intfl = ~MXC_F_UART_INTFL_TX_ALMOST_EMPTY;
        
        if(state->tx_left) {
            do_xmit(state, FALSE);
        }
        
        if(state->tx_left == 0 && state->tx_done) {
            state->tx_done(state->tx_index); /* call callback with number of bytes sent */
        }
    }
    
    if(isr_reg.rx_over_threshold)
    {
        /* clear the flag we are currently servicing */
        isr_reg.rx_over_threshold = 0;
        my_uart->intfl = ~MXC_F_UART_INTFL_RX_OVER_THRESHOLD;
        get_rx_data(my_uart, state);
    }
}

void UART0_IRQHandler(void)
{
    UART_IRQHandler(0);
}

#if (MXC_CFG_UART_INSTANCES > 1)
void UART1_IRQHandler(void)
{
    UART_IRQHandler(1);
}
#endif

#if (MXC_CFG_UART_INSTANCES > 2)
#error "UART driver only supports 2 UART instances; you should add more IRQ handlers"
#endif

int32_t UART_Config(uint32_t uart_index, uint32_t baud, uint8_t par_enable, uint8_t par_mode, uint8_t flow_control)
{
    uart_state_t *state;
    mxc_uart_regs_t *my_uart = MXC_UART_GET_UART(uart_index);
    mxc_uart_ctrl_t ctrl_reg;
    mxc_uart_inten_t inten_reg;
    
    if(my_uart == NULL) {
        return -1;
    }

    state = &uart_state[uart_index];
    memset(state, 0, sizeof(uart_state_t));

    /* setup state handle */
    state->uart_base = my_uart;

    /* clear FIFO's and set params */
    ctrl_reg = my_uart->ctrl_f;
    ctrl_reg.baud_clk_en = 1;
    ctrl_reg.tx_fifo_flush = 1;
    ctrl_reg.rx_fifo_flush = 1;
    ctrl_reg.char_length = 3; /* 8 bit data */
    ctrl_reg.parity_enable = par_enable;
    ctrl_reg.parity_mode = par_mode;
    ctrl_reg.hw_flow_ctrl_en = flow_control;
    
    /* write ctrl reg back to device */
    my_uart->ctrl_f = ctrl_reg;
    
    set_baudrate(my_uart, baud);
    
    /* clear the interrupt enables and any pending leftovers */
    my_uart->inten = 0;
    my_uart->intfl = 0;

    /* enable this instance IRQ */
    NVIC_EnableIRQ(MXC_UART_GET_IRQ(uart_index));

    inten_reg = my_uart->inten_f;
    inten_reg.tx_almost_empty = 1;
    my_uart->inten_f = inten_reg;

    return 0;
}

void UART_ReadAsync(uint32_t uart_index, uint8_t *buffer, uint32_t read_count, void(*rx_cb)(int32_t bytes_read))
{
    uart_state_t *state = &uart_state[uart_index];
    mxc_uart_regs_t *my_uart = state->uart_base;
    mxc_uart_inten_t inten_reg = my_uart->inten_f;
    mxc_uart_ctrl_t ctrl_reg = my_uart->ctrl_f;
    
    state->rx_handler = rx_cb;
    state->rx_buffer = buffer;
    state->rx_limit = read_count;
    state->rx_in = 0;

    /* set the threshold, use either 1,2,4 for simplicity based on LCD of read_count */
    if(read_count & 3)
    {
        if(read_count & 1) {
            ctrl_reg.rx_threshold = 1;
        } else {
            ctrl_reg.rx_threshold = 2;
        }
    }
    else {
        ctrl_reg.rx_threshold = 4;
    }

    /* write back the ctrl reg */
    my_uart->ctrl_f = ctrl_reg;
    
    /* if handler is given, set callback for RX threshold,  else clear (reset) */
    if(rx_cb)
        inten_reg.rx_over_threshold = 1;
    else
        inten_reg.rx_over_threshold = 0;
    
    /* write back and set the interrupt enable */
    my_uart->inten_f = inten_reg;

    /* the hardware does not trigger an interrupt if there is data in the FIFO when the interrupt is enabled,
       do the check manually and handle it */
    if(my_uart->status_f.rx_fifo_chars >= ctrl_reg.rx_threshold)
    {
        get_rx_data(my_uart, state);
    }
}

int32_t UART_Read(uint32_t uart_index, uint8_t *data, uint32_t length)
{
    mxc_uart_regs_t *my_uart = (mxc_uart_regs_t *)uart_state[uart_index].uart_base;
    mxc_uart_status_t status = my_uart->status_f;
    int32_t bytes = 0;

    while(length)
    {
        do {
            status = my_uart->status_f;
        } while(status.rx_fifo_empty);

        data[bytes] = my_uart->tx_rx_fifo;
        length--;
        bytes++;
    }
    return bytes;
}

int32_t UART_Write(uint32_t uart_index, const uint8_t *data, uint32_t length)
{
    uart_state_t *state = &uart_state[uart_index];

    state->tx_buffer = data;
    state->tx_left = length;
    state->tx_done = NULL;
    do_xmit(state, TRUE);
    return length;
}

int32_t UART_WriteAsync(uint32_t uart_index, const uint8_t *data, uint32_t length, void(*tx_done_cb)(int32_t ret_status))
{
    uart_state_t *state = &uart_state[uart_index];
    
    state->tx_buffer = data;
    state->tx_left = length;
    state->tx_done = tx_done_cb;
    state->tx_index = 0;
    do_xmit(state, FALSE);
    return (int32_t)length;
}

int32_t UART_Poll(uint32_t uart_index)
{
    int32_t rx_bytes;
    mxc_uart_regs_t *my_uart = MXC_UART_GET_UART(uart_index);
    mxc_uart_status_t stat = my_uart->status_f;

    rx_bytes = stat.rx_fifo_chars;
    return rx_bytes;
}
