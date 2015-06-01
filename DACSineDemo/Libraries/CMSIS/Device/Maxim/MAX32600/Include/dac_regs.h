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

#ifndef _MXC_DAC_REGS_H
#define _MXC_DAC_REGS_H

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

/**
 * @file  dac_regs.h
 * @addtogroup dac DAC
 * @{
 */

/**
 * @brief Defines the DAC Operational Modes.
 */
typedef enum {
    /** DAC OpMode FIFO */
    MXC_E_DAC_OP_MODE_FIFO = 0,
    /** DAC OpMode Sample Count */
    MXC_E_DAC_OP_MODE_DACSMPLCNT,
    /** DAC OpMode DAC_REG Control */
    MXC_E_DAC_OP_MODE_DAC_REG,
    /** DAC OpMode Continuous */
    MXC_E_DAC_OP_MODE_CONTINUOUS
} mxc_dac_op_mode_t;

/**
 * @brief Defines the DAC Interpolation Options.
 */
typedef enum {
    /** DAC Interpolation is Disabled */
    MXC_E_DAC_INTERP_MODE_DISABLED = 0,
    /** DAC Interpolation 2:1 */
    MXC_E_DAC_INTERP_MODE_2_TO_1,
    /** DAC Interpolation 4:1 */
    MXC_E_DAC_INTERP_MODE_4_TO_1,
    /** DAC Interpolation 8:1 */
    MXC_E_DAC_INTERP_MODE_8_TO_1
} mxc_dac_interp_mode_t;

/**
 * @brief Defines the DAC Start Modes.
 */
typedef enum {
    /** Start on FIFO Not Empty */
    MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY = 0,
    /** Start on ADC generated Start Strobe */
    MXC_E_DAC_START_MODE_ADC_STROBE,
    /** Start on DAC generated Start Strobe */
    MXC_E_DAC_START_MODE_DAC_STROBE
} mxc_dac_start_mode_t;

typedef struct
{
    uint32_t fifo_ae_cnt               : 4;
    uint32_t                           : 1;
    uint32_t fifo_almost_full          : 1;
    uint32_t fifo_empty                : 1;
    uint32_t fifo_almost_empty         : 1;
    uint32_t interp_mode               : 3;
    uint32_t                           : 1;
    uint32_t fifo_af_cnt               : 4;
    uint32_t start_mode                : 2;
    uint32_t                           : 2;
    uint32_t cpu_start                 : 1;
    uint32_t bin_2_gray_bypass         : 1;
    uint32_t fifo_clear                : 1;
    uint32_t                           : 1;
    uint32_t op_mode                   : 2;
    uint32_t power_mode_1_0            : 2;
    uint32_t power_on                  : 1;
    uint32_t clock_gate_en             : 1;
    uint32_t power_mode_2              : 1;
    uint32_t reset                     : 1;
} mxc_dac_ctrl0_t;

typedef struct
{
    uint32_t rate_cnt                  : 16;
    uint32_t sample_cnt                : 16;
} mxc_dac_rate_t;

typedef struct
{
    uint32_t out_done                  : 1;
    uint32_t underflow                 : 1;
    uint32_t almost_empty              : 1;
    uint32_t overflow                  : 1;
    uint32_t                           : 12;
    uint32_t out_done_en               : 1;
    uint32_t underflow_en              : 1;
    uint32_t almost_empty_en           : 1;
    uint32_t                           : 5;
    uint32_t ahb_retry_delay           : 3;
    uint32_t ahb_retry_en              : 1;
    uint32_t ahb_cg_disable            : 1;
    uint32_t apb_cg_disable            : 1;
    uint32_t                           : 2;
} mxc_dac_ctrl1_int_t;

typedef struct
{
    uint32_t cpudacg                   : 12;
    uint32_t                           : 20;
} mxc_dac_reg_t;

/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                                  Offset   Register Description
                                                    ======   ================================================== */
typedef struct {
    union {
        __IO uint32_t ctrl0;                    /*  0x0000   DAC Control Register 0                             */
        __IO mxc_dac_ctrl0_t ctrl0_f;
    };
    union {
        __IO uint32_t rate;                     /*  0x0004   DAC Output Rate Control                            */
        __IO mxc_dac_rate_t rate_f;
    };
    union {
        __IO uint32_t ctrl1_int;                /*  0x0008   DAC Control Register 1, Interrupt Flags and Enable */
        __IO mxc_dac_ctrl1_int_t ctrl1_int_f;
    };
    union {
        __IO uint32_t reg;                      /*  0x000C   DAC Data Register                                  */
        __IO mxc_dac_reg_t reg_f;
    };
    __IO uint32_t trm;                          /* 0x0010    DAC Trim Register */
} mxc_dac_regs_t;


/*                                                  Offset   Register Description
                                                    ======   ================================================== */
typedef struct {
    __IO uint32_t output;                       /*  0x0000   Write to push values to DAC output FIFO            */
} mxc_dac_fifo;


/*
   Register offsets for module DAC12.
*/

#define MXC_R_DAC_OFFS_CTRL0                    ((uint32_t)0x00000000UL)
#define MXC_R_DAC_OFFS_RATE                     ((uint32_t)0x00000004UL)
#define MXC_R_DAC_OFFS_CTRL1_INT                ((uint32_t)0x00000008UL)
#define MXC_R_DAC_OFFS_REG                      ((uint32_t)0x0000000CUL)

#define MXC_R_DAC_FIFO_OFFS_OUTPUT              ((uint32_t)0x00000000UL)


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* _DAC12_REGS_H */
