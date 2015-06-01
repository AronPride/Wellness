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

#ifndef _MXC_PT_REGS_H_
#define _MXC_PT_REGS_H_

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

typedef struct
{
    uint32_t                   : 1;
    uint32_t enable_all        : 1;
    uint32_t                   : 30;
} mxc_ptg_ctrl_t;

typedef struct
{
    uint32_t pt0               : 1;
    uint32_t pt1               : 1;
    uint32_t pt2               : 1;
    uint32_t pt3               : 1;
    uint32_t pt4               : 1;
    uint32_t pt5               : 1;
    uint32_t pt6               : 1;
    uint32_t pt7               : 1;
    uint32_t                   : 24;
} mxc_ptg_resync_t;

typedef struct
{
    uint32_t rate_control      : 27;
    uint32_t mode              : 5;
} mxc_pt_rate_length_t;


/*                                                  Offset   Register Description
                                                    ======   =================================================== */
typedef struct {
    union {                                     /*  0x0000   Global Pulse Train Enable/Disable                   */
        __IO uint32_t ctrl;
        __IO mxc_ptg_ctrl_t ctrl_f;
    };
    union {                                     /*  0x0004   Global Resync (All Pulse Trains) Control            */
        __IO uint32_t resync;
        __IO mxc_ptg_resync_t resync_f;
    };
} mxc_ptg_regs_t;


/*                                                   Offset   Register Description
                                                     ======   ================================================== */
typedef struct {
    union {                                      /*  0x0000   Pulse Train Configuration                          */
        __IO uint32_t rate_length;
        __IO mxc_pt_rate_length_t rate_length_f;
    };
    __IO uint32_t train;                         /*  0x0004   Pulse Train Output Pattern                         */
} mxc_pt_regs_t;

/*
   Register offsets for module PT.
*/

#define MXC_R_PTG_OFFS_CTRL                       ((uint32_t)0x00000000UL)
#define MXC_R_PTG_OFFS_RESYNC                     ((uint32_t)0x00000004UL)
#define MXC_R_PT_OFFS_RATE_LENGTH                 ((uint32_t)0x00000000UL)
#define MXC_R_PT_OFFS_TRAIN                       ((uint32_t)0x00000004UL)

#ifdef __cplusplus
}
#endif
#endif   /* _MXC_PT_REGS_H_ */

