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

/* $Revision: 3299 $ $Date: 2014-10-06 18:54:04 -0500 (Mon, 06 Oct 2014) $ */

#include "mxc_config.h"

#include "clkman_regs.h"
#include "icc.h"

void ICC_Enable(void)
{
    mxc_icc_regs_t *regs = MXC_ICC;
    mxc_icc_ctrl_stat_t ctrl_stat = regs->ctrl_stat_f;
    mxc_clkman_clk_gate_ctrl0_t gater0 = MXC_CLKMAN->clk_gate_ctrl0_f;


    /* clock gater must be 'on' not 'dynamic' for cache control */
    gater0.icache_clk_gater = MXC_E_CLKMAN_CLK_GATE_ON;
    MXC_CLKMAN->clk_gate_ctrl0_f = gater0;

    /* invalidate, wait, enable */
    regs->invdt_all = 0xFFFF;
    do {
        ctrl_stat = regs->ctrl_stat_f;
    } while(!ctrl_stat.ready);
    

    ctrl_stat.enable = 1;
    regs->ctrl_stat_f = ctrl_stat;

    /* must invalidate a second time for proper use */
    regs->invdt_all = 1;

    /* clock gater 'dynamic' safe again */
    gater0 = MXC_CLKMAN->clk_gate_ctrl0_f;
    gater0.icache_clk_gater = MXC_E_CLKMAN_CLK_GATE_DYNAMIC;
    MXC_CLKMAN->clk_gate_ctrl0_f = gater0;
}

void ICC_Disable(void)
{
    mxc_icc_ctrl_stat_t ctrl_stat = MXC_ICC->ctrl_stat_f;

    ctrl_stat.enable = 0;
    MXC_ICC->ctrl_stat_f = ctrl_stat;
}
