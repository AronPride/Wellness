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

/* $Revision: 959 $ $Date: 2014-03-28 11:00:35 -0600 (Fri, 28 Mar 2014) $ */

#ifndef _MXC_LCD_REGS_H
#define _MXC_LCD_REGS_H

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


#define MXC_LCD_ADDRESS_SEGS 21

/*
    Bitfield structs for registers in this module
*/
typedef struct {
    uint32_t lcd_en            : 1;
    uint32_t operating_mode    : 1;
    uint32_t stop_mode_en      : 1;
    uint32_t autopage_en       : 1;
    uint32_t page_sel          : 2;
    uint32_t datahold          : 1;
    uint32_t                   : 25;
} mxc_lcd_lcfg_t;


typedef struct {
    uint32_t reg_adj           : 4;
    uint32_t gnd_en            : 1;
    uint32_t                   : 3;
    uint32_t frame_rate        : 5;
    uint32_t                   : 1;
    uint32_t duty_cycle        : 2;
    uint32_t                   : 16;
} mxc_lcd_lcra_t;


typedef struct {
    uint32_t addr_sel          : 5;
    uint32_t                   : 1;
    uint32_t page_sel          : 2;
    uint32_t                   : 24;
} mxc_lcd_lcaddr_t;

typedef struct {
    uint32_t data              : 8;
    uint32_t                   : 24;
} mxc_lcd_lcdata_t;


typedef struct {
    uint32_t powerup           : 1;
    uint32_t freerun           : 1;
    uint32_t highbat_startup   : 1;
    uint32_t bias_powerup      : 1;
    uint32_t enbg_4_lcd        : 1;
    uint32_t lcd_vsel          : 2;
    uint32_t                   : 17;
    uint32_t pumpup            : 1;
    uint32_t                   : 5;
    uint32_t pump_vready       : 1;
    uint32_t                   : 1;
} mxc_lcd_lpwrctrl_t;

    /*
      Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
      register access along with union access to bit/bitfield struct (where defined).
    */

    /*                               Offset   Register Description
                                     ======   ===================================================== */
typedef struct {
    union{
        __IO uint32_t lcfg;
        __IO mxc_lcd_lcfg_t lcfg_f;         /* 0x0000  LCD Configuration / Control                            */
        };
    union{
        __IO uint32_t lcra;
        __IO mxc_lcd_lcra_t lcra_f;         /* 0x0004  LCD Internal Register Adjust / Duty Cycle / Bias Mode  */
    };
    __IO uint32_t lpcf;                     /* 0x0008  LCD Port Configuration Register                        */
    union{
        __IO uint32_t lcaddr;
        __IO mxc_lcd_lcaddr_t lcaddr_f;     /* 0x000C  LCD Memory Address Select                              */
    };
    union{
        __IO uint32_t lcdata;               /* 0x0010  LCD Memory Data Read / Write                           */
        __IO mxc_lcd_lcdata_t lcdata_f;
    };
    union{
        __IO uint32_t lpwrctrl;             /* 0x0014  LCD Power Control                                      */
        __IO mxc_lcd_lpwrctrl_t lpwrctrl_f;
    };
} mxc_lcd_regs_t;

#ifdef __cplusplus
}
#endif

#endif
