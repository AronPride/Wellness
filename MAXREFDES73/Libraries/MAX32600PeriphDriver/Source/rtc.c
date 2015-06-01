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

/* $Revision: 2581 $ $Date: 2014-07-10 15:15:29 -0600 (Thu, 10 Jul 2014) $ */

#include "mxc_config.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rtc.h"
#include "nvic_table.h"

#define RTC_COMP_NUM 2
static void(*rtc_callback_array[RTC_COMP_NUM])(void) = {0};
static void(*prescale_int_cb)(void);
static void(*overflow_int_cb)(void); 

void RTC_Enable(void)
{
    MXC_RTCTMR->ctrl_f.enable = 1;
}

void RTC_Disable(void)
{
    MXC_RTCTMR->ctrl_f.enable = 0;
}

void RTC_SetVal(uint32_t value)
{
    MXC_RTCTMR->ctrl_f.enable = 0;
    MXC_RTCTMR->timer = value;
    MXC_RTCTMR->ctrl_f.enable = 1;
}

void RTC_SetPrescale(mxc_rtc_prescale_t prescale)
{
    MXC_RTCTMR->prescale = prescale;
}

uint32_t RTC_GetVal(void)
{
    return (MXC_RTCTMR->timer);
}

mxc_rtc_prescale_t RTC_GetPrescale(void)
{
    return MXC_RTCTMR->prescale;
}

/* setup with 'weak' link in linker */
void RTC0_IRQHandler(void)
{
    RTC_ClearAlarm(0);
    if (rtc_callback_array[0])
    {
        rtc_callback_array[0]();
    }
}

/* setup with 'weak' link in linker */
void RTC1_IRQHandler(void)
{
    RTC_ClearAlarm(1);
    if (rtc_callback_array[1])
    {
        rtc_callback_array[1]();
    }
}

int8_t RTC_SetAlarm(uint32_t ticks, void (*alarm_callback)(void))
{
    uint8_t i;

    for (i = 0; i < RTC_COMP_NUM; i++)
    {
        if (!(BITBAND_GetBit((uint32_t)&MXC_RTCTMR->inten, i)))
        {
            rtc_callback_array[i] = alarm_callback;
            MXC_RTCTMR->comp[i] = ticks;
            MXC_RTCTMR->flags = 0x3F;
            BITBAND_SetBit((uint32_t)&MXC_RTCTMR->inten, i);
            if(i==0)
                NVIC_EnableIRQ(RTC0_IRQn);
            else
                NVIC_EnableIRQ(RTC1_IRQn);
            return i;
        }
    }
    return -1;
}

void RTC_ClearAlarm(int8_t alarm)
{
    MXC_RTCTMR->comp[alarm] = 0;
    BITBAND_ClrBit((uint32_t)&MXC_RTCTMR->inten, alarm);
    BITBAND_SetBit((uint32_t)&MXC_RTCTMR->flags, alarm);
}

void RTC2_IRQHandler(void)
{
    BITBAND_SetBit((uint32_t)&MXC_RTCTMR->flags, 2);
    if(prescale_int_cb)
        prescale_int_cb();
}

int8_t RTC_SetContAlarm(mxc_rtc_prescale_t mask, void(*alarm_callback)(void))
{
    MXC_RTCTMR->prescale_mask = mask;
    prescale_int_cb = alarm_callback;
    BITBAND_SetBit((uint32_t)&MXC_RTCTMR->inten, 2);
    NVIC_EnableIRQ(RTC2_IRQn);
    return 0;
}

void RTC_ClearContAlarm(int8_t alarm_num)
{
    /* this version has only one cont alarm, param alarm_num unused */
    BITBAND_ClrBit((uint32_t)&MXC_RTCTMR->inten, 2);
}

void RTC3_IRQHandler(void)
{
    BITBAND_SetBit((uint32_t)&MXC_RTCTMR->flags, 3);
    BITBAND_ClrBit((uint32_t)&MXC_RTCTMR->inten, 3);
    if(overflow_int_cb)
        overflow_int_cb();

}

void RTC_SetOvrfInt(void(*overflow_cb)(void))
{
    BITBAND_SetBit((uint32_t)&MXC_RTCTMR->inten, 3);
    NVIC_EnableIRQ(RTC3_IRQn);
    overflow_int_cb = overflow_cb;
}
