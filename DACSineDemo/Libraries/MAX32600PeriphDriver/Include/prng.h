/*******************************************************************************
* Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
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

/* $Revision: 4125 $ */

#ifndef _PRNG_H
#define _PRNG_H

#include "tpu_regs.h"

/**
 * @file  prng.h
 * @addtogroup prng PRNG
 * @{
 * @brief This is the high level API for the MAX32600 PRNG module
 * @note  The PRNG hardware does not produce true random numbers. The output
 *        should be used as a seed to an approved random-number algorithm, per 
 *        a certifying authority such as NIST or PCI. The approved algorithm
 *        will output random numbers which are cerfitied for use in encryption
 *        and authentication algorithms.
 *        
 */

/**
 * @brief Initialize required clocks and enable PRNG module 
 * @note  Function will set divisors to /1 if they are found disabled.
 *        Otherwise, it will not change the divisor.
 *
 * @return < 0 if error, otherwise success
 */
int PRNG_Init(void);

/**
 * @brief Retrieve a seed value from the PRNG
 * @note  The PRNG hardware does not produce true random numbers. The output
 *        should be used as a seed to an approved random-number algorithm, per 
 *        a certifying authority such as NIST or PCI. The approved algorithm
 *        will output random numbers which are certified for use in encryption
 *        and authentication algorithms.
 *
 * @return This function returns a 16-bit seed value
 */
uint16_t PRNG_GetSeed(void);

/**
 * @brief Add user entropy to the PRNG entropy source
 *
 * @param entropy    This value will be mixed into the PRNG entropy source
 */
void PRNG_AddUserEntropy(uint8_t entropy);

/**
 * @}
 */

#endif /* _PRNG_H */
