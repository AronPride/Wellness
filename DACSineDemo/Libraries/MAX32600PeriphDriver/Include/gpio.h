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

/* $Revision: 3630 $ $Date: 2014-11-24 17:25:27 -0600 (Mon, 24 Nov 2014) $ */

#ifndef _GPIO_H
#define _GPIO_H

#include "gpio_regs.h"

/**
 * @file  gpio.h
 * @addtogroup gpio GPIO
 * @{
 * @brief This is the high level API for the general-purpose input/output module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Defines the condition needed to generate an interrupt for a given GPIO pin.
 */
typedef enum {
    /** no interrupt generation */
    MXC_E_GPIO_INT_MODE_DISABLE = 0,
    /** falling edge detect */
    MXC_E_GPIO_INT_MODE_FALLING_EDGE,
    /** rising edge detect */
    MXC_E_GPIO_INT_MODE_RISING_EDGE,
    /** any edge detect */
    MXC_E_GPIO_INT_MODE_ANY_EDGE,
    /** low level detect */
    MXC_E_GPIO_INT_MODE_LOW_LVL,
    /** high level detect */
    MXC_E_GPIO_INT_MODE_HIGH_LVL
} gpio_int_mode_t;

/**
 * @brief Controls how the logical input value is determined for a given GPIO pin.
 *        This input value will also be used for interrupt detection if that has been enabled
 *        for the GPIO pin in question.
 */
typedef enum {
    /** Normal mode: low logic level translates to 0, high logic level translates to 1 */
    MXC_E_GPIO_IN_MODE_NORMAL = 0,
    /** Inverted mode: low logic level translates to 1, high logic level translates to 0 */
    MXC_E_GPIO_IN_MODE_INVERTED,
    /** A zero value will always be returned for this pin's input regardless of the voltage level present at the pin */
    MXC_E_GPIO_IN_MODE_ALWAYS_ZERO,
    /** A one value will always be returned for this pin's input regardless of the voltage level present at the pin */    
    MXC_E_GPIO_IN_MODE_ALWAYS_ONE
} gpio_in_mode_t;

/**
 * @brief Output drive mode of output. Defines drive state as modified by output setting of 0/1.
 */
typedef enum {
    /** Wk1/Hiz */
    MXC_E_GPIO_OUT_MODE_TRISTATE = 0,
    /** Hiz/Dr0 */
    MXC_E_GPIO_OUT_MODE_OPEN_DRAIN,
    /** Wk1/Dr0 */
    MXC_E_GPIO_OUT_MODE_OPEN_DRAIN_W_PULLUP,
    /** Unused */
    MXC_E_GPIO_OUT_MODE_TS,
    /** HiZ/Hiz */
    MXC_E_GPIO_OUT_MODE_NORMAL_TRISTATE,
    /** Dr1/Dr0 */
    MXC_E_GPIO_OUT_MODE_NORMAL,
    /** HiZ/Hiz */
    MXC_E_GPIO_OUT_MODE_SLOW_TRISTATE,
    /** Dr1/Dr0 */
    MXC_E_GPIO_OUT_MODE_SLOW,
    /** HiZ/Hiz */
    MXC_E_GPIO_OUT_MODE_FAST_TS,
    /** Dr1/Dr0 */
    MXC_E_GPIO_OUT_MODE_FAST
} gpio_out_mode_t;

/**
 * @brief Sets the output mode for the selected GPIO pin.
 *
 * @param  port  desired gpio port. 
 * @param  pin   desired gpio pin. 
 * @param  val   gpio output mode.
 *
 * @return 0 => Success. Non zero => error condition.
 */
void GPIO_SetOutMode(uint8_t port, uint8_t pin, gpio_out_mode_t val);

/**
 * @brief Sets the GPIO function select for the given GPIO pin.  This setting is only effective if the
 *           GPIO pin in question is in 'GPIO mode', which means that the GPIO pin has not been requested
 *           for use by a higher priority function such as SPI, I2C, UART, LCD, etc.
 *
 * @param  port  Selects GPIO port (starting at 0 for P0, 1 for P1, and so on)
 * @param  pin   Selects pin within the selected GPIO port, from 0 to 7.
 * @param  val   select field for selection of one a parameterized number of functions (Max 16, Min 2) 
 *                      which can control pad if owned by GPIO function. 
 * @see IOMUX matrix (gpio: firmware control; pt: pulse train; tmr: 32-bits timer)
 *
 * @verbatim
 *
 *   val-=>   0       1       2       3       4       5       6       7
 *          ------  ------  ------  ------  ------  ------  ------  ------  
 *   P0.0:   gpio    pt0     pt0     pt4     tmr0    tmr1    tmr2    tmr3
 *   P0.1:   gpio    pt1     pt4     pt0     tmr1    tmr2    tmr3    tmr0
 *   P0.2:   gpio    pt2     pt1     pt5     tmr2    tmr3    tmr0    tmr1
 *   P0.3:   gpio    pt3     pt5     pt1     tmr3    tmr0    tmr1    tmr2
 *   P0.4:   gpio    pt4     pt2     pt6     tmr0    tmr1    tmr2    tmr3
 *   P0.5:   gpio    pt5     pt6     pt2     tmr1    tmr2    tmr3    tmr0
 *   P0.6:   gpio    pt6     pt3     pt7     tmr2    tmr3    tmr0    tmr1
 *   P0.7:   gpio    pt7     pt7     pt3     tmr3    tmr0    tmr1    tmr2
 *   P1.0:   gpio    pt0     pt0     pt4     tmr0    tmr1    tmr2    tmr3
 *   P1.1:   gpio    pt1     pt4     pt0     tmr1    tmr2    tmr3    tmr0
 *   P1.2:   gpio    pt2     pt1     pt5     tmr2    tmr3    tmr0    tmr1
 *   P1.3:   gpio    pt3     pt5     pt1     tmr3    tmr0    tmr1    tmr2
 *   P1.4:   gpio    pt4     pt2     pt6     tmr0    tmr1    tmr2    tmr3
 *   P1.5:   gpio    pt5     pt6     pt2     tmr1    tmr2    tmr3    tmr0
 *   P1.6:   gpio    pt6     pt3     pt7     tmr2    tmr3    tmr0    tmr1
 *   P1.7:   gpio    pt7     pt7     pt3     tmr3    tmr0    tmr1    tmr2
 *   P2.0:   gpio    pt0     pt0     pt4     tmr0    tmr1    tmr2    tmr3
 *   P2.1:   gpio    pt1     pt4     pt0     tmr1    tmr2    tmr3    tmr0
 *   P2.2:   gpio    pt2     pt1     pt5     tmr2    tmr3    tmr0    tmr1
 *   P2.3:   gpio    pt3     pt5     pt1     tmr3    tmr0    tmr1    tmr2
 *   P2.4:   gpio    pt4     pt2     pt6     tmr0    tmr1    tmr2    tmr3
 *   P2.5:   gpio    pt5     pt6     pt2     tmr1    tmr2    tmr3    tmr0
 *   P2.6:   gpio    pt6     pt3     pt7     tmr2    tmr3    tmr0    tmr1
 *   P2.7:   gpio    pt7     pt7     pt3     tmr3    tmr0    tmr1    tmr2
 *   P6.0:   gpio    pt0     pt0     pt4     tmr0    tmr1    tmr2    tmr3
 *   P6.1:   gpio    pt1     pt4     pt0     tmr1    tmr2    tmr3    tmr0
 *   P6.2:   gpio    pt2     pt1     pt5     tmr2    tmr3    tmr0    tmr1
 *   P6.3:   gpio    pt3     pt5     pt1     tmr3    tmr0    tmr1    tmr2
 *   P6.4:   gpio    pt4     pt2     pt6     tmr0    tmr1    tmr2    tmr3
 *   P6.5:   gpio    pt5     pt6     pt2     tmr1    tmr2    tmr3    tmr0
 *   P6.6:   gpio    pt6     pt3     pt7     tmr2    tmr3    tmr0    tmr1
 *   P6.7:   gpio    pt7     pt7     pt3     tmr3    tmr0    tmr1    tmr2
 *   P7.0:   gpio    pt0     pt0     pt4     tmr0    tmr1    tmr2    tmr3
 *   P7.1:   gpio    pt1     pt4     pt0     tmr1    tmr2    tmr3    tmr0
 *   P7.2:   gpio    pt2     pt1     pt5     tmr2    tmr3    tmr0    tmr1
 *   P7.3:   gpio    pt3     pt5     pt1     tmr3    tmr0    tmr1    tmr2
 *   P7.4:   gpio    pt4     pt2     pt6     tmr0    tmr1    tmr2    tmr3
 *   P7.5:   gpio    pt5     pt6     pt2     tmr1    tmr2    tmr3    tmr0
 *   P7.6:   gpio    pt6     pt3     pt7     tmr2    tmr3    tmr0    tmr1
 *   P7.7:   gpio    pt7     pt7     pt3     tmr3    tmr0    tmr1    tmr2
 *
 * @endverbatim
 */
void GPIO_SetFuncSel(uint8_t port, uint8_t pin, uint8_t val);

/**
 * @brief This function will set gpio input mode.
 *
 * @param  port  desired gpio port. 
 * @param  pin   desired gpio pin. 
 * @param  val   gpio input mode
 */
void GPIO_SetInMode(uint8_t port, uint8_t pin, gpio_in_mode_t val);

/**
 * @brief This function will set gpio out value.
 *
 * @param  port  desired gpio port. 
 * @param  pin   desired gpio pin. 
 * @param  val   set 1 to high level; 0 to low level.
 */
void GPIO_SetOutVal(uint8_t port, uint8_t pin, uint32_t val);

/**
 * @brief Returns the logical input value (as configured by GPIO_SetInMode()) for the selected GPIO pin.
 *
 * @param  port  desired gpio port. 
 * @param  pin   desired gpio pin.
 *
 * @return  current value on this pin, as defined by GPIO_IN_MODE
 */
uint32_t GPIO_GetInVal(uint8_t port, uint8_t pin);

/**
 * @brief This function will set gpio interrupt mode and register interrupt callback function.
 *
 * @param  port         desired gpio port. 
 * @param  pin          desired gpio pin. 
 * @param  val          gpio interrupt mode
 * @param  gpio_irq_cb  gpio interrupt callback function. If NULL, no ARM interrupt is generated.  Useful for configuring internal signaling to the PMU.
 */
void GPIO_SetIntMode(uint8_t port, uint8_t pin, gpio_int_mode_t val, void(*gpio_irq_cb)(void));

/**
 * @}
 */

#endif /* _GPIO_H */
