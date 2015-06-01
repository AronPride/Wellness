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

#include "mxc_config.h"

#include "prng.h"
#include "clkman.h"
#include "clkman_regs.h"

int PRNG_Init(void)
{
    mxc_clkman_regs_t *clkman = MXC_CLKMAN;

    /* Start crypto ring, unconditionally */
    CLKMAN_CryptoClockEnable();
    CLKMAN_CryptoClockConfig(MXC_E_CLKMAN_STABILITY_COUNT_2_8_CLKS);

    /* If we find the dividers in anything other than off, don't touch them */
    if (clkman->crypt_clk_ctrl_2_prng == 0) {
      /* Div 1 mode */
      clkman->crypt_clk_ctrl_2_prng = 1;
    }
    if (clkman->clk_ctrl_10_prng == 0) {
      /* Div 1 mode */
      clkman->clk_ctrl_10_prng = 1;
    }

    return 0;
}

uint16_t PRNG_GetSeed(void)
{
  return MXC_TPU->prng_rnd_num;
}

void PRNG_AddUserEntropy(uint8_t entropy)
{
  MXC_TPU->prng_user_entropy = (uint32_t)entropy;
}
