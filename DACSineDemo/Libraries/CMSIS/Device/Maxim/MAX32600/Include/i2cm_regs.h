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

/* $Revision: 3550 $ $Date: 2014-11-12 11:45:23 -0600 (Wed, 12 Nov 2014) $ */

#ifndef _MXC_I2CM_REGS_H_
#define _MXC_I2CM_REGS_H_

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
    uint32_t fs_filter_clk_div      : 8;
    uint32_t fs_scl_lo_cnt          : 12;
    uint32_t fs_scl_hi_cnt          : 12;
} mxc_i2cm_fs_clk_div_t;

typedef struct
{
    uint32_t hs_filter_clk_div      : 8;
    uint32_t hs_scl_lo_cnt          : 12;
    uint32_t hs_scl_hi_cnt          : 12;
} mxc_i2cm_hs_clk_div_t;

typedef struct
{
    uint32_t                        : 16;
    uint32_t tx_timeout             : 8;
    uint32_t auto_stop_en           : 1;
    uint32_t                        : 7;
} mxc_i2cm_timeout_t;

typedef struct
{
    uint32_t                        : 2;
    uint32_t tx_fifo_en             : 1;
    uint32_t rx_fifo_en             : 1;
    uint32_t                        : 3;
    uint32_t mstr_reset_en          : 1;
    uint32_t                        : 24;
} mxc_i2cm_ctrl_t;

typedef struct
{
    uint32_t tx_start               : 1;
    uint32_t tx_in_progress         : 1;
    uint32_t tx_done                : 1;
    uint32_t tx_nacked              : 1;
    uint32_t tx_lost_arbitr         : 1;
    uint32_t tx_timeout             : 1;
    uint32_t                        : 26;
} mxc_i2cm_trans_t;

typedef struct
{
    uint32_t tx_done                : 1;
    uint32_t tx_nacked              : 1;
    uint32_t tx_lost_arbitr         : 1;
    uint32_t tx_timeout             : 1;
    uint32_t tx_fifo_empty          : 1;
    uint32_t tx_fifo_3q_empty       : 1;
    uint32_t rx_fifo_not_empty      : 1;
    uint32_t rx_fifo_2q_full        : 1;
    uint32_t rx_fifo_3q_full        : 1;
    uint32_t rx_fifo_full           : 1;
    uint32_t                        : 22;
} mxc_i2cm_intfl_t;

typedef struct
{
    uint32_t tx_done                : 1;
    uint32_t tx_nacked              : 1;
    uint32_t tx_lost_arbitr         : 1;
    uint32_t tx_timeout             : 1;
    uint32_t tx_fifo_empty          : 1;
    uint32_t tx_fifo_3q_empty       : 1;
    uint32_t rx_fifo_empty          : 1;
    uint32_t rx_fifo_2q_full        : 1;
    uint32_t rx_fifo_3q_full        : 1;
    uint32_t rx_fifo_full           : 1;
    uint32_t                        : 22;
} mxc_i2cm_inten_t;

typedef struct
{
    uint32_t bb_scl_out             : 1;
    uint32_t bb_sda_out             : 1;
    uint32_t bb_scl_in_val          : 1;
    uint32_t bb_sda_in_val          : 1;
    uint32_t                        : 12;
    uint32_t rx_fifo_cnt            : 5;
    uint32_t                        : 11;
} mxc_i2cm_bb_t;

typedef struct
{
    uint32_t enable                 : 1;
    uint32_t                        : 3;
    uint32_t delay                  : 3;
    uint32_t                        : 25;
} mxc_i2cm_ahb_retry_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                                    Offset   Register Description
                                                      ======   ================================================ */
typedef struct {
    union {
        __IO uint32_t fs_clk_div;                 /*  0x0000   Full Speed SCL Clock Settings                    */
        __IO mxc_i2cm_fs_clk_div_t fs_clk_div_f;
    };
    union {
        __IO uint32_t hs_clk_div;                 /*  0x0004   High Speed SCL Clock Settings                    */
        __IO mxc_i2cm_hs_clk_div_t hs_clk_div_f;
    };
    __R uint32_t rsv0008;                         /*  0x0008                                                    */
    union {
        __IO uint32_t timeout;                    /*  0x000C   [TO_CNTL] Timeout and Auto-Stop Settings         */
        __IO mxc_i2cm_timeout_t timeout_f;
    };
    union {
        __IO uint32_t ctrl;                       /*  0x0010   [EN_CNTL] I2C Master Control Register            */
        __IO mxc_i2cm_ctrl_t ctrl_f;
    };
    union {
        __IO uint32_t trans;                      /*  0x0014   [MSTR_CNTL] I2C Master Tx Start and Status Flags */
        __IO mxc_i2cm_trans_t trans_f;
    };
    union {
        __IO uint32_t intfl;                      /*  0x0018   Interrupt Flags                                  */
        __IO mxc_i2cm_intfl_t intfl_f;
    };
    union {
        __IO uint32_t inten;                      /*  0x001C   Interrupt Enable/Disable Controls                */
        __IO mxc_i2cm_inten_t inten_f;
    };
    __R uint32_t rsv0020[2];                      /*  0x0020                                                    */
    union {
        __IO uint32_t bb;                         /*  0x0028   Bit-Bang Control Register                        */
        __IO mxc_i2cm_bb_t bb_f;
    };
    __R uint32_t rsv002C;                         /*  0x002C                                                    */
    union {
        __IO uint32_t retry;                      /*  0x0030   Bit-Bang Control Register                        */
        __IO mxc_i2cm_ahb_retry_t retry_f;
    };
} mxc_i2cm_regs_t;


/*                                                    Offset   Register Description
                                                      ======   ================================================ */
typedef struct {
    __IO uint32_t trans[512];                     /*  0x0000   I2C Master Transaction FIFO                      */
    __IO uint32_t rslts[512];                     /*  0x0800   I2C Master Results FIFO                          */
} mxc_i2cm_fifo_regs_t;


/*
   Register offsets for module I2CM.
*/

#define MXC_R_I2CM_OFFS_FS_CLK_DIV                ((uint32_t)0x00000000UL)
#define MXC_R_I2CM_OFFS_HS_CLK_DIV                ((uint32_t)0x00000004UL)
#define MXC_R_I2CM_OFFS_TIMEOUT                   ((uint32_t)0x0000000CUL)
#define MXC_R_I2CM_OFFS_CTRL                      ((uint32_t)0x00000010UL)
#define MXC_R_I2CM_OFFS_TRANS                     ((uint32_t)0x00000014UL)
#define MXC_R_I2CM_OFFS_INTFL                     ((uint32_t)0x00000018UL)
#define MXC_R_I2CM_OFFS_INTEN                     ((uint32_t)0x0000001CUL)
#define MXC_R_I2CM_OFFS_BB                        ((uint32_t)0x00000028UL)
#define MXC_R_I2CM_OFFS_AHB_RETRY                 ((uint32_t)0x00000030UL)

#define MXC_R_I2CM_FIFO_OFFS_TRANS                ((uint32_t)0x00000000UL)
#define MXC_R_I2CM_FIFO_OFFS_RSLTS                ((uint32_t)0x00000800UL)

#define MXC_F_I2CM_CTRL_TX_FIFO_EN_POS            (2)
#define MXC_F_I2CM_CTRL_TX_FIFO_EN                (0x00000001UL << MXC_F_I2CM_CTRL_TX_FIFO_EN_POS)
#define MXC_F_I2CM_CTRL_RX_FIFO_EN_POS            (3)
#define MXC_F_I2CM_CTRL_RX_FIFO_EN                (0x00000001UL << MXC_F_I2CM_CTRL_RX_FIFO_EN_POS)
#define MXC_F_I2CM_CTRL_MSTR_RESET_POS            (7)
#define MXC_F_I2CM_CTRL_MSTR_RESET                (0x00000001UL << MXC_F_I2CM_CTRL_MSTR_RESET_POS)

#define MXC_S_I2CM_TRANS_TAG_START                0x000
#define MXC_S_I2CM_TRANS_TAG_TXDATA_ACK           0x100
#define MXC_S_I2CM_TRANS_TAG_TXDATA_NACK          0x200
#define MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT         0x400
#define MXC_S_I2CM_TRANS_TAG_RXDATA_NACK          0x500
#define MXC_S_I2CM_TRANS_TAG_STOP                 0x700
#define MXC_S_I2CM_RSTLS_TAG_DATA                 0x100
#define MXC_S_I2CM_RSTLS_TAG_EMPTY                0x200

#ifdef __cplusplus
}
#endif

#endif
