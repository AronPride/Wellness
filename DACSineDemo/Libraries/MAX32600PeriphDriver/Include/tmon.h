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

#ifndef _TMON_H
#define _TMON_H

/**
 * @file  tmon.h
 * @addtogroup tmon TMON
 * @{
 * @brief This is the high level API for the internal temperature monitor.
 *        
 */

#include "afe_regs.h"

/**
* @brief Enable TMON
*
* @param tmon_select       Internal TMON Circuit = 0, External TMON Circuit to AIN1+ = 1
*/
void TMON_Enable(uint8_t tmon_select);

/**
* @brief Disable TMON
*
*/
void TMON_Disable(void);

/**
* @brief Setup of TMON current
*
* @param tmon_current_val  TMON current value
*
*/
void TMON_SetCurrent(mxc_afe_tmon_current_t tmon_current_val);

/**
 * @}
 */

#endif /* _TMON_H */
