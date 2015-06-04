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

#include "mxc_config.h"
#include "board.h"

#include "string.h"
#include <inttypes.h>
#include <math.h>
#include "mxc_config.h"

#include "icc.h"
#include "ioman.h"
#include "clkman.h"
#include "gpio.h"
#include "power.h"
#include "systick.h"
#include "rtc.h"
#include "spi.h"
#include "tmr.h"
#include "uart.h"

#include "dac.h"
#include "adc.h"
#include "afe.h"

#include "trim_regs.h"

#include <stdio.h>
#include <string.h>

#define UART_BAUD_RATE 115200
#define LOOPS 0
#define CAPT_SAMPLES 1024

static adc_transport_t adc_capture_handle;
static uint16_t capt_buf0[CAPT_SAMPLES];
static uint16_t capt_buf1[CAPT_SAMPLES];

float excitation_frequency = 1000;

/* DAC0N 1vpp 1vcm const leaves it in flash, without in sram */
static const uint16_t sine_wave16bit[] = {
        0x82ff,
        0x7cdf,
        0x76ce,
        0x70db,
        0x6b15,
        0x6589,
        0x6046,
        0x5b59,
        0x56ce,
        0x52af,
        0x4f08,
        0x4be1,
        0x4941,
        0x4730,
        0x45b3,
        0x44cd,
        0x447f,
        0x44cd,
        0x45b3,
        0x4730,
        0x4941,
        0x4be1,
        0x4f08,
        0x52af,
        0x56ce,
        0x5b59,
        0x6046,
        0x6589,
        0x6b15,
        0x70db,
        0x76ce,
        0x7cdf,
        0x82ff,
        0x8920,
        0x8f31,
        0x9524,
        0x9aea,
        0xa076,
        0xa5b9,
        0xaaa6,
        0xaf31,
        0xb350,
        0xb6f7,
        0xba1e,
        0xbcbe,
        0xbecf,
        0xc04c,
        0xc132,
        0xc17f,
        0xc132,
        0xc04c,
        0xbecf,
        0xbcbe,
        0xba1e,
        0xb6f7,
        0xb350,
        0xaf31,
        0xaaa6,
        0xa5b9,
        0xa076,
        0x9aea,
        0x9524,
        0x8f31,
        0x8920,
};

static uint32_t data_samples16bit = sizeof(sine_wave16bit)/2;
static dac_transport_t dac_wave_handle;

#define CAPTURE_STOP TRUE  /* fill bufferes and stop */

/* state variables; volatile for non-register saving, different ISR level accesses */
static volatile uint8_t running = 0;
static uint8_t done_buf_num = 0;

/* mutex must be volatile because its set/cleared in two different ISRs */
static volatile uint8_t uart_mutex = 0;

/* function called in ISR context */
static void uart_done(int32_t status)
{
    uart_mutex = 0;
}


/* create an intermediate buffer to convert the ADC data to ASCII 'csv' for output,
 * 5 ascii digits + comma per sample */
static char ascii_buf0[CAPT_SAMPLES*6];
static char ascii_buf1[CAPT_SAMPLES*6];
static int bin2ascii(uint16_t *binp, char *ap, int count)
{
    int i;
    int siz = 0;
    for(i=0; i<count; i++) {
        siz += sprintf(&ap[siz],"%d",binp[i]);
        ap[siz++] = ',';
    }
    ap[siz++] = 0;
    return siz;
}

/* function called at ISR context when any buffer is completely filled */
static void capt_results(int32_t status, void *arg)
{
	if(status > 0)
	{
		DAC_PatternStop(&dac_wave_handle);
	}

	int print_bytes;
    
    if(done_buf_num == 0) { 
        print_bytes = bin2ascii(capt_buf0, ascii_buf0, CAPT_SAMPLES);
        done_buf_num = 1;
        
        /* Make sure the uart is not busy sending out the previous buffer.
         * PMU priority MUST be higher number (lower priority) than UART along
         * with ability for nested ISRs for this to work if the mutex is still set
         */
        while(uart_mutex)
            __WFI(); 
        uart_mutex = 1;
        
        UART_WriteAsync(0, (uint8_t*)ascii_buf0, print_bytes, uart_done); 
    } else {
        print_bytes = bin2ascii(capt_buf1, ascii_buf1, CAPT_SAMPLES);
        done_buf_num = 0;

        while(uart_mutex)
            __WFI(); 
        uart_mutex = 1;
        
        UART_WriteAsync(0, (uint8_t*)ascii_buf1, print_bytes, uart_done); 
    }    

    if(status == 1) {  /* last capture */
        done_buf_num = 0;
        running = 0;
        
        /* Turn off YELLOW LED */
        GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_OFF);
    }
}

/* DAC0 Initialization */
static void DAC_Init(void) {
    DAC_Enable(0, MXC_E_DAC_PWR_MODE_LVL2);
    DAC_SetStartMode(0, MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY);
    DAC_SetOutputRaw(0, sine_wave16bit[0]);
}

static void ADC_Init(float excitation_frequency)
{
    uint32_t adc_slp_cnt = 2000000.0/excitation_frequency - 100;

	/* Set ADC Clock Source to 24MHz Ring Oscillator */
	CLKMAN_SetADCClock(MXC_E_CLKMAN_ADC_SOURCE_SELECT_24MHZ_RO, MXC_E_ADC_CLK_MODE_THIRD);

   /* ADC Setup for 32 kHz sample rate */
	ADC_SetRate(1,1,7,adc_slp_cnt);
	ADC_SetMode(MXC_E_ADC_MODE_SMPLCNT_LOW_POWER,MXC_E_ADC_AVG_MODE_FILTER_OUTPUT,2,MXC_E_ADC_BI_POL_BIPOLAR,MXC_E_ADC_RANGE_FULL);
	ADC_SetMuxSel(MXC_E_ADC_PGA_MUX_CH_SEL_AIN0,MXC_E_ADC_PGA_MUX_DIFF_ENABLE);
	ADC_SetPGAMode(0,MXC_E_ADC_PGA_GAIN_2);
	ADC_SetStartMode(MXC_E_ADC_STRT_MODE_SOFTWARE);

    /* Enable ADC, Clear Interrupts */
    ADC_Enable();
    SysTick_Wait(333); 	/*~10 ms*/
}

static void ADC_Capture(float excitation_frequency) {
	uint16_t rate = 24000000.0/(64.0*excitation_frequency)-2;
	DAC_SetRate(0,rate,MXC_E_DAC_INTERP_MODE_DISABLED);
	DAC_SetStartMode(0,MXC_E_DAC_START_MODE_ADC_STROBE);

    /* Setup PMU parameters for DAC0 using dac_wave_handle - DAC Configuration */
    DAC_PatternStart(&dac_wave_handle);

    /* Lower system clock scale to conserve power */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_SYS,MXC_E_CLKMAN_CLK_SCALE_DIV_4);

    ADC_CaptureStart(&adc_capture_handle);

    CLKMAN_SetClkScale( MXC_E_CLKMAN_CLK_SYS,MXC_E_CLKMAN_CLK_SCALE_ENABLED);
}

/* ISR function called by button GPIO interrupt*/
void capture(void)
{
	if(!running) {
    	/* Turn on YELLOW LED */
        GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_ON);
        DAC_Init();
        ADC_Init(excitation_frequency);
        ADC_Capture(excitation_frequency);

        running = 1;
    } else {
        ADC_CaptureStop(&adc_capture_handle);
        DAC_PatternStop(&dac_wave_handle);
    }
}

#ifndef TOP_MAIN
int main(void)
{
    /* enable instruction cache */
    ICC_Enable();

    /* set systick to the RTC input 32.768kHz clock, not system clock; this is needed to keep JTAG alive */
    CLKMAN_SetRTOSMode(TRUE);
    
    /* use the internal Ring Osc in 24MHz mode */
    CLKMAN_SetSystemClock(MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO);
    CLKMAN_WaitForSystemClockStable();

    /* set GPIO clock to 24MHz */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_GPIO, MXC_E_CLKMAN_CLK_SCALE_ENABLED);

    /* enable real-time clock during run mode, this is needed to drive the systick with the RTC crystal */
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_RTC);

    /* trim the internal clock to get more accurate BAUD rate */
    CLKMAN_TrimRO_Start();
    SysTick_Wait(1635); /* let it run about 50ms */
    CLKMAN_TrimRO_Stop();

    /* enable the AFE Power */
    PWR_Enable(MXC_E_PWR_ENABLE_AFE);

    /* setup of Voltage Reference*/
    AFE_ADCVRefEnable(MXC_E_AFE_REF_VOLT_SEL_2048);
    AFE_DACVRefEnable(MXC_E_AFE_REF_VOLT_SEL_2048, MXC_E_AFE_DAC_REF_REFADC);

    /* set positive input to OpAmpD to DAC0 in follower mode (OpAmpD is the SMA connector on EvKit) */
    AFE_OpAmpSetup(3, MXC_E_AFE_OPAMP_MODE_OPAMP, MXC_E_AFE_OPAMP_POS_IN_DAC0P, MXC_E_AFE_OPAMP_NEG_IN_OUTx, MXC_E_AFE_IN_MODE_COMP_NCH_PCH);
    AFE_OpAmpEnable(3);

    DAC_PatternConfig(0,&dac_wave_handle, sine_wave16bit, data_samples16bit, LOOPS, NULL, NULL);
    ADC_CaptureConfig(&adc_capture_handle, capt_buf0, CAPT_SAMPLES,
                      capt_buf1, CAPT_SAMPLES,
                      capt_results, capt_buf0, CAPTURE_STOP);

    /* setup UART0 pins, mapping as EvKit to onboard FTDI UART to USB */
    IOMAN_UART0(MXC_E_IOMAN_MAPPING_A, TRUE, FALSE, FALSE);

    /* setup UART */
    UART_Config(0, UART_BAUD_RATE, FALSE, FALSE, FALSE);
    
    /* initialize the SW1_TEST button on the MAX32600EVKIT for manual trigger of application */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_GPIO, MXC_E_CLKMAN_STABILITY_COUNT_2_23_CLKS); /* slowest GPIO clock; its a human button */
    GPIO_SetInMode(SW1_PORT, SW1_PIN, MXC_E_GPIO_IN_MODE_INVERTED);
    GPIO_SetIntMode(SW1_PORT, SW1_PIN, MXC_E_GPIO_INT_MODE_FALLING_EDGE, capture); /* trigger on button release */

    /* setup GPIO for green LED status on EvKit */
    GPIO_SetOutMode(GREEN_LED_PORT, GREEN_LED_PIN, MXC_E_GPIO_OUT_MODE_OPEN_DRAIN_W_PULLUP);
    GPIO_SetOutVal(GREEN_LED_PORT, GREEN_LED_PIN, LED_ON);

    /* yellow LED will indicate active capture */
    GPIO_SetOutMode(YELLOW_LED_PORT, YELLOW_LED_PIN, MXC_E_GPIO_OUT_MODE_NORMAL);
    GPIO_SetOutVal(YELLOW_LED_PORT, YELLOW_LED_PIN, LED_OFF);

    /* set interrupt priority for PMU(ADC) lower (higher number) than UART (UART is default==0) */
    NVIC_SetPriority(PMU_IRQn, 1);
    NVIC_SetPriority(SPI0_IRQn, 2);
    
    for(;;) {
        /* default sleep mode is "LP2"; core powered up, ARM in "Wait For Interrupt" mode */
        PWR_Sleep();
    }
    return 0;
}
#endif
