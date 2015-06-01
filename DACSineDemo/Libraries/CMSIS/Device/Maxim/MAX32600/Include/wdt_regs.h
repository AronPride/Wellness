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

#ifndef _MXC_WDT_REGS_H_
#define _MXC_WDT_REGS_H_

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

/**
 * @brief Defines watchdog timer periods
 */
typedef enum {
    /** 2^31 cycle period */
    MXC_E_WDT_PERIOD_2_31_CLKS = 0,
    /** 2^30 cycle period */
    MXC_E_WDT_PERIOD_2_30_CLKS,
    /** 2^29 cycle period */
    MXC_E_WDT_PERIOD_2_29_CLKS,
    /** 2^28 cycle period */
    MXC_E_WDT_PERIOD_2_28_CLKS,
    /** 2^27 cycle period */
    MXC_E_WDT_PERIOD_2_27_CLKS,
    /** 2^26 cycle period */
    MXC_E_WDT_PERIOD_2_26_CLKS,
    /** 2^25 cycle period */
    MXC_E_WDT_PERIOD_2_25_CLKS,
    /** 2^24 cycle period */
    MXC_E_WDT_PERIOD_2_24_CLKS,
    /** 2^23 cycle period */
    MXC_E_WDT_PERIOD_2_23_CLKS,
    /** 2^22 cycle period */
    MXC_E_WDT_PERIOD_2_22_CLKS,
    /** 2^21 cycle period */
    MXC_E_WDT_PERIOD_2_21_CLKS,
    /** 2^20 cycle period */
    MXC_E_WDT_PERIOD_2_20_CLKS,
    /** 2^19 cycle period */
    MXC_E_WDT_PERIOD_2_19_CLKS,
    /** 2^18 cycle period */
    MXC_E_WDT_PERIOD_2_18_CLKS,
    /** 2^17 cycle period */
    MXC_E_WDT_PERIOD_2_17_CLKS,
    /** 2^16 cycle period */
    MXC_E_WDT_PERIOD_2_16_CLKS,
} mxc_wdt_period_t;

/*
    Bitfield structs for registers in this module
*/

typedef struct
{
    uint32_t int_period        : 4;
    uint32_t rst_period        : 4;
    uint32_t en_timer          : 1;
    uint32_t en_clock          : 1;
    uint32_t                   : 2;
    uint32_t wait_period       : 4;
    uint32_t                   : 16;
} mxc_wdt_ctrl_t;

typedef struct
{
    uint32_t if_timeout        : 1;
    uint32_t if_pre_win        : 1;
    uint32_t reset_flag        : 1;
    uint32_t                   : 29;
} mxc_wdt_int_rst_fl_t;

typedef struct
{
    uint32_t ie_timeout        : 1;
    uint32_t prewin_reset0_en  : 1;
    uint32_t wdt_reset0_en     : 1;
    uint32_t wdt_reset1_en     : 1;
    uint32_t                   : 28;
} mxc_wdt_int_rst_en_t;

typedef struct
{
    uint32_t wdlock            : 8;
    uint32_t                   : 24;
} mxc_wdt_lock_ctrl_t;



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                                      Offset   Register Description
                                                        ======   ================================================ */
typedef struct {
    union {
        __IO uint32_t ctrl;                         /*  0x0000   Watchdog Timer Control Register                  */
        __IO mxc_wdt_ctrl_t ctrl_f;
    };
    __IO uint32_t clear;                            /*  0x0004   Watchdog Clear Register (Feed Dog)               */
    union {
        __IO uint32_t int_rst_fl;                   /*  0x0008   Watchdog Interrupt/Reset Flags                   */
        __IO mxc_wdt_int_rst_fl_t int_rst_fl_f;
    };
    union {
        __IO uint32_t int_rst_en;                   /*  0x000C   Interrupt/Reset Enable/Disable Controls          */
        __IO mxc_wdt_int_rst_en_t int_rst_en_f;
    };
    __R uint32_t rsv0010;                           /*  0x0010                                                    */
    union {
        __IO uint32_t lock_ctrl;                    /*  0x0014   Lock Register Setting for WDT CTRL               */
        __IO mxc_wdt_lock_ctrl_t lock_ctrl_f;
    };
} mxc_wdt_regs_t;


/*
   Register offsets for module WDT.
*/

#define MXC_R_WDT_OFFS_CTRL                       ((uint32_t)0x00000000UL)
#define MXC_R_WDT_OFFS_CLEAR                      ((uint32_t)0x00000004UL)
#define MXC_R_WDT_OFFS_INT_RST_FL                 ((uint32_t)0x00000008UL)
#define MXC_R_WDT_OFFS_INT_RST_EN                 ((uint32_t)0x0000000CUL)
#define MXC_R_WDT_OFFS_LOCK_CTRL                  ((uint32_t)0x00000014UL)

#define MXC_V_WDT_WDLOCK_LOCK_KEY       ((uint8_t)0x24)
#define MXC_V_WDT_WDLOCK_UNLOCK_KEY     ((uint8_t)0x42)

#ifdef __cplusplus
}
#endif

#endif   /* _MXC_WDT_REGS_H_ */

