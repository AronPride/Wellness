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

/* $Revision: 3568 $ $Date: 2014-11-13 16:17:25 -0600 (Thu, 13 Nov 2014) $ */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "board.h"

/* config.h is the required application configuration; RAM layout, stack, chip type etc. */
#include "mxc_config.h" 
#include "board.h"

#include "clkman.h"
#include "power.h"
#include "gpio.h"
#include "icc.h"
#include "systick.h"
#include "uart.h"
#include "afe.h"
#include "dac.h"
#include "adc.h"
#include "fixedptc.h"
#include "rtc.h"
#include "ioman.h"

/* these are used for the ADC MUX selector setups - we will cycle through each channel and pick the best signal */
#define MUX_CH_AIN0       0
#define MUX_CH_AIN1       1
#define MUX_CH_AIN2       2
#define MUX_CH_AIN3       3
#define MUX_CH_AIN4       4
#define MUX_CH_AIN5       5
#define MUX_CH_AIN6       6
#define MUX_CH_AIN7       7

#define PGA_ACQ_CNT       0
#define ADC_ACQ_CNT       0
#define ADC_SCN_CNT	      8
#define PGA_TRK_CNT       9
#define ADC_SLP_CNT     664


/* these are for the ADC setup*/
#define ADC_MODE     MXC_E_ADC_MODE_SMPLCNT_LOW_POWER

#define FILTER_MODE  MXC_E_ADC_AVG_MODE_FILTER_OUTPUT  	/* or ADC_FILTER_BYPASS */
#define FILTER_CNT   3                  				/* number of averaging samples = 2^FILTER_CNT (FILTER_CNT range from 1-7) */
#define BIPOLAR_MODE MXC_E_ADC_BI_POL_BIPOLAR       	/* use single or Bi-polar inputs                   */
#define BI_RANGE     MXC_E_ADC_RANGE_HALF     			/* range value only applicable when BIPOLAR==TRUE (HALF---> -VRef/2:VRef/2) */

#define PGA_BYPASS TRUE              					/* TRUE => bypass the PGA; FALSE => use the PGA      */
#define PGA_GAIN   MXC_E_ADC_PGA_GAIN_1    				/* gain value only applicable when PGA_BYPASS==FALSE */

#define START_MODE MXC_E_ADC_STRT_MODE_SOFTWARE 		/* use either software or pulse-train to trigger the ADC samples */

#define MUX_MODE  MXC_E_ADC_PGA_MUX_DIFF_DISABLE   		/* use one pin and ground; or differential with two pins AIN+/AIN- *

/* these are used for the DAC, OPAMP and CLOCK Setups */
#define DAC_NUM         0 /* DAC0 */
#define OPAMP_NUM       3 /* OpAmpD */
#define DAC_RATE      198 /* DAC Rate Count =  (DAC_RATE + 2) / 24MHz = Freq of sample delay
                             Freq of sine wave --->  24MHz / ((DAC_RATE + 2) * sizeof(sine_wave16bit) * interpolationNum)
                             1 kHz = 24MHz / ((198+2)*120*1) */
#define PLL_BYPASS      0 /* Do NOT Bypass the PLL */
#define PLL_8MHZ_ENABLE 1 /* Enable PLL 8 MHz */
#define LOOPS           0 /* Run until Stopped */

/* 120 point sine wave 16bit ('const' will leave it in flash) */
static const uint16_t sine_wave16bit[] = {
		0x5555,
		0x59cc,
		0x5e40,
		0x62ae,
		0x6713,
		0x6b6b,
		0x6fb3,
		0x73ea,
		0x780a,
		0x7c12,
		0x8000,
		0x83cf,
		0x877d,
		0x8b09,
		0x8e6e,
		0x91ac,
		0x94bf,
		0x97a6,
		0x9a5e,
		0x9ce6,
		0x9f3b,
		0xa15d,
		0xa349,
		0xa4ff,
		0xa67d,
		0xa7c2,
		0xa8cd,
		0xa99d,
		0xaa32,
		0xaa8c,
		0xaaaa,
		0xaa8c,
		0xaa32,
		0xa99d,
		0xa8cd,
		0xa7c2,
		0xa67d,
		0xa4ff,
		0xa349,
		0xa15d,
		0x9f3b,
		0x9ce6,
		0x9a5e,
		0x97a6,
		0x94bf,
		0x91ac,
		0x8e6e,
		0x8b09,
		0x877d,
		0x83cf,
		0x8000,
		0x7c12,
		0x780a,
		0x73ea,
		0x6fb3,
		0x6b6b,
		0x6713,
		0x62ae,
		0x5e40,
		0x59cc,
		0x5555,
		0x50de,
		0x4c6a,
		0x47fc,
		0x4397,
		0x3f3f,
		0x3af7,
		0x36c0,
		0x32a0,
		0x2e98,
		0x2aab,
		0x26db,
		0x232d,
		0x1fa1,
		0x1c3c,
		0x18fe,
		0x15eb,
		0x1304,
		0x104c,
		0xdc4,
		0xb6f,
		0x94d,
		0x761,
		0x5ab,
		0x42d,
		0x2e8,
		0x1dd,
		0x10d,
		0x78,
		0x1e,
		0x0,
		0x1e,
		0x78,
		0x10d,
		0x1dd,
		0x2e8,
		0x42d,
		0x5ab,
		0x761,
		0x94d,
		0xb6f,
		0xdc4,
		0x104c,
		0x1304,
		0x15eb,
		0x18fe,
		0x1c3c,
		0x1fa1,
		0x232d,
		0x26db,
		0x2aab,
		0x2e98,
		0x32a0,
		0x36c0,
		0x3af7,
		0x3f3f,
		0x4397,
		0x47fc,
		0x4c6a,
		0x50de,
};

static uint32_t data_samples16bit = sizeof(sine_wave16bit)/2;
static dac_transport_t dac_wave_handle;

/* used for starting and stopping the waveform */
void trigger_wave(void) {
    static uint8_t running = 0;
    
    if(!running) {
        /* Turn on YELLOW LED */
        GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_ON);
        DAC_PatternStart(&dac_wave_handle);
        running = 1;
    } else {
        /* Turn off YELLOW LED */
        GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_OFF);
        DAC_PatternStop(&dac_wave_handle);
        running = 0;
    }
}

/* used for setting up the Voltage Reference, OpAmp, and DAC */
static void dacsine_demo_init(void)
{
    /* enable the AFE Power */
    MXC_PWRMAN->pwr_rst_ctrl_f.afe_powered = 1;

    /* setup of Voltage Reference*/
    AFE_ADCVRefEnable(MXC_E_AFE_REF_VOLT_SEL_1500);
    AFE_DACVRefEnable(MXC_E_AFE_REF_VOLT_SEL_1500, MXC_E_AFE_DAC_REF_REFADC);

    /* set positive input to OpAmpD to DAC0 in follower mode (OpAmpD is the SMA connector on EvKit) */
    AFE_OpAmpSetup(OPAMP_NUM, MXC_E_AFE_OPAMP_MODE_OPAMP, MXC_E_AFE_OPAMP_POS_IN_DAC0P, MXC_E_AFE_OPAMP_NEG_IN_OUTx, MXC_E_AFE_IN_MODE_COMP_NCH_PCH);
    AFE_OpAmpEnable(OPAMP_NUM);

    /* DAC setup */
    DAC_Enable(DAC_NUM, MXC_E_DAC_PWR_MODE_FULL);
    DAC_SetRate(DAC_NUM, DAC_RATE, MXC_E_DAC_INTERP_MODE_DISABLED);
    DAC_SetStartMode(DAC_NUM, MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY);

    /* sine wave config; handle is allocated heap RAM and used for start/stop; could be free()'d if no longer needed */
    DAC_PatternConfig(DAC_NUM, &dac_wave_handle, sine_wave16bit, data_samples16bit, LOOPS, NULL, NULL);
}

#ifndef TOP_MAIN
int main(void)
{
    /* enable instruction cache */
    ICC_Enable();

    /* use the internal Ring Osc in 24MHz mode */
    CLKMAN_PLLConfig(MXC_E_CLKMAN_PLL_INPUT_SELECT_24MHZ_RO, MXC_E_CLKMAN_PLL_DIVISOR_SELECT_8MHZ, MXC_E_CLKMAN_STABILITY_COUNT_2_13_CLKS, PLL_BYPASS, PLL_8MHZ_ENABLE);
    CLKMAN_PLLEnable();
    CLKMAN_SetSystemClock(MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO);
    CLKMAN_WaitForSystemClockStable();
    
    /* adc clock is needed for OpAmp Configuration */
    CLKMAN_SetADCClock(MXC_E_CLKMAN_ADC_SOURCE_SELECT_PLL_8MHZ, MXC_E_ADC_CLK_MODE_FULL);
    
    /* set DAC0 CLK_SCALE for 24 MHz */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_DAC0, MXC_E_CLKMAN_CLK_SCALE_ENABLED);
    
    /* set systick to the RTC input 32.768kHz clock, not system clock; this is needed to keep JTAG alive */
    CLKMAN_SetRTOSMode(TRUE);

    /* setup DAC and YELLOW LED */
    dacsine_demo_init();

    /* initialize the SW1_TEST button on the MAX32600 EVKIT */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_GPIO, MXC_E_CLKMAN_STABILITY_COUNT_2_23_CLKS);

    /* set SW1 GPIO for input and interrupt driven */
    GPIO_SetInMode(SW1_PORT, SW1_PIN, MXC_E_GPIO_IN_MODE_INVERTED);

    /* set interrupt for when button is released */
    /* the interrupt is a falling edge when the button is released, because the GPIO was set to an inverted level in GPIO_SetInMode */
    GPIO_SetIntMode(SW1_PORT, SW1_PIN, MXC_E_GPIO_INT_MODE_FALLING_EDGE, trigger_wave);

    /* turn on Green LED */
    GPIO_SetOutMode(GREEN_LED_PORT, GREEN_LED_PIN, MXC_E_GPIO_OUT_MODE_NORMAL);
    GPIO_SetOutVal(GREEN_LED_PORT, GREEN_LED_PIN, 0);

    /* init yellow LED to off */
    GPIO_SetOutMode(YELLOW_LED_PORT, YELLOW_LED_PIN, MXC_E_GPIO_OUT_MODE_NORMAL);
    GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_OFF);
    
    for(;;) {
        /* default sleep mode is "LP2"; core powered up, ARM in "Wait For Interrupt" mode */
        PWR_Sleep();
    }
    return 0;
}
#endif /* TOP_MAIN */
