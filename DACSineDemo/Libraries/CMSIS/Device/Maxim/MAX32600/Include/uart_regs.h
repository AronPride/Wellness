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

/* $Revision: 3545 $ $Date: 2014-11-11 18:20:37 -0600 (Tue, 11 Nov 2014) $ */

#ifndef _MXC_UART_REGS_H_
#define _MXC_UART_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif

/*
    Bitfield structs for registers in this module
*/

typedef struct
{
    uint32_t rx_threshold      : 4;
    uint32_t parity_enable     : 1;
    uint32_t parity_mode       : 1;
    uint32_t parity_bias       : 1;
    uint32_t                   : 1;
    uint32_t tx_fifo_flush     : 1;
    uint32_t rx_fifo_flush     : 1;
    uint32_t char_length       : 2;
    uint32_t stop_bit_mode     : 1;
    uint32_t hw_flow_ctrl_en   : 1;
    uint32_t baud_clk_en       : 1;
    uint32_t                   : 17;
} mxc_uart_ctrl_t;

typedef struct
{
    uint32_t tx_busy           : 1;
    uint32_t rx_busy           : 1;
    uint32_t                   : 2;
    uint32_t rx_fifo_empty     : 1;
    uint32_t rx_fifo_full      : 1;
    uint32_t tx_fifo_empty     : 1;
    uint32_t tx_fifo_full      : 1;
    uint32_t rx_fifo_chars     : 4;
    uint32_t tx_fifo_chars     : 4;
    uint32_t                   : 16;
} mxc_uart_status_t;

typedef struct
{
    uint32_t rx_frame_error    : 1;
    uint32_t rx_parity_error   : 1;
    uint32_t cts_change        : 1;
    uint32_t rx_overrun        : 1;
    uint32_t rx_over_threshold : 1;
    uint32_t tx_almost_empty   : 1;
    uint32_t tx_half_empty     : 1;
    uint32_t                   : 25;
} mxc_uart_inten_t;

typedef struct
{
    uint32_t rx_frame_error    : 1;
    uint32_t rx_parity_error   : 1;
    uint32_t cts_change        : 1;
    uint32_t rx_overrun        : 1;
    uint32_t rx_over_threshold : 1;
    uint32_t tx_almost_empty   : 1;
    uint32_t tx_half_empty     : 1;
    uint32_t                   : 25;
} mxc_uart_intfl_t;
       
typedef struct
{
    uint32_t fbaud             : 12;
    uint32_t                   : 20;
} mxc_uart_baud_int_t;

typedef struct
{
    uint32_t div               : 7;
    uint32_t                   : 25;
} mxc_uart_baud_div_128_t;

typedef struct
{
    uint32_t tx_fifo           : 8;
    uint32_t                   : 24;
} mxc_uart_tx_fifo_out_t;

typedef struct
{
    uint32_t cts_input         : 1;
    uint32_t rts_output        : 1;
    uint32_t                   : 30;
} mxc_uart_hw_flow_ctrl_t;

typedef struct
{
    uint32_t fifo_data         : 8;
    uint32_t parity_error      : 1;
    uint32_t                   : 23;
} mxc_uart_tx_rx_fifo_t;



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                        Offset   Register Description
                                                          ======   ============================================== */
typedef struct {
    union {
        __IO uint32_t ctrl;                          /*  0x0000   [CR] UART Control Register                      */
        __IO mxc_uart_ctrl_t ctrl_f;
    };
    union {
        __IO uint32_t status;                        /*  0x0004   [SR] UART Status Register                       */
        __IO mxc_uart_status_t status_f;
    };
    union {
        __IO uint32_t inten;                         /*  0x0008   [IER] Interrupt Enable/Disable Controls         */
        __IO mxc_uart_inten_t inten_f;
    };
    union {
        __IO uint32_t intfl;                         /*  0x000C   [ISR] Interrupt Flags                           */
        __IO mxc_uart_intfl_t intfl_f;
    };
    union {
        __IO uint32_t baud_int;                      /*  0x0010   [BRR] Baud Rate Setting (Integer Portion)       */
        __IO mxc_uart_baud_int_t baud_int_f;
    };
    union {
        __IO uint32_t baud_div_128;                  /*  0x0014   [RCR] Baud Rate Setting                         */
        __IO mxc_uart_baud_div_128_t baud_div_128_f;
    };
    union {
        __IO uint32_t tx_fifo_out;                   /*  0x0018   [TXR] TX FIFO Output End (read-only)            */
        __IO mxc_uart_tx_fifo_out_t tx_fifo_out_f;
    };
    union {
        __IO uint32_t hw_flow_ctrl;                  /*  0x001C   [PNR] Hardware Flow Control Register            */
        __IO mxc_uart_hw_flow_ctrl_t hw_flow_ctrl_f;
    };
    union {
        __IO uint32_t tx_rx_fifo;                    /*  0x0020   [DR] Write to load TX FIFO, Read to unload RX FIFO */
        __IO mxc_uart_tx_rx_fifo_t tx_rx_fifo_f;
    };
} mxc_uart_regs_t;


/*
 *   Register offsets for module UART.
 */

#define MXC_R_UART_OFFS_CTRL                      ((uint32_t)0x00000000UL)
#define MXC_R_UART_OFFS_STATUS                    ((uint32_t)0x00000004UL)
#define MXC_R_UART_OFFS_INTEN                     ((uint32_t)0x00000008UL)
#define MXC_R_UART_OFFS_INTFL                     ((uint32_t)0x0000000CUL)
#define MXC_R_UART_OFFS_BAUD_INT                  ((uint32_t)0x00000010UL)
#define MXC_R_UART_OFFS_BAUD_DIV_128              ((uint32_t)0x00000014UL)
#define MXC_R_UART_OFFS_TX_FIFO_OUT               ((uint32_t)0x00000018UL)
#define MXC_R_UART_OFFS_HW_FLOW_CTRL              ((uint32_t)0x0000001CUL)
#define MXC_R_UART_OFFS_TX_RX_FIFO                ((uint32_t)0x00000020UL)

/*
 *   bit offsets for interrupt flag registers 
 */
#define MXC_F_UART_INTFL_RX_FRAME_ERROR            ((uint32_t)0x00000001UL)
#define MXC_F_UART_INTFL_RX_FRAME_ERROR_POS        (0)

#define MXC_F_UART_INTFL_RX_PARITY_ERROR           ((uint32_t)0x00000002UL)
#define MXC_F_UART_INTFL_RX_PARITY_ERROR_POS       (1)

#define MXC_F_UART_INTFL_CTS_CHANGE                ((uint32_t)0x00000004UL)
#define MXC_F_UART_INTFL_CTS_CHANGE_POS            (2)

#define MXC_F_UART_INTFL_RX_OVERRUN                ((uint32_t)0x00000008UL)
#define MXC_F_UART_INTFL_RX_OVERRUN_POS            (3)

#define MXC_F_UART_INTFL_RX_OVER_THRESHOLD         ((uint32_t)0x00000010UL)
#define MXC_F_UART_INTFL_RX_OVER_THRESHOLD_POS     (4)

#define MXC_F_UART_INTFL_TX_ALMOST_EMPTY           ((uint32_t)0x00000020UL)
#define MXC_F_UART_INTFL_TX_ALMOST_EMPTY_POS       (5)

#define MXC_F_UART_INTFL_TX_HALF_EMPTY             ((uint32_t)0x00000040UL)
#define MXC_F_UART_INTFL_TX_HALF_EMPTY_POS         (6)


#ifdef __cplusplus
}
#endif
#endif /* _MXC_UART_REGS_H_ */

