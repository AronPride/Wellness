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

#ifndef _MXC_TPU_REGS_H_
#define _MXC_TPU_REGS_H_

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
    uint32_t reset           : 1;
    uint32_t power_on        : 1;
    uint32_t preamp_en       : 1;
    uint32_t cmp_en          : 1;
    uint32_t ref_sel         : 1;
    uint32_t vcm_sel         : 1;
    uint32_t                 : 2;
    uint32_t cmp_vth         : 3;
    uint32_t                 : 21;
} mxc_tpu_puf_ctrl_t;

typedef struct
{
    uint32_t err_thr         : 5;
    uint32_t out_freq        : 3;
    uint32_t clock_div       : 3;
    uint32_t                 : 3;
    uint32_t rtc_tx_busy     : 1;
    uint32_t lock            : 1;
    uint32_t                 : 16;
} mxc_tpu_tsr_ctrl0_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                              Offset   Register Description
                                                ======   ================================================== */
typedef struct {
    __R uint32_t rsv0000;                    /*  0x0000   Reserved                                          */
    __R uint32_t rsv0004;                    /*  0x0004   Reserved - PUF Control (Deprecated)               */
    __R uint32_t rsv0008;                    /*  0x0008   Reserved - PUF Output (Deprecated)                */
    __R uint32_t rsv000C[125];               /*  0x000C                                                     */
    __IO uint32_t prng_user_entropy;         /*  0x0200   PRNG User Entropy Value                           */
    __IO uint32_t prng_rnd_num;              /*  0x0204   PRNG Random Number Output                         */
} mxc_tpu_regs_t;


/*                                               Offset   Register Description
                                                 ======   ================================================= */
typedef struct {
    __IO uint32_t status;                    /*  0x0000   Dynamic Tamper Sensor Status                      */
    union {
        __IO uint32_t ctrl0;                 /*  0x0004   Dynamic Tamper Sensor Control 0                   */
        __IO mxc_tpu_tsr_ctrl0_t ctrl0_f;
    };
    __IO uint32_t ctrl1;                     /*  0x0008   Dynamic Tamper Sensor Control 1                   */
    __IO uint32_t sks0;                      /*  0x0010   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks1;                      /*  0x0014   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks2;                      /*  0x0018   TPU Secure Key Storage Register 0                 */
    __IO uint32_t sks3;                      /*  0x001C   TPU Secure Key Storage Register 0                 */
} mxc_tpu_tsr_regs_t;
/*
   Register offsets for module TPU.
*/

#define MXC_R_TPU_OFFS_PRNG_USER_ENTROPY          ((uint32_t)0x00000200UL)
#define MXC_R_TPU_OFFS_PRNG_RND_NUM               ((uint32_t)0x00000204UL)
#define MXC_R_TPU_TSR_OFFS_STATUS                 ((uint32_t)0x00000000UL)
#define MXC_R_TPU_TSR_OFFS_CTRL0                  ((uint32_t)0x00000004UL)
#define MXC_R_TPU_TSR_OFFS_CTRL1                  ((uint32_t)0x00000008UL)
#define MXC_R_TPU_TSR_OFFS_KEY_OF_KEYS_0          ((uint32_t)0x00000010UL)
#define MXC_R_TPU_TSR_OFFS_KEY_OF_KEYS_1          ((uint32_t)0x00000014UL)
#define MXC_R_TPU_TSR_OFFS_KEY_OF_KEYS_2          ((uint32_t)0x00000018UL)
#define MXC_R_TPU_TSR_OFFS_KEY_OF_KEYS_3          ((uint32_t)0x0000001CUL)

#ifdef __cplusplus
}
#endif

#endif   /* _MXC_TPU_REGS_H_ */

