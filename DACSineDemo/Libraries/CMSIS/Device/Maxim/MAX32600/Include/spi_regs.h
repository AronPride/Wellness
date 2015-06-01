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

#ifndef _MXC_SPI_REGS_H
#define _MXC_SPI_REGS_H

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
    uint32_t slave_sel         : 3;
    uint32_t three_wire_mode   : 1;
    uint32_t spi_mode          : 2;
    uint32_t page_size         : 2;

    uint32_t sck_hi_clk        : 4;
    uint32_t sck_lo_clk        : 4;

    uint32_t act_delay         : 2;
    uint32_t inact_delay       : 2;
    uint32_t alt_sck_hi_clk    : 4;

    uint32_t alt_sck_lo_clk    : 4;
    uint32_t                   : 4;
} mxc_spi_mstr_cfg_t;

typedef struct
{
    uint32_t ss_polarity       : 8;
    uint32_t fc_polarity       : 8;
    uint32_t                   : 16;
} mxc_spi_ss_sr_polarity_t;

typedef struct
{
    uint32_t spi_mstr_en       : 1;
    uint32_t tx_fifo_en        : 1;
    uint32_t rx_fifo_en        : 1;
    uint32_t bit_bang_mode     : 1;
    uint32_t bb_ss_in_out      : 1;
    uint32_t bb_sr_in          : 1;
    uint32_t bb_sck_in_out     : 1;
    uint32_t                   : 1;

    uint32_t bb_sdio_in        : 4;
    uint32_t bb_sdio_out       : 4;

    uint32_t bb_sdio_dr_en     : 4;
    uint32_t                   : 12;
} mxc_spi_gen_ctrl_t;

typedef struct
{
    uint32_t tx_fifo_ae_lvl    : 4;
    uint32_t                   : 4;

    uint32_t tx_fifo_used      : 5;
    uint32_t                   : 3;

    uint32_t rx_fifo_af_lvl    : 5;
    uint32_t                   : 3;

    uint32_t rx_fifo_used      : 6;
    uint32_t                   : 2;
} mxc_spi_fifo_ctrl_t;

typedef struct
{
    uint32_t ss_sample_mode    : 1;
    uint32_t miso_fc_en        : 1;
    uint32_t                   : 2;
    uint32_t ss_sa_sdio_out    : 4;
    uint32_t ss_sa_sdio_dr_en  : 4;
    uint32_t                   : 20;
} mxc_spi_spcl_ctrl_t;

typedef struct
{
    uint32_t tx_stalled        : 1;
    uint32_t rx_stalled        : 1;
    uint32_t tx_ready          : 1;
    uint32_t rx_done           : 1;
    uint32_t tx_fifo_ae        : 1;
    uint32_t rx_fifo_af        : 1;
    uint32_t                   : 26;
} mxc_spi_intfl_t;

typedef struct
{
    uint32_t tx_stalled        : 1;
    uint32_t rx_stalled        : 1;
    uint32_t tx_ready          : 1;
    uint32_t rx_done           : 1;
    uint32_t tx_fifo_ae        : 1;
    uint32_t rx_fifo_af        : 1;
    uint32_t                   : 26;
} mxc_spi_inten_t;

typedef struct
{
    uint32_t tx_fifo_retry_en    : 1;
    uint32_t                     : 3;
    uint32_t tx_fifo_retry_delay : 3;
    uint32_t                     : 1;
    uint32_t rx_fifo_retry_en    : 1;
    uint32_t                     : 3;
    uint32_t rx_fifo_retry_delay : 3;
    uint32_t                     : 17;
} mxc_spi_mstr_ahb_retry_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                          Offset   Register Description
                                                            ======   ============================================ */
typedef struct {
    union {
        __IO uint32_t mstr_cfg;                         /*  0x0000   SPI Master Configuration Register            */
        __IO mxc_spi_mstr_cfg_t mstr_cfg_f;
    };
    union {
        __IO uint32_t ss_sr_polarity;                   /*  0x0004   Polarity Control for SS and SR Signals       */
        __IO mxc_spi_ss_sr_polarity_t ss_sr_polarity_f;
    };
    union {
        __IO uint32_t gen_ctrl;                         /*  0x0008   SPI Master General Control Register          */
        __IO mxc_spi_gen_ctrl_t gen_ctrl_f;
    };
    union {
        __IO uint32_t fifo_ctrl;                        /*  0x000C   SPI Master FIFO Control Register             */
        __IO mxc_spi_fifo_ctrl_t fifo_ctrl_f;
    };
    union {
        __IO uint32_t spcl_ctrl;                        /*  0x0010   SPI Master Special Mode Controls             */
        __IO mxc_spi_spcl_ctrl_t spcl_ctrl_f;
    };
    union {
        __IO uint32_t intfl;                            /*  0x0014   SPI Master Interrupt Flags                   */
        __IO mxc_spi_intfl_t intfl_f;
    };
    union {
        __IO uint32_t inten;                            /*  0x0018   SPI Master Interrupt Enable/Disable Settings */
        __IO mxc_spi_inten_t inten_f;
    };
    __R uint32_t rsv001C;                               /*  0x001C   Deprecated - was SPI_AHB_RETRY               */
} mxc_spi_regs_t;


/*                                                          Offset   Register Description
                                                            ======   ============================================ */
typedef struct {
    __IO uint32_t trans[512];                           /*  0x0000   FIFO Write Point for Transaction Setup       */
    __IO uint32_t rslts[512];                           /*  0x0800   FIFO Read Point for Results Data             */
} mxc_spi_fifo_regs_t;


/*
   Register offsets for module SPI.
*/

#define MXC_R_SPI_OFFS_MSTR_CFG                   ((uint32_t)0x00000000UL)
#define MXC_R_SPI_OFFS_SS_SR_POLARITY             ((uint32_t)0x00000004UL)
#define MXC_R_SPI_OFFS_GEN_CTRL                   ((uint32_t)0x00000008UL)
#define MXC_R_SPI_OFFS_FIFO_CTRL                  ((uint32_t)0x0000000CUL)
#define MXC_R_SPI_OFFS_SPCL_CTRL                  ((uint32_t)0x00000010UL)
#define MXC_R_SPI_OFFS_INTFL                      ((uint32_t)0x00000014UL)
#define MXC_R_SPI_OFFS_INTEN                      ((uint32_t)0x00000018UL)

#define MXC_R_SPI_FIFO_OFFS_TRANS                 ((uint32_t)0x00000000UL)
#define MXC_R_SPI_FIFO_OFFS_RSLTS                 ((uint32_t)0x00000800UL)


#ifdef __cplusplus
}
#endif
#endif
