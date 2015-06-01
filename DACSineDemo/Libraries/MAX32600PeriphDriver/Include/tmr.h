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

#ifndef _TIMER_H
#define _TIMER_H

#include "tmr_regs.h"

/**
 * @file  tmr.h
 * @addtogroup timer Timer
 * @{
 * @brief This is the high level API for the general purpose timer module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

typedef struct {
    int8_t index;
    mxc_tmr_mode_t mode;
    uint32_t term;
    uint32_t pwm;
    uint8_t prescale;
    uint8_t polarity;
} tmr32_config_t;

typedef struct {
    int8_t index;
    int8_t sub_index;
    mxc_tmr_mode_t mode;
    uint16_t term;
    uint8_t prescale;
} tmr16_config_t;

/**  
 * @brief unit option for tick passing to timer_setup()
 */
typedef enum { 
    /** nanosecond */
    MXC_E_TMR_PERIOD_UNIT_NANOSEC = 0,
    /** microsecond */
    MXC_E_TMR_PERIOD_UNIT_MICROSEC,
    /** millisecond */
    MXC_E_TMR_PERIOD_UNIT_MILLISEC,
    /** second */
    MXC_E_TMR_PERIOD_UNIT_SEC
} tmr_period_unit_t;

/**
 * @brief Converts a number of ticks and a prescale value to a period and units for the 32-bit timer.
 *
 * @param ticks     number of ticks.
 * @param prescale  timer clock prescale value.
 * @param period    calculated period value.
 * @param units     calculated period units.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR32_TicksToPeriod(uint32_t ticks, uint8_t prescale, uint32_t *period, tmr_period_unit_t *units);

/**
 * @brief Converts a number of ticks and a prescale value to a period and units for the 16-bit timer.
 *
 * @param ticks     number of ticks.
 * @param prescale  timer clock prescale value.
 * @param period    calculated period value.
 * @param units     calculated period units.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR16_TicksToPeriod(uint16_t ticks, uint8_t prescale, uint32_t *period, tmr_period_unit_t *units);

/**
 * @brief Converts a period and units to a number of ticks and a prescale value for the 32-bit timer.
 *
 * @param period    period value.
 * @param unit      period units.
 * @param ticks     calculated number of ticks.
 * @param prescale  calculated timer clock prescale value.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR32_PeriodToTicks(uint32_t period, tmr_period_unit_t unit, uint32_t *ticks, uint8_t *prescale);

/**
 * @brief Converts a period and units to a number of ticks and a prescale value for the 16-bit timer.
 *
 * @param period    period value.
 * @param unit      period units.
 * @param ticks     calculated number of ticks.
 * @param prescale  calculated timer clock prescale value.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR16_PeriodToTicks(uint32_t period, tmr_period_unit_t unit, uint16_t *ticks, uint8_t *prescale);

/**
 * @brief This function will allocate and configure a handle for the 32-bit timer.
 *
 * @param cfg           pointer to tmr32_config_t
 * @param index         timer index (-1 for auto-assign).
 * @param mode          timer mode.
 * @param ticks         period in ticks.
 * @param prescale      clock prescale value.
 * @param duty_cycle    duty cycle (only used for TMR_CTRL_PWM mode).
 * @param polarity      polarity control for pad.
 *
 * @return  0 => Success. Non zero => error condition.
 */
int32_t TMR32_Config(tmr32_config_t *cfg, int32_t index, mxc_tmr_mode_t mode, uint32_t ticks, uint8_t prescale, uint8_t duty_cycle, uint8_t polarity);

/**
 * @brief This function will allocate and configure a handle for the 16-bit timer. Only MXC_E_TMR_CTRL_ONE_SHOT
 *          and MXC_E_TMR_CTRL_CONTINUOUS modes are available for 16-bit timers.
 *
 * @param cfg           pointer to tmr16_config_t
 * @param index         timer index (-1 for auto-assign).
 * @param sub_index     timer sub index (0 or 1).
 * @param mode          timer mode.
 * @param ticks         period in ticks.
 * @param prescale      clock prescale value.
 *
 * @return  0 => Success. Non zero => error condition.
 */
int32_t TMR16_Config(tmr16_config_t *cfg, int32_t index, uint8_t sub_index, mxc_tmr_mode_t mode, uint32_t ticks, uint8_t prescale);

/**
 * @brief This function will start the timer using the configuration handle allocated and returned by TMR32_Config.
 *
 * @param cfg     pointer to tmr32_config_t
 * @param cb_fn   callback function with number of ticks for capture modes.
 *
 * @return  0 => Success. Non zero => error condition.
 */
int32_t TMR32_Start(tmr32_config_t *cfg, void(*cb_fn)(uint32_t ticks));

/**
 * @brief This function will start the timer using the configuration handle allocated and returned by TMR16_Config.
 *
 * @param cfg     pointer to tmr16_config_t
 * @param cb_fn   callback function.
 *
 * @return  0 => Success. Non zero => error condition.
 */
int32_t TMR16_Start(tmr16_config_t *cfg, void(*cb_fn)(void));

/**
 * @brief This function will stop the timer using the configuration handle allocated and returned by TMR32_Config.
 *
 * @param cfg     pointer to tmr32_config_t
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR32_Stop(tmr32_config_t *cfg);

/**
 * @brief This function will stop the timer using the configuration handle allocated and returned by TMR16_Config.
 *
 * @param cfg     pointer to tmr16_config_t
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t TMR16_Stop(tmr16_config_t *cfg);

/**
 * @}
 */

#endif /* _TIMER_H */
