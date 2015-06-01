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

/* $Revision: 2581 $ $Date: 2014-07-10 16:15:29 -0500 (Thu, 10 Jul 2014) $ */

#include "mxc_config.h" /* used to get chip and core includes */

#include <stdint.h>
#include <stdlib.h>

static uint32_t systicks = 0;
static void (*SysTick_Callback)(uint32_t ticks) = NULL;

void SysTick_IRQHandler(void)
{
    systicks++;
    if(SysTick_Callback)
        SysTick_Callback(systicks);
}

static void SysTick_Init(void)
{
    SysTick->CTRL = 0;
    systicks = 0;
    SysTick->VAL = 0; /* Load the SysTick Counter Value */
    SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk   |                       \
                     SysTick_CTRL_ENABLE_Msk);  /* Enable SysTick IRQ and SysTick Timer */   
}

/** Original SysTick_Config is defined in core_cm3.h */
int32_t SysTick_Config(uint32_t ticks, void(*func)(uint32_t))
{
    if(!ticks) /* turn off systick */
    {
        SysTick->CTRL = 0;
        SysTick->LOAD = 0;
        SysTick->VAL = 0;
        systicks = 0;
        return 0;
    }

    if((ticks - 1) > SysTick_LOAD_RELOAD_Msk) 
        return -1;

    SysTick_Callback = func;
    SysTick->LOAD = ticks -1; /* set reload register */
    SysTick_Init();
    return 0;
}

int32_t SysTick_Wait(uint32_t ticks)
{
    if(!ticks || ((ticks - 1) > SysTick_LOAD_RELOAD_Msk))
        return -1;

    if(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)
        return -1;

    if(!(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)) /* SysTick is not running yet */
    {
        SysTick_Callback = NULL;
        SysTick->LOAD = ticks;
        SysTick->VAL = 0;
        SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk);  /* Enable SysTick IRQ and SysTick Timer */   
    }
    uint32_t timeout = 100;

    while(timeout--)
    {
        if(SysTick->VAL)
            break;
    }
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0;

    return 0;
}

