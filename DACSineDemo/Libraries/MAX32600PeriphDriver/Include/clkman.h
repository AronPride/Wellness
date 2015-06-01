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

/* $Revision: 3581 $ $Date: 2014-11-18 11:46:39 -0600 (Tue, 18 Nov 2014) $ */

#ifndef _CLKMAN_H
#define _CLKMAN_H

#include "clkman_regs.h"
#include "adc_regs.h"

/**
 * @file  clkman.h
 * @addtogroup clkman CLKMAN
 * @{
 * @brief This is the high level API for the clock management module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Selects an internal module clock for clock scaling configuration.
 */
typedef enum {
    /** Main System clock */
    MXC_E_CLKMAN_CLK_SYS = 0,
    /** GPIO module clock */
    MXC_E_CLKMAN_CLK_GPIO,
    /** Pulse Train engine clock */
    MXC_E_CLKMAN_CLK_PT,
    /** SPI instance 0 module clock */
    MXC_E_CLKMAN_CLK_SPI0,
    /** SPI instance 1 module clock */
    MXC_E_CLKMAN_CLK_SPI1,
    /** SPI instance 2 module clock */
    MXC_E_CLKMAN_CLK_SPI2,
    /** I2C Master module clock (for all instances) */
    MXC_E_CLKMAN_CLK_I2CM,
    /** I2C Slave module clock */
    MXC_E_CLKMAN_CLK_I2CS,
    /** LCD Charge pump clock */
    MXC_E_CLKMAN_CLK_LCD_CHPUMP,
    /** Reserved */
    MXC_E_CLKMAN_CLK_PUF,
    /** PRNG module clock */
    MXC_E_CLKMAN_CLK_PRNG,
    /** Watchdog Timer 0 clock */
    MXC_E_CLKMAN_CLK_WDT0,
    /** Watchdog Timer 1 clock */
    MXC_E_CLKMAN_CLK_WDT1,
    /** RTC synchronizer clock (required for cross-clock-domain register updates) */
    MXC_E_CLKMAN_CLK_RTC_INT_SYNC,
    /** Clock for DAC 0 */
    MXC_E_CLKMAN_CLK_DAC0,
    /** Clock for DAC 1 */
    MXC_E_CLKMAN_CLK_DAC1,
    /** Clock for DAC 2 */
    MXC_E_CLKMAN_CLK_DAC2,
    /** Clock for DAC 3 */
    MXC_E_CLKMAN_CLK_DAC3
} mxc_clkman_clk_t;

/**
 * @brief Selects a TPU module clock for crypto ring-oscillator clock scaling configuration
 */
typedef enum {
    /** AES engine clock */
    MXC_E_CLKMAN_CRYPT_CLK_AES = 0,
    /** Modular Arithmetic Accelerator (MAA) clock */
    MXC_E_CLKMAN_CRYPT_CLK_MAA,
    /** Pseudo-random number Generator (PRNG) clock */
    MXC_E_CLKMAN_CRYPT_CLK_PRNG
} mxc_clkman_crypt_clk_t;

/**
 * @brief Configures but does not enable the high frequency external oscillator circuitry.
 *
 * @param hfx_bypass 1 for crystal receiver bypass, 0 for no bypass.
 * @param hfx_gm_adjust High frequency crystal gain adjust.
 * @param hfx_dc_control High frequency crystal dc control.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_HFXConfig(uint8_t hfx_bypass, uint8_t hfx_gm_adjust, uint8_t hfx_dc_control);

/**
 * @brief Enables the high frequency crystal receiver. Make sure HFX is stable before switching system clock.
 */
void CLKMAN_HFXEnable(void);

/**
 * @brief Disables the high frequency crystal receiver.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_HFXDisable(void);

/**
 * @brief Configures but does not enable the phase locked loop circuitry.
 *
 * @param pll_input_select    Phase locked loop clock input.
 * @param pll_divisor_select  Input clock frequency for the phase locked loop.
 * @param pll_stability_count Number of clocks before phase locked loop is stable.
 * @param pll_bypass   1 for high frequency oscillator output for 48MHz clock, 0 for phase locked loop output.
 * @param pll_8mhz_enable  1 for enable 8MHz phase locked loop output, 0 for disable.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_PLLConfig(mxc_clkman_pll_input_select_t pll_input_select,
        mxc_clkman_pll_divisor_select_t pll_divisor_select,
        mxc_clkman_stability_count_t pll_stability_count,
        uint8_t pll_bypass, uint8_t pll_8mhz_enable);

/**
 * @brief Enables the phase locked loop circuitry.
 */
void CLKMAN_PLLEnable(void);

/**
 * @brief Disables the phase locked loop circuitry.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_PLLDisable(void);

/**
 * @brief Starts the Trim calibration of the  relaxation oscillator off the 32kHz crystal for use with USB.
 */
void CLKMAN_TrimRO_Start(void);

/**
 * @brief Stops the Trim calibration of the  relaxation oscillator off the 32kHz crystal for use with USB.
 */
void CLKMAN_TrimRO_Stop(void);

/**
 * @brief Sets the system clock source if the source is valid. Make sure HFX is stable before switching system clock.
 *
 * @param system_source_select System clock source.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_SetSystemClock(mxc_clkman_system_source_select_t system_source_select);

/**
 * @brief Polls on the clock stable flags until all are stable.
 */
void CLKMAN_WaitForSystemClockStable(void);

/**
 * @brief Enables the USB clock.
 */
void CLKMAN_USBClockEnable(void);

/**
 * @brief Disables the USB clock.
 */
void CLKMAN_USBClockDisable(void);

/**
 * @brief Configures but does not enable the crypto clock.
 *
 * @param crypto_stability_count Number of clocks before crypto clock is stable.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_CryptoClockConfig(mxc_clkman_stability_count_t crypto_stability_count);

/**
 * @brief Enables the crypto clock.
 */
void CLKMAN_CryptoClockEnable(void);

/**
 * @brief Disables the crypto clock.
 */
void CLKMAN_CryptoClockDisable(void);

/**
 * @brief Sets the analog to digital converter clock source if the source is valid.
 *
 * @param adc_source_select Analog to digital converter clock source.
 * @param adc_clk_mode      Divide the clock source into the ADC if source is too high.
 *                          ADC must run at 8MHz.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_SetADCClock(mxc_clkman_adc_source_select_t adc_source_select, mxc_adc_clk_mode adc_clk_mode);

/**
 * @brief Disables the analog to digital converter clock source.
 */
void CLKMAN_ADCClockDisable(void);

/**
 * @brief Sets the watchdog clock source if the source is valid for the watchdog specified.
 *
 * @param index Index of watchdog to set clock.
 * @param watchdog_source_select Watchdog clock source.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_SetWatchdogClock(uint8_t index, mxc_clkman_wdt_source_select_t watchdog_source_select);

/**
 * @brief Disable the watchdog clock source for the watchdog specified.
 *
 * @param index Index of watchdog to disable.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t CLKMAN_WatchdogClockDisable(uint8_t index);

/**
 * @brief Set the system clock scale.
 * @param device_clk device enum for clock scale setup
 * @param clk_scale System clock scale.
 */
void CLKMAN_SetClkScale(mxc_clkman_clk_t device_clk, mxc_clkman_clk_scale_t clk_scale);

/**
 * @brief Set the TPU clock scale.
 * @param device_clk device enum for clock scale setup
 * @param clk_scale System clock scale.
 */
void CLKMAN_SetCryptClkScale(mxc_clkman_crypt_clk_t device_clk, mxc_clkman_clk_scale_t clk_scale);

/**
 * @brief Set RTC clock for systick counter, allowing systick to operate in full clockgating powersaving mode
 * @param enable 1 enable 0 disable
 */
void CLKMAN_SetRTOSMode(uint8_t enable);

/**
 * @}
 */

#endif /* _CLKMAN_H */
