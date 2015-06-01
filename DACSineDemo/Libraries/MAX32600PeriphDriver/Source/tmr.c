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

/* $Revision: 3743 $ $Date: 2014-12-15 18:11:44 -0600 (Mon, 15 Dec 2014) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "tmr.h"
#include "nvic_table.h"

static uint8_t tmr_mutex_low = 0;
static uint8_t tmr_mutex_high = 0;

static void (*tmr32_callbacks[MXC_CFG_TMR_INSTANCES])(uint32_t ticks) = {0};
static void (*tmr16_callbacks_low[MXC_CFG_TMR_INSTANCES])(void) = {0};
static void (*tmr16_callbacks_high[MXC_CFG_TMR_INSTANCES])(void) = {0};
static uint32_t tmr32_irq_en = 0;
static uint32_t tmr16_irq_en = 0;

int32_t TMR32_TicksToPeriod(uint32_t ticks, uint8_t prescale, uint32_t *period, tmr_period_unit_t *units)
{
    uint64_t temp_period = 0;

    tmr_period_unit_t temp_unit = MXC_E_TMR_PERIOD_UNIT_NANOSEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (SystemCoreClock / 1000000);
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_MICROSEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (SystemCoreClock / 1000);
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_MILLISEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / SystemCoreClock;
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_SEC;
    temp_period = (uint64_t)ticks * (1 << (prescale & 0xF)) / SystemCoreClock;
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    return -1;
}

int32_t TMR32_PeriodToTicks(uint32_t period, tmr_period_unit_t units, uint32_t *ticks, uint8_t *prescale)
{
    uint64_t temp_ticks = 0;
    int8_t temp_prescale = 0;

    switch (units)
    {
        case MXC_E_TMR_PERIOD_UNIT_NANOSEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * (SystemCoreClock / 1000000) / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffff00000000)  && (temp_ticks & 0xffffffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_MICROSEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * (SystemCoreClock / 1000) / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffff00000000) && (temp_ticks & 0xffffffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_MILLISEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * SystemCoreClock / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffff00000000) && (temp_ticks & 0xffffffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_SEC:
            temp_prescale = 12;
            while (temp_prescale >= 0)
            {
                temp_ticks = (uint64_t)period * SystemCoreClock / (1 << (temp_prescale & 0xF));
                if (!(temp_ticks & 0xffffffff00000000) && (temp_ticks & 0xffffffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale--;
            }
            break;
    }
    return -1;
}

int32_t TMR16_TicksToPeriod(uint16_t ticks, uint8_t prescale, uint32_t *period, tmr_period_unit_t *units)
{
    uint64_t temp_period = 0;

    tmr_period_unit_t temp_unit = MXC_E_TMR_PERIOD_UNIT_NANOSEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (SystemCoreClock / 1000000);
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_MICROSEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / (SystemCoreClock / 1000);
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_MILLISEC;
    temp_period = (uint64_t)ticks * 1000 * (1 << (prescale & 0xF)) / SystemCoreClock;
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    temp_unit = MXC_E_TMR_PERIOD_UNIT_SEC;
    temp_period = (uint64_t)ticks * (1 << (prescale & 0xF)) / SystemCoreClock;
    if (!(temp_period & 0xffffffff00000000))
    {
        *period = temp_period;
        *units = temp_unit;
        return 0;
    }

    return -1;
}

int32_t TMR16_PeriodToTicks(uint32_t period, tmr_period_unit_t units, uint16_t *ticks, uint8_t *prescale)
{
    uint64_t temp_ticks = 0;
    int8_t temp_prescale = 0;

    switch (units)
    {
        case MXC_E_TMR_PERIOD_UNIT_NANOSEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * (SystemCoreClock / 1000000) / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffffffff0000) && (temp_ticks & 0xffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_MICROSEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * (SystemCoreClock / 1000) / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffffffff0000) && (temp_ticks & 0xffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_MILLISEC:
            while (temp_prescale <= 0xc)
            {
                temp_ticks = (uint64_t)period * SystemCoreClock / (1000 * (1 << (temp_prescale & 0xF)));
                if (!(temp_ticks & 0xffffffffffff0000) && (temp_ticks & 0xffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale++;
            }
            break;
        case MXC_E_TMR_PERIOD_UNIT_SEC:
            temp_prescale = 12;
            while (temp_prescale >= 0)
            {
                temp_ticks = (uint64_t)period * SystemCoreClock / (1 << (temp_prescale & 0xF));
                if (!(temp_ticks & 0xffffffffffff0000) && (temp_ticks & 0xffff))
                {
                    *ticks = temp_ticks;
                    *prescale = temp_prescale;
                    return 0;
                }
                temp_prescale--;
            }
            break;
    }
    return -1;
}

static void tmr32_irq_handler(void)
{
    uint8_t i;

    for(i = 0; i < MXC_CFG_TMR_INSTANCES; i++)
    {
        if(tmr32_irq_en && (1 << i))
        {
            mxc_tmr_regs_t *regs = MXC_TMR_GET_TMR(i);

            if(regs->intfl) 
            {
                regs->intfl = 3;

                if(tmr32_callbacks[i]) {
                    tmr32_callbacks[i](regs->pwm_cap32);
                }
            }
        }
    }
}

static void tmr16_irq_handler(void)
{
    uint8_t i;

    for(i = 0; i < MXC_CFG_TMR_INSTANCES; i++)
    {
        if(tmr16_irq_en && (1 << i))
        {
            mxc_tmr_regs_t *regs = MXC_TMR_GET_TMR(i);

            if(regs->intfl & 1) 
            {
                regs->intfl = 1;

                if(tmr16_callbacks_low[i]) {
                    tmr16_callbacks_low[i]();
                }
            }
            else if(regs->intfl & 2)
            {
                regs->intfl = 2;

                if(tmr16_callbacks_high[i]) {
                    tmr16_callbacks_high[i]();
                }
            }
        }
    }
}

int32_t TMR32_Start(tmr32_config_t *cfg, void(*cb_fn)(uint32_t ticks))
{
    if (!cfg)
        return -1;

    mxc_tmr_regs_t *regs;
    mxc_tmr_ctrl_t ctrl;
    mxc_tmr_inten_t inten;

    if (cfg->index < MXC_CFG_TMR_INSTANCES)
    {
        if (cfg->index == -1)
        {
            uint8_t i;

            for (i = 0; i < MXC_CFG_TMR_INSTANCES; i++)
            {
                if (!BITBAND_GetBit((uint32_t)&tmr_mutex_low, i) &&     \
                    !BITBAND_GetBit((uint32_t)&tmr_mutex_high, i)) {
                    break;
                }
            }

            if (i == MXC_CFG_TMR_INSTANCES) {
                return -1;
            }

            cfg->index = i;
        }
        regs = MXC_TMR_GET_TMR(cfg->index);
        ctrl = regs->ctrl_f;
        inten = regs->inten_f;

        if (BITBAND_GetBit((uint32_t)&tmr_mutex_low, cfg->index) ||     \
            BITBAND_GetBit((uint32_t)&tmr_mutex_high, cfg->index)) {
            return -1;
        }

        BITBAND_SetBit((uint32_t)&tmr_mutex_low, cfg->index);
        BITBAND_SetBit((uint32_t)&tmr_mutex_high, cfg->index);

        ctrl = regs->ctrl_f;
        ctrl.mode = cfg->mode;
        ctrl.tmr2x16 = 0;
        ctrl.polarity = cfg->polarity;
        ctrl.prescale = cfg->prescale;
        regs->ctrl_f = ctrl;

        ctrl.enable0 = 0;
        regs->ctrl_f = ctrl;

        regs->term_cnt32 = cfg->term;
        regs->pwm_cap32 = cfg->pwm;
        regs->count32 = 0;

        regs->intfl = 3;

        NVIC_SetVector(tmr32_irq_handler, (IRQn_Type)MXC_TMR_GET_IRQ_32(cfg->index));

        inten = regs->inten_f;
        inten.timer0 = 1;
        regs->inten_f = inten;
        tmr32_irq_en |= 1 << cfg->index;

        if (cb_fn) {
            tmr32_callbacks[cfg->index] = cb_fn;
        }

        ctrl.enable0 = 1;
        regs->ctrl_f = ctrl;
        return 0;
    }
    else {
        return -1;
    }
}

int32_t TMR16_Start(tmr16_config_t *cfg, void(*cb_fn)(void))
{
    if (!cfg) {
        return -1;
    }

    mxc_tmr_regs_t *regs;
    mxc_tmr_ctrl_t ctrl;
    mxc_tmr_inten_t inten;

    if (cfg->index < MXC_CFG_TMR_INSTANCES)
    {
        if (cfg->index == -1)
        {
            uint8_t i;

            for (i = 0; i < MXC_CFG_TMR_INSTANCES; i++)
            {
                if (cfg->sub_index == -1)
                {
                    if (!BITBAND_GetBit((uint32_t)&tmr_mutex_low, i))
                    {
                        cfg->sub_index = 0;
                        break;
                    }
                    if (!BITBAND_GetBit((uint32_t)&tmr_mutex_high, i))
                    {
                        cfg->sub_index = 1;
                        break;
                    }
                }
                else
                {
                    if (cfg->sub_index == 0 && !BITBAND_GetBit((uint32_t)&tmr_mutex_low, i)) {
                        break;
                    }

                    if (cfg->sub_index == 1 && !BITBAND_GetBit((uint32_t)&tmr_mutex_high, i)) {
                        break;
                    }
                }
            }

            if (i == MXC_CFG_TMR_INSTANCES)
                return -1;

            cfg->index = i;
        }
        regs = MXC_TMR_GET_TMR(cfg->index);
        ctrl = regs->ctrl_f;
        inten = regs->inten_f;
        tmr16_irq_en |= (1 << cfg->index);

        if (cfg->sub_index == 0)
        {
            if (BITBAND_GetBit((uint32_t)&tmr_mutex_low, cfg->index)) {
                return -1;
            }

            BITBAND_SetBit((uint32_t)&tmr_mutex_low, cfg->index);
        }
        else
        {
            if (BITBAND_GetBit((uint32_t)&tmr_mutex_high, cfg->index)) {
                return -1;
            }

            BITBAND_SetBit((uint32_t)&tmr_mutex_high, cfg->index);
        }

        ctrl = regs->ctrl_f;
        if (cfg->mode)
            ctrl.mode |= cfg->mode << cfg->sub_index;
        else
            ctrl.mode &= ~(cfg->mode << cfg->sub_index);
        ctrl.tmr2x16 = 1;
        ctrl.prescale = cfg->prescale;
        regs->ctrl_f = ctrl;

        if (cfg->sub_index == 0)
        {
            ctrl.enable0 = 0;
            regs->ctrl_f = ctrl;

            regs->term_cnt16_0 = cfg->term;
            regs->count16_0 = 0;

            regs->intfl = 1;

            NVIC_SetVector(tmr16_irq_handler, (IRQn_Type)MXC_TMR_GET_IRQ_16(cfg->index));

            inten = regs->inten_f;
            inten.timer0 = 1;
            regs->inten_f = inten;

            ctrl.enable0 = 1;
            regs->ctrl_f = ctrl;

            if (cb_fn) {
                tmr16_callbacks_low[cfg->index] = cb_fn;
            }
        }
        else
        {
            ctrl.enable1 = 0;
            regs->ctrl_f = ctrl;

            regs->term_cnt16_1 = cfg->term;
            regs->count16_1 = 0;

            regs->intfl = 2;

            NVIC_SetVector(tmr16_irq_handler, (IRQn_Type)MXC_TMR_GET_IRQ_16(cfg->index + 4));

            regs->inten_f;
            inten.timer1 = 1;
            regs->inten_f = inten;

            ctrl.enable1 = 1;
            regs->ctrl_f = ctrl;

            if (cb_fn) {
                tmr16_callbacks_high[cfg->index] = cb_fn;
            }
        }

        return 0;
    }
    else {
        return -1;
    }
}

int32_t TMR32_Stop(tmr32_config_t *cfg)
{
    if (!cfg) {
        return -1;
    }

    mxc_tmr_regs_t *regs = MXC_TMR_GET_TMR(cfg->index);
    mxc_tmr_ctrl_t ctrl = regs->ctrl_f;

    ctrl.enable0 = 0;
    regs->ctrl_f = ctrl;

    BITBAND_ClrBit((uint32_t)&tmr_mutex_low, cfg->index);
    BITBAND_ClrBit((uint32_t)&tmr_mutex_high, cfg->index);
    tmr32_callbacks[cfg->index] = NULL;
    tmr32_irq_en &= ~(1 << cfg->index);

    return 0;
}

int32_t TMR16_Stop(tmr16_config_t *cfg)
{
    if (!cfg) {
        return -1;
    }

    mxc_tmr_regs_t *regs = MXC_TMR_GET_TMR(cfg->index);
    mxc_tmr_ctrl_t ctrl = regs->ctrl_f;

    if (cfg->sub_index == 0)
    {
        ctrl = regs->ctrl_f;
        ctrl.enable0 = 0;
        regs->ctrl_f = ctrl;
        tmr16_callbacks_low[cfg->index] = NULL;

        BITBAND_ClrBit((uint32_t)&tmr_mutex_low, cfg->index);
    }
    else
    {
        ctrl = regs->ctrl_f;
        ctrl.enable1 = 0;
        regs->ctrl_f = ctrl;
        tmr16_callbacks_high[cfg->index] = NULL;

        BITBAND_ClrBit((uint32_t)&tmr_mutex_high, cfg->index);
    }
    tmr16_irq_en &= ~(1 << cfg->index);

    return 0;
}

int32_t TMR32_Config(tmr32_config_t *cfg, int32_t index, mxc_tmr_mode_t mode, uint32_t ticks, uint8_t prescale, uint8_t duty_cycle, uint8_t polarity)
{
    if (index > MXC_CFG_TMR_INSTANCES) {
        return -1;
    }

    memset(cfg, 0, sizeof(tmr32_config_t));
    cfg->index = index;
    cfg->mode = mode;
    cfg->polarity = polarity;
    cfg->prescale = prescale;
    cfg->term = ticks;
    if (mode == MXC_E_TMR_MODE_PWM) {
        cfg->pwm = ticks - (duty_cycle * ticks / 100);
    }
    else {
        cfg->pwm = 0;
    }

    return 0;
}

int32_t TMR16_Config(tmr16_config_t *cfg, int32_t index, uint8_t sub_index, mxc_tmr_mode_t mode, uint32_t ticks, uint8_t prescale)
{
    if (index > MXC_CFG_TMR_INSTANCES) {
        return -1;
    }

    if (sub_index > 1) {
        return -1;
    }

    memset(cfg, 0, sizeof(tmr16_config_t));
    cfg->index = index;
    cfg->sub_index = sub_index;
    cfg->mode = mode;
    cfg->prescale = prescale;
    cfg->term = ticks;

    return 0;
}
