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

#ifndef _MXC_AFE_REGS_H
#define _MXC_AFE_REGS_H

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
 * @file  afe_regs.h
 * @addtogroup afe AFE
 * @{
 */

typedef struct
{
    uint32_t op_comp0_int  : 1;
    uint32_t op_comp1_int  : 1;
    uint32_t op_comp2_int  : 1;
    uint32_t op_comp3_int  : 1;
    uint32_t lp_comp0_int  : 1;
    uint32_t lp_comp1_int  : 1;
    uint32_t lp_comp2_int  : 1;
    uint32_t lp_comp3_int  : 1;

    uint32_t op_comp0_nma  : 1;
    uint32_t op_comp1_nma  : 1;
    uint32_t op_comp2_nma  : 1;
    uint32_t op_comp3_nma  : 1;
    uint32_t lp_comp0_nma  : 1;
    uint32_t lp_comp1_nma  : 1;
    uint32_t lp_comp2_nma  : 1;
    uint32_t lp_comp3_nma  : 1;

    uint32_t op_comp0_pol  : 1;
    uint32_t op_comp1_pol  : 1;
    uint32_t op_comp2_pol  : 1;
    uint32_t op_comp3_pol  : 1;
    uint32_t lp_comp0_pol  : 1;
    uint32_t lp_comp1_pol  : 1;
    uint32_t lp_comp2_pol  : 1;
    uint32_t lp_comp3_pol  : 1;

    uint32_t op_comp0_en   : 1;
    uint32_t op_comp1_en   : 1;
    uint32_t op_comp2_en   : 1;
    uint32_t op_comp3_en   : 1;
    uint32_t lp_comp0_en   : 1;
    uint32_t lp_comp1_en   : 1;
    uint32_t lp_comp2_en   : 1;
    uint32_t lp_comp3_en   : 1;
} mxc_afe_intr_t;
/**
 * @brief Defines Configure Options for the LED Ports.
 */
typedef enum {
    /** LED Sink Port 0 with OpAmp A, LED Sink Port 1 with OpAmp C */
    MXC_E_AFE_LED_CFG_PORT_OPAMP_A_C = 0,
    /** LED Sink Port 0 with OpAmp B, LED Sink Port 1 with OpAmp D */
    MXC_E_AFE_LED_CFG_PORT_OPAMP_B_D,
    /** Disable LED Sink Port 0,Disable LED Sink Port 1 */
    MXC_E_AFE_LED_CFG_PORT_DISABLED,
} mxc_afe_led_cfg_port_t;

/**
 * @brief Setup of Wake Up Detector for LPCs.
 */
typedef enum {
    /** IDLE */
    MXC_E_AFE_EN_WUD_COMP_IDLE = 0,
    /** Activate WUD for falling edges */
    MXC_E_AFE_EN_WUD_COMP_FALLING_EDGE = 2,
    /** Activate WUD for rising edges */
    MXC_E_AFE_EN_WUD_COMP_RISING_EDGE = 3
} mxc_afe_en_wud_comp_t;

/**
 * @brief LPC InMode.
 */
typedef enum {
    /** InMode: both Nch and Pch */
    MXC_E_AFE_IN_MODE_COMP_NCH_PCH = 0,
    /** InMode: only Nch  */
    MXC_E_AFE_IN_MODE_COMP_NCH,
    /** InMode: only Pch  */
    MXC_E_AFE_IN_MODE_COMP_PCH,
} mxc_afe_in_mode_comp_t;

/**
 * @brief LPC Bias.
 */
typedef enum {
    /** BIAS 0.52uA Delay 4.0us  */
    MXC_E_AFE_BIAS_MODE_COMP_0 = 0,
    /** BIAS 1.4uA Delay 1.7us  */
    MXC_E_AFE_BIAS_MODE_COMP_1,
    /** BIAS 2.8uA Delay 1.1us  */
    MXC_E_AFE_BIAS_MODE_COMP_2,
    /** BIAS 5.1uA Delay 0.7us  */
    MXC_E_AFE_BIAS_MODE_COMP_3
} mxc_afe_bias_mode_comp_t;

typedef struct
{
    uint32_t led_cfg_port0         : 2;
    uint32_t led_cfg_port1         : 2;

    uint32_t clear_wud_comp0       : 1;
    uint32_t clear_wud_comp1       : 1;
    uint32_t clear_wud_comp2       : 1;
    uint32_t clear_wud_comp3       : 1;

    uint32_t en_wud_comp0          : 2;
    uint32_t en_wud_comp1          : 2;
    uint32_t en_wud_comp2          : 2;
    uint32_t en_wud_comp3          : 2;

    uint32_t in_mode_comp0         : 2;
    uint32_t in_mode_comp1         : 2;
    uint32_t in_mode_comp2         : 2;
    uint32_t in_mode_comp3         : 2;

    uint32_t bias_mode_comp0       : 2;
    uint32_t bias_mode_comp1       : 2;
    uint32_t bias_mode_comp2       : 2;
    uint32_t bias_mode_comp3       : 2;
} mxc_afe_ctrl0_t;

/**
 * @brief TMON Current Value.
 */
typedef enum {
    /** TMON Current 4uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_0 = 0,
    /** TMON Current 60uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_1,
    /** TMON Current 64uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_2,
    /** TMON Current 120uA  */
    MXC_E_AFE_TMON_CURRENT_VAL_3
} mxc_afe_tmon_current_t;

/**
 * @brief REFADC and REFDAC Voltage Select.
 */
typedef enum {
    /** Voltage Reference = 1.024 V */
    MXC_E_AFE_REF_VOLT_SEL_1024 = 0,
    /** Voltage Reference = 1.5 V */
    MXC_E_AFE_REF_VOLT_SEL_1500,
    /** Voltage Reference = 2.048 V */
    MXC_E_AFE_REF_VOLT_SEL_2048,
    /** Voltage Reference = 2.5 V */
    MXC_E_AFE_REF_VOLT_SEL_2500
} mxc_afe_ref_volt_sel_t;

/**
 * @brief Selection for DAC VOltage Reference, REFADC or REFDAC.
 */
typedef enum {
    /** DAC Voltage Reference = REFADC */
    MXC_E_AFE_DAC_REF_REFADC = 0,
    /** DAC Voltage Reference = REFDAC */
    MXC_E_AFE_DAC_REF_REFDAC
} mxc_afe_dac_ref_t;

typedef struct
{
    uint32_t tmon_current_en                    : 1;
    uint32_t tmon_current_val                   : 2;
    uint32_t refadc_fast_pwrdn_en               : 1;
    uint32_t refdac_fast_pwrdn_en               : 1;
    uint32_t bgextsel                           : 1;
    uint32_t adcrefsel                          : 2;
    uint32_t dacrefsel                          : 2;
    uint32_t dacsel                             : 1;
    uint32_t refadc_outen                       : 1;
    uint32_t refdac_outen                       : 1;
    uint32_t ref_pu                             : 1;
    uint32_t refadc_cp                          : 1;
    uint32_t refdac_cp                          : 1;
    uint32_t refadc_gain                        : 2;
    uint32_t refdac_gain                        : 2;
    uint32_t abus_page_2_0                      : 3;
    uint32_t tm3_tst_ib                         : 1;
    uint32_t abus_page_3                        : 1;
    uint32_t v1extadj                           : 5;
    uint32_t tmon_ext_sel                       : 1;
    uint32_t                                    : 1;
} mxc_afe_ctrl1_t;

/**
 * @brief Selection for LPC Hysteresis.
 */
typedef enum {
    /** LPC Hysteresis = 0 mV */
    MXC_E_AFE_HYST_COMP_0 = 0,
    /** LPC Hysteresis = 7.5 mV */
    MXC_E_AFE_HYST_COMP_1,
    /** LPC Hysteresis = 15 mV */
    MXC_E_AFE_HYST_COMP_2,
    /** LPC Hysteresis = 30 mV */
    MXC_E_AFE_HYST_COMP_3
} mxc_afe_hyst_comp_t;

/**
 * @brief Selection for MUX for  SCM_or_sel.
 */
typedef enum {
    /** SCM_or = HIZ */
    MXC_E_AFE_SCM_OR_SEL_HIZ = 0,
    /** SCM_or = SCM0 */
    MXC_E_AFE_SCM_OR_SEL_SCM0,
    /** SCM_or = SCM1 */
    MXC_E_AFE_SCM_OR_SEL_SCM1,
    /** SCM_or = SCM2 */
    MXC_E_AFE_SCM_OR_SEL_SCM2,
    /** SCM_or = SCM3 */
    MXC_E_AFE_SCM_OR_SEL_SCM3
} mxc_afe_scm_or_sel_t;

/**
 * @brief Selection for MUX for  SNO_or_sel.
 */
typedef enum {
    /** SNO_or = HIZ */
    MXC_E_AFE_SNO_OR_SEL_HIZ = 0,
    /** SNO_or = SNO0 */
    MXC_E_AFE_SNO_OR_SEL_SNO0,
    /** SNO_or = SNO1 */
    MXC_E_AFE_SNO_OR_SEL_SNO1,
    /** SNO_or = SNO2 */
    MXC_E_AFE_SNO_OR_SEL_SNO2,
    /** SNO_or = SNO3 */
    MXC_E_AFE_SNO_OR_SEL_SNO3
} mxc_afe_sno_or_sel_t;

/**
 * @brief Selection for MUX  DACx_sel.
 */
typedef enum {
    /** dacx  = DACOP */
    MXC_E_AFE_DACX_SEL_P = 0,
    /** dacx  = DACON */
    MXC_E_AFE_DACX_SEL_N
} mxc_afe_dacx_sel_t;

typedef struct
{
    uint32_t hyst_comp0          : 2;
    uint32_t hyst_comp1          : 2;
    uint32_t hyst_comp2          : 2;
    uint32_t hyst_comp3          : 2;

    uint32_t hy_pol_comp0        : 1;
    uint32_t hy_pol_comp1        : 1;
    uint32_t hy_pol_comp2        : 1;
    uint32_t hy_pol_comp3        : 1;

    uint32_t poweru_comp0        : 1;
    uint32_t poweru_comp1        : 1;
    uint32_t poweru_comp2        : 1;
    uint32_t poweru_comp3        : 1;

    uint32_t dacout_en0          : 1;
    uint32_t dacout_en1          : 1;
    uint32_t dacout_en2          : 1;
    uint32_t dacout_en3          : 1;

    uint32_t scm_or_sel          : 3;
    uint32_t sno_or_sel          : 3;
    uint32_t dac0_sel            : 1;
    uint32_t dac1_sel            : 1;
    uint32_t                     : 4;
} mxc_afe_ctrl2_t;
    
    
/**
 * @brief Selection for state of Switch.
 */
typedef enum {
    /** Switch is OPEN */
    MXC_E_AFE_CLOSE_SPST_SWITCH_OPEN = 0,
    /** Switch is CLOSED */
    MXC_E_AFE_CLOSE_SPST_SWITCH_CLOSE
} mxc_afe_close_spst_t;
    
/**
 * @brief Switch to Connect Positive Pad to GND.
 */
typedef enum {
    /** Positive Pad GND Switch OPEN */
    MXC_E_AFE_GND_SEL_OPAMP_SWITCH_OPEN = 0,
    /** Positive Pad GND Switch CLOSED */
    MXC_E_AFE_GND_SEL_OPAMP_SWITCH_CLOSED
} mxc_afe_gnd_sel_opamp_t;

typedef struct
{
    uint32_t                    : 12;
    uint32_t pu_opamp0          : 1;
    uint32_t pu_opamp1          : 1;
    uint32_t pu_opamp2          : 1;
    uint32_t pu_opamp3          : 1;
    uint32_t gnd_sel_opamp0     : 1;
    uint32_t gnd_sel_opamp1     : 1;
    uint32_t gnd_sel_opamp2     : 1;
    uint32_t gnd_sel_opamp3     : 1;
    uint32_t close_spst0        : 1;
    uint32_t close_spst1        : 1;
    uint32_t close_spst2        : 1;
    uint32_t close_spst3        : 1;
    uint32_t en_p_in_opamp0     : 1;
    uint32_t en_p_in_opamp1     : 1;
    uint32_t en_p_in_opamp2     : 1;
    uint32_t en_p_in_opamp3     : 1;
    uint32_t en_n_in_opamp0     : 1;
    uint32_t en_n_in_opamp1     : 1;
    uint32_t en_n_in_opamp2     : 1;
    uint32_t en_n_in_opamp3     : 1;
} mxc_afe_ctrl3_t;

/**
 * @brief MUX Selection for OpPsel.
 */
typedef enum {
    /** OpPsel = INx+ */
    MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS = 0,
    /** OpPsel = DAC_or */
    MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR,
    /** OpPsel = SNO_or */
    MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR,
    /** OpPsel = DAC_or also output on INx+ */
    MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS
} mxc_afe_p_in_sel_opamp_t;

/**
 * @brief MUX Selection for OpNsel.
 */
typedef enum {
    /** OpNsel = INx- */
    MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS = 0,
    /** OpNsel = OUTx */
    MXC_E_AFE_N_IN_SEL_OPAMP_OUT,
    /** OpNsel = SCM_or */
    MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR,
    /**OpNsel = SCM_or also output on INx- */
    MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS,
} mxc_afe_n_in_sel_opamp_t;

/**
 * @brief MUX Selection for DAC_sel.
 */
typedef enum {
    /** DAC_or = DAC0 */
    MXC_E_AFE_DAC_SEL_DAC0 = 0,
    /** DAC_or = DAC1 */
    MXC_E_AFE_DAC_SEL_DAC1,
    /** DAC_or = DAC2P */
    MXC_E_AFE_DAC_SEL_DAC2P,
    /** DAC_or = DAC3P */
    MXC_E_AFE_DAC_SEL_DAC3P
} mxc_afe_dac_sel_t;

/**
 * @brief MUX Selection for NPAD_sel.
 */
typedef enum {
    /** NPAD_Sel = HIZ */
    MXC_E_AFE_NPAD_SEL_HIZ = 0,
    /** NPAD_Sel = LED Observe Port */
    MXC_E_AFE_NPAD_SEL_LED_OBS_PORT,
    /** NPAD_Sel = DAC_or */
    MXC_E_AFE_NPAD_SEL_DAC_OR,
    /** NPAD_Sel = DAC_or and LED Observe Port */
    MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT
} mxc_afe_npad_sel_t;

typedef struct
{
    uint32_t p_in_sel_opamp0    : 2;
    uint32_t p_in_sel_opamp1    : 2;
    uint32_t p_in_sel_opamp2    : 2;
    uint32_t p_in_sel_opamp3    : 2;

    uint32_t n_in_sel_opamp0    : 2;
    uint32_t n_in_sel_opamp1    : 2;
    uint32_t n_in_sel_opamp2    : 2;
    uint32_t n_in_sel_opamp3    : 2;

    uint32_t dac_sel_a          : 2;
    uint32_t dac_sel_b          : 2;
    uint32_t dac_sel_c          : 2;
    uint32_t dac_sel_d          : 2;

    uint32_t npad_sel_a         : 2;
    uint32_t npad_sel_b         : 2;
    uint32_t npad_sel_c         : 2;
    uint32_t npad_sel_d         : 2;
} mxc_afe_ctrl4_t;


/**
 * @brief MUX Selection for CmpPSel.
 */
typedef enum {
    /** CmpPSel = INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_INPLUS = 0,
    /** CmpPSel = SCM */
    MXC_E_AFE_POS_IN_SEL_COMP_SCM,
    /** CmpPSel = dac1 */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1,
    /** CmpPSel = DAC3P */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC3P,
    /** CmpPSel = LED Observe Port */
    MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT,
    /** CmpPSel = dac1 also output on INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS,
    /** CmpPSel = DAC3P also output on INx+ */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS,
    /** CmpPSel = dac1 also output on SCM */
    MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM
} mxc_afe_pos_in_sel_comp_t;

/**
     * @brief MUX Selection for CmpNSel.
*/
typedef enum {
    /** CmpNSel = INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS = 0,
    /** CmpNSel = SNO */
    MXC_E_AFE_NEG_IN_SEL_COMP_SNO,
    /** CmpNSel = dac0 */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC0,
    /** CmpNSel = DAC2P */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P,
    /** CmpNSel = LED Observation Port */
    MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT,
    /** CmpNSel = dac0 also output on INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS,
    /** CmpNSel = DAC2 also output on INx- */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS,
    /** CmpNSel = DAC2 also output on SNO */
    MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO
} mxc_afe_neg_in_sel_comp_t;

typedef struct
{
    uint32_t pos_in_sel_comp0   : 3;
    uint32_t pos_in_sel_comp1   : 3;
    uint32_t pos_in_sel_comp2   : 3;
    uint32_t pos_in_sel_comp3   : 3;
    uint32_t neg_in_sel_comp0   : 3;
    uint32_t neg_in_sel_comp1   : 3;
    uint32_t neg_in_sel_comp2   : 3;
    uint32_t neg_in_sel_comp3   : 3;
    uint32_t op_cmp0            : 1;
    uint32_t op_cmp1            : 1;
    uint32_t op_cmp2            : 1;
    uint32_t op_cmp3            : 1;
    uint32_t                    : 4;
} mxc_afe_ctrl5_t;



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                          Offset   Register Description
                                            ======   ==================================================== */
typedef struct {
    union {
        __IO uint32_t intr;             /*  0x0000   Analog Front End Interrupt Flags and Enable/Disable  */
        __IO mxc_afe_intr_t intr_f;
    };
    union {
        __IO uint32_t ctrl0;            /*  0x0004   Analog Front End Control 0                           */
        __IO mxc_afe_ctrl0_t ctrl0_f;
    };
    union {
        __IO uint32_t ctrl1;            /*  0x0008   Analog Front End Control 1                           */
        __IO mxc_afe_ctrl1_t ctrl1_f;
    };
    union {
        __IO uint32_t ctrl2;            /*  0x000C   Analog Front End Control 2                           */
        __IO mxc_afe_ctrl2_t ctrl2_f;
    };
    union {
        __IO uint32_t ctrl3;            /*  0x0010   Analog Front End Control 3                           */
        __IO mxc_afe_ctrl3_t ctrl3_f;
    };
    union {
        __IO uint32_t ctrl4;            /*  0x0014   Analog Front End Control 4                           */
        __IO mxc_afe_ctrl4_t ctrl4_f;
    };
    union {
        __IO uint32_t ctrl5;            /*  0x0018   Analog Front End Control 5                           */
        __IO mxc_afe_ctrl5_t ctrl5_f;
    };
} mxc_afe_regs_t;


/*
   Register offsets for module AFE.
*/

#define MXC_R_AFE_OFFS_INTR                   ((uint32_t)0x00000000UL)
#define MXC_R_AFE_OFFS_CTRL0                  ((uint32_t)0x00000004UL)
#define MXC_R_AFE_OFFS_CTRL1                  ((uint32_t)0x00000008UL)
#define MXC_R_AFE_OFFS_CTRL2                  ((uint32_t)0x0000000CUL)
#define MXC_R_AFE_OFFS_CTRL3                  ((uint32_t)0x00000010UL)
#define MXC_R_AFE_OFFS_CTRL4                  ((uint32_t)0x00000014UL)
#define MXC_R_AFE_OFFS_CTRL5                  ((uint32_t)0x00000018UL)


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif   /* _MXC_AFE_REGS_H_ */
