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

#ifndef _MXC_RTC_REGS_H
#define _MXC_RTC_REGS_H

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
    uint32_t enable                 : 1;
    uint32_t clear                  : 1;
    uint32_t pending                : 1;
    uint32_t use_async_flags        : 1;
    uint32_t aggressive_rst         : 1;
    uint32_t                        : 11;
    uint32_t en_active              : 1;
    uint32_t osc_goto_low_active    : 1;
    uint32_t osc_frce_sm_en_active  : 1;
    uint32_t osc_frce_st_active     : 1;
    uint32_t set_active             : 1;
    uint32_t clr_active             : 1;
    uint32_t rollover_clr_active    : 1;
    uint32_t prescale_cmpr0_active  : 1;
    uint32_t prescale_update_active : 1;
    uint32_t cmpr1_clr_active       : 1;
    uint32_t cmpr0_clr_active       : 1;
    uint32_t                        : 5;
} mxc_rtctmr_ctrl_t;

typedef struct
{
    uint32_t comp0                  : 1;
    uint32_t comp1                  : 1;
    uint32_t prescale_comp          : 1;
    uint32_t overflow               : 1;
    uint32_t trim                   : 1;
    uint32_t                        : 3;

    uint32_t comp0_flag_a           : 1;
    uint32_t comp1_flag_a           : 1;
    uint32_t prescl_flag_a          : 1;
    uint32_t overflow_flag_a        : 1;
    uint32_t trim_flag_a            : 1;
    uint32_t                        : 18;
    uint32_t async_clr_flags        : 1;
} mxc_rtctmr_flags_t;

typedef struct
{
    uint32_t comp0                  : 1;
    uint32_t comp1                  : 1;
    uint32_t prescale_comp          : 1;
    uint32_t overflow               : 1;
    uint32_t trim                   : 1;
    uint32_t                        : 27;
} mxc_rtctmr_inten_t;


/**
 * @brief Defines clock divider for 4096Hz input clock.
 */
typedef enum {
    /** (4kHz) divide input clock by 2^0 = 1 */
    MXC_E_RTC_PRESCALE_DIV_2_0 = 0,
    /** (2kHz) divide input clock by 2^1 = 2 */
    MXC_E_RTC_PRESCALE_DIV_2_1,
    /** (1kHz) divide input clock by 2^2 = 4 */
    MXC_E_RTC_PRESCALE_DIV_2_2,
    /** (512Hz) divide input clock by 2^3 = 8 */
    MXC_E_RTC_PRESCALE_DIV_2_3,
    /** (256Hz) divide input clock by 2^4 = 16 */
    MXC_E_RTC_PRESCALE_DIV_2_4,
    /** (128Hz) divide input clock by 2^5 = 32 */
    MXC_E_RTC_PRESCALE_DIV_2_5,
    /** (64Hz) divide input clock by 2^6 = 64 */
    MXC_E_RTC_PRESCALE_DIV_2_6,
    /** (32Hz) divide input clock by 2^7 = 128 */
    MXC_E_RTC_PRESCALE_DIV_2_7,
    /** (16Hz) divide input clock by 2^8 = 256 */
    MXC_E_RTC_PRESCALE_DIV_2_8,
    /** (8Hz) divide input clock by 2^9 = 512 */
    MXC_E_RTC_PRESCALE_DIV_2_9,
    /** (4Hz) divide input clock by 2^10 = 1024 */
    MXC_E_RTC_PRESCALE_DIV_2_10,
    /** (2Hz) divide input clock by 2^11 = 2048 */
    MXC_E_RTC_PRESCALE_DIV_2_11,
    /** (1Hz) divide input clock by 2^12 = 4096 */
    MXC_E_RTC_PRESCALE_DIV_2_12,
} mxc_rtc_prescale_t;

typedef struct
{
    uint32_t prescale               : 4;
    uint32_t                        : 28;
} mxc_rtctmr_prescale_t;

typedef struct
{
    uint32_t comp_mask              : 13;
    uint32_t                        : 19;
} mxc_rtctmr_prescale_mask_t;

typedef struct
{
    uint32_t trim_enable_r          : 1;
    uint32_t trim_faster_ovr_r      : 1;
    uint32_t trim_slower_r          : 1;
    uint32_t                        : 29;
} mxc_rtctmr_trim_ctrl_t;

typedef struct
{
    uint32_t trim_value             : 18;
    uint32_t trim_control           : 1;
    uint32_t                        : 13;
} mxc_rtctmr_trim_value_t;

typedef struct
{
    uint32_t nanoring_counter       : 16;
    uint32_t                        : 16;
} mxc_rtccfg_nano_cntr_t;

typedef struct
{
    uint32_t osc1_en                : 1;
    uint32_t osc2_en                : 1;
    uint32_t nano_en                : 1;
    uint32_t                        : 29;
} mxc_rtccfg_clk_ctrl_t;

typedef struct
{
    uint32_t dsen0_dis              : 1;
    uint32_t dsen0_tm_mux           : 1;
    uint32_t dsen0_tm_powrdown      : 1;
    uint32_t                        : 29;
} mxc_rtccfg_dsen_ctrl_t;

typedef struct
{
    uint32_t osc_bypass             : 1;
    uint32_t osc_disable_r          : 1;
    uint32_t osc_disable_sel        : 1;
    uint32_t osc_disable_o          : 1;
    uint32_t                        : 28;
} mxc_rtccfg_osc_ctrl_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                          Offset   Register Description
                                                            ======   ========================================= */
typedef struct {
    union {
        __IO uint32_t ctrl;                             /*  0x0000   RTC Timer Control                         */
        __IO mxc_rtctmr_ctrl_t ctrl_f;
    };
    __IO uint32_t timer;                                /*  0x0004   RTC Timer Count Value                     */
    __IO uint32_t comp[2];                              /*  0x0008   RTC Alarm (0..1) Compare Registers        */
    union {
        __IO uint32_t flags;                            /*  0x0010   CPU Interrupt and RTC Domain Flags        */
        __IO mxc_rtctmr_flags_t flags_f;
    };
    __R uint32_t rsv0014;                               /*  0x0014                                             */
    union {
        __IO uint32_t inten;                            /*  0x0018   Interrupt Enable Controls                 */
        __IO mxc_rtctmr_inten_t inten_f;
    };
    union {
        __IO uint32_t prescale;                         /*  0x001C   RTC Timer Prescale Setting                */
        __IO mxc_rtctmr_prescale_t prescale_f;
    };
    __R uint32_t rsv0020;                               /*  0x0020                                             */
    union {
        __IO uint32_t prescale_mask;                    /*  0x0024   RTC Timer Prescale Compare Mask           */
        __IO mxc_rtctmr_prescale_mask_t prescale_mask_f;
    };
    union {
        __IO uint32_t trim_ctrl;                        /*  0x0028   RTC Timer Trim Controls                   */
        __IO mxc_rtctmr_trim_ctrl_t trim_ctrl_f;
    };
    union {
        __IO uint32_t trim_value;                       /*  0x002C   RTC Timer Trim Adjustment Interval        */
        __IO mxc_rtctmr_trim_value_t trim_value_f;
    };
} mxc_rtctmr_regs_t;


/*
   Register offsets for module RTCTMR.
*/

#define MXC_R_RTCTMR_OFFS_CTRL                    ((uint32_t)0x00000000UL)
#define MXC_R_RTCTMR_OFFS_TIMER                   ((uint32_t)0x00000004UL)
#define MXC_R_RTCTMR_OFFS_COMP_0                  ((uint32_t)0x00000008UL)
#define MXC_R_RTCTMR_OFFS_COMP_1                  ((uint32_t)0x0000000CUL)
#define MXC_R_RTCTMR_OFFS_FLAGS                   ((uint32_t)0x00000010UL)
#define MXC_R_RTCTMR_OFFS_INTEN                   ((uint32_t)0x00000018UL)
#define MXC_R_RTCTMR_OFFS_PRESCALE                ((uint32_t)0x0000001CUL)
#define MXC_R_RTCTMR_OFFS_PRESCALE_MASK           ((uint32_t)0x00000024UL)
#define MXC_R_RTCTMR_OFFS_TRIM_CTRL               ((uint32_t)0x00000028UL)
#define MXC_R_RTCTMR_OFFS_TRIM_VALUE              ((uint32_t)0x0000002CUL)


/*                                                          Offset   Register Description
                                                            ======   ===================================================================== */
typedef struct {
    __IO uint32_t nano_counter;                         /*  0x0000   Nanoring Counter Read Register                                        */
    __IO uint32_t clk_ctrl;                             /*  0x0004   RTC Clock Control Settings                                            */
    __IO uint32_t dsen_ctrl;                            /*  0x0008   Dynamic Tamper Sensor Control                                         */
    __IO uint32_t osc_ctrl;                             /*  0x000C   RTC Oscillator Control                                                */
} mxc_rtccfg_regs_t;


/*
   Register offsets for module RTCCFG.
*/

#define MXC_R_RTCCFG_OFFS_NANO_COUNTER            ((uint32_t)0x00000000UL)
#define MXC_R_RTCCFG_OFFS_CLK_CTRL                ((uint32_t)0x00000004UL)
#define MXC_R_RTCCFG_OFFS_DSEN_CTRL               ((uint32_t)0x00000008UL)
#define MXC_R_RTCCFG_OFFS_OSC_CTRL                ((uint32_t)0x0000000CUL)


#ifdef __cplusplus
}
#endif

#endif
