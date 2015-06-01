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

/* $Revision: 4542 $ $Date: 2015-04-03 15:24:02 -0500 (Fri, 03 Apr 2015) $ */

#include "mxc_config.h"

#include "pt.h"
#include "clkman_regs.h"

/*
 * Note:
 *
 * The ARM APB does not support 8 or 16 bit reads/writes, and GCC tries to 
 * be smart about accessing bits within bitfield structs (using byte accesses).
 * Thus, we use temporary variables to change the bits within the register and
 * then write that back in one shot, forcing GCC to use a 32-bit write.
 * 
 */

void PT_Init(void)
{
  PT_Stop();
}

void PT_SetPulseTrain(uint8_t index, uint32_t rate_control, uint8_t mode, uint32_t pattern)
{
  mxc_pt_regs_t *selected_pt = MXC_PT;
  mxc_pt_rate_length_t length_tmp;

  /* Adjust pulse train pointer to desired pulse train index 
   * C will adjust the pointer by index * sizeof(mxc_pt_regs_t)
   * WARNING: This math requires that the structure fully covers each pulse
   * train register area (using padding where appropriate)
   */
  selected_pt += index;

  /* Set up rate and mode. */
  length_tmp.rate_control = rate_control;
  length_tmp.mode = mode;
  selected_pt->rate_length_f = length_tmp;

  /* Insert pattern */
  selected_pt->train = pattern;
}

void PT_Start(void)
{
  mxc_ptg_ctrl_t tmp = MXC_PTG->ctrl_f;

  /* Enable all pulse train engines */
  tmp.enable_all = 1;
  MXC_PTG->ctrl_f = tmp;
}

void PT_Stop(void)
{
  mxc_ptg_ctrl_t tmp = MXC_PTG->ctrl_f;

  /* Disable all pulse train engines */
  tmp.enable_all = 0;
  MXC_PTG->ctrl_f = tmp;
}

void PT_Resync(uint32_t resync_pts)
{
  /* Not using a bit-field, so a direct write is OK */
  MXC_PTG->resync = resync_pts;
}
