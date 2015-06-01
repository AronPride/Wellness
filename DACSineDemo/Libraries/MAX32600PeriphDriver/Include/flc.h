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

#ifndef _FLASH_H
#define _FLASH_H

#include "flc_regs.h"

/**
 * @file  flc.h
 * @addtogroup flash Flash Controller
 * @{
 * @brief This is the high level API for the internal flash controller module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief This function will erase a single page of flash, 1 page is
 * 2K bytes.  Keys needed for flash are in the hardware specific
 * register file "flc_regs.h" 
 *
 * @param address     Start address that needs to be erased, must be aligned with 0x800
 * @param erase_code  Flash erase code; defined as 'MXC_V_FLC_ERASE_CODE_PAGE_ERASE' for page erase
 * @param unlock_key  Key necessary for accessing flash; defined as 'MXC_V_FLC_FLSH_UNLOCK_KEY' 
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t FLC_Erase(uint32_t address, uint8_t erase_code, uint8_t unlock_key);

/**
 * @brief This function writes data to the flash device through flash controller
 *
 * @param address     Start address that needs to be written, must be aligned with 4 bytes
 * @param data        Pointer to the buffer containing data to write
 * @param length      Size of the data to write in bytes, must be multiple of 4 bytes
 * @param unlock_key  Key necessary for accessing flash; defined as 'MXC_V_FLC_FLSH_UNLOCK_KEY'
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t FLC_WriteBlock(uint32_t address, const void *data, uint32_t length, uint8_t unlock_key);

/**
 * @}
 */

#endif
