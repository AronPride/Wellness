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

#ifndef _MXC_GPIO_REGS_H_
#define _MXC_GPIO_REGS_H_

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
    uint32_t pin0 : 1;
    uint32_t pin1 : 1;
    uint32_t pin2 : 1;
    uint32_t pin3 : 1;
    uint32_t pin4 : 1;
    uint32_t pin5 : 1;
    uint32_t pin6 : 1;
    uint32_t pin7 : 1;
    uint32_t      : 24;
} mxc_gpio_free_t;

typedef struct
{
    uint32_t pin0 : 4;
    uint32_t pin1 : 4;
    uint32_t pin2 : 4;
    uint32_t pin3 : 4;
    uint32_t pin4 : 4;
    uint32_t pin5 : 4;
    uint32_t pin6 : 4;
    uint32_t pin7 : 4;
} mxc_gpio_out_mode_t;

typedef struct
{
    uint32_t pin0 : 1;
    uint32_t pin1 : 1;
    uint32_t pin2 : 1;
    uint32_t pin3 : 1;
    uint32_t pin4 : 1;
    uint32_t pin5 : 1;
    uint32_t pin6 : 1;
    uint32_t pin7 : 1;
    uint32_t      : 24;
} mxc_gpio_out_val_t;

typedef struct
{
    uint32_t pin0 : 4;
    uint32_t pin1 : 4;
    uint32_t pin2 : 4;
    uint32_t pin3 : 4;
    uint32_t pin4 : 4;
    uint32_t pin5 : 4;
    uint32_t pin6 : 4;
    uint32_t pin7 : 4;
} mxc_gpio_func_sel_t;

typedef struct
{
    uint32_t pin0 : 2;
    uint32_t      : 2;
    uint32_t pin1 : 2;
    uint32_t      : 2;
    uint32_t pin2 : 2;
    uint32_t      : 2;
    uint32_t pin3 : 2;
    uint32_t      : 2;
    uint32_t pin4 : 2;
    uint32_t      : 2;
    uint32_t pin5 : 2;
    uint32_t      : 2;
    uint32_t pin6 : 2;
    uint32_t      : 2;
    uint32_t pin7 : 2;
    uint32_t      : 2;
} mxc_gpio_in_mode_t;

typedef struct
{
    uint32_t pin0 : 1;
    uint32_t pin1 : 1;
    uint32_t pin2 : 1;
    uint32_t pin3 : 1;
    uint32_t pin4 : 1;
    uint32_t pin5 : 1;
    uint32_t pin6 : 1;
    uint32_t pin7 : 1;
    uint32_t      : 24;
} mxc_gpio_in_val_t;

typedef struct
{
    uint32_t pin0 : 3;
    uint32_t      : 1;
    uint32_t pin1 : 3;
    uint32_t      : 1;
    uint32_t pin2 : 3;
    uint32_t      : 1;
    uint32_t pin3 : 3;
    uint32_t      : 1;
    uint32_t pin4 : 3;
    uint32_t      : 1;
    uint32_t pin5 : 3;
    uint32_t      : 1;
    uint32_t pin6 : 3;
    uint32_t      : 1;
    uint32_t pin7 : 3;
    uint32_t      : 1;
} mxc_gpio_int_mode_t;

typedef struct
{
    uint32_t pin0 : 1;
    uint32_t pin1 : 1;
    uint32_t pin2 : 1;
    uint32_t pin3 : 1;
    uint32_t pin4 : 1;
    uint32_t pin5 : 1;
    uint32_t pin6 : 1;
    uint32_t pin7 : 1;
    uint32_t      : 24;
} mxc_gpio_intfl_t;

typedef struct
{
    uint32_t pin0 : 1;
    uint32_t pin1 : 1;
    uint32_t pin2 : 1;
    uint32_t pin3 : 1;
    uint32_t pin4 : 1;
    uint32_t pin5 : 1;
    uint32_t pin6 : 1;
    uint32_t pin7 : 1;
    uint32_t      : 24;
} mxc_gpio_inten_t;


/*                                                       Offset          Register Description
                                                      =============   ========================================== */
typedef struct {
    __R uint32_t rsv000[16];                      /*  0x0000-0x003C                                              */
    union {                                       /*  0x0040-0x005C   Port P[0..7] Free for GPIO Operation Flags */
        __IO uint32_t free[8];
        __IO mxc_gpio_free_t free_f[8];
    };
    __R uint32_t rsv060[8];                       /*  0x0060-0x007C                                              */
    union {                                       /*  0x0080-0x009C   Port P[0..7] GPIO Output Drive Mode        */
        __IO uint32_t out_mode[8];
        __IO mxc_gpio_out_mode_t out_mode_f[8];
    };
    __R uint32_t rsv0A0[8];                       /*  0x00A0-0x00BC                                              */
    union {                                       /*  0x00C0-0x00DC   Port P[0..7] GPIO Output Value             */
        __IO uint32_t out_val[8];
        __IO mxc_gpio_out_val_t out_val_f[8];
    };
    __R uint32_t rsv0E0[8];                       /*  0x00E0-0x00FC                                              */
    union {                                       /*  0x0100-0x011C   Port P[0..7] GPIO Function Select          */
        __IO uint32_t func_sel[8];
        __IO mxc_gpio_func_sel_t func_sel_f[8];
    };
    __R uint32_t rsv120[8];                       /*  0x0120-0x013C                                              */
    union {                                       /*  0x0140-0x015C   Port P[0..7] GPIO Input Monitoring Mode    */
        __IO uint32_t in_mode[8];
        __IO mxc_gpio_in_mode_t in_mode_f[8];
    };
    __R uint32_t rsv160[8];                       /*  0x0160-0x017C                                              */
    union {                                       /*  0x0180-0x019C   Port P[0..7] GPIO Input Value              */
        __IO uint32_t in_val[8];
        __IO mxc_gpio_in_val_t in_val_f[8];
    };
    __R uint32_t rsv1A0[8];                       /*  0x01A0-0x01BC                                              */
    union {                                       /*  0x01C0-0x01DC   Port P[0..7] Interrupt Detection Mode      */
        __IO uint32_t int_mode[8];
        __IO mxc_gpio_int_mode_t int_mode_f[8];
    };
    __R uint32_t rsv1E0[8];                       /*  0x01E0-0x01FC                                              */
    union {                                       /*  0x0200-0x021C   Port P[0..7] Interrupt Flags               */
        __IO uint32_t intfl[8];
        __IO mxc_gpio_intfl_t intfl_f[8];
    };
    __R uint32_t rsv220[8];                       /*  0x0220-0x023C                                              */
    union {                                       /*  0x0240-0x025C   Port P[0..7] Interrupt Enables             */
        __IO uint32_t inten[8];
        __IO mxc_gpio_inten_t inten_f[8];
    };
} mxc_gpio_regs_t;


/*
   Register offsets for module GPIO.
*/

#define MXC_R_GPIO_OFFS_FREE_P0                   ((uint32_t)0x00000040UL)
#define MXC_R_GPIO_OFFS_FREE_P1                   ((uint32_t)0x00000044UL)
#define MXC_R_GPIO_OFFS_FREE_P2                   ((uint32_t)0x00000048UL)
#define MXC_R_GPIO_OFFS_FREE_P3                   ((uint32_t)0x0000004CUL)
#define MXC_R_GPIO_OFFS_FREE_P4                   ((uint32_t)0x00000050UL)
#define MXC_R_GPIO_OFFS_FREE_P5                   ((uint32_t)0x00000054UL)
#define MXC_R_GPIO_OFFS_FREE_P6                   ((uint32_t)0x00000058UL)
#define MXC_R_GPIO_OFFS_FREE_P7                   ((uint32_t)0x0000005CUL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P0               ((uint32_t)0x00000080UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P1               ((uint32_t)0x00000084UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P2               ((uint32_t)0x00000088UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P3               ((uint32_t)0x0000008CUL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P4               ((uint32_t)0x00000090UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P5               ((uint32_t)0x00000094UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P6               ((uint32_t)0x00000098UL)
#define MXC_R_GPIO_OFFS_OUT_MODE_P7               ((uint32_t)0x0000009CUL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P0                ((uint32_t)0x000000C0UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P1                ((uint32_t)0x000000C4UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P2                ((uint32_t)0x000000C8UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P3                ((uint32_t)0x000000CCUL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P4                ((uint32_t)0x000000D0UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P5                ((uint32_t)0x000000D4UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P6                ((uint32_t)0x000000D8UL)
#define MXC_R_GPIO_OFFS_OUT_VAL_P7                ((uint32_t)0x000000DCUL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P0               ((uint32_t)0x00000100UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P1               ((uint32_t)0x00000104UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P2               ((uint32_t)0x00000108UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P6               ((uint32_t)0x00000118UL)
#define MXC_R_GPIO_OFFS_FUNC_SEL_P7               ((uint32_t)0x0000011CUL)
#define MXC_R_GPIO_OFFS_IN_MODE_P0                ((uint32_t)0x00000140UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P1                ((uint32_t)0x00000144UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P2                ((uint32_t)0x00000148UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P3                ((uint32_t)0x0000014CUL)
#define MXC_R_GPIO_OFFS_IN_MODE_P4                ((uint32_t)0x00000150UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P5                ((uint32_t)0x00000154UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P6                ((uint32_t)0x00000158UL)
#define MXC_R_GPIO_OFFS_IN_MODE_P7                ((uint32_t)0x0000015CUL)
#define MXC_R_GPIO_OFFS_IN_VAL_P0                 ((uint32_t)0x00000180UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P1                 ((uint32_t)0x00000184UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P2                 ((uint32_t)0x00000188UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P3                 ((uint32_t)0x0000018CUL)
#define MXC_R_GPIO_OFFS_IN_VAL_P4                 ((uint32_t)0x00000190UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P5                 ((uint32_t)0x00000194UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P6                 ((uint32_t)0x00000198UL)
#define MXC_R_GPIO_OFFS_IN_VAL_P7                 ((uint32_t)0x0000019CUL)
#define MXC_R_GPIO_OFFS_INT_MODE_P0               ((uint32_t)0x000001C0UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P1               ((uint32_t)0x000001C4UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P2               ((uint32_t)0x000001C8UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P3               ((uint32_t)0x000001CCUL)
#define MXC_R_GPIO_OFFS_INT_MODE_P4               ((uint32_t)0x000001D0UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P5               ((uint32_t)0x000001D4UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P6               ((uint32_t)0x000001D8UL)
#define MXC_R_GPIO_OFFS_INT_MODE_P7               ((uint32_t)0x000001DCUL)
#define MXC_R_GPIO_OFFS_INTFL_P0                  ((uint32_t)0x00000200UL)
#define MXC_R_GPIO_OFFS_INTFL_P1                  ((uint32_t)0x00000204UL)
#define MXC_R_GPIO_OFFS_INTFL_P2                  ((uint32_t)0x00000208UL)
#define MXC_R_GPIO_OFFS_INTFL_P3                  ((uint32_t)0x0000020CUL)
#define MXC_R_GPIO_OFFS_INTFL_P4                  ((uint32_t)0x00000210UL)
#define MXC_R_GPIO_OFFS_INTFL_P5                  ((uint32_t)0x00000214UL)
#define MXC_R_GPIO_OFFS_INTFL_P6                  ((uint32_t)0x00000218UL)
#define MXC_R_GPIO_OFFS_INTFL_P7                  ((uint32_t)0x0000021CUL)
#define MXC_R_GPIO_OFFS_INTEN_P0                  ((uint32_t)0x00000240UL)
#define MXC_R_GPIO_OFFS_INTEN_P1                  ((uint32_t)0x00000244UL)
#define MXC_R_GPIO_OFFS_INTEN_P2                  ((uint32_t)0x00000248UL)
#define MXC_R_GPIO_OFFS_INTEN_P3                  ((uint32_t)0x0000024CUL)
#define MXC_R_GPIO_OFFS_INTEN_P4                  ((uint32_t)0x00000250UL)
#define MXC_R_GPIO_OFFS_INTEN_P5                  ((uint32_t)0x00000254UL)
#define MXC_R_GPIO_OFFS_INTEN_P6                  ((uint32_t)0x00000258UL)
#define MXC_R_GPIO_OFFS_INTEN_P7                  ((uint32_t)0x0000025CUL)

#ifdef __cplusplus
}
#endif

#endif /* _MXC_GPIO_REGS_H_ */
