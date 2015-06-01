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

/* $Revision: 2182 $ $Date: 2014-06-04 13:43:33 -0500 (Wed, 04 Jun 2014) $ */

#ifndef _SYSTICK_H
#define _SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file  systick.h
 * @addtogroup Cortex_M3
 * @{
 *        
 */

/**
 * @brief Configure the ARM Cortex internal timer 'systick'
 *
 * @param ticks   number of clock ticks to cause the timer to call the ISR function
 * @param func    set the callback function for every time the timer matches number of 'ticks'
 *
 */
int32_t SysTick_Config(uint32_t ticks, void(*func)(uint32_t));

/**
 * @brief Simple busy wait function to delay execution for a set number of ticks on the systick timer.
 *
 * @param ticks      number of systick timer ticks to wait
 * 
 */
int32_t SysTick_Wait(uint32_t ticks);

#ifdef __cplusplus
}
#endif

/**
 * @}
*/

#endif /* _SYSTICK_H */
