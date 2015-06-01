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

/* $Revision: 959 $ $Date: 2014-03-28 11:00:35 -0600 (Fri, 28 Mar 2014) $ */

#include "mxc_config.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lcd_regs.h"
#include "lcd.h"

static int32_t(*driver_callback)(uint8_t i, uint8_t ch) = NULL;
static uint8_t max_lcd_length;

int32_t LCD_DisplayChar(uint8_t i, uint8_t ch)
{
    if(driver_callback)
        return driver_callback(i, ch);
    return 0;
}

void LCD_Hold(void) {
    mxc_lcd_lcfg_t lcfg = MXC_LCD->lcfg_f;
    lcfg.datahold = 1;
    MXC_LCD->lcfg_f = lcfg;
}

void LCD_Update(void) {
    mxc_lcd_lcfg_t lcfg = MXC_LCD->lcfg_f;
    lcfg.datahold = 0;
    MXC_LCD->lcfg_f = lcfg;
}

void LCD_Write(uint8_t address, uint8_t data)
{
    MXC_LCD->lcaddr = address;
    MXC_LCD->lcdata= data;
}

void LCD_Clear(void)
{
    uint8_t i;

    for (i = 0; i < MXC_LCD_ADDRESS_SEGS; i++)
    {
        MXC_LCD->lcaddr = i;
        MXC_LCD->lcdata = 0;
    }
}


int32_t LCD_Display(uint8_t *msg)
{
    uint8_t i;

    LCD_Hold();
    LCD_Clear();
    for (i = 0; i < max_lcd_length; i++) {
        if(msg[i] == '\0') {
            break;
        }
        LCD_DisplayChar(i, msg[i]);
    }
    LCD_Update();

    return 0;
}

void LCD_Enable()
{
    mxc_lcd_lpwrctrl_t pwrctrl = MXC_LCD->lpwrctrl_f;
    mxc_lcd_lcfg_t lcfg = MXC_LCD->lcfg_f;

    pwrctrl.powerup = 1;
    MXC_LCD->lpwrctrl_f = pwrctrl;

    lcfg.operating_mode = 1;
    lcfg.lcd_en = 1;
    MXC_LCD->lcfg_f = lcfg;
}

void LCD_Disable()
{
    mxc_lcd_lpwrctrl_t pwrctrl = MXC_LCD->lpwrctrl_f;
    mxc_lcd_lcfg_t lcfg = MXC_LCD->lcfg_f;

    pwrctrl.powerup = 0;
    MXC_LCD->lpwrctrl_f = pwrctrl;
    
    lcfg.operating_mode = 0;
    lcfg.lcd_en = 0;
    MXC_LCD->lcfg_f = lcfg;
}

void LCD_SetAdjust(uint8_t value)
{
    mxc_lcd_lcra_t lcra = MXC_LCD->lcra_f;

    lcra.reg_adj = value;
    MXC_LCD->lcra_f = lcra;
}

int32_t LCD_Init(uint8_t segments, uint8_t gnd_enable, uint8_t frame_rate, lcd_duty_t duty_cycle, int32_t(*callback)(uint8_t position, uint8_t ch), uint8_t max_length)
{
    mxc_lcd_lpwrctrl_t pwrctrl = MXC_LCD->lpwrctrl_f;
    mxc_lcd_lcra_t lcra = MXC_LCD->lcra_f;
    uint32_t lpcf = 0;
    int seg_regs = (int)(segments >> 1);

    if (!callback)
        return -1;

    driver_callback = callback;

    pwrctrl.highbat_startup = 1;
    pwrctrl.bias_powerup = 1;
    pwrctrl.enbg_4_lcd = 1;
    pwrctrl.lcd_vsel = 2;
    MXC_LCD->lpwrctrl_f= pwrctrl;

    do
    {
        lpcf = (lpcf << 1) | 1;
        seg_regs--;
    } while (seg_regs);

    MXC_LCD->lpcf = lpcf;

    lcra.duty_cycle = duty_cycle;
    lcra.frame_rate = frame_rate;
    lcra.gnd_en = gnd_enable;
    MXC_LCD->lcra_f = lcra;

    max_lcd_length = max_length;

    return 0;
}
