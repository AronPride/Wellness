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

/* $Revision: 3545 $ $Date: 2014-11-11 18:20:37 -0600 (Tue, 11 Nov 2014) $ */

#ifndef _MXC_CLKMAN_REGS_H_
#define _MXC_CLKMAN_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif

/*
    Bitfield structs for registers in this module
*/

/**
 * @file  clkman_regs.h
 * @addtogroup clkman CLKMAN
 * @{
 */

/**
 * @brief Defines clock input selections for the phase locked loop.
 */
typedef enum {
    /** Input select for high frequency crystal oscillator */
    MXC_E_CLKMAN_PLL_INPUT_SELECT_HFX = 0,
    /** Input select for 24MHz ring oscillator */
    MXC_E_CLKMAN_PLL_INPUT_SELECT_24MHZ_RO,
} mxc_clkman_pll_input_select_t;

/**
 * @brief Defines clock input frequency for the phase locked loop.
 */
typedef enum {
    /** Input frequency of 24MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_24MHZ = 0,
    /** Input frequency of 12MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_12MHZ,
    /** Input frequency of 8MHz */
    MXC_E_CLKMAN_PLL_DIVISOR_SELECT_8MHZ,
} mxc_clkman_pll_divisor_select_t;

/**
 * @brief Defines terminal count for PLL stable.
 */
typedef enum {
    /** Clock stable after 2^8 = 256 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_8_CLKS = 0,
    /** Clock stable after 2^9 = 512 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_9_CLKS,
    /** Clock stable after 2^10 = 1024 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_10_CLKS,
    /** Clock stable after 2^11 = 2048 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_11_CLKS,
    /** Clock stable after 2^12 = 4096 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_12_CLKS,
    /** Clock stable after 2^13 = 8192 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_13_CLKS,
    /** Clock stable after 2^14 = 16384 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_14_CLKS,
    /** Clock stable after 2^15 = 32768 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_15_CLKS,
    /** Clock stable after 2^16 = 65536 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_16_CLKS,
    /** Clock stable after 2^17 = 131072 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_17_CLKS,
    /** Clock stable after 2^18 = 262144 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_18_CLKS,
    /** Clock stable after 2^19 = 524288 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_19_CLKS,
    /** Clock stable after 2^20 = 1048576 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_20_CLKS,
    /** Clock stable after 2^21 = 2097152 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_21_CLKS,
    /** Clock stable after 2^22 = 4194304 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_22_CLKS,
    /** Clock stable after 2^23 = 8388608 clock cycles */
    MXC_E_CLKMAN_STABILITY_COUNT_2_23_CLKS
} mxc_clkman_stability_count_t;

typedef struct
{
    uint32_t hfx_enable                                   : 1;
    uint32_t hfx_bypass                                   : 1;
    uint32_t hfx_test_enable                              : 1;
    uint32_t                                              : 1;

    uint32_t hfx_gm_adjust                                : 5;
    uint32_t hfx_dc_control                               : 3;

    uint32_t pll_enable                                   : 1;
    uint32_t pll_reset_n                                  : 1;
    uint32_t pll_input_select                             : 1;
    uint32_t                                              : 1;

    uint32_t pll_divisor_select                           : 2;
    uint32_t pll_8mhz_enable                              : 1;
    uint32_t pll_bypass                                   : 1;

    uint32_t pll_stability_count                          : 4;
    uint32_t crypto_enable                                : 1;
    uint32_t crypto_reset_n                               : 1;
    uint32_t                                              : 2;

    uint32_t crypto_stability_count                       : 4;
} mxc_clkman_clk_config_t;

/**
 * @brief Defines clock source selections for system clock.
 */
typedef enum {
    /** Clock select for 24MHz ring oscillator divided by 8 (3MHz) */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO_DIV_8 = 0,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX,
    /** Clock select for 48MHz phase locked loop output divided by 2 (24MHz) */
    MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2
} mxc_clkman_system_source_select_t;

/**
 * @brief Defines clock source selections for analog to digital converter clock.
 */
typedef enum {
    /** Clock select for system clock frequency */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_SYSTEM = 0,
    /** Clock select for 8MHz phase locked loop output */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_PLL_8MHZ,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_HFX,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_ADC_SOURCE_SELECT_24MHZ_RO,
} mxc_clkman_adc_source_select_t;

/**
 * @brief Defines clock source selections for watchdog timer clock.
 */
typedef enum {
    /** Clock select for system clock frequency */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_SYSTEM = 0,
    /** Clock select for 8MHz phase locked loop output */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_RTC,
    /** Clock select for high frequency crystal oscillator */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_24MHZ_RO,
    /** Clock select for 24MHz ring oscillator */
    MXC_E_CLKMAN_WDT_SOURCE_SELECT_NANO,
} mxc_clkman_wdt_source_select_t;

typedef struct
{
    uint32_t                          : 1;
    uint32_t system_source_select     : 2;
    uint32_t auto_clk_disable         : 1;
    uint32_t usb_gate_n               : 1;
    uint32_t                          : 3;
    uint32_t adc_gate_n               : 1;
    uint32_t adc_source_select        : 2;
    uint32_t                          : 1;
    uint32_t crypto_gate_n            : 1;
    uint32_t                          : 3;
    uint32_t watchdog0_gate_n         : 1;
    uint32_t watchdog0_source_select  : 2;
    uint32_t                          : 1;
    uint32_t watchdog1_gate_n         : 1;
    uint32_t watchdog1_source_select  : 2;
    uint32_t                          : 1;
    uint32_t rtos_mode                : 1;
    uint32_t                          : 7;
} mxc_clkman_clk_ctrl_t;

typedef struct
{
    uint32_t ring_stable              : 1;
    uint32_t pll_stable               : 1;
    uint32_t crypto_stable            : 1;
    uint32_t                          : 29;
} mxc_clkman_intfl_t;

typedef struct
{
    uint32_t ring_stable              : 1;
    uint32_t pll_stable               : 1;
    uint32_t crypto_stable            : 1;
    uint32_t                          : 29;
} mxc_clkman_inten_t;

typedef struct
{
    uint32_t trim_clk_sel             : 1;
    uint32_t trim_calc_start          : 1;
    uint32_t trim_calc_completed      : 1;
    uint32_t trim_enable              : 1;
    uint32_t                          : 12;
    uint32_t trim_calc_results        : 10;
    uint32_t                          : 6;
} mxc_clkman_trim_calc_t;


typedef struct
{
    uint32_t i2c_1ms_timer_en         : 1;
    uint32_t                          : 31;
} mxc_clkman_i2c_timer_ctrl_t;

/**
 * @brief Defines clock scales for various clocks.
 */
typedef enum {
    /** Clock disabled */
    MXC_E_CLKMAN_CLK_SCALE_DISABLED = 0,
    /** Clock enabled */
    MXC_E_CLKMAN_CLK_SCALE_ENABLED,
    /** Clock scale for dividing by 2 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_2,
    /** Clock scale for dividing by 4 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_4,
    /** Clock scale for dividing by 8 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_8,
    /** Clock scale for dividing by 16 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_16,
    /** Clock scale for dividing by 32 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_32,
    /** Clock scale for dividing by 64 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_64,
    /** Clock scale for dividing by 128 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_128,
    /** Clock scale for dividing by 256 */
    MXC_E_CLKMAN_CLK_SCALE_DIV_256
} mxc_clkman_clk_scale_t;

typedef struct
{
    uint32_t sys_clk_scale            : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_0_system_t;

typedef struct
{
    uint32_t gpio_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_1_gpio_t;

typedef struct
{
    uint32_t pulse_train_clk_scale    : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_2_pt_t;

typedef struct
{
    uint32_t spi0_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_3_spi0_t;

typedef struct
{
    uint32_t spi1_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_4_spi1_t;

typedef struct
{
    uint32_t spi2_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_5_spi2_t;

typedef struct
{
    uint32_t i2cm_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_6_i2cm_t;

typedef struct
{
    uint32_t i2cs_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_7_i2cs_t;

typedef struct
{
    uint32_t lcd_clk_scale            : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_8_lcd_chpump_t;

typedef struct
{
    uint32_t puf_clk_scale            : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_9_puf_t;

typedef struct
{
    uint32_t prng_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_10_prng_t;

typedef struct
{
    uint32_t watchdog0_clk_scale      : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_11_wdt0_t;

typedef struct
{
    uint32_t watchdog1_clk_scale      : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_12_wdt1_t;

typedef struct
{
    uint32_t rtc_clk_scale            : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_13_rtc_int_sync_t;

typedef struct
{
    uint32_t dac0_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_14_dac0_t;

typedef struct
{
    uint32_t dac1_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_15_dac1_t;

typedef struct
{
    uint32_t dac2_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_16_dac2_t;

typedef struct
{
    uint32_t dac3_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_clk_ctrl_17_dac3_t;

typedef struct
{
    uint32_t aes_clk_scale            : 4;
    uint32_t                          : 28;
} mxc_clkman_crypt_clk_ctrl_0_aes_t;

typedef struct
{
    uint32_t umaa_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_crypt_clk_ctrl_1_maa_t;

typedef struct
{
    uint32_t prng_clk_scale           : 4;
    uint32_t                          : 28;
} mxc_clkman_crypt_clk_ctrl_2_prng_t;


/**
 * @brief Defines Setting of the Clock Gates .
 */
typedef enum {
    /** Clock Gater is Off */
    MXC_E_CLKMAN_CLK_GATE_OFF  = 0,
    /** Clock Gater is Dynamic */
    MXC_E_CLKMAN_CLK_GATE_DYNAMIC,
    /** Clock Gater is On */
    MXC_E_CLKMAN_CLK_GATE_ON
} mxc_clkman_clk_gate_t;

typedef struct
{
    uint32_t cm3_clk_gater            : 2;
    uint32_t sysbus_clk_gater         : 2;
    uint32_t icache_clk_gater         : 2;
    uint32_t flash_clk_gater          : 2;
    uint32_t sram_clk_gater           : 2;
    uint32_t apb_bridge_clk_gater     : 2;
    uint32_t sysman_clk_gater         : 2;
    uint32_t uart0_clk_gater          : 2;
    uint32_t uart1_clk_gater          : 2;
    uint32_t timer0_clk_gater         : 2;
    uint32_t timer1_clk_gater         : 2;
    uint32_t timer2_clk_gater         : 2;
    uint32_t timer3_clk_gater         : 2;
    uint32_t watchdog0_clk_gater      : 2;
    uint32_t watchdog1_clk_gater      : 2;
    uint32_t usb_clk_gater            : 2;
} mxc_clkman_clk_gate_ctrl0_t;

typedef struct
{
    uint32_t testacc_clk_gater        : 2;
    uint32_t adc_clk_gater            : 2;
    uint32_t dac12_0_clk_gater        : 2;
    uint32_t dac12_1_clk_gater        : 2;
    uint32_t dac8_0_clk_gater         : 2;
    uint32_t dac8_1_clk_gater         : 2;
    uint32_t pmu_clk_gater            : 2;
    uint32_t lcd_clk_gater            : 2;
    uint32_t gpio_clk_gater           : 2;
    uint32_t pulsetrain_clk_gater     : 2;
    uint32_t spi0_clk_gater           : 2;
    uint32_t spi1_clk_gater           : 2;
    uint32_t spi2_clk_gater           : 2;
    uint32_t i2cm0_clk_gater          : 2;
    uint32_t i2cm1_clk_gater          : 2;
    uint32_t i2cs_clk_gater           : 2;
} mxc_clkman_clk_gate_ctrl1_t;

typedef struct
{
    uint32_t crc_clk_gater            : 2;
    uint32_t tpu_clk_gater            : 2;
    uint32_t ssbmux_clk_gater         : 2;
    uint32_t pad_clk_gater            : 2;
    uint32_t                          : 24;
} mxc_clkman_clk_gate_ctrl2_t;


/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                                          Offset   Register Description
                                                            ======   ===================================================================== */
typedef struct {
    union {
        __IO uint32_t clk_config;                       /*  0x0000   System Clock Configuration                                            */
        __IO mxc_clkman_clk_config_t clk_config_f;
    };
    union {
        __IO uint32_t clk_ctrl;                         /*  0x0004   System Clock Controls                                                 */
        __IO mxc_clkman_clk_ctrl_t clk_ctrl_f;

    };
    union {
        __IO uint32_t intfl;                            /*  0x0008   Interrupt Flags                                                       */
        __IO mxc_clkman_intfl_t intfl_f;
    };
    union {
        __IO uint32_t inten;                            /*  0x000C   Interrupt Enable/Disable Controls                                     */
        __IO mxc_clkman_inten_t inten_f;
    };
    union {
        __IO uint32_t trim_calc;                        /*  0x0010   Trim Calculation Controls                                             */
        __IO mxc_clkman_trim_calc_t trim_calc_f;
    };
     __R uint32_t rsv0014[4];                           /*  0x0014                                                                         */
    union {
        __IO uint32_t i2c_timer_ctrl;                   /*  0x0024   I2C Timer Control                                                     */
        __IO mxc_clkman_i2c_timer_ctrl_t i2c_timer_ctrl_f;
    };
     __R uint32_t rsv0028[6];                           /*  0x0028                                                                         */
    union {
        __IO uint32_t clk_ctrl_0_system;                /*  0x0040   Control Settings for CLK0 - System Clock                              */
        __IO mxc_clkman_clk_ctrl_0_system_t clk_ctrl_0_system_f;
    };
    union {
        __IO uint32_t clk_ctrl_1_gpio;                  /*  0x0044   Control Settings for CLK1 - GPIO Module Clock                         */
        __IO mxc_clkman_clk_ctrl_1_gpio_t clk_ctrl_1_gpio_f;
    };
    union {
        __IO uint32_t clk_ctrl_2_pt;                    /*  0x0048   Control Settings for CLK2 - Pulse Train Module Clock                  */
        __IO mxc_clkman_clk_ctrl_2_pt_t clk_ctrl_2_pt_f;
    };
    union {
        __IO uint32_t clk_ctrl_3_spi0;                  /*  0x004C   Control Settings for CLK3 - SPI0 Master Clock                         */
        __IO mxc_clkman_clk_ctrl_3_spi0_t clk_ctrl_3_spi0_f;
    };
    union {
        __IO uint32_t clk_ctrl_4_spi1;                  /*  0x0050   Control Settings for CLK4 - SPI1 Master Clock                         */
        __IO mxc_clkman_clk_ctrl_4_spi1_t clk_ctrl_4_spi1_f;
    };
    union {
        __IO uint32_t clk_ctrl_5_spi2;                  /*  0x0054   Control Settings for CLK5 - SPI2 Master Clock                         */
        __IO mxc_clkman_clk_ctrl_5_spi2_t clk_ctrl_5_spi2_f;
    };
    union {
        __IO uint32_t clk_ctrl_6_i2cm;                  /*  0x0058   Control Settings for CLK6 - Clock for all I2C Masters                 */
        __IO mxc_clkman_clk_ctrl_6_i2cm_t clk_ctrl_6_i2cm_f;
    };
    union {
        __IO uint32_t clk_ctrl_7_i2cs;                  /*  0x005C   Control Settings for CLK7 - I2C Slave Clock                           */
        __IO mxc_clkman_clk_ctrl_7_i2cs_t clk_ctrl_7_i2cs_f;
    };
    union {
        __IO uint32_t clk_ctrl_8_lcd_chpump;            /*  0x0060   Control Settings for CLK8 - LCD Charge Pump Clock                     */
        __IO mxc_clkman_clk_ctrl_8_lcd_chpump_t clk_ctrl_8_lcd_chpump_f;
    };
    union {
        __IO uint32_t clk_ctrl_9_puf;                   /*  0x0064   Control Settings for CLK9 - PUF Clock                                 */
        __IO mxc_clkman_clk_ctrl_9_puf_t clk_ctrl_9_puf_f;
    };
    union {
        __IO uint32_t clk_ctrl_10_prng;                 /*  0x0068   Control Settings for CLK10 - PRNG Clock                               */
        __IO mxc_clkman_clk_ctrl_10_prng_t clk_ctrl_10_prng_f;
    };
    union {
        __IO uint32_t clk_ctrl_11_wdt0;                 /*  0x006C   Control Settings for CLK11 - Watchdog Timer 0 ScaledSysClk            */
        __IO mxc_clkman_clk_ctrl_11_wdt0_t clk_ctrl_11_wdt0_f;
    };
    union {
        __IO uint32_t clk_ctrl_12_wdt1;                 /*  0x0070   Control Settings for CLK12 - Watchdog Timer 1 ScaledSysClk            */
        __IO mxc_clkman_clk_ctrl_12_wdt1_t clk_ctrl_12_wdt1_f;
    };
    union {
        __IO uint32_t clk_ctrl_13_rtc_int_sync;         /*  0x0074   Control Settings for CLK13 - RTC Interrupt Sync Clock                 */
        __IO mxc_clkman_clk_ctrl_13_rtc_int_sync_t clk_ctrl_13_rtc_int_sync_f;
    };
    union {
        __IO uint32_t clk_ctrl_14_dac0;              /*  0x0078   Control Settings for CLK14 - 12-bit DAC 0 Clock                       */
        __IO mxc_clkman_clk_ctrl_14_dac0_t clk_ctrl_14_dac0_f;
    };
    union {
        __IO uint32_t clk_ctrl_15_dac1;              /*  0x007C   Control Settings for CLK15 - 12-bit DAC 1 Clock                       */
        __IO mxc_clkman_clk_ctrl_15_dac1_t clk_ctrl_15_dac1_f;
    };
    union {
        __IO uint32_t clk_ctrl_16_dac2;               /*  0x0080   Control Settings for CLK16 - 8-bit DAC 0 Clock                        */
        __IO mxc_clkman_clk_ctrl_16_dac2_t clk_ctrl_16_dac2_f;
    };
    union {
        __IO uint32_t clk_ctrl_17_dac3;               /*  0x0084   Control Settings for CLK17 - 8-bit DAC 1 Clock                        */
        __IO mxc_clkman_clk_ctrl_17_dac3_t clk_ctrl_17_dac3_f;
    };
     __R uint32_t rsv0088[30];                          /*  0x0088                                                                         */
    union {
        __IO uint32_t crypt_clk_ctrl_0_aes;             /*  0x0100   Control Settings for Crypto Clock 0 - AES                             */
        __IO mxc_clkman_crypt_clk_ctrl_0_aes_t crypt_clk_ctrl_0_aes_f;
    };
    union {
        __IO uint32_t crypt_clk_ctrl_1_maa;             /*  0x0104   Control Settings for Crypto Clock 1 - MAA                             */
        __IO mxc_clkman_crypt_clk_ctrl_1_maa_t crypt_clk_ctrl_1_maa_f;
    };
    union {
        __IO uint32_t crypt_clk_ctrl_2_prng;            /*  0x0108   Control Settings for Crypto Clock 2 - PRNG                            */
        __IO mxc_clkman_crypt_clk_ctrl_2_prng_t crypt_clk_ctrl_2_prng_f;
    };
     __R uint32_t rsv010C[13];                          /*  0x010C                                                                         */
    union {
        __IO uint32_t clk_gate_ctrl0;                   /*  0x0140   Dynamic Clock Gating Control Register 0                               */
        __IO mxc_clkman_clk_gate_ctrl0_t clk_gate_ctrl0_f;
    };
    union {
        __IO uint32_t clk_gate_ctrl1;                   /*  0x0144   Dynamic Clock Gating Control Register 1                               */
        __IO mxc_clkman_clk_gate_ctrl1_t clk_gate_ctrl1_f;
    };
    union {
        __IO uint32_t clk_gate_ctrl2;                   /*  0x0148   Dynamic Clock Gating Control Register 2                               */
        __IO mxc_clkman_clk_gate_ctrl2_t clk_gate_ctrl2_f;
    };
} mxc_clkman_regs_t;

/*
   Register offsets for module CLKMAN.
*/
#define MXC_R_CLKMAN_OFFS_CLK_CONFIG               ((uint32_t)0x00000000UL)
#define MXC_R_CLKMAN_OFFS_CLK_CNTL                 ((uint32_t)0x00000004UL)
#define MXC_R_CLKMAN_OFFS_INTFL                    ((uint32_t)0x00000008UL)
#define MXC_R_CLKMAN_OFFS_INTEN                    ((uint32_t)0x0000000CUL)
#define MXC_R_CLKMAN_OFFS_TRIM_CALC                ((uint32_t)0x00000010UL)
#define MXC_R_CLKMAN_OFFS_I2C_TIMER_CTRL           ((uint32_t)0x00000024UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_0_SYSTEM        ((uint32_t)0x00000040UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_1_GPIO          ((uint32_t)0x00000044UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_2_PT            ((uint32_t)0x00000048UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_3_SPI0          ((uint32_t)0x0000004CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_4_SPI1          ((uint32_t)0x00000050UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_5_SPI2          ((uint32_t)0x00000054UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_6_I2CM          ((uint32_t)0x00000058UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_7_I2CS          ((uint32_t)0x0000005CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_8_LCD_CHPUMP    ((uint32_t)0x00000060UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_9_PUF           ((uint32_t)0x00000064UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_10_PRNG         ((uint32_t)0x00000068UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_11_WDT0         ((uint32_t)0x0000006CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_12_WDT1         ((uint32_t)0x00000070UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_13_RTC_INT_SYNC ((uint32_t)0x00000074UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_14_DAC12_0      ((uint32_t)0x00000078UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_15_DAC12_1      ((uint32_t)0x0000007CUL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_16_DAC8_0       ((uint32_t)0x00000080UL)
#define MXC_R_CLKMAN_OFFS_CLK_CTRL_17_DAC8_1       ((uint32_t)0x00000084UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_0_AES     ((uint32_t)0x00000100UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_1_MAA     ((uint32_t)0x00000104UL)
#define MXC_R_CLKMAN_OFFS_CRYPT_CLK_CTRL_2_PRNG    ((uint32_t)0x00000108UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL0           ((uint32_t)0x00000140UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL1           ((uint32_t)0x00000144UL)
#define MXC_R_CLKMAN_OFFS_CLK_GATE_CTRL2           ((uint32_t)0x00000148UL)

#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif   /* _MXC_CLKMAN_REGS_H_ */



