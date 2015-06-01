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

#ifndef _MXC_PMU_REGS_H_
#define _MXC_PMU_REGS_H_

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
    uint32_t enable     : 1;
    uint32_t            : 1;
    uint32_t ll_stopped : 1;
    uint32_t manual     : 1;
    uint32_t bus_error  : 1;
    uint32_t            : 1;
    uint32_t to_stat    : 1;
    uint32_t            : 4;
    uint32_t to_sel     : 3;
    uint32_t ps_sel     : 2;

    uint32_t interrupt  : 1;
    uint32_t int_en     : 1;
    uint32_t            : 6;
    uint32_t burst_size : 5;
    uint32_t            : 3;
} mxc_pmu_cfg_t;

typedef struct
{
    uint32_t counter_0 : 16;
    uint32_t counter_1 : 16;
} mxc_pmu_loop_t;


typedef struct {
    __IO uint32_t start_opcode[32];
    __IO uint32_t enable;
    __IO uint32_t rsvd0; 
    __IO uint32_t ll_stopped;
    __IO uint32_t manual; 
    __IO uint32_t bus_error; 
    __IO uint32_t rsvd1; 
    __IO uint32_t to_stat; 
    __IO uint32_t rsvd2[4]; 
    __IO uint32_t to_sel[3]; 
    __IO uint32_t ps_sel[2];
    __IO uint32_t interrupt; 
    __IO uint32_t int_enable;
    __IO uint32_t rsvd3[6]; 
    __IO uint32_t burst_size[5];
    __IO uint32_t rsvd4[3];  
    __IO uint32_t padding[192]; /* Offset to next channel */
} mxc_pmu_bits_t;

/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                         Offset   Register Description
                                           ======   ======================================================== */
typedef struct {
    __IO uint32_t dscadr;              /*  0x0000   Starting Descriptor Address                              */
    union {
        __IO uint32_t cfg;             /*  0x0004   Channel Configuration                                    */
        __IO mxc_pmu_cfg_t cfg_f;
    };
    union {
        __IO uint32_t loop;            /*  0x0008   Channel Loop Counters                                    */
        __IO mxc_pmu_loop_t loop_f;
    };
    __IO uint32_t op;                  /*  0x000C   Current Descriptor DWORD 0 (OP)                          */
    __IO uint32_t dsc1;                /*  0x0010   Current Descriptor DWORD 1                               */
    __IO uint32_t dsc2;                /*  0x0014   Current Descriptor DWORD 2                               */
    __IO uint32_t dsc3;                /*  0x0018   Current Descriptor DWORD 3                               */
    __IO uint32_t dsc4;                /*  0x001C   Current Descriptor DWORD 4                               */
} mxc_pmu_regs_t;


/*
   Register offsets for module PMU.
*/

#define MXC_R_PMU_OFFS_DSCADR                     ((uint32_t)0x00000000UL)
#define MXC_R_PMU_OFFS_CFG                        ((uint32_t)0x00000004UL)
#define MXC_R_PMU_OFFS_LOOP                       ((uint32_t)0x00000008UL)
#define MXC_R_PMU_OFFS_OP                         ((uint32_t)0x0000000CUL)
#define MXC_R_PMU_OFFS_DSC1                       ((uint32_t)0x00000010UL)
#define MXC_R_PMU_OFFS_DSC2                       ((uint32_t)0x00000014UL)
#define MXC_R_PMU_OFFS_DSC3                       ((uint32_t)0x00000018UL)
#define MXC_R_PMU_OFFS_DSC4                       ((uint32_t)0x0000001CUL)


#ifdef __cplusplus
}
#endif

#endif   /* _MXC_PMU_REGS_H_ */
