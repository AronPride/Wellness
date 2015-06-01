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

#include <stdlib.h>

#include "wdt.h"
#include "nvic_table.h"

typedef struct {
    int8_t index;
    int8_t int_period;
    int8_t wait_period;
    int8_t rst_period;
} wdt_config_t;

static uint8_t wdt_mutex = 0;

int32_t WDT_EnableInt(uint8_t index, mxc_wdt_period_t int_period, void(*int_cb_fn)(void), uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        if (!int_cb_fn)
        {
            return -1;
        }

        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_ctrl_t ctrl = wdt_regs->ctrl_f;
        ctrl.int_period = int_period;
        wdt_regs->ctrl_f = ctrl;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        NVIC_SetVector(int_cb_fn, (IRQn_Type)MXC_WDT_GET_IRQ(index));
        int_rst_en.ie_timeout = 1;
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_DisableInt(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        int_rst_en.ie_timeout = 0;
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_EnableWait(uint8_t index, mxc_wdt_period_t wait_period, void(*prewin_cb_fn)(void), uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        if (!prewin_cb_fn)
        {
            return -1;
        }

        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_ctrl_t ctrl = wdt_regs->ctrl_f;
        ctrl.wait_period = wait_period;
        wdt_regs->ctrl_f = ctrl;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        NVIC_SetVector(prewin_cb_fn, (IRQn_Type)MXC_WDT_GET_IRQ_P(index));
        int_rst_en.prewin_reset0_en = 1;
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_DisableWait(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        int_rst_en.prewin_reset0_en = 0;
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_EnableReset(uint8_t index, mxc_wdt_period_t rst_period, uint8_t reboot, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_ctrl_t ctrl = wdt_regs->ctrl_f;
        ctrl.rst_period = rst_period;
        wdt_regs->ctrl_f = ctrl;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        if (reboot)
        {
            int_rst_en.wdt_reset1_en = 1;
        }
        else
        {
            int_rst_en.wdt_reset0_en = 1;
        }
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_DisableReset(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_int_rst_en_t int_rst_en = wdt_regs->int_rst_en_f;
        int_rst_en.wdt_reset1_en = 0;
        int_rst_en.wdt_reset0_en = 0;
        wdt_regs->int_rst_en_f = int_rst_en;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_Start(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        if (BITBAND_GetBit((uint32_t)&wdt_mutex, index))
        {
            return -1;
        }

        BITBAND_SetBit((uint32_t)&wdt_mutex, index);

        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_ctrl_t ctrl = wdt_regs->ctrl_f;

        ctrl.en_timer = 0;
        ctrl.en_clock = 1;
        wdt_regs->ctrl_f = ctrl;
        wdt_regs->int_rst_fl = 0xffffffff;

        ctrl.en_timer = 1;
        wdt_regs->ctrl_f = ctrl;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_Reset(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES)
    {
        if (!BITBAND_GetBit((uint32_t)&wdt_mutex, index))
        {
            return -1;
        }

        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        wdt_regs->clear = 0xA5;
        wdt_regs->clear = 0x5A;

        wdt_regs->int_rst_fl = 0xffffffff;

        wdt_regs->lock_ctrl = lock_key;

        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t WDT_Stop(uint8_t index, uint8_t unlock_key, uint8_t lock_key)
{
    if (index < MXC_CFG_WDT_INSTANCES) 
    {
        if (!BITBAND_GetBit((uint32_t)&wdt_mutex, index))
        {
            return -1;
        }

        mxc_wdt_regs_t *wdt_regs = MXC_WDT_GET_WDT(index);

        wdt_regs->lock_ctrl = unlock_key;

        mxc_wdt_ctrl_t ctrl = wdt_regs->ctrl_f;
        ctrl.en_timer = 0;
        wdt_regs->ctrl_f = ctrl;
        wdt_regs->int_rst_en = 0;

        ctrl.en_clock = 0;
        wdt_regs->ctrl_f = ctrl;

        wdt_regs->lock_ctrl = lock_key;

        BITBAND_ClrBit((uint32_t)&wdt_mutex, index);

        return 0;
    }
    else
    {
        return -1;
    }
}
