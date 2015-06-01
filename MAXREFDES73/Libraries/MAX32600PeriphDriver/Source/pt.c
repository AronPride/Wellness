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

#include "pt.h"
#include "clkman_regs.h"


void PT_Init(void)
{
    PT_Stop();
}

void PT_SetPulseTrain(uint8_t index, uint32_t rate_control, uint8_t mode, uint32_t pattern)
{
    mxc_pt_regs_t *pt_regs = MXC_PT;
    volatile mxc_pt_rate_length_t *rate = (mxc_pt_rate_length_t *)&(pt_regs + index)->rate_length;

    rate->rate_control = rate_control;
    rate->mode = mode;
    (pt_regs + index)->train = pattern;
}

void PT_Start(void)
{
    MXC_PTG->ctrl_f.enable_all = 1;
}

void PT_Stop(void)
{
    MXC_PTG->ctrl_f.enable_all = 0;
}

void PT_Resync(uint32_t resync_pts)
{
    mxc_ptg_regs_t *regs = MXC_PTG;
    
    regs->resync = resync_pts;
}
