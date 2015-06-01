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

/* $Revision: 4040 $ $Date: 2015-01-20 09:41:44 -0600 (Tue, 20 Jan 2015) $ */

#include "mxc_config.h"

#include "clkman.h"
#include "pwrseq_regs.h"
#include "adc_regs.h"
#include "systick.h"
#include "rtc.c"
#include "power.c"

static inline uint8_t hfx_valid()
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_config.hfx_enable != 0 || clkman_clk_config.hfx_bypass != 0) {
        return TRUE;
    }

    return FALSE;
}

int32_t CLKMAN_HFXConfig(uint8_t hfx_bypass, uint8_t hfx_gm_adjust, uint8_t hfx_dc_control)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_config.hfx_enable) {
        return -1;
    }

    clkman_clk_config.hfx_enable = 0;
    clkman_clk_config.hfx_bypass = hfx_bypass;
    clkman_clk_config.hfx_test_enable = 0;
    clkman_clk_config.hfx_gm_adjust = hfx_gm_adjust;
    clkman_clk_config.hfx_dc_control = hfx_dc_control;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    return 0;
}

void CLKMAN_HFXEnable(void)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (!clkman_clk_config.hfx_bypass) {
        clkman_clk_config.hfx_enable = 1;
    }

    MXC_CLKMAN->clk_config_f = clkman_clk_config;
}

int32_t CLKMAN_HFXDisable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_ctrl.system_source_select == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX) {
        return -1;
    }

    if (clkman_clk_ctrl.system_source_select == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2 &&
        clkman_clk_config.pll_input_select == MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX) {
        return -1;
    }

    clkman_clk_config.hfx_enable = 0;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    return 0;
}

int32_t CLKMAN_PLLConfig(mxc_clkman_pll_input_select_t pll_input_select,
        mxc_clkman_pll_divisor_select_t pll_divisor_select,
        mxc_clkman_stability_count_t pll_stability_count,
        uint8_t pll_bypass, uint8_t pll_8mhz_enable)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_config.pll_enable) {
        return -1;
    }

    if (pll_input_select == MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX && !hfx_valid()) {
        return -1;
    }

    clkman_clk_config.pll_enable = 0;
    clkman_clk_config.pll_reset_n = 0;
    clkman_clk_config.pll_input_select = pll_input_select;
    clkman_clk_config.pll_divisor_select = pll_divisor_select;
    clkman_clk_config.pll_8mhz_enable = pll_8mhz_enable;
    clkman_clk_config.pll_bypass = pll_bypass;
    clkman_clk_config.pll_stability_count = pll_stability_count;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    return 0;
}

void CLKMAN_PLLEnable(void)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    clkman_clk_config.pll_enable = 1;
    clkman_clk_config.pll_reset_n = 1;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;
}

int32_t CLKMAN_PLLDisable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_ctrl.system_source_select == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2) {
        return -1;
    }

    clkman_clk_config.pll_enable = 0;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    return 0;
}


static uint8_t running;

void CLKMAN_TrimRO_Start(void)
{
    mxc_pwrseq_reg0_t reg0 = MXC_PWRSEQ->reg0_f;
    mxc_adc_ro_cal0_t ro_cal0 = MXC_ADCCFG->ro_cal0_f;
    mxc_adc_ro_cal1_t ro_cal1 = MXC_ADCCFG->ro_cal1_f;
    mxc_pwrseq_reg5_t reg5 = MXC_PWRSEQ->reg5_f;

    running = reg0.pwr_rtcen_run;
    reg0.pwr_rtcen_run = 1;
    MXC_PWRSEQ->reg0_f = reg0;

    /* needed if parts are untrimmed */
    if ((reg5.pwr_trim_osc_vref == 0) | (reg5.pwr_trim_osc_vref == 127)){
        reg5.pwr_trim_osc_vref = 16;
        MXC_PWRSEQ->reg5_f = reg5;
    }
    ro_cal1.trm_init = (reg5.pwr_trim_osc_vref << 2);
    MXC_ADCCFG->ro_cal1_f = ro_cal1;
    ro_cal0.trm_mu = 0x04;
    MXC_ADCCFG->ro_cal0_f = ro_cal0;
    ro_cal0.ro_cal_load = 1;
    MXC_ADCCFG->ro_cal0_f = ro_cal0;
    ro_cal0.ro_cal_en = 1;
    MXC_ADCCFG->ro_cal0_f = ro_cal0;
    ro_cal0.ro_cal_run = 1;
    MXC_ADCCFG->ro_cal0_f = ro_cal0;
}

void CLKMAN_TrimRO_Stop(void)
{
    uint32_t trim;
    uint32_t reg;
    mxc_pwrseq_reg5_t reg5;
    mxc_pwrseq_reg0_t reg0 = MXC_PWRSEQ->reg0_f;

    trim = MXC_ADCCFG->ro_cal0_f.ro_trm;
    reg = MXC_ADCCFG->ro_cal0;
    reg = reg & 0xfffffffe;
    MXC_ADCCFG->ro_cal0 = reg;
    reg5.pwr_trim_osc_vref = (trim >> 2);
    MXC_PWRSEQ->reg5_f = reg5;

    reg0.pwr_rtcen_run = running;
    MXC_PWRSEQ->reg0_f = reg0;
}


int32_t CLKMAN_SetSystemClock(mxc_clkman_system_source_select_t system_source_select)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (system_source_select == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX && !hfx_valid()) {
        return -1;
    }

    if (system_source_select == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2) {
        if (!clkman_clk_config.pll_enable) {
            return -1;
        }
        if (clkman_clk_config.pll_input_select == MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX && !hfx_valid()) {
            return -1;
        }
    }

    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    clkman_clk_ctrl.system_source_select = system_source_select;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;

    return 0;
}

void CLKMAN_WaitForSystemClockStable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    mxc_clkman_system_source_select_t source = clkman_clk_ctrl.system_source_select;

    MXC_CLKMAN->intfl = 0x7;

    if (source == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2) {
        mxc_clkman_pll_input_select_t pll_source = clkman_clk_config.pll_input_select;
        mxc_clkman_intfl_t temp;

        if (pll_source == MXC_E_CLKMAN_PLL_INPUT_SELECT_24MHZ_RO) {
            temp = MXC_CLKMAN->intfl_f;
            while (!temp.ring_stable)
                temp = MXC_CLKMAN->intfl_f;
        }

        temp = MXC_CLKMAN->intfl_f;
        while (!temp.pll_stable)
            temp = MXC_CLKMAN->intfl_f;
    }
    else if (source == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO || source == MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO_DIV_8) {
        mxc_clkman_intfl_t temp = MXC_CLKMAN->intfl_f;
        while (!temp.ring_stable)
            temp = MXC_CLKMAN->intfl_f;
    }
}

void CLKMAN_USBClockEnable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    clkman_clk_ctrl.usb_gate_n = 1;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
}

void CLKMAN_USBClockDisable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    clkman_clk_ctrl.usb_gate_n = 0;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
}

int32_t CLKMAN_CryptoClockConfig(mxc_clkman_stability_count_t crypto_stability_count)
{
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    if (clkman_clk_config.crypto_enable) {
        return -1;
    }

    clkman_clk_config.crypto_enable = 0;
    clkman_clk_config.crypto_reset_n = 0;
    clkman_clk_config.crypto_stability_count = crypto_stability_count;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    return 0;
}

void CLKMAN_CryptoClockEnable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    mxc_clkman_clk_config_t clkman_clk_config = MXC_CLKMAN->clk_config_f;

    /* Release reset and enable crypto RO */
    clkman_clk_config.crypto_reset_n = 1;
    clkman_clk_config.crypto_enable = 1;

    MXC_CLKMAN->clk_config_f = clkman_clk_config;

    /* Un-gate crypto RO */
    clkman_clk_ctrl.crypto_gate_n = 1;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
}

void CLKMAN_CryptoClockDisable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    clkman_clk_ctrl.crypto_gate_n = 0;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
}

int32_t CLKMAN_SetADCClock(mxc_clkman_adc_source_select_t adc_source_select, mxc_adc_clk_mode adc_clk_mode)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    mxc_adc_ctrl0_t adc_ctrl0 = MXC_ADC->ctrl0_f;

    clkman_clk_ctrl.adc_gate_n = 1;
    clkman_clk_ctrl.adc_source_select = adc_source_select;
    adc_ctrl0.adc_clk_mode = adc_clk_mode;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
    MXC_ADC->ctrl0_f = adc_ctrl0;

    return 0;
}

void CLKMAN_ADCClockDisable(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    clkman_clk_ctrl.adc_gate_n = 0;

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
}

int32_t CLKMAN_SetWatchdogClock(uint8_t index, mxc_clkman_wdt_source_select_t watchdog_source_select)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    if (watchdog_source_select == MXC_E_CLKMAN_WDT_SOURCE_SELECT_RTC)
    {
        PWR_EnableDevRun(MXC_E_PWR_DEVICE_RTC);
        RTC_SetPrescale(MXC_E_RTC_PRESCALE_DIV_2_12);
        RTC_Enable();
    }
    switch (index)
    {
        case 0:
            while (clkman_clk_ctrl.watchdog0_source_select != watchdog_source_select)
            {
            clkman_clk_ctrl.watchdog0_gate_n = 1;
            clkman_clk_ctrl.watchdog0_source_select = watchdog_source_select;
            MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
            clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
            }
            break;
        case 1:
            while (clkman_clk_ctrl.watchdog1_source_select != watchdog_source_select)
            {
            clkman_clk_ctrl.watchdog1_gate_n = 1;
            clkman_clk_ctrl.watchdog1_source_select = watchdog_source_select;
            MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;
            clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
            }
            break;
        default:
            return -1;
    }


    return 0;
}

int32_t CLKMAN_WatchdogClockDisable(uint8_t index)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    switch (index)
    {
        case 0:
            clkman_clk_ctrl.watchdog0_gate_n = 0;
            break;
        case 1:
            clkman_clk_ctrl.watchdog1_gate_n = 0;
            break;
        default:
            return -1;
    }

    MXC_CLKMAN->clk_ctrl_f = clkman_clk_ctrl;

    return 0;
}

void CLKMAN_SetClkScale(mxc_clkman_clk_t device_clk, mxc_clkman_clk_scale_t clk_scale)
{
    volatile uint32_t *scale_reg = (uint32_t*)(&MXC_CLKMAN->clk_ctrl_0_system + device_clk);
    *scale_reg = (uint32_t) clk_scale;
}

void CLKMAN_SetCryptClkScale(mxc_clkman_crypt_clk_t device_clk, mxc_clkman_clk_scale_t clk_scale)
{
    volatile uint32_t *scale_reg = (uint32_t*)(&MXC_CLKMAN->crypt_clk_ctrl_0_aes + device_clk);
    *scale_reg = (uint32_t) clk_scale;
}

void CLKMAN_SetRTOSMode(uint8_t enable)
{
    if(enable) {
        BITBAND_SetBit((uint32_t)&MXC_CLKMAN->clk_ctrl, 24);
    } else {
        BITBAND_ClrBit((uint32_t)&MXC_CLKMAN->clk_ctrl, 24);
    }
}
