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

#ifndef _MXC_ICC_REGS_H_
#define _MXC_ICC_REGS_H_


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
    uint32_t rtl_version       : 6;
    uint32_t part_num          : 4;
    uint32_t cache_id          : 6;
    uint32_t                   : 16;
} mxc_icc_id_t;

typedef struct
{
    uint32_t cache_size        : 16;
    uint32_t main_memory_size  : 16;
} mxc_icc_mem_cfg_t;

typedef struct
{
    uint32_t enable            : 1;
    uint32_t                   : 15;
    uint32_t ready             : 1;
    uint32_t                   : 15;
} mxc_icc_ctrl_stat_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/
/*                                                  Offset   Register Description
                                                    ======   =================================================== */
typedef struct {
    union {
        __IO uint32_t id;                       /*  0x0000   Device ID Register                                  */
        __IO mxc_icc_id_t id_f;
    };
    union {
        __IO uint32_t mem_cfg;                  /*  0x0004   Memory Configuration                                */
        __IO mxc_icc_mem_cfg_t mem_cfg_f;
    };
    __R uint32_t rsv0008[62];                   /*  0x0008                                                       */
    union {
        __IO uint32_t ctrl_stat;                /*  0x0100   Control and Status                                  */
        __IO mxc_icc_ctrl_stat_t ctrl_stat_f;
    };
    __R uint32_t rsv0104[383];                  /*  0x0104                                                       */
    __IO uint32_t invdt_all;                    /*  0x0700   Invalidate (Clear) Cache Control                    */
} mxc_icc_regs_t;


/*
   Register offsets for module ICC.
*/
#define MXC_R_ICC_OFFS_ID                         ((uint32_t)0x00000000UL)
#define MXC_R_ICC_OFFS_MEM_CFG                    ((uint32_t)0x00000004UL)
#define MXC_R_ICC_OFFS_CTRL_STAT                  ((uint32_t)0x00000100UL)
#define MXC_R_ICC_OFFS_INVDT_ALL                  ((uint32_t)0x00000700UL)

#ifdef __cplusplus
}
#endif
#endif
