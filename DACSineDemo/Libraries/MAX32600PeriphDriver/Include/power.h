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

/* $Revision: 4264 $ $Date: 2015-02-05 09:29:32 -0600 (Thu, 05 Feb 2015) $ */

#ifndef _POWER_H
#define _POWER_H

#include "pwrman_regs.h"
#include "pwrseq_regs.h"

/**
 * @file  power.h
 * @addtogroup pwrman Power Management
 * @{
 * @brief This is the high level API for the power management module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Defines the Supply Voltage Monitor Trip Setting for VDD3.
 */
typedef enum {
    /** VDD3 trip point = 1.764V */
    MXC_E_VDD3_1_764V_TRIP_POINT = 0,
    /** VDD3 trip point = 1.798V */
    MXC_E_VDD3_1_798V_TRIP_POINT,
    /** VDD3 trip point = 1.833V */
    MXC_E_VDD3_1_833V_TRIP_POINT,
    /** VDD3 trip point = 1.870V */
    MXC_E_VDD3_1_870V_TRIP_POINT,
    /** VDD3 trip point = 1.908V */
    MXC_E_VDD3_1_908V_TRIP_POINT,
    /** VDD3 trip point = 1.948V */
    MXC_E_VDD3_1_948V_TRIP_POINT,
    /** VDD3 trip point = 1.989V */
    MXC_E_VDD3_1_989V_TRIP_POINT,
    /** VDD3 trip point = 2.032V */
    MXC_E_VDD3_2_032V_TRIP_POINT,
    /** VDD3 trip point = 2.077V */
    MXC_E_VDD3_2_077V_TRIP_POINT,
    /** VDD3 trip point = 2.125V */
    MXC_E_VDD3_2_125V_TRIP_POINT,
    /** VDD3 trip point = 2.174V */
    MXC_E_VDD3_2_174V_TRIP_POINT,
    /** VDD3 trip point = 2.226V */
    MXC_E_VDD3_2_226V_TRIP_POINT,
    /** VDD3 trip point = 2.280V */
    MXC_E_VDD3_2_280V_TRIP_POINT,
    /** VDD3 trip point = 2.337V */
    MXC_E_VDD3_2_337V_TRIP_POINT,
    /** VDD3 trip point = 2.397V */
    MXC_E_VDD3_2_397V_TRIP_POINT,
    /** VDD3 trip point = 2.460V */
    MXC_E_VDD3_2_460V_TRIP_POINT,
    /** VDD3 trip point = 2.526V */
    MXC_E_VDD3_2_526V_TRIP_POINT,
    /** VDD3 trip point = 2.597V */
    MXC_E_VDD3_2_597V_TRIP_POINT,
    /** VDD3 trip point = 2.671V */
    MXC_E_VDD3_2_671V_TRIP_POINT,
    /** VDD3 trip point = 2.749V */
    MXC_E_VDD3_2_749V_TRIP_POINT,
    /** VDD3 trip point = 2.833V */
    MXC_E_VDD3_2_833V_TRIP_POINT,
    /** VDD3 trip point = 2.921V */
    MXC_E_VDD3_2_921V_TRIP_POINT,
    /** VDD3 trip point = 3.015V */
    MXC_E_VDD3_3_015V_TRIP_POINT,
    /** VDD3 trip point = 3.116V */
    MXC_E_VDD3_3_116V_TRIP_POINT,
    /** VDD3 trip point = 3.223V */
    MXC_E_VDD3_3_223V_TRIP_POINT,
    /** VDD3 trip point = 3.339V */
    MXC_E_VDD3_3_339V_TRIP_POINT,
    /** VDD3 trip point = 3.462V */
    MXC_E_VDD3_3_462V_TRIP_POINT,
    /** VDD3 trip point = 3.595V */
    MXC_E_VDD3_3_595V_TRIP_POINT,
    /** VDD3 trip point = 3.739V */
    MXC_E_VDD3_3_730V_TRIP_POINT,
    /** VDD3 trip point = 3.895V */
    MXC_E_VDD3_3_895V_TRIP_POINT,
    /** VDD3 trip point = 4.064V */
    MXC_E_VDD3_4_064V_TRIP_POINT

} pwrseq_vdd3_trip_point_t;

/**
 * @brief Sets the Voltage Trip Point for VDD3
 *
 * @param vdd3      Use the pwrseq_vdd3_trip_point_t enumerations.
 * @param trippoint Callback function for when the VDD3 voltage trippoint is reached      .
 */
void PWR_SetTripPointVDD3(uint32_t vdd3,void (*trippoint)(void));

/**
 * @brief Enables all GPIOs.
 */
void PWR_EnableGPIO(void);

/**
 * @brief Disables all GPIOs.
 */
void PWR_DisableGPIO(void);

/**
 * @brief Sets up WUD for designated GPIO port and pin.
 *
 * @param port      Port index.
 * @param pin       Pin index.
 * @param act_high  1 for active high, 0 for active low.
 */
void PWR_SetGPIOWUD(uint8_t port, uint8_t pin, uint8_t act_high);

/**
 * @brief Clears WUD for all GPIO ports and pins.
 */
void PWR_ClearAllGPIOWUD(void);

/**
 * @brief Clears WUD for designated GPIO port and pin.
 *
 * @param port      Port index.
 * @param pin       Pin index.
 */
void PWR_ClearGPIOWUD(uint8_t port, uint8_t pin);

/**
 * @brief Sets up WUD for designated comparator.
 *
 * @param index         Comparator index.
 * @param rising_edge   1 for rising edge, 0 for falling edge.
 */
void PWR_SetCompWUD(uint8_t index, uint8_t rising_edge);

/**
 * @brief Clears WUD for designated comparator.
 *
 * @param index   Comparator index.
 */
void PWR_ClearCompWUD(uint8_t index);

/**
 * @brief Clears WUD for all comparators.
 *
 */
void PWR_ClearAllCompWUD(void);

/**
 * @brief Clears power sequencer flag latch.
 */
void PWR_ClearFlags(void);

/**
 * @brief Defines power modes.
 */
typedef enum {
    /** ARM deep sleep mode without data retention (WFE) */
    MXC_E_PWR_MODE_LP0 = 0,
    /** ARM deep sleep mode with data retention (WFE) */
    MXC_E_PWR_MODE_LP1,
    /** ARM sleep mode (WFI) */
    MXC_E_PWR_MODE_LP2,
    /** No sleep mode */
    MXC_E_PWR_MODE_LP3
} mxc_pwr_mode_t;

/**
 * @brief Sets processor mode.
 *
 * @param mode    Sleep mode.
 * @param wakeup  Callback function for return from LP1.
 */
void PWR_SetMode(mxc_pwr_mode_t mode, void (*wakeup)(void));

/**
 * @brief Sends processor to sleep. Chooses WFI/WFE based on current mode.
 */
void PWR_Sleep(void);

/**
 * @brief Initializes the power management module.
 */
void PWR_Init(void);

/**
 * @brief Defines modules to enable/disable.
 */
typedef enum {
    /** AFE Powered */
    MXC_E_PWR_ENABLE_AFE = 0,
    /** I/O Active */
    MXC_E_PWR_ENABLE_IO,
    /** USB Powered */
    MXC_E_PWR_ENABLE_USB,
    /** Static Pullups Enabled */
    MXC_E_PWR_ENABLE_STATIC_PULLUPS
} mxc_pwr_enable_t;

/**
 * @brief Enables modules in pwr_rst_ctrl.
 */
void PWR_Enable(mxc_pwr_enable_t module);

/**
 * @brief Disables modules in pwr_rst_ctrl.
 */
void PWR_Disable(mxc_pwr_enable_t module);

typedef enum {
    /** Trickle charger with no diode and 250 ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_NO_DIODE_W_250_OHM = 0x5,
    /** Trickle charger with no diode and 2k ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_NO_DIODE_W_2K_OHM = 0x6,
    /** Trickle charger with no diode and 4k ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_NO_DIODE_W_4K_OHM = 0x7,
    /** Trickle charger with diode and 250 ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_DIODE_W_250_OHM = 0x9,
    /** Trickle charger with diode and 2k ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_DIODE_W_2K_OHM = 0xA,
    /** Trickle charger with diode and 4k ohm resistor */
    MXC_E_PWR_TRICKLE_CHARGER_DIODE_W_4K_OHM = 0xB,
} mxc_pwr_trickle_charger_t;

/**
 * @brief Set up trickle charger super-cap
 *
 * @param decode     Trickle charger resistor and diode.
 */
void PWR_SetTrickleCharger(mxc_pwr_trickle_charger_t decode);

/**
 * @brief Defines devices to enable/disable.
 */
typedef enum {
    /** LDO regulator power switch */
    MXC_E_PWR_DEVICE_LDO  = 3,
    /** CHZY regulator power switch */
    MXC_E_PWR_DEVICE_CHZY = 5,
    /** Relaxation oscillator power switch */
    MXC_E_PWR_DEVICE_RO   = 7,
    /** Nano ring oscillator power switch */
    MXC_E_PWR_DEVICE_NR   = 9,
    /** Real-time clock power switch */
    MXC_E_PWR_DEVICE_RTC  = 11,
    /** VDD3 system voltage monitor power switch */
    MXC_E_PWR_DEVICE_SVM3 = 13,
    /** VREG18 system voltage monitor power switch */
    MXC_E_PWR_DEVICE_SVM1 = 15,
    /** VRTC system voltage monitor power switch */
    MXC_E_PWR_DEVICE_SVMRTC = 17,
    /** VDDA3 system voltage monitor power switch */
    MXC_E_PWR_DEVICE_SVMVDDA3 = 19,
} mxc_pwr_device_t;

/**
 * @brief Enable a module in run mode.
 *
 * @param device    Device to enable in run mode.
 */
void PWR_EnableDevRun(mxc_pwr_device_t device);

/**
 * @brief Enable a module in sleep mode.
 *
 * @param device    Device to enable in sleep mode.
 */
void PWR_EnableDevSleep(mxc_pwr_device_t device);

/**
 * @brief Disable a module in run mode.
 *
 * @param device    Device to disable in run mode.
 */
void PWR_DisableDevRun(mxc_pwr_device_t device);

/**
 * @brief Disable a module in sleep mode.
 *
 * @param device    Device to disable in sleep mode.
 */
void PWR_DisableDevSleep(mxc_pwr_device_t device);

/**
 * @brief Enable all wakeup events to wake up power sequencer.
 */
void PWR_EnableAllWakeupEvents(void);

/**
 * @brief Disable all wakeup events to wake up power sequencer.
 */
void PWR_DisableAllWakeupEvents(void);

/**
 * @brief Defines event masks to enable/disable.
 */
typedef enum {
    /** Firmware reset event */
    MXC_E_PWR_EVENT_SYS_REBOOT = 1,
    /** Power fail event */
    MXC_E_PWR_EVENT_POWER_FAIL,
    /** Boot fail event */
    MXC_E_PWR_EVENT_BOOT_FAIL,
    /** Comparator wakeup event */
    MXC_E_PWR_EVENT_COMP_FLAG,
    /** GPIO wakeup event */
    MXC_E_PWR_EVENT_IO_FLAG,
    /** VDD3 reset comparator event */
    MXC_E_PWR_EVENT_VDD3_RST,
    /** VDD3 warning comparator event */
    MXC_E_PWR_EVENT_VDD3_WARN,
    /** VREG18 reset comparator event*/
    MXC_E_PWR_EVENT_VDD1_RST,
    /** VREG18 reset low comparator event */
    MXC_E_PWR_EVENT_VDD1_LOW_RST,
    /** VREG18 warning comparator event */
    MXC_E_PWR_EVENT_VDD1_WARN,
    /** VRTC comparator event */
    MXC_E_PWR_EVENT_VRTC_WARN,
    /** POR3 and POR3_lite event */
    MXC_E_PWR_EVENT_POR3Z_FAIL,
    /** RTC cmpr0 event */
    MXC_E_PWR_EVENT_RTC_CMPR0,
    /** RTC cmpr1 event */
    MXC_E_PWR_EVENT_RTC_CMPR1,
    /** RTC prescale event */
    MXC_E_PWR_EVENT_RTC_PRESCALE_CMP,
    /** RTC rollover event */
    MXC_E_PWR_EVENT_RTC_ROLLOVER,
    /** RTC brownout event */
    MXC_E_PWR_EVENT_BROWNOUT,
    /** RTC usb plug inserted event*/
    MXC_E_PWR_EVENT_USB_PLUG,
    /** RTC usb plug removed event */
    MXC_E_PWR_EVENT_USB_REMOVE,
    /** VDD22 reset comparator event */
    MXC_E_PWR_EVENT_VDD22_RST,
    /** VDD195 reset comparator event */
    MXC_E_PWR_EVENT_VDD195_RST
} mxc_pwr_event_t;

/**
 * @brief Enables wakeup events to wake up power sequencer for a given event.
 *
 * @param event     Event mask to enable.
 */
void PWR_EnableWakeupEvent(mxc_pwr_event_t event);

/**
 * @brief Disables wakeup event to wake up power sequencer for a given event.
 *
 * @param event     Event mask to disable.
 */
void PWR_DisableWakeupEvent(mxc_pwr_event_t event);

/**
 * @brief This function will set gpio in tristate with a 1 MEG pulldown
 *
 * @param  port  desired gpio port.
 * @param  pin   desired gpio pin.
 * @param  act_high   set 1 to high level; 0 to low level.
 */
void PWR_SetGPIOWeakDriver(uint8_t port, uint8_t pin, uint8_t act_high);

/**
 * @}
 */

#endif /* POWER_H_ */
