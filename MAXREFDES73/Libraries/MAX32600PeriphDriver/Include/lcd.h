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

/* $Revision: 901 $ $Date: 2014-03-25 12:07:16 -0600 (Tue, 25 Mar 2014) $ */

#ifndef _LCD_H
#define _LCD_H
#pragma pack(1)

#include "lcd_regs.h"

/**
 * @file  lcd.h
 * @addtogroup lcd LCD Display Driver
 * @{
 * @brief This is the high level API for the liquid-crystal display driver module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Supported duty cycles for the LCD Controller.
 */
typedef enum lcd_duty_t {
    /** Each pin is dedicated to a single LCD segment. */
    LCD_DUTY_STATIC,
    /** 1/2 duty cycle. Each pin can drive two LCD segments. */
    LCD_DUTY_50,
    /** 1/3 duty cycle. Each pin can drive three LCD segments. */
    LCD_DUTY_33,
    /** 1/4 duty cycle. Each pin can drive four LCD segments. */
    LCD_DUTY_25,
} lcd_duty_t;

/**
 * @brief This function is to be defined in whole by the external device specific driver code.
 *        This is where the device specific driver should decode from the position and display_char
 *        which segments of LCD RAM do write and then call lcd_write() correctly.
 * 
 * @param position position of display.
 * @param display_char character to display.
 */
typedef int32_t (*lcd_display_callback_t)(uint8_t position, uint8_t display_char);

/**
 * @brief Enable the LCD display.
 */
void LCD_Enable(void);

/**
 * @brief Disable the LCD display.
 */
void LCD_Disable(void);

/**
 * @brief Initialize the controller for use with a specific LCD display.
 * 
 * @param segments Number of segments driven by the controller.
 * @param gnd_enable Connect Radj to ground if true.
 * @param frame_rate Display frame rate.
 * @param duty_cydle See \ref{lcd_duty_t} for duty cycle enumerations.
 * @param LCD_DisplayCHar_cb Callback function to write character to display.
 * @param max_length  maximum lcd display length 
 *
 * @return 0 for success
 */
int32_t LCD_Init(uint8_t segments, uint8_t gnd_enable, uint8_t frame_rate, lcd_duty_t duty_cycle, int32_t(*LCD_DisplayChar_cb)(uint8_t position, uint8_t ch), uint8_t max_length);

/**
 * @brief Set the adjustment resistor.  This will change the contrast in the LCD controller waveform generator.
 *
 * @param value resistor value (0-255, four bits of resolution).
 */
void LCD_SetAdjust(uint8_t value);

/**
 * @brief This will clear out all the LCD memory in an atomic way to the external device.
 */
void LCD_Clear(void);

/**
 * @brief Send a full string to the LCD device and activate in an atomic way.
 *
 * @param msg string do display in whole.
 */
int32_t LCD_Display(uint8_t *msg);

/**
 * @brief Write a byte to a specific LCD address.  This is the function that the device specific
 *        function lcd_display_char() should use.
 *
 * @param address LCD RAM address.
 * @param data  LCD RAM data.
 */
void LCD_Write(uint8_t address, uint8_t data);

/**
 * @brief Hold LCD display.
 */
void LCD_Hold(void);

/**
 * @brief Update LCD display.
 */
void LCD_Update(void);

/**
 * @}
 */

#endif /* _LCD_H */
