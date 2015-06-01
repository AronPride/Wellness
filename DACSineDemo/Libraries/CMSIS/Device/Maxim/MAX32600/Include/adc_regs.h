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

#ifndef _MXC_ADC_REGS_H
#define _MXC_ADC_REGS_H

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
 * @file  adc_regs.h
 * @addtogroup adc ADC
 * @{
 */

/**
 * @brief Defines ADC Clock Divider Options, Must Run at 8MHz
 */
typedef enum {
    /** Do not divide input clock */
    MXC_E_ADC_CLK_MODE_FULL   = 0,
    /** Divide input clock by 2 */
    MXC_E_ADC_CLK_MODE_HALF   = 1,
    /** Divide input clock by 3 */
    MXC_E_ADC_CLK_MODE_THIRD  = 2,
    /** Divide input clock by 4 */
    MXC_E_ADC_CLK_MODE_FOURTH = 3,
    /** Divide input clock by 6 */
    MXC_E_ADC_CLK_MODE_SIX    = 4,
    /** Divide input clock by 8 */
    MXC_E_ADC_CLK_MODE_EIGHTH = 5,
    /** Divide input clock by 12 */
    MXC_E_ADC_CLK_MODE_TWELVE = 6,
} mxc_adc_clk_mode;
    
/**
 * @brief Defines ADC Modes.
 */
typedef enum {
    /** Single Mode Full Rate */
    MXC_E_ADC_MODE_SMPLCNT_FULL_RATE = 0,
    /** Single Mode Low Power */
    MXC_E_ADC_MODE_SMPLCNT_LOW_POWER = 1,
    /** Continuous Mode Full Rate */
    MXC_E_ADC_MODE_CONTINUOUS_FULL_RATE = 2,
    /** Continuous Mode Low Power */
    MXC_E_ADC_MODE_CONTINUOUS_LOW_POWER = 3,
    /** Single Mode Full Rate with Scan Enabled */
    MXC_E_ADC_MODE_SMPLCNT_SCAN_FULL_RATE = 8,
    /** Single Mode Low Power with Scan Enabled */
    MXC_E_ADC_MODE_SMPLCNT_SCAN_LOW_POWER = 9,
    /** Continuous Mode Full Rate with Scan Enabled */
    MXC_E_ADC_MODE_CONTINUOUS_SCAN_FULL_RATE = 10,
    /** Continuous Mode Low Power with Scan Enabled */
    MXC_E_ADC_MODE_CONTINUOUS_SCAN_LOW_POWER = 11
} mxc_adc_mode_t;


/**
 * @brief Defines ADC Range Control.
 */
typedef enum {
    /** Bi-polar Operation (-Vref/2 -> Vref/2) */
    MXC_E_ADC_RANGE_HALF = 0,
    /** Bi-polar Operation (-Vref -> Vref) */
    MXC_E_ADC_RANGE_FULL
} mxc_adc_range_t;

/**
 * @brief Defines ADC Range Control.
 */
typedef enum {
    /** Uni-polar operation (0 -> Vref) */
    MXC_E_ADC_BI_POL_UNIPOLAR = 0,
    /** Bi-polar operation see ADC Range Control */
    MXC_E_ADC_BI_POL_BIPOLAR
} mxc_adc_bi_pol_t;

/**
 * @brief Defines Decimation Filter Modes.
 */
typedef enum {
    /** Decimation Filter ByPassed */
    MXC_E_ADC_AVG_MODE_FILTER_BYPASS = 0,
    /** Output Average Only*/
    MXC_E_ADC_AVG_MODE_FILTER_OUTPUT,
    /** Output Average and Raw Data (Test Mode Only) */
    MXC_E_ADC_AVG_MODE_FILTER_OUTPUT_RAW
} mxc_adc_avg_mode_t;

/**
 * @brief Defines ADc StartMode Modes.
 */
typedef enum {
    /** StarMode via Software */
    MXC_E_ADC_STRT_MODE_SOFTWARE = 0,
    /** StarMode via PulseTrain */
    MXC_E_ADC_STRT_MODE_PULSETRAIN
} mxc_adc_strt_mode_t;

typedef struct
{
    uint32_t adc_wake_cnt               : 4;
    uint32_t adc_tst_en                 : 1;
    uint32_t adc_strt_mode              : 1;
    uint32_t range                      : 1;
    uint32_t bi_pol                     : 1;
    uint32_t adc_dv_reg                 : 1;
    uint32_t adc_dv                     : 1;
    uint32_t adc_lmt_dmode              : 1;
    uint32_t adc_smp_ext                : 1;
    uint32_t adc_clk_en                 : 1;
    uint32_t cpu_adc_rst                : 1;
    uint32_t cpu_adc_strt               : 1;
    uint32_t adc_en                     : 1;
    uint32_t avg_sgn_x                  : 1;
    uint32_t                            : 1;
    uint32_t adc_fifo_full              : 1;
    uint32_t adc_fifo_empty             : 1;
    uint32_t avg_mode                   : 2;
    uint32_t cpu_dac_strt               : 1;
    uint32_t test_clk_en                : 1;
    uint32_t adc_clk_mode               : 3;
    uint32_t                            : 1;
    uint32_t mode                       : 4;
} mxc_adc_ctrl0_t;

/* Bitband definitions */
#define ADC_CTRL0_ADC_CPU_STRT_POS  14
#define ADC_CTRL0_ADC_EN_POS        15

/**
 * @brief Defines Mux Channel Select for the Positive Input to the ADC.
 */  
typedef enum {
    /** Single Mode Input AIN0+; Diff Mode AIN0+/AIN8-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN0 = 0,
    /** Single Mode Input AIN1+; Diff Mode AIN1+/AIN9-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN1 = 1,
    /** Single Mode Input AIN2+; Diff Mode AIN2+/AIN10- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN2 = 2,
    /** Single Mode Input AIN3+; Diff Mode AIN3+/AIN11- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN3 = 3,
    /** Single Mode Input AIN4+; Diff Mode AIN4+/AIN12- */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN4 = 4,
    /** Single Mode Input AIN5+; Diff Mode AIN5+/AIN13-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN5 = 5,
    /** Single Mode Input AIN6+; Diff Mode AIN6+/AIN14-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN6 = 6,
    /** Single Mode Input AIN7+; Diff Mode AIN7+/AIN15-  */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN7 = 7,
    /** Single Mode Input AIN8+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN8 = 8,
    /** Single Mode Input AIN9+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN9 = 9,
    /** Single Mode Input AIN10+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN10 = 10,
    /** Single Mode Input AIN11+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN11 = 11,
    /** Single Mode Input AIN12+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN12 = 12,
    /** Single Mode Input AIN13+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN13 = 13,
    /** Single Mode Input AIN14+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN14 = 14,
    /** Single Mode Input AIN15+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN15 = 15,
    /** Positive Input VSSADC */
    MXC_E_ADC_PGA_MUX_CH_SEL_VSSADC = 16,
    /** Positive Input TMON_R */
    MXC_E_ADC_PGA_MUX_CH_SEL_TMON_R = 17,
    /** Positive Input VDDA/4 */
    MXC_E_ADC_PGA_MUX_CH_SEL_VDDA4 = 18,
    /** Positive Input PWRMAN_TST */
    MXC_E_ADC_PGA_MUX_CH_SEL_PWRMON_TST = 19,
    /** Positive Input Ain0Div */
    MXC_E_ADC_PGA_MUX_CH_SEL_AIN0DIV = 20,
    /** Positive Input OpAmp OUTA */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTA = 32,
    /** Positive Input OpAmp OUTB */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTB = 33,
    /** Positive Input OpAmp OUTC */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTC = 34,
    /** Positive Input OpAmp OUTD */
    MXC_E_ADC_PGA_MUX_CH_SEL_OUTD = 35,
    /** Positive INA+ */
    MXC_E_ADC_PGA_MUX_CH_SEL_INAPLUS = 36,
    /** Positive SNO_or */
    MXC_E_ADC_PGA_MUX_CH_SEL_SNO_OR = 37,
    /** Positive SCM_or */
    MXC_E_ADC_PGA_MUX_CH_SEL_SCM_OR = 38,
    /** Positive TPROBE_sense */
    MXC_E_ADC_PGA_MUX_CH_SEL_TPROBE_SENSE = 48,
    /** Positive VREFDAC */
    MXC_E_ADC_PGA_MUX_CH_SEL_VREFDAC = 49,
    /** Positive VREFADJ */
    MXC_E_ADC_PGA_MUX_CH_SEL_VREFADJ = 50,
    /** Positive Vdd3xtal */
    MXC_E_ADC_PGA_MUX_CH_SEL_VDD3XTAL = 51
} mxc_adc_pga_mux_ch_sel_t;

/**
 * @brief Decoded with the MUX Channel Select to enable Differential Mode Input to the ADC.
 */
typedef enum {
    /** Differential Mode Disabled */
    MXC_E_ADC_PGA_MUX_DIFF_DISABLE = 0,
    /** Differential Mode Enabled */
    MXC_E_ADC_PGA_MUX_DIFF_ENABLE
} mxc_adc_pga_mux_diff_t;

/**
 * @brief Defines the PGA Gain Options.
 */
typedef enum {
    /** PGA Gain = 1 */
    MXC_E_ADC_PGA_GAIN_1 = 0,
    /** PGA Gain = 2 */
    MXC_E_ADC_PGA_GAIN_2,
    /** PGA Gain = 4 */
    MXC_E_ADC_PGA_GAIN_4,
    /** PGA Gain = 8 */
    MXC_E_ADC_PGA_GAIN_8,
} mxc_adc_pga_gain_t;

typedef struct
{
    uint32_t gain                   : 2;
    uint32_t cpu_pga_rst_clk_en     : 1;
    uint32_t cpu_pga_rst            : 1;
    uint32_t cpu_pga_trk_dly        : 1;
    uint32_t cpu_pga_trk            : 1;
    uint32_t cpu_pga_bypass         : 1;
    uint32_t                        : 1;
    uint32_t pga_wake_cnt           : 5;
    uint32_t mux_sw_ain             : 1;
    uint32_t mux_diff               : 1;
    uint32_t mux_mode               : 1;
    uint32_t test                   : 4;
    uint32_t pga_rst_clk_cnt        : 4;
    uint32_t mux_ch_sel             : 6;
    uint32_t pga_fpo                : 1;
    uint32_t pga_cm_adj             : 1;
} mxc_adc_pga_ctrl_t;

typedef struct
{
    uint32_t pga_trk_cnt   : 16;
    uint32_t adc_smpl_cnt  : 16;
} mxc_adc_tg_ctrl0_t;

typedef struct
{
    uint32_t pga_acq_cnt   : 4;
    uint32_t fifo_af_cnt   : 4;
    uint32_t adc_brst_cnt  : 3;
    uint32_t               : 1;
    uint32_t adc_acq_cnt   : 4;
    uint32_t adc_sleep_cnt : 16;
} mxc_adc_tg_ctrl1_t;

typedef struct
{
    uint32_t lo_limit      : 16;
    uint32_t hi_limit      : 16;
} mxc_adc_limit_t;

/**
 * @brief Defines the Switch Control Mode.
 */
typedef enum {
    /** Switch Control Mode = Software */
    MXC_E_ADC_SPST_SW_CTRL_SOFTWARE = 0,
    /** Switch Control Mode = Pulse Train */
    MXC_E_ADC_SPST_SW_CTRL_PULSETRAIN
} mxc_adc_spst_sw_ctrl_t;

typedef struct
{
    uint32_t                : 6;
    uint32_t fifo_af        : 1;
    uint32_t out_rng        : 1;
    uint32_t hi_rng         : 1;
    uint32_t lo_rng         : 1;
    uint32_t done           : 1;
    uint32_t fifo_uf        : 1;
    uint32_t fifo_of        : 1;
    uint32_t fifo_tf        : 1;
    uint32_t fifo_hf        : 1;
    uint32_t fifo_qf        : 1;
    uint32_t spst_sw0_ctrl  : 1;
    uint32_t spst_sw1_ctrl  : 1;
    uint32_t spst_sw2_ctrl  : 1;
    uint32_t spst_sw3_ctrl  : 1;
    uint32_t                : 2;
    uint32_t fifo_af_en     : 1;
    uint32_t out_rng_en     : 1;
    uint32_t hi_rng_en      : 1;
    uint32_t lo_rng_en      : 1;
    uint32_t done_en        : 1;
    uint32_t fifo_uf_en     : 1;
    uint32_t fifo_of_en     : 1;
    uint32_t fifo_tf_en     : 1;
    uint32_t fifo_hf_en     : 1;
    uint32_t fifo_qf_en     : 1;
} mxc_adc_intr_t;

typedef struct
{
    uint32_t data_reg : 16;
    uint32_t data_bus : 16;
} mxc_adc_out_t;

/**
 * @brief Defines the number of channels to scan when Scan Mode is enabled.
 */
typedef enum {
    /** Number of Channels to Scan = 1 */
    MXC_E_ADC_SCAN_CNT_1 = 0,
    /** Number of Channels to Scan = 2 */
    MXC_E_ADC_SCAN_CNT_2,
    /** Number of Channels to Scan = 3 */
    MXC_E_ADC_SCAN_CNT_3,
    /** Number of Channels to Scan = 4 */
    MXC_E_ADC_SCAN_CNT_4,
    /** Number of Channels to Scan = 5 */
    MXC_E_ADC_SCAN_CNT_5,
    /** Number of Channels to Scan = 6 */
    MXC_E_ADC_SCAN_CNT_6,
    /** Number of Channels to Scan = 7 */
    MXC_E_ADC_SCAN_CNT_7,
    /** Number of Channels to Scan = 8 */
    MXC_E_ADC_SCAN_CNT_8,
} mxc_adc_scan_cnt_t;


typedef struct
{
    uint32_t ahb_retry_dly        : 3;
    uint32_t ahb_retry_en         : 1;
    uint32_t adc_clk_delay        : 3;
    uint32_t                      : 1;
    uint32_t adc_clk_gate_disable : 4;
    uint32_t ahb_clk_gate_disable : 1;
    uint32_t                      : 3;
    uint32_t scan_cnt             : 3;
    uint32_t                      : 13;
} mxc_adc_ctrl1_t;

typedef struct
{
    uint8_t mux_ch_sel : 4;
    uint8_t pga_gain   : 2;
    uint8_t mux_diff   : 1;
    uint8_t            : 1;
} mxc_adc_scan_desc_t;

typedef struct
{
    uint8_t adc_scan_desc[4];
} mxc_adc_scan_t;

typedef struct
{
    uint32_t ro_cal_en      : 1;
    uint32_t ro_cal_run     : 1;
    uint32_t ro_cal_load    : 1;
    uint32_t ro_cal_gain    : 1;
    uint32_t ro_cal_tst     : 1;
    uint32_t                : 3;
    uint32_t trm_mu         : 12;
    uint32_t                : 3;
    uint32_t ro_trm         : 9;
} mxc_adc_ro_cal0_t;

typedef struct
{
    uint32_t trm_init    : 9;
    uint32_t             : 1;
    uint32_t trm_min     : 9;
    uint32_t             : 1;
    uint32_t trm_max     : 9;
    uint32_t             : 3;
} mxc_adc_ro_cal1_t;



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/


/*                                                  Offset   Register Description
                                                    ======   =================================================== */
typedef struct {
    union {
        __IO uint32_t ctrl0;                    /*  0x0000   ADC Control Register 0                              */
        __IO mxc_adc_ctrl0_t ctrl0_f;
    };
    union {
        __IO uint32_t pga_ctrl;                 /*  0x0004   PGA Control Register                                */
        __IO mxc_adc_pga_ctrl_t pga_ctrl_f;
    };
    union {
        __IO uint32_t tg_ctrl0;                 /*  0x0008   ADC Timing Generator Control 0                      */
        __IO mxc_adc_tg_ctrl0_t tg_ctrl0_f;
    };
    union {
        __IO uint32_t tg_ctrl1;                 /*  0x000C   ADC Timing Generator Control 1                      */
        __IO mxc_adc_tg_ctrl1_t tg_ctrl1_f;
    };
    union {
        __IO uint32_t limit;                    /*  0x0010   ADC Limit Settings                                  */
        __IO mxc_adc_limit_t limit_f;
    };
    union {
        __IO uint32_t intr;                     /*  0x0014   ADC Interrupt Flags and Enable/Disable Controls     */
        __IO mxc_adc_intr_t intr_f;
    };
    union {
        __IO uint32_t out;                      /*  0x0018   ADC Output Register                                 */
        __IO mxc_adc_out_t out_f;
    };
} mxc_adc_regs_t;


/*                                                  Offset   Register Description
                                                    ======   =================================================== */
typedef struct {
    union {
        __IO uint32_t ctrl1;                    /*  0x0000   ADC Control Register 1                              */
        __IO mxc_adc_ctrl1_t ctrl1_f;
    };
    union {
        __IO uint32_t scan1;                    /*  0x0004   ADC Auto-Scan Settings 1                            */
        __IO mxc_adc_scan_t scan1_f;
    };
    union {
        __IO uint32_t scan2;                    /*  0x0008   ADC Auto-Scan Settings 2                            */
        __IO mxc_adc_scan_t scan2_f;
    };
    union {
        __IO uint32_t ro_cal0;                  /*  0x000C   ADC Ring Osc Calibration 0                          */
        __IO mxc_adc_ro_cal0_t ro_cal0_f;
    };
    union {
        __IO uint32_t ro_cal1;                  /*  0x0010   ADC Ring Osc Calibration 1                          */
        __IO mxc_adc_ro_cal1_t ro_cal1_f;
    };
} mxc_adccfg_regs_t;

typedef struct {
        __IO uint32_t data;                     /*  0x0000   Read to pull sample data from ADC FIFO              */
} mxc_adc_fifo_regs_t;


/*
   Register offsets for module ADC, ADCCFG, ADC_FIFO
*/
#define MXC_R_ADC_OFFS_CTRL0                      ((uint32_t)0x00000000UL)
#define MXC_R_ADC_OFFS_PGA_CTRL                   ((uint32_t)0x00000004UL)
#define MXC_R_ADC_OFFS_TG_CTRL0                   ((uint32_t)0x00000008UL)
#define MXC_R_ADC_OFFS_TG_CTRL1                   ((uint32_t)0x0000000CUL)
#define MXC_R_ADC_OFFS_LIMIT                      ((uint32_t)0x00000010UL)
#define MXC_R_ADC_OFFS_INTR                       ((uint32_t)0x00000014UL)
#define MXC_R_ADC_OFFS_OUT                        ((uint32_t)0x00000018UL)

#define MXC_R_ADCCFG_OFFS_CTRL1                   ((uint32_t)0x00000000UL)
#define MXC_R_ADCCFG_OFFS_SCAN1                   ((uint32_t)0x00000004UL)
#define MXC_R_ADCCFG_OFFS_SCAN2                   ((uint32_t)0x00000008UL)
#define MXC_R_ADCCFG_OFFS_RO_CAL0                 ((uint32_t)0x0000000CUL)
#define MXC_R_ADCCFG_OFFS_RO_CAL1                 ((uint32_t)0x00000010UL)

#define MXC_R_ADC_FIFO_OFFS_DATA                  ((uint32_t)0x00000000UL)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* _MXC_ADC_REGS_H */
