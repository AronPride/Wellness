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

#ifndef _MXC_FLC_REGS_H
#define _MXC_FLC_REGS_H

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
    uint32_t faddr                     : 18;
    uint32_t                           : 14;
} mxc_flc_faddr_t;

typedef struct
{
    uint32_t fckdiv                    : 5;
    uint32_t                           : 27;
} mxc_flc_fckdiv_t;

typedef struct
{
    uint32_t write                     : 1;
    uint32_t mass_erase                : 1;
    uint32_t page_erase                : 1;
    uint32_t                           : 5;
    uint32_t erase_code                : 8;
    uint32_t info_block_unlock         : 1;
    uint32_t write_enable              : 1;
    uint32_t                           : 6;
    uint32_t pending                   : 1;
    uint32_t info_block_valid          : 1;
    uint32_t                           : 1;
    uint32_t auto_incre_mode           : 1;
    uint32_t flsh_unlock               : 4;
} mxc_flc_ctrl_t;

typedef struct
{
    uint32_t write_erase               : 1;
    uint32_t flsh_fail                 : 1;
    uint32_t                           : 6;
    uint32_t done                      : 1;
    uint32_t failed                    : 1;
    uint32_t                           : 22;
} mxc_flc_intr_t;

typedef struct
{
    uint32_t delay_se_en               : 1;
    uint32_t                           : 7;
    uint32_t fast_read_mode_en         : 1;
    uint32_t                           : 23;
} mxc_flc_perform_t;

typedef struct
{
    uint32_t jtag_lock_window          : 1;
    uint32_t jtag_lock_static          : 1;
    uint32_t                           : 1;
    uint32_t auto_lock                 : 1;
    uint32_t                           : 25;
    uint32_t trim_update_done          : 1;
    uint32_t info_block_valid          : 1;
    uint32_t                           : 1;
} mxc_flc_status_t;

typedef struct
{
    uint32_t debug_disable             : 1;
    uint32_t                           : 7;
    uint32_t mass_erase_lock           : 1;
    uint32_t                           : 22;
    uint32_t security_lock             : 1;
} mxc_flc_security_t;

typedef struct
{
    uint32_t destruct_bypass_erase     : 1;
    uint32_t superwipe_erase           : 1;
    uint32_t destruct_bypass_complete  : 1;
    uint32_t superwipe_complete        : 1;
    uint32_t                           : 28;
} mxc_flc_bypass_t;

typedef struct
{
    uint32_t flash_lve                 : 1;
    uint32_t                           : 7;
    uint32_t bypass_ahb_fail           : 1;
    uint32_t                           : 23;
} mxc_flc_ctrl2_t;

typedef struct
{
    uint32_t sram_addr_wrapped         : 1;
    uint32_t invalid_flash_addr        : 1;
    uint32_t flash_read_locked         : 1;
    uint32_t trim_update_done          : 1;
    uint32_t                           : 28;
} mxc_flc_intfl1_t;

typedef struct
{
    uint32_t sram_addr_wrapped         : 1;
    uint32_t invalid_flash_addr        : 1;
    uint32_t flash_read_locked         : 1;
    uint32_t trim_update_done          : 1;
    uint32_t                           : 28;
} mxc_flc_inten1_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                              Offset   Register Description
                                                ======   ======================================================= */
typedef struct {
    union {
        __IO uint32_t faddr;                /*  0x0000   Flash Operation Address                                 */
        __IO mxc_flc_faddr_t faddr_f;
    };
    union {
        __IO uint32_t fckdiv;               /*  0x0004   Flash Clock Rate Divisor                                */
        __IO mxc_flc_fckdiv_t fckdiv_f;
    };
    union {
        __IO uint32_t ctrl;                 /*  0x0008   Flash Control Register                                  */
        __IO mxc_flc_ctrl_t ctrl_f;
    };
    __R uint32_t rsv000C[6];                /*  0x000C                                                           */
    union {
        __IO uint32_t intr;                 /*  0x0024   Flash Controller Interrupt Flags and Enable/Disable 0   */
        __IO mxc_flc_intr_t intr_f;
    };
    __R uint32_t rsv0028[2];                /*  0x0028                                                           */

    __IO uint32_t fdata;                    /*  0x0030   Flash Operation Data Register                           */

    __R uint32_t rsv0034[7];                /*  0x0034                                                           */
    union {
        __IO uint32_t perform;              /*  0x0050   Flash Performance Settings                              */
        __IO mxc_flc_perform_t perform_f;
    };
    __R uint32_t rsv0054[11];               /*  0x0054                                                           */
    union {
        __IO uint32_t status;               /*  0x0080   Security Status Flags                                   */
        __IO mxc_flc_status_t status_f;
    };
    __R uint32_t rsv0084;                   /*  0x0084                                                           */
    union {
        __IO uint32_t security;             /*  0x0088   Flash Controller Security Settings                      */
        __IO mxc_flc_security_t security_f;
    };
    __R uint32_t rsv008C[4];                /*  0x008C                                                           */
    union {
        __IO uint32_t bypass;               /*  0x009C   Status Flags for DSB Operations                         */
        __IO mxc_flc_bypass_t bypass_f;
    };

    __IO uint32_t user_option;              /*  0x0100   Used to set DSB Access code and Auto-Lock in info block */
    __R uint32_t rsv0104[15];               /*  0x0104                                                           */
    union {
        __IO uint32_t ctrl2;                /*  0x0140   Flash Control Register 2                                */
        __IO mxc_flc_ctrl2_t ctrl2_f;
    };
    union {
        __IO uint32_t intfl1;               /*  0x0144   Interrupt Flags Register 1                              */
        __IO mxc_flc_intfl1_t intfl1_f;
    };
    union {
        __IO uint32_t inten1;               /*  0x0148   Interrupt Enable/Disable Register 1                     */
        __IO mxc_flc_inten1_t inten1_f;
    };
    __R uint32_t rsv014C;                   /*  0x014C                                                           */
    __IO uint32_t disable_xr0;              /*  0x0150   Disable Flash Page Exec/Read Register 0                 */
    __IO uint32_t disable_xr1;              /*  0x0154   Disable Flash Page Exec/Read Register 1                 */
    __IO uint32_t disable_xr2;              /*  0x0158   Disable Flash Page Exec/Read Register 2                 */
    __IO uint32_t disable_xr3;              /*  0x015C   Disable Flash Page Exec/Read Register 3                 */
    __IO uint32_t disable_we0;              /*  0x0160   Disable Flash Page Write/Erase Register 0               */
    __IO uint32_t disable_we1;              /*  0x0164   Disable Flash Page Write/Erase Register 1               */
    __IO uint32_t disable_we2;              /*  0x0168   Disable Flash Page Write/Erase Register 2               */
    __IO uint32_t disable_we3;              /*  0x016C   Disable Flash Page Write/Erase Register 3               */
} mxc_flc_regs_t;


/*
   Register offsets for module FLC.
*/
#define MXC_R_FLC_OFFS_FADDR                      ((uint32_t)0x00000000UL)
#define MXC_R_FLC_OFFS_FCKDIV                     ((uint32_t)0x00000004UL)
#define MXC_R_FLC_OFFS_CTRL                       ((uint32_t)0x00000008UL)
#define MXC_R_FLC_OFFS_INTR                       ((uint32_t)0x00000024UL)
#define MXC_R_FLC_OFFS_FDATA                      ((uint32_t)0x00000030UL)
#define MXC_R_FLC_OFFS_PERFORM                    ((uint32_t)0x00000050UL)
#define MXC_R_FLC_OFFS_STATUS                     ((uint32_t)0x00000080UL)
#define MXC_R_FLC_OFFS_SECURITY                   ((uint32_t)0x00000088UL)
#define MXC_R_FLC_OFFS_BYPASS                     ((uint32_t)0x0000009CUL)
#define MXC_R_FLC_OFFS_USER_OPTION                ((uint32_t)0x00000100UL)
#define MXC_R_FLC_OFFS_CTRL2                      ((uint32_t)0x00000140UL)
#define MXC_R_FLC_OFFS_INTFL1                     ((uint32_t)0x00000144UL)
#define MXC_R_FLC_OFFS_INTEN1                     ((uint32_t)0x00000148UL)
#define MXC_R_FLC_OFFS_DISABLE_XR0                ((uint32_t)0x00000150UL)
#define MXC_R_FLC_OFFS_DISABLE_XR1                ((uint32_t)0x00000154UL)
#define MXC_R_FLC_OFFS_DISABLE_XR2                ((uint32_t)0x00000158UL)
#define MXC_R_FLC_OFFS_DISABLE_XR3                ((uint32_t)0x0000015CUL)
#define MXC_R_FLC_OFFS_DISABLE_WE0                ((uint32_t)0x00000160UL)
#define MXC_R_FLC_OFFS_DISABLE_WE1                ((uint32_t)0x00000164UL)
#define MXC_R_FLC_OFFS_DISABLE_WE2                ((uint32_t)0x00000168UL)
#define MXC_R_FLC_OFFS_DISABLE_WE3                ((uint32_t)0x0000016CUL)

#define MXC_V_FLC_ERASE_CODE_PAGE_ERASE   ((uint8_t)0x55)
#define MXC_V_FLC_ERASE_CODE_MASS_ERASE   ((uint8_t)0xAA)

#define MXC_V_FLC_FLSH_UNLOCK_KEY         ((uint8_t)0x2)

#ifdef __cplusplus
}
#endif

#endif   /* _MXC_FLC_REGS_H_ */
