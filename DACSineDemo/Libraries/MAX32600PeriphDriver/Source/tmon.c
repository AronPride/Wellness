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

#include "mxc_config.h"

#include "afe.h"

void TMON_SetCurrent(mxc_afe_tmon_current_t tmon_current_val)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.tmon_current_val = tmon_current_val;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void TMON_Enable(uint8_t tmon_select)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.tmon_current_en = 1;
    afe_ctrl1.tmon_ext_sel = tmon_select;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void TMON_Disable(void)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.tmon_current_en = 0;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}
