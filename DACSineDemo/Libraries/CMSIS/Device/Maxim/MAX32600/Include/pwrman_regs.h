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

#ifndef _MXC_PWRMAN_REGS_H_
#define _MXC_PWRMAN_REGS_H_

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

/**
 * @file  pwrman_regs.h
 * @addtogroup pwrman PWRMAN
 * @{
 */



typedef struct
{
    uint32_t flash_active      : 1;
    uint32_t sram_active       : 1;
    uint32_t afe_powered       : 1;
    uint32_t io_active         : 1;
    uint32_t usb_powered       : 1;
    uint32_t pullups_enabled   : 1;
    uint32_t                   : 2;
    uint32_t firmware_reset    : 1;
    uint32_t arm_lockup_reset  : 1;
    uint32_t                   : 2;
    uint32_t wud_clear         : 1;
    uint32_t                   : 3;
    uint32_t tamper_detect     : 1;
    uint32_t fw_command_sysman : 1;
    uint32_t watchdog_timeout  : 1;
    uint32_t fw_command_arm    : 1;
    uint32_t arm_lockup        : 1;
    uint32_t srstn_assertion   : 1;
    uint32_t por               : 1;
    uint32_t                   : 8;
    uint32_t low_power_mode    : 1;
} mxc_pwrman_pwr_rst_ctrl_t;

typedef struct
{
    uint32_t v1_8_warning      : 1;
    uint32_t v3_3_warning      : 1;
    uint32_t rtc_warning       : 1;
    uint32_t v3_3_reset        : 1;
    uint32_t vdda_warning      : 1;
    uint32_t                   : 27;
} mxc_pwrman_intfl_t;

typedef struct
{
    uint32_t v1_8_warning      : 1;
    uint32_t v3_3_warning      : 1;
    uint32_t rtc_warning       : 1;
    uint32_t v3_3_reset        : 1;
    uint32_t vdda_warning      : 1;
    uint32_t                   : 27;
} mxc_pwrman_inten_t;

typedef struct
{
    uint32_t v1_8_warning      : 1;
    uint32_t v3_3_warning      : 1;
    uint32_t rtc_warning       : 1;
    uint32_t v3_3_reset        : 1;
    uint32_t vdda_warning      : 1;
    uint32_t                   : 27;
} mxc_pwrman_svm_events_t;


/**
 * @brief Defines PAD Modes for Wake Up Detection.
 */
typedef enum {
    /** WUD Mode for Selected PAD = Clear/Activate */
    MXC_E_PWRMAN_PAD_MODE_CLEAR_SET,
    /** WUD Mode for Selected PAD = Set WUD Act Hi/Set WUD Act Lo */
    MXC_E_PWRMAN_PAD_MODE_ACT_HI_LO,
    /** WUD Mode for Selected PAD = Set Weak Hi/ Set Weak Lo */
    MXC_E_PWRMAN_PAD_MODE_WEAK_HI_LO,
    /** WUD Mode for Selected PAD = No pad state change */
    MXC_E_PWRMAN_PAD_MODE_NONE
} mxc_pwrman_pad_mode_t;

typedef struct
{
    uint32_t pad_select     : 6;
    uint32_t                : 2;
    uint32_t pad_mode       : 2;
    uint32_t                : 2;
    uint32_t clear_all      : 1;
    uint32_t                : 19;
} mxc_pwrman_wud_ctrl_t;

typedef struct
{
    uint32_t gpio0             : 1;
    uint32_t gpio1             : 1;
    uint32_t gpio2             : 1;
    uint32_t gpio3             : 1;
    uint32_t gpio4             : 1;
    uint32_t gpio5             : 1;
    uint32_t gpio6             : 1;
    uint32_t gpio7             : 1;
    uint32_t gpio8             : 1;
    uint32_t gpio9             : 1;
    uint32_t gpio10            : 1;
    uint32_t gpio11            : 1;
    uint32_t gpio12            : 1;
    uint32_t gpio13            : 1;
    uint32_t gpio14            : 1;
    uint32_t gpio15            : 1;
    uint32_t gpio16            : 1;
    uint32_t gpio17            : 1;
    uint32_t gpio18            : 1;
    uint32_t gpio19            : 1;
    uint32_t gpio20            : 1;
    uint32_t gpio21            : 1;
    uint32_t gpio22            : 1;
    uint32_t gpio23            : 1;
    uint32_t gpio24            : 1;
    uint32_t gpio25            : 1;
    uint32_t gpio26            : 1;
    uint32_t gpio27            : 1;
    uint32_t gpio28            : 1;
    uint32_t gpio29            : 1;
    uint32_t gpio30            : 1;
    uint32_t gpio31            : 1;
} mxc_pwrman_wud_seen0_t;

typedef struct
{
    uint32_t gpio32            : 1;
    uint32_t gpio33            : 1;
    uint32_t gpio34            : 1;
    uint32_t gpio35            : 1;
    uint32_t gpio36            : 1;
    uint32_t gpio37            : 1;
    uint32_t gpio38            : 1;
    uint32_t gpio39            : 1;
    uint32_t gpio40            : 1;
    uint32_t gpio41            : 1;
    uint32_t gpio42            : 1;
    uint32_t gpio43            : 1;
    uint32_t gpio44            : 1;
    uint32_t gpio45            : 1;
    uint32_t gpio46            : 1;
    uint32_t gpio47            : 1;
    uint32_t gpio48            : 1;
    uint32_t gpio49            : 1;
    uint32_t gpio50            : 1;
    uint32_t gpio51            : 1;
    uint32_t gpio52            : 1;
    uint32_t gpio53            : 1;
    uint32_t gpio54            : 1;
    uint32_t gpio55            : 1;
    uint32_t gpio56            : 1;
    uint32_t gpio57            : 1;
    uint32_t gpio58            : 1;
    uint32_t gpio59            : 1;
    uint32_t gpio60            : 1;
    uint32_t gpio61            : 1;
    uint32_t gpio62            : 1;
    uint32_t gpio63            : 1;
} mxc_pwrman_wud_seen1_t;

typedef struct
{
    uint32_t base_part_number  : 16;
    uint32_t                   : 12;
    uint32_t package_select    : 1;
    uint32_t                   : 3;
} mxc_pwrman_base_part_num_t;

typedef struct
{
    uint32_t revision_id       : 4;
    uint32_t mask_id           : 28;
} mxc_pwrman_mask_id0_t;

typedef struct
{
    uint32_t mask_id           : 31;
    uint32_t mask_id_enable    : 1;
} mxc_pwrman_mask_id1_t;

typedef struct
{
    uint32_t uart0             : 1;
    uint32_t uart1             : 1;
    uint32_t timer0            : 1;
    uint32_t timer1            : 1;
    uint32_t timer2            : 1;
    uint32_t timer3            : 1;
    uint32_t watchdog0         : 1;
    uint32_t usb               : 1;
    uint32_t adc               : 1;
    uint32_t dac12_0           : 1;
    uint32_t dac12_1           : 1;
    uint32_t dac8_0            : 1;
    uint32_t dac8_1            : 1;
    uint32_t pmu               : 1;
    uint32_t lcd               : 1;
    uint32_t gpio              : 1;
    uint32_t pulse_train       : 1;
    uint32_t spi0              : 1;
    uint32_t spi1              : 1;
    uint32_t spi2              : 1;
    uint32_t i2cm0             : 1;
    uint32_t i2cm1             : 1;
    uint32_t i2cs              : 1;
    uint32_t crc               : 1;
    uint32_t tpu               : 1;
    uint32_t ssb               : 1;
    uint32_t                   : 6;
} mxc_pwrman_peripheral_reset_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                          Offset   Register Description
                                                            ======   =========================================== */
typedef struct {
    union {
        __IO uint32_t pwr_rst_ctrl;                     /*  0x0000   Power Reset Control and Status              */
        __IO mxc_pwrman_pwr_rst_ctrl_t pwr_rst_ctrl_f;
    };
    union {
        __IO uint32_t intfl;                            /*  0x0004   Interrupt Flags                             */
        __IO mxc_pwrman_intfl_t intfl_f;
    };
    union {
        __IO uint32_t inten;                            /*  0x0008   Interrupt Enable/Disable Controls           */
        __IO mxc_pwrman_inten_t inten_f;
    };
    union {
        __IO uint32_t svm_events;                       /*  0x000C   SVM Event Status Flags (read-only)          */
        __IO mxc_pwrman_svm_events_t svm_events_f;
    };
    union {
        __IO uint32_t wud_ctrl;                         /*  0x0010   Wake-Up Detect Control                      */
        __IO mxc_pwrman_wud_ctrl_t wud_ctrl_f;
    };
    __IO uint32_t wud_pulse0;                           /*  0x0014   WUD Pulse To Mode Bit 0                     */
    __IO uint32_t wud_pulse1;                           /*  0x0018   WUD Pulse To Mode Bit 1                     */
    __R uint32_t rsv001C[5];                            /*  0x001C                                               */
    union {
        __IO uint32_t wud_seen0;                        /*  0x0030   Wake-up Detect Status for P0/P1/P2/P3       */
        __IO mxc_pwrman_wud_seen0_t wud_seen0_f;
    };
    union {
        __IO uint32_t wud_seen1;                        /*  0x0034   Wake-up Detect Status for P4/P5/P6/P7       */
        __IO mxc_pwrman_wud_seen1_t wud_seen1_f;
    };
    __IO uint32_t die_type;                             /*  0x0038   Die ID Register (Device Type)               */
    union {
        __IO uint32_t base_part_num;                    /*  0x003C   Base Part Number                            */
        __IO mxc_pwrman_base_part_num_t base_part_num_f;
    };
    union {
        __IO uint32_t mask_id0;                         /*  0x0040   Mask ID Register 0                          */
        __IO mxc_pwrman_mask_id0_t mask_id0_f;
    };
    union {
        __IO uint32_t mask_id1;                         /*  0x0044   Mask ID Register 1                          */
        __IO mxc_pwrman_mask_id1_t mask_id1_f;
    };
    union {
        __IO uint32_t peripheral_reset;                 /*  0x0048   Peripheral Reset Control Register           */
        __IO mxc_pwrman_peripheral_reset_t peripheral_reset_f;
    };
} mxc_pwrman_regs_t;


/*
   Register offsets for module PWRMAN.
*/

#define MXC_R_PWRMAN_OFFS_PWR_RST_CTRL            ((uint32_t)0x00000000UL)
#define MXC_R_PWRMAN_OFFS_INTFL                   ((uint32_t)0x00000004UL)
#define MXC_R_PWRMAN_OFFS_INTEN                   ((uint32_t)0x00000008UL)
#define MXC_R_PWRMAN_OFFS_SVM_EVENTS              ((uint32_t)0x0000000CUL)
#define MXC_R_PWRMAN_OFFS_WUD_CTRL                ((uint32_t)0x00000010UL)
#define MXC_R_PWRMAN_OFFS_WUD_PULSE0              ((uint32_t)0x00000014UL)
#define MXC_R_PWRMAN_OFFS_WUD_PULSE1              ((uint32_t)0x00000018UL)
#define MXC_R_PWRMAN_OFFS_WUD_SEEN0               ((uint32_t)0x00000030UL)
#define MXC_R_PWRMAN_OFFS_WUD_SEEN1               ((uint32_t)0x00000034UL)
#define MXC_R_PWRMAN_OFFS_DIE_TYPE                ((uint32_t)0x00000038UL)
#define MXC_R_PWRMAN_OFFS_BASE_PART_NUM           ((uint32_t)0x0000003CUL)
#define MXC_R_PWRMAN_OFFS_MASK_ID0                ((uint32_t)0x00000040UL)
#define MXC_R_PWRMAN_OFFS_MASK_ID1                ((uint32_t)0x00000044UL)
#define MXC_R_PWRMAN_OFFS_PERIPHERAL_RESET        ((uint32_t)0x00000048UL)


#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
*/
#endif /* _MXC_PWRMAN_REGS_H_ */
