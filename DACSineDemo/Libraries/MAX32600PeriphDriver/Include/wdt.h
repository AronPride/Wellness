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

/* $Revision: 2905 $ $Date: 2014-08-05 17:18:09 -0500 (Tue, 05 Aug 2014) $ */

#ifndef _WDT_H
#define _WDT_H

#include "wdt_regs.h"

/**
 * @file wdt.h
 * @addtogroup wdt WDT
 * @{
 * @brief This is the high level API for the watchdog timer interface module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Configures and enables the interrupt timeout for the watchdog specified.
 *
 * @param index Index of watchdog to configure and enable.
 * @param int_period Interrupt period.
 * @param int_cb_fn Interrupt callback function.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_EnableInt(uint8_t index, mxc_wdt_period_t int_period, void(*int_cb_fn)(void), uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Disables the interrupt timeout for the watchdog specified.
 *
 * @param index Index of watchdog to disable.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_DisableInt(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Configures and enables the pre-window timeout for the watchdog specified.
 *
 * @param index Index of watchdog to configure and enable.
 * @param wait_period Pre-window period.
 * @param prewin_cb_fn Pre-window callback function.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_EnableWait(uint8_t index, mxc_wdt_period_t wait_period, void(*prewin_cb_fn)(void), uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Disables the pre-window timeout for the watchdog specified.
 *
 * @param index Index of watchdog to disable.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_DisableWait(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Configures and enables the reset timeout for the watchdog specified.
 *
 * @param index Index of watchdog to configure and enable.
 * @param rst_period Reset period.
 * @param reboot 0 => reboot system. 1 => reset system.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_EnableReset(uint8_t index, mxc_wdt_period_t rst_period, uint8_t reboot, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Disables the reset timeout for the watchdog specified.
 *
 * @param index Index of watchdog to disable.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_DisableReset(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Starts the watchdog specified.
 *
 * @param index Index of watchdog to start.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_Start(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Feeds the watchdog specified.
 *
 * @param index Index of watchdog to feed.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_Reset(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @brief Stops the watchdog specified.
 *
 * @param index Index of watchdog to stop.
 * @param unlock_key Key to unlock watchdog.
 * @param lock_key Key to lock watchdog.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t WDT_Stop(uint8_t index, uint8_t unlock_key, uint8_t lock_key);

/**
 * @}
 */

#endif /* _WDT_H */
