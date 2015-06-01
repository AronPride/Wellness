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

#ifndef _PULSE_TRAIN_H
#define _PULSE_TRAIN_H

#include "pt_regs.h"

/**
 * @file  pt.h
 * @addtogroup pt Pulse Train
 * @{
 * @brief This is the high level API for the pulse train module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */


/**
 * @brief This function initializes pulse train modules to a known stopped state.
 */
void PT_Init(void);

/**
 * @brief This function configures pulse train module.
 *
 * @param  index  pulse train index
 * @param  rate_control  pulse train output rate
 * @param  mode  sets either square wave or pulse train mode; for pulse train mode, 
 *               defines pulse train length, also, pattern parameter will be used. (range 1-32)
 *
 * @param  pattern  no effect in square wave mode; in pulse train mode, it contains the 
 *                  repeating pattern that will be shifted out as the pulse train output stream
 */
void PT_SetPulseTrain(uint8_t index, uint32_t rate_control, uint8_t mode, uint32_t pattern);

/**
 * @brief Start all pulse train modules together.
 */
void PT_Start(void);

/**
 * @brief Stop all pulse train modules together.
 */
void PT_Stop(void);

/**
 * @brief Resynchronize individual pulse trains together.
 *
 * @param  resync_pts  Mask of pulse train modules that need to be re-synced by bit number.
 *                       Bit0->pt0, Bit1->pt1... etc.
 */
void PT_Resync(uint32_t resync_pts);

/**
 * @}
 */

#endif
