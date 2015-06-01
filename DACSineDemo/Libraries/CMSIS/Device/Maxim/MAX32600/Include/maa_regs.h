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

#ifndef _MXC_MAA_REGS_H_
#define _MXC_MAA_REGS_H_

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
    uint32_t start             : 1;
    uint32_t opsel             : 3;
    uint32_t ocalc             : 1;
    uint32_t inten             : 1;
    uint32_t if_done           : 1;
    uint32_t if_error          : 1;
    uint32_t ofs_a             : 2;
    uint32_t ofs_b             : 2;
    uint32_t ofs_exp           : 2;
    uint32_t ofs_mod           : 2;
    uint32_t seg_a             : 4;
    uint32_t seg_b             : 4;
    uint32_t seg_res           : 4;
    uint32_t seg_tmp           : 4;
} mxc_maa_ctrl_t;

typedef struct
{
    uint32_t modlen            : 10;
    uint32_t                   : 6;
    uint32_t byteswap          : 1;
    uint32_t                   : 15;
} mxc_maa_maws_t;



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                        Offset   Register Description
                                          ======   ========================================================== */
typedef struct {
    union {
        __IO uint32_t ctrl;           /*  0x0000   MAA Control, Configuration and Status                      */
        __IO mxc_maa_ctrl_t ctrl_f;
    };
    union {
        __IO uint32_t maws;           /*  0x0004   MAA Word (Operand) Size, Big/Little Endian Mode Select     */
        __IO mxc_maa_maws_t maws_f;
    };
} mxc_maa_regs_t;


/*                                        Offset   Register Description
                                          ======   ========================================================== */
typedef struct {
    __IO uint32_t seg0[16];           /*  0x0000   [64 bytes] MAA Memory Segment 0                            */
    __IO uint32_t seg1[16];           /*  0x0040   [64 bytes] MAA Memory Segment 1                            */
    __IO uint32_t seg2[16];           /*  0x0080   [64 bytes] MAA Memory Segment 2                            */
    __IO uint32_t seg3[16];           /*  0x00C0   [64 bytes] MAA Memory Segment 3                            */
    __IO uint32_t seg4[16];           /*  0x0100   [64 bytes] MAA Memory Segment 4                            */
    __IO uint32_t seg5[16];           /*  0x0140   [64 bytes] MAA Memory Segment 5                            */
} mxc_maa_mem_regs_t;


/*
   Register offsets for module MAA.
*/

#define MXC_R_MAA_OFFS_CTRL                       ((uint32_t)0x00000000UL)
#define MXC_R_MAA_OFFS_MAWS                       ((uint32_t)0x00000004UL)
#define MXC_R_MAA_MEM_OFFS_SEG0                   ((uint32_t)0x00000000UL)
#define MXC_R_MAA_MEM_OFFS_SEG1                   ((uint32_t)0x00000040UL)
#define MXC_R_MAA_MEM_OFFS_SEG2                   ((uint32_t)0x00000080UL)
#define MXC_R_MAA_MEM_OFFS_SEG3                   ((uint32_t)0x000000C0UL)
#define MXC_R_MAA_MEM_OFFS_SEG4                   ((uint32_t)0x00000100UL)
#define MXC_R_MAA_MEM_OFFS_SEG5                   ((uint32_t)0x00000140UL)


#ifdef __cplusplus
}
#endif;

#endif   /* _MXC_MAA_REGS_H_ */

