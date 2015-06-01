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

/* $Revision: 3041 $ $Date: 2014-08-22 17:05:45 -0500 (Fri, 22 Aug 2014) $ */

#ifndef _RTC_H
#define _RTC_H

#include "rtc_regs.h"

/**
 * @file  rtc.h
 * @addtogroup rtc Real-time Clock
 * @{
 * @brief This is the high level API for the real-time clock module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief  Enable and start the real-time clock continuing from its current value
 */
void RTC_Enable(void);

/**
 * @brief  Disable and stop the real-time clock
 */
void RTC_Disable(void);

/**
 * @brief Set and start the real-time clock
 *
 * @param value       value wanted to be set for real-time timer.
 */
void RTC_SetVal(uint32_t value);

/**
 * @brief Set the prescale of real-time clock, the value of which it ticks as related to the RTC crystal
 *
 * @param prescale   prescale will determine the accuracy of rtc.
 */
void RTC_SetPrescale(mxc_rtc_prescale_t prescale);

/**
 * @brief Get the current value of the real-time clock counter
 *
 * @return  uint32_t  current real-time timer value. 
 */
uint32_t RTC_GetVal(void);

/**
 * @brief Get the current value of the real-time clock prescale ticks
 *
 * @return  mxc_rtc_prescale_t  current real-time timer prescale.
 */
mxc_rtc_prescale_t RTC_GetPrescale(void);

/**
 * @brief Set a one shot alarm at desired real-time clock timer match
 *
 * @param value           rtc timer match value
 * @param alarm_callback  callback function when the rtc reached the value being
 *
 * @return alarm number, -1 for error
 */
int8_t RTC_SetAlarm(uint32_t value, void (*alarm_callback)(void));

/**
 * @brief Clear the alarm set by RTC_SetAlarm()
 *
 * @param alarm   rtc_alarm returned by RTC_SetAlarm();
 */
void RTC_ClearAlarm(int8_t alarm);

/**
 * @brief Set a continuous alarm at desired real-time clock prescale mask value
 *
 * @param mask            rtc timer prescale mask value
 * @param alarm_callback  callback function when the rtc reached the value being
 *
 * @return alarm number,  -1 for error
 */
int8_t RTC_SetContAlarm(mxc_rtc_prescale_t mask, void(*alarm_callback)(void));

/**
 * @brief Clear a configured continuous alarm set by RTC_SetContAlarm()
 *
 */
void RTC_ClearContAlarm(int8_t alarm_num);

/**
 * @brief Set callback for overflow interrupt
 *
 */
void RTC_SetOvrfInt(void(*overflow_cb)(void));

/**
 * @}
 */

#endif /* _RTC_H */
