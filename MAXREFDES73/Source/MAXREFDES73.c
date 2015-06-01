/** \file MAXREFDES73.c ******************************************************
 *
 *             Project: MAXREFDES73
 *             Filename: MAXREFDES73.c
 *         Description: This module contains the Main application for the
 *                      implementation of the example program for the MAXREFDES73.
 *
 *    Revision History:
 *\n                    05-01-2015    Rev 01.00    MG    Initial release.
 *
/*
 * Copyright (C) 2012 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED PRODUCTS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated Products
 * shall not be used except as stated in the Maxim Integrated Products
 * Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products retains all ownership rights.
 *
 ***************************************************************************/

/*!\mainpage Main Page
 *
 * \section intro_sec Introduction
 *
 * This is the code documentation for the MAXREFDES73# reference design.
 * \n
 * \n The Files page contains the File List page and the Globals page.
 * \n
 * \n The Globals page contains the Functions, Variables, and Macros sub-pages.
 * \n
 * \image html MAXREFDES73_Block_Diagram_V10.png "MAXREFDES73# System Block Diagram"
 * \n
 * \image html MAXREFDES73_Firmware_Main_Flowchart_V10.png "MAXREFDES73# Firmware Main Flowchart"
 * \n
 * \n
 * \image html MAXREFDES73_Firmware_ISR_Flowchart_V10.png "MAXREFDES73# Firmware ISR Flowchart"
 *
 */
#include "string.h"
#include <inttypes.h>
#include <math.h>

#include "wsf_types.h"
#include "wsf_os.h"
#include "wsf_buf.h"
#include "wsf_sec.h"
#include "hci_handler.h"
#include "dm_handler.h"
#include "l2c_handler.h"
#include "att_handler.h"
#include "smp_handler.h"
#include "app_api.h"
#include "l2c_api.h"
#include "smp_api.h"


#include "mxc_config.h"

#include "icc.h"
#include "ioman.h"
#include "clkman.h"
#include "gpio.h"
#include "power.h"
#include "systick.h"
#include "fit_api.h"
#include "hci_drv.h"
#include "rtc.h"
#include "spi.h"
#include "tmr.h"
#include "tmon.h"

#include "dac.h"
#include "adc.h"
#include "afe.h"

#include "trim_regs.h"

#define EM9301_ASSERT_RESET        1
#define EM9301_RELEASE_RESET       0
#define EM9301_SLEEP               0
#define EM9301_WAKEUP              1
#define BLE_MS_PER_TIMER_TICK      10  /* milliseconds per WSF timer tick */
#define SYSTICK_10_MS              327

/* LED pin mapping on the MAXREFDES73 */
#define LED_ON                     	0
#define LED_OFF                    	1

#define LED_PORT					0
#define RED_LED_PIN                	7
#define GREEN_LED_PIN              	6
//#define YELLOW_LED_PIN              5	// not installed.

#define SPI_PORT                   	0
#define BLE_SLAVE_SELECT           	0
#define FC_POLARITY                	1
#define FC_ENABLE                  	1
#define SS_POLARITY                	0
#define ACT_DELAY                  	1
#define INACT_DELAY                	0
/*
 *  BLE pin mapping on the MAXREFDES73: *
 *  WASP    EM9301
 *  ----    ------
 *  P0.0 ->  SCK      SPI master clock
 *  P0.1 ->  SDO      SPI MOSI
 *  P0.2 <-  SDI      SPI MISO
 *  P0.3 ->  CSN      SPI CSN (active low)
 *  P0.4 <-  IRQ      EM9301 ready to receive
 *  P0.5 ->  RST      RST (active high)
 */
#define SPI0_PORT                  	0
#define SPI0_SCK                   	0
#define SPI0_SDO                   	1
#define SPI0_SDI                   	2
#define SPI0_CSN                   	3

#define BLE_IRQ_PORT				0
#define BLE_IRQ_PIN					4
#define BLE_RST_PORT				0
#define BLE_RST_PIN					5

#define CHARGING_PORT				2
#define CHARGING_PIN				7

// NTC parameters in Steinhart¨CHart equation.
#define NTC_A 824.9707194577557
#define NTC_B 222.45487555218145
#define NTC_C 0.09559990904037504

uint8_t packet_0_buf[20], packet_1_buf[20], packet_2_buf[20];
uint8_t sweeping, sweepingDone;
uint8_t BATLEVEL = 100;
uint8_t preBATLEVEL = 100;
uint16_t packetNumber = 0;
uint8_t firstMeasurement = 1;
uint8_t BLEconnected = 0;
uint8_t BLEadvertising = 1;

/**************************************************************************************************
  Local Variables
**************************************************************************************************/
#define WSF_BUF_POOLS   4 /* Number of WSF buffer pools */

/*! Free memory for pool buffers. */
static uint8_t mainBufMem[768];

/*! Default pool descriptor. */
static wsfBufPoolDesc_t mainPoolDesc[WSF_BUF_POOLS] =
{
    {  16,  8 },
    {  32,  4 },
    {  64,  2 },
    { 128,  2 }
};

/* Initialize WSF(Wicentric Software Foundation) and BLE stack */
static void bleStackInit(uint8_t msPerTick)
{
    wsfHandlerId_t handlerId;
  
    /* init OS subsystems */
    WsfTimerInit(msPerTick);

    WsfBufInit(sizeof(mainBufMem), mainBufMem, WSF_BUF_POOLS, &mainPoolDesc[0]);
    WsfSecInit(); // security service
  
    /* initialize HCI */
    handlerId = WsfOsSetNextHandler(HciHandler);
    HciHandlerInit(handlerId);
  
    /* initialize DM */
    handlerId = WsfOsSetNextHandler(DmHandler);
    DmAdvInit();
    DmConnInit();
    DmConnSlaveInit();
    DmSecInit();
    DmHandlerInit(handlerId);

    /* initialize L2C */
    handlerId = WsfOsSetNextHandler(L2cSlaveHandler);
    L2cSlaveHandlerInit(handlerId);
    L2cInit();
    L2cSlaveInit();
  
    /* Initialize ATT */
    handlerId = WsfOsSetNextHandler(AttHandler);
    AttHandlerInit(handlerId);
    AttsInit();
    AttsIndInit();
    AttcInit();

    handlerId = WsfOsSetNextHandler(SmpHandler);
    SmpHandlerInit(handlerId);
    SmprInit();
  
    handlerId = WsfOsSetNextHandler(AppHandler);
    AppHandlerInit(handlerId);

    handlerId = WsfOsSetNextHandler(FitHandler);
    FitHandlerInit(handlerId);
}

/* Bring the EM9301 out of sleep (via WU pin) */
static void em9301_hw_wakeup(unsigned int wu)
{
    if (wu == EM9301_WAKEUP)
        GPIO_SetOutVal(SPI0_PORT, SPI0_CSN, EM9301_WAKEUP); /* Assert reset */
    else
        GPIO_SetOutVal(SPI0_PORT, SPI0_CSN, EM9301_SLEEP); /* Release reset */
}

/* Reset the EM9301 via external (active high) pin */
static void em9301_hw_reset(unsigned int reset)
{
    if (reset == EM9301_ASSERT_RESET)
        GPIO_SetOutVal(BLE_RST_PORT, BLE_RST_PIN, EM9301_ASSERT_RESET);	/* Assert reset */
    else
        GPIO_SetOutVal(BLE_RST_PORT, BLE_RST_PIN, EM9301_RELEASE_RESET);/* Release reset */
}

spi_slave_t ss;
uint8_t mainHciBuf[64];

static void spi_read_irq(void)
{
    if(GPIO_GetInVal(BLE_IRQ_PORT, BLE_IRQ_PIN))
    {
        SPI_ConfigSpecial(&ss, MXC_E_SPI_FLOW_CTRL_SR, FC_POLARITY, 1, 0, 1);
    	//SPI_ConfigSpecial(&ss, MXC_E_SPI_FLOW_CTRL_NONE, FC_POLARITY, 1, 0, 1);
        while(SPI_Setup(&ss));

        if(SPI_WaitFlowControl(&ss)) {
            memset(mainHciBuf, 0, sizeof(mainHciBuf));
            hciDrvRead(sizeof(mainHciBuf), &mainHciBuf[0]);
        }
    }
}

#define TMR0 0
static tmr32_config_t tmr32_cfg;

#define LOOPS 0 /* Run until Stopped */

/* globals for the capture data */
#define CAPT_SAMPLES0 184
#define CAPT_CYCLES0 46
#define CYCLE_START0 6

#define R1 10000
#define RCAL 10000

double ZMAG = 0;
double ZPHASE = 0;

static adc_transport_t adc_capture_handle0;
static adc_transport_t adc_capture_handle1;
static uint16_t capt_buf0[CAPT_SAMPLES0];
static uint16_t capt_buf1[CAPT_SAMPLES0];
static uint16_t calc_calA1[CAPT_CYCLES0];
static uint16_t calc_calB1[CAPT_CYCLES0];
static uint16_t calc_calA2[CAPT_CYCLES0];
static uint16_t calc_calB2[CAPT_CYCLES0];

static uint16_t calc_tstA1[CAPT_CYCLES0];
static uint16_t calc_tstB1[CAPT_CYCLES0];
static uint16_t calc_tstA2[CAPT_CYCLES0];
static uint16_t calc_tstB2[CAPT_CYCLES0];

/* DAC0N 1vpp 1vcm const leaves it in flash, without in sram */
static uint16_t sine_wave16bit[] = {
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

static void data_avg (void)
{
    //Averaging
    int i;
    double Ic = 0;
    double It = 0;
    double Qc = 0;
    double Qt = 0;
    double PhaseC = 0;
    double PhaseT = 0;
    double MagC = 0;
    double MagT = 0;

    double cal_a1 = 0;
    double cal_b1 = 0;
    double cal_a2 = 0;
    double cal_b2 = 0;

    double tst_a1 = 0;
    double tst_b1 = 0;
    double tst_a2 = 0;
    double tst_b2 = 0;

    for (i = CYCLE_START0  ; i < CAPT_CYCLES0; ++i)
    {
            cal_a1 = cal_a1 + calc_calA1[i];
            cal_a2 = cal_a2 + calc_calA2[i];
            cal_b1 = cal_b1 + calc_calB1[i];
            cal_b2 = cal_b2 + calc_calB2[i];
            tst_a1 = tst_a1 + calc_tstA1[i];
            tst_a2 = tst_a2 + calc_tstA2[i];
            tst_b1 = tst_b1 + calc_tstB1[i];
            tst_b2 = tst_b2 + calc_tstB2[i];
    }

     Ic = (cal_a1 - cal_a2)/(CAPT_CYCLES0 - CYCLE_START0 );
     It = (tst_a1 - tst_a2)/(CAPT_CYCLES0- CYCLE_START0 );
     Qc = (cal_b1 - cal_b2)/(CAPT_CYCLES0 - CYCLE_START0 );
     Qt = (tst_b1 - tst_b2)/(CAPT_CYCLES0 - CYCLE_START0 );
     PhaseC = atan2(Qc,Ic) ;
     PhaseT = atan2(Qt,It);
     MagC = sqrt((Ic*Ic) + (Qc * Qc));
     MagT = sqrt((It*It) + (Qt * Qt));

     ZMAG = ((MagC)/(MagT))*RCAL - R1;
     ZPHASE = (PhaseC - PhaseT)*180/3.14159;
}

static void print_results(void)
{
    int i;
    int k;

    k = CYCLE_START0 * 4;
    for (i = CYCLE_START0;i < CAPT_CYCLES0; ++i)
    {
    calc_calA1[i] = capt_buf0[k];
    calc_calB1[i] = capt_buf0[k+1];
    calc_calA2[i] = capt_buf0[k+2];
    calc_calB2[i] = capt_buf0[k+3];
    calc_tstA1[i] = capt_buf1[k];
    calc_tstB1[i] = capt_buf1[k+1];
    calc_tstA2[i] = capt_buf1[k+2];
    calc_tstB2[i] = capt_buf1[k+3];

    k = k + 4;
    }

    data_avg();

    /*if calibration is needed, based on lab data*/
#ifdef GSR1
    if (ZMAG > 1500)
       {
       ZMAG = ZMAG*1.0113 - 38.38;
       }
       else
       {
       ZMAG = ZMAG*1.0092 - 10.609;
       }
#endif

}

static void capt_results(int32_t exit_status, void *arg)
{
    if(exit_status > 0)
    {
        DAC_PatternStop(&dac_wave_handle);
    }
}

static void PwrSeq_Setup(void)
{
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_LDO);
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_RO);
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_RTC);
    PWR_DisableDevRun(MXC_E_PWR_DEVICE_SVM3);
    PWR_DisableDevRun(MXC_E_PWR_DEVICE_SVM1);

    mxc_pwrseq_reg0_t pwr_reg0 = MXC_PWRSEQ->reg0_f;
    pwr_reg0.pwr_first_boot = 1;
    MXC_PWRSEQ->reg0_f = pwr_reg0;


    PWR_Disable(MXC_E_PWR_ENABLE_AFE);
    PWR_Disable(MXC_E_PWR_ENABLE_STATIC_PULLUPS);
    PWR_Disable(MXC_E_PWR_ENABLE_USB);

    /* enabled dynamic clock gating for PWRMAN functions */
    mxc_pwrman_pwr_rst_ctrl_t pwr_rst_ctrl = MXC_PWRMAN->pwr_rst_ctrl_f;
    pwr_rst_ctrl.low_power_mode = 1;
    MXC_PWRMAN->pwr_rst_ctrl_f = pwr_rst_ctrl;
}

static void ClkMan_Setup(void)
{
    /* use the internal Ring Osc in 24MHz mode */
    CLKMAN_SetSystemClock(MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO);
    //CLKMAN_SetSystemClock(MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX);

    CLKMAN_WaitForSystemClockStable();

    /* set systick to the RTC input 32.768kHz clock, not system clock; this is needed to keep JTAG alive */
    CLKMAN_SetRTOSMode(TRUE);

    /* trim the internal clock */
    CLKMAN_TrimRO_Start();
    SysTick_Wait(0x663);
    CLKMAN_TrimRO_Stop();

    MXC_CLKMAN->clk_config = 0x00;

    mxc_clkman_clk_gate_ctrl0_t clk_gator0 = MXC_CLKMAN->clk_gate_ctrl0_f;
    mxc_clkman_clk_gate_ctrl1_t clk_gator1 = MXC_CLKMAN->clk_gate_ctrl1_f;
    mxc_clkman_clk_gate_ctrl2_t clk_gator2 = MXC_CLKMAN->clk_gate_ctrl2_f;

    clk_gator0.cm3_clk_gater = 1;
    clk_gator0.sysbus_clk_gater = 1;
    clk_gator0.icache_clk_gater = 1;
    clk_gator0.flash_clk_gater = 1;
    clk_gator0.sram_clk_gater = 1;
    clk_gator0.apb_bridge_clk_gater = 1;
    clk_gator0.sysman_clk_gater = 1;
    clk_gator0.uart0_clk_gater = 1;
    clk_gator0.uart1_clk_gater = 0;

    clk_gator0.watchdog0_clk_gater = 0;
    clk_gator0.watchdog1_clk_gater = 0;
    clk_gator0.usb_clk_gater = 0;
    MXC_CLKMAN->clk_gate_ctrl0_f = clk_gator0;

    clk_gator1.testacc_clk_gater = 0;
    clk_gator1.adc_clk_gater = 1;
    clk_gator1.dac12_0_clk_gater = 1;
    clk_gator1.dac12_1_clk_gater = 0;
    clk_gator1.dac8_0_clk_gater = 1;
    clk_gator1.dac8_1_clk_gater = 0;
    clk_gator1.pmu_clk_gater = 1;
    clk_gator1.lcd_clk_gater = 0;
    clk_gator1.gpio_clk_gater = 1;
    clk_gator1.pulsetrain_clk_gater = 0;
    clk_gator1.spi0_clk_gater = 1;
    clk_gator1.spi1_clk_gater = 0;
    clk_gator1.spi2_clk_gater = 0;
    clk_gator1.i2cm0_clk_gater = 0;
    clk_gator1.i2cm1_clk_gater = 0;
    clk_gator1.i2cs_clk_gater = 0;
    MXC_CLKMAN->clk_gate_ctrl1_f = clk_gator1;

    clk_gator2.crc_clk_gater = 0;
    clk_gator2.tpu_clk_gater = 0;
    clk_gator2.ssbmux_clk_gater = 1;
    clk_gator2.pad_clk_gater = 1;
    MXC_CLKMAN->clk_gate_ctrl2_f = clk_gator2;

    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_SYS,MXC_E_CLKMAN_CLK_SCALE_ENABLED);
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_RTC_INT_SYNC, MXC_E_CLKMAN_CLK_SCALE_ENABLED);
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_DAC0, MXC_E_CLKMAN_CLK_SCALE_ENABLED);
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_DAC2, MXC_E_CLKMAN_CLK_SCALE_DIV_256);

}

static void Voltage_Ref(void)
{
    /* Enable the AFE Power */
    PWR_Enable(MXC_E_PWR_ENABLE_AFE);

    /* Enable and Set the Voltage Reference for the DACs and ADC */
    AFE_ADCVRefEnable(MXC_E_AFE_REF_VOLT_SEL_2048);
    AFE_DACVRefEnable(MXC_E_AFE_REF_VOLT_SEL_2048, MXC_E_AFE_DAC_REF_REFADC);

}

static void AFE_VRefDisable(void)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.refadc_fast_pwrdn_en = 1;
    afe_ctrl1.refdac_fast_pwrdn_en = 1;
    afe_ctrl1.refadc_outen = 0;
    afe_ctrl1.refdac_outen = 0;
    afe_ctrl1.ref_pu = 0;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

static void AFE_Disable(void)
{
    PWR_Disable(MXC_E_PWR_ENABLE_AFE);
    AFE_VRefDisable();
    AFE_OpAmpDisable(0);
    AFE_OpAmpDisable(1);
    AFE_OpAmpDisable(3);
    DAC_Disable(0);
    DAC_Disable(2);
    ADC_Disable();

    /* Sets the ADC Clock back to default values */
    mxc_adc_ctrl0_t adc_ctrl0 = MXC_ADC->ctrl0_f;
    adc_ctrl0.adc_clk_mode = 0x0;
    MXC_ADC->ctrl0_f = adc_ctrl0;
    mxc_clkman_clk_ctrl_t clk_ctrl = MXC_CLKMAN->clk_ctrl_f;
    clk_ctrl.adc_gate_n = 0;
    clk_ctrl.adc_source_select = 0;
    MXC_CLKMAN->clk_ctrl_f = clk_ctrl;

    /* Clears the ADC interrupt */
    mxc_adc_intr_t adc_int = MXC_ADC->intr_f; //clear the interrupt
    MXC_ADC->intr_f = adc_int;
}

static void Switch_Setup (int i)
{
    if (i == 0)
    {
        AFE_SetSwitchState(0,1);
        AFE_SetSwitchState(2,1);
        AFE_SetSwitchState(1,0);
        AFE_SetSwitchState(3,0);
    }

    if (i == 1)
    {
        AFE_SetSwitchState(0,0);
        AFE_SetSwitchState(2,0);
        AFE_SetSwitchState(1,1);
        AFE_SetSwitchState(3,1);
    }
}

static void AFE_Init(int i)
{
#ifdef GSR3
    MXC_DAC0->trm = 0xffff4200;
    MXC_DAC2->reg = 0x002400ff;

#endif

    /* Setup DAC0 for DC LEvel Set */
    DAC_Enable(0,  MXC_E_DAC_PWR_MODE_LVL2);
    DAC_SetStartMode(0, MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY);
    DAC_SetOutputRaw(0,sine_wave16bit[0]);

    /* Setup DAC2 for DC LEvel Set */
    DAC_Enable(2,MXC_E_DAC_PWR_MODE_LVL0);
    DAC_SetStartMode(2,MXC_E_DAC_START_MODE_FIFO_NOT_EMPTY);
    DAC_SetOutput(2,140);

   /* i == 0 used for Calibration Capture, i == 1 used for Test Load Capture */
    if (i == 0)
    {
        //AFE_OpAmpSetup(0,0,MXC_E_AFE_OPAMP_POS_IN_PAD_INxP,MXC_E_AFE_OPAMP_NEG_IN_OUTx,MXC_E_AFE_IN_MODE_COMP_NCH_PCH);
        AFE_OpAmpSetup(0,0,MXC_E_AFE_OPAMP_POS_IN_PAD_INxP,MXC_E_AFE_OPAMP_NEG_IN_OUTx,MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH);
        //AFE_NpadSetup(0,MXC_E_AFE_OPAMP_NEG_PAD_DAC0N);
        AFE_OpAmpEnable(0);
        //AFE_OpAmpSetup(1,0,MXC_E_AFE_OPAMP_POS_IN_DAC2P,MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN,MXC_E_AFE_IN_MODE_COMP_NCH_PCH);
        AFE_OpAmpSetup(1,0,MXC_E_AFE_OPAMP_POS_IN_DAC2P,MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN,MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH);
        AFE_OpAmpEnable(1);
        //AFE_OpAmpSetup(3,0,MXC_E_AFE_OPAMP_POS_IN_DAC0N,MXC_E_AFE_OPAMP_NEG_IN_OUTx,MXC_E_AFE_IN_MODE_COMP_NCH_PCH);
        AFE_OpAmpSetup(3,0,MXC_E_AFE_OPAMP_POS_IN_DAC0N,MXC_E_AFE_OPAMP_NEG_IN_OUTx,MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH);
        AFE_OpAmpEnable(3);
        Switch_Setup(0);
        //RTC_delay(10); 	/* Stabilization after power up of Voltage Reference, OpAmps and DACs */
        SysTick_Wait(333); 	/*~10 ms*/
    }

    if (i == 1)
    {
        Switch_Setup(1);
    }

}

static void ADC_Init(int i, float excitation_frequency)
{
    uint32_t adc_slp_cnt = 2000000.0/excitation_frequency - 100;
	/* i == 0 used for Calibration Capture, i == 1 used for Test Load Capture */
    if (i == 0)
    {
        /* Set MCLK to Divide/3 mode 0'b10 */
        mxc_adc_ctrl0_t adc_ctrl0 = MXC_ADC->ctrl0_f;
        adc_ctrl0.adc_clk_mode = 0x2;
        MXC_ADC->ctrl0_f = adc_ctrl0;

        /* Set ADC Clock Source to 24MHz Ring Oscillator */
        CLKMAN_SetADCClock(MXC_E_CLKMAN_ADC_SOURCE_SELECT_24MHZ_RO);

       /* ADC Setup for 32 kHz sample rate */
        ADC_SetRate(1,1,7,adc_slp_cnt);

        ADC_SetMode(MXC_E_ADC_MODE_SMPLCNT_LOW_POWER,MXC_E_ADC_AVG_MODE_FILTER_OUTPUT,2,MXC_E_ADC_BI_POL_BIPOLAR,MXC_E_ADC_RANGE_FULL);
        ADC_SetMuxSel(MXC_E_ADC_PGA_MUX_CH_SEL_AIN0,MXC_E_ADC_PGA_MUX_DIFF_ENABLE);
        ADC_SetPGAMode(0,MXC_E_ADC_PGA_GAIN_2);
        ADC_SetStartMode(MXC_E_ADC_STRT_MODE_SOFTWARE);
    }

    /* Enable ADC, Clear Interrupts */
        ADC_Enable();
}

static void ADC_Capt(int i, float excitation_frequency)
{
    /* Setup of DAC0 for Sinewave generation at 8 kHz, to Start on ADC Strobe */
    /* frequency,	dac_rate_cnt,	adc_sleep_cnt
     * 100,			3748,			19900
     * 200,			1873,			9900
     * 500,			748,			3900
     * 1000,		373, 			1900
     * 1953.125,	190, 			924
     * 5000,		73,				300
     * 7812.5,		46,				156
     * 12500,		28, 			60
     * 15625,		22,				28
     */
	uint16_t rate = 24000000.0/(64.0*excitation_frequency)-2;
    DAC_SetRate(0,rate,MXC_E_DAC_INTERP_MODE_DISABLED);
    DAC_SetStartMode(0,MXC_E_DAC_START_MODE_ADC_STROBE);


    /* Setup PMU parameters for DAC0 using dac_wave_handle - DAC Configuration */
    DAC_PatternStart(&dac_wave_handle);

    /* disable ssb mux clock gator, no longer needed */
    mxc_clkman_clk_gate_ctrl2_t clk_gator2 = MXC_CLKMAN->clk_gate_ctrl2_f;
    clk_gator2.ssbmux_clk_gater = 0;
    MXC_CLKMAN->clk_gate_ctrl2_f = clk_gator2;

    /* Lower system clock scale to conserve power */
    CLKMAN_SetClkScale( MXC_E_CLKMAN_CLK_SYS,MXC_E_CLKMAN_CLK_SCALE_DIV_4);

    if (i == 0)
    {
        /* Start ADC Capture for Calibration path */
        ADC_CaptureStart(&adc_capture_handle0);
        PWR_SetMode(MXC_E_PWR_MODE_LP2, NULL);
        PWR_Sleep();
    }

   if (i == 1)
    {
       /* Start ADC Capture for Test Load path */
        ADC_CaptureStart(&adc_capture_handle1);
        PWR_SetMode(MXC_E_PWR_MODE_LP2, NULL);
        PWR_Sleep();
    }
   CLKMAN_SetClkScale( MXC_E_CLKMAN_CLK_SYS,MXC_E_CLKMAN_CLK_SCALE_ENABLED);

}

static void ADC_Measure(float excitation_frequency)
{
   /* Setup Voltage Reference */
    Voltage_Ref();

   /* Measurement of Calibration path */
    AFE_Init(0);
    ADC_Init(0, excitation_frequency);
    ADC_Capt(0, excitation_frequency);

   /* Measurement of Test Load Path */
    AFE_Init(1);
    ADC_Init(1, excitation_frequency);
    ADC_Capt(1, excitation_frequency);

    /*Allow DAC to finish, prior to disabling the AFE */
    SysTick_Wait(10); /*~0.305 ms*/

    /* Disable all Analog Components */
    AFE_Disable();

    /* Turn on the ssb mux clock gator */
    mxc_clkman_clk_gate_ctrl2_t clk_gator2 = MXC_CLKMAN->clk_gate_ctrl2_f;
    clk_gator2.ssbmux_clk_gater = 1;
    MXC_CLKMAN->clk_gate_ctrl2_f = clk_gator2;
}

/* Called by tmr0_isr */
static uint32_t tmr0_counter;
static void tmr32_led(uint32_t ticks)
{
	if((BLEadvertising == 0) && (BLEconnected == 0))
		return;

	static uint8_t yellow_led_off = 1;

    /* Update our BLE stack timers */
    WsfTimerUpdate(1);
    wsfOsDispatcher();

    if(BLEconnected && (tmr0_counter++ == 50))
    {
    	if (yellow_led_off)
    	{
    		// start GSR measurements
    		GPIO_SetOutVal(LED_PORT, RED_LED_PIN, LED_ON);

    		if(sweeping)
    		{
    			uint8_t loop;
    			for(loop = 0; loop < 8; loop++)
    			{
    				// clear power sequencer wake-up flags
    			    PWR_ClearFlags();

    			    // Function for Setting up Part to collect measurement
    			    switch(loop)
    			    {
    			    	case 0:
    			    		ADC_Measure(100.0);
    			    		break;
    			    	case 1:
    			    		ADC_Measure(200.0);
    			    		break;
    			    	case 2:
    			    		ADC_Measure(500.0);
    			    		break;
    			    	case 3:
    			    		ADC_Measure(1000.0);
    			    		break;
    			    	case 4:
    			    		ADC_Measure(1953.125);
    			    		break;
    			    	case 5:
    			    		ADC_Measure(5000.0);
    			    		break;
    			    	case 6:
    			    		ADC_Measure(12500.0);
    			    		break;
    			    	case 7:
    			    		ADC_Measure(15625.0);
    			    		break;
    			    }

    			    // Perform calculations and print results
    			    print_results();
       			    // place ZMAG to the GSR1_buf.

    			    if(loop < 4)
    			    {
    			    	*(packet_1_buf+(loop+1)*4+0) = ((uint32_t)ZMAG & 0xFF000000) >> 24;
    			    	*(packet_1_buf+(loop+1)*4+1) = ((uint32_t)ZMAG & 0x00FF0000) >> 16;
    			    	*(packet_1_buf+(loop+1)*4+2) = ((uint32_t)ZMAG & 0x0000FF00) >> 8;
    			    	*(packet_1_buf+(loop+1)*4+3) = (uint32_t)ZMAG & 0x000000FF;
    			    }
    			    else
    			    {
    			    	*(packet_2_buf+((loop-4)+1)*4+0) = ((uint32_t)ZMAG & 0xFF000000) >> 24;
    			    	*(packet_2_buf+((loop-4)+1)*4+1) = ((uint32_t)ZMAG & 0x00FF0000) >> 16;
    			    	*(packet_2_buf+((loop-4)+1)*4+2) = ((uint32_t)ZMAG & 0x0000FF00) >> 8;
    			    	*(packet_2_buf+((loop-4)+1)*4+3) = (uint32_t)ZMAG & 0x000000FF;
    			    }
    			}
    			*packet_1_buf = (packetNumber & 0xFF00) >> 8;
    			*(packet_1_buf+1) = packetNumber & 0x00FF;
    			packetNumber++;
    			*(packet_1_buf+2) = 0;
    			*(packet_1_buf+3) = 1;
    			*packet_2_buf = (packetNumber & 0xFF00) >> 8;
    			*(packet_2_buf+1) = packetNumber & 0x00FF;
    			packetNumber++;
    			*(packet_2_buf+2) = 0;
    			*(packet_2_buf+3) = 2;

    			sweepingDone = 1;
    			//sweeping = 0;
    		}
    		else	// not sweeping
    		{
    			// clear power sequencer wake-up flags
    			PWR_ClearFlags();

    			// Function for Setting up Part to collect measurement
    			ADC_Measure(7812.5);

    			// Perform calculations and print results
    			print_results();

        		// measure temperature
        	    /* Enable the AFE Power */
        	    PWR_Enable(MXC_E_PWR_ENABLE_AFE);
        	    /* Enable and Set the Voltage Reference for the ADC */
        	    AFE_ADCVRefEnable(MXC_E_AFE_REF_VOLT_SEL_2048);
        	    /* Setup ADC decimation filter to average 1 sample */
        	    ADC_SetMode(MXC_E_ADC_MODE_SMPLCNT_FULL_RATE, MXC_E_ADC_AVG_MODE_FILTER_OUTPUT, 7, 0, MXC_E_ADC_RANGE_FULL);
        	    /* Set MCLK to Divide/3 mode 0'b10 */
        	    mxc_adc_ctrl0_t adc_ctrl0 = MXC_ADC->ctrl0_f;
        	    adc_ctrl0.adc_clk_mode = 0x2;
        	    MXC_ADC->ctrl0_f = adc_ctrl0;
        	    /* Set ADC Clock Source to 24MHz Ring Oscillator */
        	    CLKMAN_SetADCClock(MXC_E_CLKMAN_ADC_SOURCE_SELECT_24MHZ_RO);
        	    ADC_SetRate(1,1,0x3F,0);
        	    /* Setup current source for external temperature sensor*/
        	    TMON_Enable(1);
        	    TMON_SetCurrent(0);		// 4uA
                /* PGA = 2*/
        	    ADC_SetPGAMode(0, MXC_E_ADC_PGA_GAIN_2);
        	    /* Setup ADC input multiplexor and disable a differential measurement */
        	    ADC_SetMuxSel(MXC_E_ADC_PGA_MUX_CH_SEL_AIN1, 0);
        	    /* enable ADC */
        	    ADC_Enable();

        	    /* wait 1 ms to get stable ADC capture */
        	    SysTick_Wait(32);

        	    /* Read NTC sample */
        	    uint16_t NTCCODE = ADC_ManualRead();

        	    // measure battery voltage
        	    /* PGA = 1 */
        	    ADC_SetPGAMode(0, MXC_E_ADC_PGA_GAIN_1);
        	    /* Setup ADC input multiplexor and disable a differential measurement */
        	    ADC_SetMuxSel(MXC_E_ADC_PGA_MUX_CH_SEL_AIN2, 0);
        	    /* enable ADC */
        	    ADC_Enable();

        	    /* wait 1 ms to get stable ADC capture */
        	    SysTick_Wait(32);

        	    /* Read VBAT sample */
        	    uint16_t BATCODE = ADC_ManualRead();

        	    // measure charging current
        	    // If charging current is less than 1mA (ADC code = 30), battery is fully charged.
        	    /* Setup ADC input multiplexor and disable a differential measurement */
        	    uint8_t CHARGING = !GPIO_GetInVal(CHARGING_PORT, CHARGING_PIN);

        	    if(CHARGING)
        	    {
            	    ADC_SetMuxSel(MXC_E_ADC_PGA_MUX_CH_SEL_AIN5, 0);
            	    /* enable ADC */
            	    ADC_Enable();
            	    /* wait 1 ms to get stable ADC capture */
            	    SysTick_Wait(32);
            	    /* Read ICHARGING sample */
            	    uint16_t CHARGINGCODE = ADC_ManualRead();
            	    // TO DO...
        	    }

        	    /* Disable ADC reference voltage */
        	    AFE_ADCVRefDisable();
        	    /* Disable TMON */
        	    TMON_Disable();
        	    /* Disable ADC */
        	    ADC_Disable();
        	    PWR_Disable(MXC_E_PWR_ENABLE_AFE);

        	    // calculate temperature
        	    double RNTC = NTCCODE*2.048/(0.065535*2.0*4.0);
        	    double TNTC = 1000000.0/((double)(NTC_A) + (double)(NTC_B) * log(RNTC) + (double)NTC_C * pow(log(RNTC), 3)) - 273.15;

        	    // build the packet
        		*packet_0_buf = (packetNumber & 0xFF00) >> 8;
    			*(packet_0_buf+1) = packetNumber & 0x00FF;
    			packetNumber++;
    			*(packet_0_buf+2) = 0;
    			*(packet_0_buf+3) = 0;
    			*(packet_0_buf+4) = (int)TNTC & 0xFF;
    			*(packet_0_buf+5) = TNTC>0?(TNTC- (int)TNTC)*100:((int)TNTC-TNTC)*100;
    			// place ZMAG to the packet
    			*(packet_0_buf+6) = ((uint32_t)ZMAG & 0xFF000000) >> 24;
    			*(packet_0_buf+7) = ((uint32_t)ZMAG & 0x00FF0000) >> 16;
    			*(packet_0_buf+8) = ((uint32_t)ZMAG & 0x0000FF00) >> 8;
    			*(packet_0_buf+9) = (uint32_t)ZMAG & 0x000000FF;


        		// roughly calculate battery level %.
        		double VBAT = BATCODE * 2.048 * 2.0/65535.0;
        		if(VBAT >= 4.05)
        			BATLEVEL = 100;
        		else if (VBAT < 2.5)
        			BATLEVEL = 0;
        		else
        			BATLEVEL = (VBAT-2.5)/1.55*100.0;

        		if(CHARGING)
        		{
        			if(firstMeasurement)
        				preBATLEVEL = BATLEVEL;
        			else
        				BATLEVEL > preBATLEVEL? (preBATLEVEL = BATLEVEL) : (BATLEVEL = preBATLEVEL);

        			BATLEVEL |= 0x80;	// include the charging bit.
        		}
        		else
        		{
        			if(firstMeasurement)
        				preBATLEVEL = BATLEVEL;
        			else
        				BATLEVEL < preBATLEVEL? (preBATLEVEL = BATLEVEL) : (BATLEVEL = preBATLEVEL);

        			BATLEVEL &= 0x7F;	// include the charging bit.
        		}

        		firstMeasurement = 0;
    		}

    		yellow_led_off = 0;
    		GPIO_SetOutVal(LED_PORT, RED_LED_PIN, LED_OFF);
    	}
    	else
    		yellow_led_off = 1;

        tmr0_counter = 0;
    }
}

int main(void)
{
	/* enable instruction cache */
    ICC_Enable();
    PwrSeq_Setup();
    ClkMan_Setup();
    PWR_Init();

    firstMeasurement = 1;
    sweeping = 0;
    sweepingDone = 0;
    packetNumber = 0;
    firstMeasurement = 1;
    BLEconnected = 0;
    BLEadvertising = 1;

    DAC_PatternConfig(0,&dac_wave_handle, sine_wave16bit, data_samples16bit, LOOPS, NULL, NULL);
    ADC_CaptureConfig(&adc_capture_handle0,capt_buf0, CAPT_SAMPLES0, NULL, 0,capt_results, capt_buf0, 1);
    ADC_CaptureConfig(&adc_capture_handle1,capt_buf1, CAPT_SAMPLES0, NULL, 0,capt_results, capt_buf1, 1);

    /* setup SPI pins */
    IOMAN_SPI0(MXC_E_IOMAN_MAPPING_A, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0);

    /* set GPIO clock to 24MHz */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_GPIO, MXC_E_CLKMAN_CLK_SCALE_ENABLED);

    /* set SPI0 clock to 24MHz */
    CLKMAN_SetClkScale(MXC_E_CLKMAN_CLK_SPI0, MXC_E_CLKMAN_CLK_SCALE_ENABLED);

    /* enable real-time clock during run mode, this is needed to drive the systick with the RTC crystal */
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_RTC);

    /* setup GPIO for the LED */
    GPIO_SetOutVal(LED_PORT, GREEN_LED_PIN, 1);
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);
    GPIO_SetOutMode(LED_PORT, GREEN_LED_PIN, MXC_E_GPIO_OUT_MODE_OPEN_DRAIN_W_PULLUP);
    GPIO_SetOutMode(LED_PORT, RED_LED_PIN, MXC_E_GPIO_OUT_MODE_OPEN_DRAIN_W_PULLUP);

    // flash RED led to indicate system boot up
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 0);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 0);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 0);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 0);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 0);
    SysTick_Wait(6104);		// 200ms
    GPIO_SetOutVal(LED_PORT, RED_LED_PIN, 1);

    /* setup GPIO for the charging indicator */
    GPIO_SetInMode(CHARGING_PORT, CHARGING_PIN, MXC_E_GPIO_IN_MODE_NORMAL);

    /* Setup BLE chip IRQ/CSN/RST pins */
    GPIO_SetInMode(BLE_IRQ_PORT, BLE_IRQ_PIN, MXC_E_GPIO_IN_MODE_NORMAL);
    GPIO_SetOutMode(BLE_RST_PORT, BLE_RST_PIN, MXC_E_GPIO_OUT_MODE_NORMAL);
    GPIO_SetOutMode(SPI0_PORT, SPI0_CSN, MXC_E_GPIO_OUT_MODE_NORMAL);

    /* Assert CSN and deassert RST_H */
    GPIO_SetOutVal(BLE_RST_PORT, BLE_RST_PIN, EM9301_RELEASE_RESET);
    GPIO_SetOutVal(SPI0_PORT, SPI0_CSN, EM9301_SLEEP);

    /* Delay for 100us */
    SysTick_Wait(3);

    /* Hold EM3901 in reset for at least 1ms */
    em9301_hw_reset(EM9301_ASSERT_RESET);

    /* Wait for 2ms */
    SysTick_Wait(64);

    /* Relese EM9301 from reset */
    em9301_hw_reset(EM9301_RELEASE_RESET);

    /* Initialize SPI */
    SPI_Config(&ss, SPI_PORT);
    SPI_ConfigClock(&ss, 3, 3, 0, 0, 0, 0);

    /* wait at least 100ns after asserting CS */
    SPI_ConfigSlaveSelect(&ss, BLE_SLAVE_SELECT, SS_POLARITY, ACT_DELAY, INACT_DELAY);

    NVIC_SetPriority(SPI0_IRQn, 2);
    NVIC_SetPriority(GPIO_P0_IRQn, 6);
    NVIC_SetPriority(TMR0_IRQn, 6);

    /* Setup IRQ handler */
    GPIO_SetIntMode(BLE_IRQ_PORT, BLE_IRQ_PIN, MXC_E_GPIO_INT_MODE_HIGH_LVL, &spi_read_irq);

    /* Enable tmr0 callback */
    uint32_t ticks;
    uint8_t prescale;
    memset(&tmr32_cfg, 0, sizeof(tmr32_cfg));
    TMR32_PeriodToTicks(10, MXC_E_TMR_PERIOD_UNIT_MILLISEC, &ticks, &prescale);
    TMR32_Config(&tmr32_cfg, TMR0, MXC_E_TMR_MODE_CONTINUOUS, ticks, prescale, 0, 0);
    TMR32_Start(&tmr32_cfg, tmr32_led);

    /* initialize BLE stack */
    bleStackInit(BLE_MS_PER_TIMER_TICK);
            
    /* Configure advertising and services */
    FitStart();

    for(;;) {
    	if(BLEconnected == 0 && BLEadvertising == 0)
    		PWR_SetMode(MXC_E_PWR_MODE_LP1, NULL);
    	else
    		PWR_SetMode(MXC_E_PWR_MODE_LP2, NULL);

        PWR_Sleep();
    }

    return 0;
}
