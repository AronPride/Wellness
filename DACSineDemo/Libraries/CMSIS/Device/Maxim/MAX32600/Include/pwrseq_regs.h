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

#ifndef _MXC_PWRSEQ_REGS_H
#define _MXC_PWRSEQ_REGS_H

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
    uint32_t pwr_lp1                : 1;
    uint32_t pwr_first_boot         : 1;
    uint32_t pwr_sys_reboot         : 1;
    uint32_t pwr_ldoen_run          : 1;
    uint32_t pwr_ldoen_slp          : 1;
    uint32_t pwr_chzyen_run         : 1;
    uint32_t pwr_chzyen_slp         : 1;
    uint32_t pwr_roen_run           : 1;
    uint32_t pwr_roen_slp           : 1;
    uint32_t pwr_nren_run           : 1;
    uint32_t pwr_nren_slp           : 1;
    uint32_t pwr_rtcen_run          : 1;
    uint32_t pwr_rtcen_slp          : 1;
    uint32_t pwr_svm3en_run         : 1;
    uint32_t pwr_svm3en_slp         : 1;
    uint32_t pwr_svm1en_run         : 1;
    uint32_t pwr_svm1en_slp         : 1;
    uint32_t pwr_svmrtcen_run       : 1;
    uint32_t pwr_svmrtcen_slp       : 1;
    uint32_t pwr_svmvdda3en         : 1;
    uint32_t                        : 12;
} mxc_pwrseq_reg0_t;

typedef struct
{
    uint32_t pwr_trikl_chrg         : 8;
    uint32_t pwr_pd_vdda3           : 1;
    uint32_t pwr_temp_sensor_pd     : 1;
    uint32_t pwr_pd_vddio           : 1;
    uint32_t pwr_man_vddio_sw       : 1;
    uint32_t pwr_man_vddio_sw2      : 1;
    uint32_t pwr_man_vddio_sw1      : 1;
    uint32_t pwr_gpio_freeze        : 1;
    uint32_t                        : 17;
} mxc_pwrseq_reg1_t;

typedef struct
{
    uint32_t pwr_rst3               : 5;
    uint32_t pwr_w3                 : 5;
    uint32_t pwr_w1                 : 5;
    uint32_t pwr_w1_low             : 5;
    uint32_t pwr_wrtc               : 5;
    uint32_t pwr_wvdda3             : 6;
    uint32_t                        : 1;
} mxc_pwrseq_reg2_t;

typedef struct
{
    uint32_t pwr_rosel              : 3;
    uint32_t pwr_rosel_quick        : 2;
    uint32_t pwr_svmsel             : 3;
    uint32_t pwr_pwrfltrsvmselo     : 2;
    uint32_t pwr_pwrfltrrosel       : 3;
    uint32_t pwr_svm_clk_mux        : 2;
    uint32_t pwr_ro_clk_mux         : 1;
    uint32_t pwr_quick_cnt          : 1;
    uint32_t pwr_bo_tc              : 2;
    uint32_t                        : 13;
} mxc_pwrseq_reg3_t;

typedef struct
{
    uint32_t pwr_tm_ps_2_gpio       : 1;
    uint32_t pwr_tm_fast_timers     : 1;
    uint32_t pwr_usb_prot_trim      : 1;
    uint32_t pwr_usb_dis_comp       : 1;
    uint32_t pwr_usb_to_vdd_fast    : 1;
    uint32_t pwr_usb_ldo_off        : 1;
    uint32_t pwr_usb_frc_vdd        : 1;
    uint32_t                        : 25;
} mxc_pwrseq_reg4_t;

typedef struct
{
    uint32_t pwr_trim_svm_bg        : 6;
    uint32_t pwr_trim_reg1p8        : 4;
    uint32_t pwr_trim_reg3p3        : 5;
    uint32_t pwr_trim_osc_vref      : 7;
    uint32_t                        : 10;
} mxc_pwrseq_reg5_t;

typedef struct
{
    uint32_t pwr_trim_usb_bias      : 3;
    uint32_t pwr_trim_usb_pm_res    : 4;
    uint32_t pwr_trim_usb_dm_res    : 4;
    uint32_t                        : 21;
} mxc_pwrseq_reg6_t;

typedef struct
{
    uint32_t pwr_first_boot         : 1;
    uint32_t pwr_sys_reboot         : 1;
    uint32_t pwr_prv_pwr_fail       : 1;
    uint32_t pwr_prv_boot_fail      : 1;
    uint32_t pwr_comp_wakeup        : 1;
    uint32_t pwr_iowakeup           : 1;
    uint32_t pwr_vdd3_rst           : 1;
    uint32_t pwr_vdd3_warn          : 1;
    uint32_t pwr_vdd1_rst           : 1;
    uint32_t pwr_vdd1_low_rst       : 1;
    uint32_t pwr_vdd1_warn          : 1;
    uint32_t pwr_vrtc_warn          : 1;
    uint32_t pwr_por3z_fail         : 1;
    uint32_t rtc_cmpr0              : 1;
    uint32_t rtc_cmpr1              : 1;
    uint32_t rtc_prescale_cmp       : 1;
    uint32_t rtc_rollover           : 1;
    uint32_t pwr_brownout_det       : 1;
    uint32_t pwr_usb_plug_wakeup    : 1;
    uint32_t pwr_usb_remove_wakeup  : 1;
    uint32_t pwr_vdd22_rst_bad      : 1;
    uint32_t pwr_vdd195_rst_bad     : 1;
    uint32_t                        : 10;
} mxc_pwrseq_flags_t;

typedef struct
{
    uint32_t                        : 1;
    uint32_t pwr_sys_reboot         : 1;
    uint32_t pwr_powerfail          : 1;
    uint32_t pwr_bootfail           : 1;
    uint32_t pwr_comp_wakeup        : 1;
    uint32_t pwr_iowakeup           : 1;
    uint32_t pwr_vdd3_rst           : 1;
    uint32_t pwr_vdd3_warn          : 1;
    uint32_t pwr_vdd1_rst           : 1;
    uint32_t pwr_vdd1_low_rst       : 1;
    uint32_t pwr_vdd1_warn          : 1;
    uint32_t pwr_vrtc_warn          : 1;
    uint32_t pwr_por3z_fail         : 1;
    uint32_t pwr_cmpr0_flag         : 1;
    uint32_t pwr_cmpr1_flag         : 1;
    uint32_t pwr_prescle_cmp_flag   : 1;
    uint32_t pwr_rollovr_flag       : 1;
    uint32_t pwr_brownout_det       : 1;
    uint32_t pwr_usb_plug_wakeup    : 1;
    uint32_t pwr_usb_remove_wakeup  : 1;
    uint32_t pwr_vdd22_rst_bad      : 1;
    uint32_t pwr_vdd195_rst_bad     : 1;
    uint32_t                        : 10;
} mxc_pwrseq_msk_flags_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                  Offset   Register Description
                                                    ======   ================================================= */
typedef struct {
    union {
        __IO uint32_t reg0;                     /*  0x0000   Power Sequencer Control Register 0                */
        __IO mxc_pwrseq_reg0_t reg0_f;
    };
    union {
        __IO uint32_t reg1;                     /*  0x0004   Power Sequencer Control Register 1                */
        __IO mxc_pwrseq_reg1_t reg1_f;
    };
    union {
        __IO uint32_t reg2;                     /*  0x0008   Power Sequencer Control Register 2                */
        __IO mxc_pwrseq_reg2_t reg2_f;
    };
    union {
        __IO uint32_t reg3;                     /*  0x000C   Power Sequencer Control Register 3                */
        __IO mxc_pwrseq_reg3_t reg3_f;
    };
    union {
        __IO uint32_t reg4;                     /*  0x0010   Power Sequencer Control Register 4                */
        __IO mxc_pwrseq_reg4_t reg4_f;
    };
    union {
        __IO uint32_t reg5;                     /*  0x0014   Power Sequencer Control Register 5 (Trim 0)       */
        __IO mxc_pwrseq_reg5_t reg5_f;
    };
    union {
        __IO uint32_t reg6;                     /*  0x0018   Power Sequencer Control Register 6 (Trim 1)       */
        __IO mxc_pwrseq_reg6_t reg6_f;
    };
    __R uint32_t rsv001C;                       /*  0x001C                                                     */
    union {
        __IO uint32_t flags;                    /*  0x0020   Power Sequencer Flags                             */
        __IO mxc_pwrseq_flags_t flags_f;
    };
    union {
        __IO uint32_t msk_flags;                /*  0x0024   Power Sequencer Flags Mask Register               */
        __IO mxc_pwrseq_msk_flags_t msk_flags_f;
    };
} mxc_pwrseq_regs_t;


/*
   Register offsets for module PWRSEQ.
*/

#define MXC_R_PWRSEQ_OFFS_REG0                    ((uint32_t)0x00000000UL)
#define MXC_R_PWRSEQ_OFFS_REG1                    ((uint32_t)0x00000004UL)
#define MXC_R_PWRSEQ_OFFS_REG2                    ((uint32_t)0x00000008UL)
#define MXC_R_PWRSEQ_OFFS_REG3                    ((uint32_t)0x0000000CUL)
#define MXC_R_PWRSEQ_OFFS_REG4                    ((uint32_t)0x00000010UL)
#define MXC_R_PWRSEQ_OFFS_REG5                    ((uint32_t)0x00000014UL)
#define MXC_R_PWRSEQ_OFFS_REG6                    ((uint32_t)0x00000018UL)
#define MXC_R_PWRSEQ_OFFS_FLAGS                   ((uint32_t)0x00000020UL)
#define MXC_R_PWRSEQ_OFFS_MSK_FLAGS               ((uint32_t)0x00000024UL)


#ifdef __cplusplus
}
#endif

#endif
