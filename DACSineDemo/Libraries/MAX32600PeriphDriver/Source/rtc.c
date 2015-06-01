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

/* $Revision: 3840 $ $Date: 2015-01-09 16:01:55 -0600 (Fri, 09 Jan 2015) $ */

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
static mxc_rtctmr_flags_t pwr_flg;
static mxc_rtctmr_ctrl_t rtc_ctrl;
mxc_rtctmr_inten_t alarm_int;
mxc_rtctmr_flags_t alarm_flgs;

void RTC_Enable(void)
{
    mxc_rtctmr_ctrl_t ctrl = MXC_RTCTMR->ctrl_f;
    ctrl.enable = 1;
    MXC_RTCTMR->ctrl_f = ctrl;
}

void RTC_Disable(void)
{
    mxc_rtctmr_ctrl_t ctrl = MXC_RTCTMR->ctrl_f;
    ctrl.enable = 0;
    MXC_RTCTMR->ctrl_f = ctrl;
}

void RTC_SetVal(uint32_t value)
{
    RTC_Disable();
    MXC_RTCTMR->timer = value;
    RTC_Enable();
}

void RTC_SetPrescale(mxc_rtc_prescale_t prescale)
{
    MXC_RTCTMR->prescale = prescale;
    pwr_flg = MXC_RTCTMR->flags_f;
    pwr_flg.comp0  = 1;
	MXC_RTCTMR->flags_f = pwr_flg;
	rtc_ctrl = MXC_RTCTMR->ctrl_f;
	while (rtc_ctrl.pending)
	rtc_ctrl = MXC_RTCTMR->ctrl_f;
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
    uint32_t  alarm = MXC_RTCTMR->inten;

    for (i = 0; i < RTC_COMP_NUM; i++)
    {

        alarm_int = MXC_RTCTMR->inten_f;

           if (!(alarm &  i))
           {
        	   rtc_callback_array[i] = alarm_callback;
        	   MXC_RTCTMR->comp[i] = ticks;
        	   MXC_RTCTMR->flags = 0x3F;

        	   if (i == 0)
        	   {

        		   alarm_int.comp0 = 1;
        		   MXC_RTCTMR->inten_f = alarm_int;
        		   NVIC_EnableIRQ(RTC0_IRQn);
        	   }
        	   else
        	   {

        		   alarm_int.comp1 = 1;
        		   MXC_RTCTMR->inten_f = alarm_int;
        		   NVIC_EnableIRQ(RTC1_IRQn);
        	   }
        	   return i;
           }
    }


    return -1;
}

void RTC_ClearAlarm(int8_t alarm)
{
      MXC_RTCTMR->comp[alarm] = 0;
      alarm_int = MXC_RTCTMR->inten_f;
      alarm_flgs =  MXC_RTCTMR->flags_f;
     if (alarm == 0)
     {
         alarm_int.comp0 = 0;
         alarm_flgs.comp0 = 1;
     }
     if (alarm == 1)
     {
         alarm_int.comp1 = 0;
         alarm_flgs.comp1 = 1;
     }
    MXC_RTCTMR->inten_f = alarm_int;
    MXC_RTCTMR->flags_f = alarm_flgs;
}

void RTC2_IRQHandler(void)
{
    #if defined(ASYNC_FLAGS)
		MXC_RTCTMR->flags = 0x80000000;
	#else
	mxc_rtctmr_flags_t flgs = MXC_RTCTMR-> flags_f;
	flgs.prescale_comp = 1;
	MXC_RTCTMR-> flags_f = flgs;
   #endif
    if(prescale_int_cb)
        prescale_int_cb();
}

int8_t RTC_SetContAlarm(mxc_rtc_prescale_t mask, void(*alarm_callback)(void))
{
    MXC_RTCTMR->prescale_mask = mask;
    prescale_int_cb = alarm_callback;
    mxc_rtctmr_inten_t intr = MXC_RTCTMR->inten_f;
    intr.prescale_comp = 1;
    MXC_RTCTMR->inten_f = intr;
    pwr_flg = MXC_RTCTMR->flags_f;
 	pwr_flg.comp0  = 1;
 	MXC_RTCTMR->flags_f = pwr_flg;
     rtc_ctrl = MXC_RTCTMR->ctrl_f;
 	while (rtc_ctrl.pending)
 		rtc_ctrl = MXC_RTCTMR->ctrl_f;
     NVIC_EnableIRQ(RTC2_IRQn);
    return 0;
}

void RTC_ClearContAlarm(int8_t alarm_num)
{
    /* this version has only one cont alarm, param alarm_num unused */
    mxc_rtctmr_inten_t intr = MXC_RTCTMR->inten_f;
	intr.prescale_comp = 0;
	MXC_RTCTMR->inten_f = intr;
}

void RTC3_IRQHandler(void)
{
 	mxc_rtctmr_flags_t flgs = MXC_RTCTMR->flags_f;
 	flgs.overflow = 1;
 	MXC_RTCTMR->flags_f = flgs;
 	mxc_rtctmr_inten_t interrupt = MXC_RTCTMR->inten_f;
 	interrupt.overflow = 0;
	MXC_RTCTMR->inten_f = interrupt;
    if(overflow_int_cb)
        overflow_int_cb();

}

void RTC_SetOvrfInt(void(*overflow_cb)(void))
{
	mxc_rtctmr_inten_t interrupt = MXC_RTCTMR->inten_f;
	interrupt.overflow = 1;
	MXC_RTCTMR->inten_f = interrupt;
    NVIC_EnableIRQ(RTC3_IRQn);
    overflow_int_cb = overflow_cb;
}
