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

/* $Revision: 3298 $ $Date: 2014-10-06 17:47:48 -0500 (Mon, 06 Oct 2014) $ */

#ifndef _AFE_H
#define _AFE_H

#include "afe_regs.h"
#include "adc_regs.h"

/**
 * @file  afe.h
 * @addtogroup afe AFE
 * @{
 * @brief This is the high level API for the analog front end module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/* Enumerations used by highlevel APIs for MUX settings */
/**
 * @brief OpAmp Positive Input.
 */
typedef enum {
    /** OpAmp Positive Input = PAD_INxP */
    MXC_E_AFE_OPAMP_POS_IN_PAD_INxP = 0,
    /** OpAmp Positive Input = DAC0p */
    MXC_E_AFE_OPAMP_POS_IN_DAC0P,
    /** OpAmp Positive Input = DAC0n */
    MXC_E_AFE_OPAMP_POS_IN_DAC0N,
    /** OpAmp Positive Input = DAC1p */
    MXC_E_AFE_OPAMP_POS_IN_DAC1P,
    /** OpAmp Positive Input = DAC1n */
    MXC_E_AFE_OPAMP_POS_IN_DAC1N,
    /** OpAmp Positive Input = DAC2p */
    MXC_E_AFE_OPAMP_POS_IN_DAC2P,
    /** OpAmp Positive Input = DAC3p */
    MXC_E_AFE_OPAMP_POS_IN_DAC3P,
    /** OpAmp Positive Input = SNO_HIZ */
    MXC_E_AFE_OPAMP_POS_IN_SNO_HIZ,
    /** OpAmp Positive Input = SNO0 */
    MXC_E_AFE_OPAMP_POS_IN_SNO0,
    /** OpAmp Positive Input = SNO1 */
    MXC_E_AFE_OPAMP_POS_IN_SNO1,
    /** OpAmp Positive Input = SNO2 */
    MXC_E_AFE_OPAMP_POS_IN_SNO2,
    /** OpAmp Positive Input = SNO3 */
    MXC_E_AFE_OPAMP_POS_IN_SNO3,
    /** OpAmp Positive Input = DAC0p output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC0P_INxP,
    /** OpAmp Positive Input = DAC0n output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC0N_INxP,
    /** OpAmp Positive Input = DAC1p output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC1P_INxP,
    /** OpAmp Positive Input = DAC1n output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC1N_INxP,
    /** OpAmp Positive Input = DAC2p output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC2P_INxP,
    /** OpAmp Positive Input = DAC3p output to INxP */
    MXC_E_AFE_OPAMP_POS_IN_DAC3P_INxP,
} mxc_opamp_pos_in_t;

/**
 * @brief OpAmp Negative Input.
 */
typedef enum {
    /** OpAmp Negative Input = PAD_INxN */
    MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN = 0,
    /** OpAmp Negative Input = OUTx */
    MXC_E_AFE_OPAMP_NEG_IN_OUTx,
    /** OpAmp Negative Input = SCM_HIZ */
    MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ,
    /** OpAmp Negative Input = SCM0 */
    MXC_E_AFE_OPAMP_NEG_IN_SCM0,
    /** OpAmp Negative Input = SCM1 */
    MXC_E_AFE_OPAMP_NEG_IN_SCM1,
    /** OpAmp Negative Input = SCM2 */
    MXC_E_AFE_OPAMP_NEG_IN_SCM2,
    /** OpAmp Negative Input = SCM3 */
    MXC_E_AFE_OPAMP_NEG_IN_SCM3,
    /** OpAmp Negative Input = SCM_HIZ output to INxN */
    MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ_INxN,
    /** OpAmp Negative Input = SCM0 output to INxN */
    MXC_E_AFE_OPAMP_NEG_IN_SCM0_INxN,
    /** OpAmp Negative Input = SCM1 output to INxN  */
    MXC_E_AFE_OPAMP_NEG_IN_SCM1_INxN,
    /** OpAmp Negative Input = SCM2 output to INxN */
    MXC_E_AFE_OPAMP_NEG_IN_SCM2_INxN,
    /** OpAmp Negative Input = SCM3 output to INxN  */
    MXC_E_AFE_OPAMP_NEG_IN_SCM3_INxN,
} mxc_opamp_neg_in_t;

/**
 * @brief OpAmp negative PAD Selection.
 */
typedef enum {
    /** OpAmp Negative Pad Selection = OFF */
    MXC_E_AFE_OPAMP_NEG_PAD_OFF = 0,
    /** OpAmp Negative Pad Selection = LED Observe Port*/
    MXC_E_AFE_OPAMP_NEG_PAD_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC0p */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC0P,
    /** OpAmp Negative Pad Selection = DAC0n */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC0N,
    /** OpAmp Negative Pad Selection = DAC1p */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC1P,
    /** OpAmp Negative Pad Selection = DAC1n */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC1N,
    /** OpAmp Negative Pad Selection = DAC2p */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC2P,
    /** OpAmp Negative Pad Selection = DAC3p */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC3P,
    /** OpAmp Negative Pad Selection = DAC0p and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC0P_AND_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC0n and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC0N_AND_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC1p and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC1P_AND_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC1n and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC1N_AND_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC2p and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC2P_AND_LED_OBS_PORT,
    /** OpAmp Negative Pad Selection = DAC3p and LED Obs Port */
    MXC_E_AFE_OPAMP_NEG_PAD_DAC3P_AND_LED_OBS_PORT,
} mxc_opamp_neg_pad_t;

/**
 * @brief LPC Positive Input.
 */
typedef enum {
    /** LPC Positive Input  = PAD_INxP */
    MXC_E_AFE_LPC_POS_IN_PAD_INxP = 0,
    /** LPC Positive Input  = SCMx */
    MXC_E_AFE_LPC_POS_IN_SCMx,
    /** LPC Positive Input  = DAC1p */
    MXC_E_AFE_LPC_POS_IN_DAC1P,
    /** LPC Positive Input  = DAC1n */
    MXC_E_AFE_LPC_POS_IN_DAC1N,
    /** LPC Positive Input  = DAC3p */
    MXC_E_AFE_LPC_POS_IN_DAC3P,
    /** LPC Positive Input  = LED Observation Port */
    MXC_E_AFE_LPC_POS_IN_LED_OBS_PORT,
    /** LPC Positive Input  = DAC1P output on INxP */
    MXC_E_AFE_LPC_POS_IN_DAC1P_AND_INxP,
    /** LPC Positive Input  = DAC1N output on INxP */
    MXC_E_AFE_LPC_POS_IN_DAC1N_AND_INxP,
    /** LPC Positive Input  = DAC3P output on INxP */
    MXC_E_AFE_LPC_POS_IN_DAC3P_AND_INxP,
    /** LPC Positive Input  = DAC1P output on SCM */
    MXC_E_AFE_LPC_POS_IN_DAC1P_AND_SCM,
    /** LPC Positive Input  = DAC1N output on SCM */
    MXC_E_AFE_LPC_POS_IN_DAC1N_AND_SCM,
} mxc_lpc_pos_in_t;

/**
 * @brief LPC Negative Input.
 */
typedef enum {
    /** LPC Negative Input  = PAD_INxN */
    MXC_E_AFE_LPC_NEG_IN_PAD_INxN = 0,
    /** LPC Negative Input  = SNOx */
    MXC_E_AFE_LPC_NEG_IN_SNOx,
    /** LPC Negative Input  = DAC0p */
    MXC_E_AFE_LPC_NEG_IN_DAC0P,
    /** LPC Negative Input  = DAC0n */
    MXC_E_AFE_LPC_NEG_IN_DAC0N,
    /** LPC Negative Input  = DAC2p */
    MXC_E_AFE_LPC_NEG_IN_DAC2P,
    /** LPC Negative Input  = LED Observation Port */
    MXC_E_AFE_LPC_NEG_IN_LED_OBS_PORT,
    /** LPC Negative Input  = DAC0p output on INxN */
    MXC_E_AFE_LPC_NEG_IN_DAC0P_AND_INxN,
    /** LPC Negative Input  = DAC0n output on INxN */
    MXC_E_AFE_LPC_NEG_IN_DAC0N_AND_INxN,
    /** LPC Negative Input  = DAC2p output on INxN */
    MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_INxN,
    /** LPC Negative Input  = DAC2p output on SNO */
    MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_SNO,
} mxc_lpc_neg_in_t;

/**
 * @brief OpAmp vs Comparator Mode.
 */
typedef enum {
    /** MODE = OpAmp Mode */
    MXC_E_AFE_OPAMP_MODE_OPAMP = 0,
    /** MODE = Comparator Mode */
    MXC_E_AFE_OPAMP_MODE_COMP,
} mxc_opamp_mode_t;

/**
 * @brief OpAmp InMode.
 */
typedef enum {
    /** InMode: both Nch and Pch */
    MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH = 0,
    /** InMode: only Nch */
    MXC_E_AFE_IN_MODE_OPAMP_NCH,
    /** InMode: only Pch */
    MXC_E_AFE_IN_MODE_OPAMP_PCH,
} mxc_afe_in_mode_opamp_t;

/**
 * @brief Setup of OPAMPs
 *
 * @param opamp_index     Index of OpAmp to use.
 * @param mode            OpAmp = 0, Comparator = 1
 * @param pos_input       MUXs of possible inputs for positive side of the opamp.
 * @param neg_input       MUXs of possible inputs for the negative side of the opamp.
 * @param opamp_inmode    Set mode for the input pads.
 *
 */
void AFE_OpAmpSetup(uint8_t opamp_index, mxc_opamp_mode_t mode, mxc_opamp_pos_in_t pos_input, mxc_opamp_neg_in_t neg_input, mxc_afe_in_mode_opamp_t opamp_inmode);

/**
 * @brief Power Enable of OPAMPs
 *
 * @param opamp_index     Index of OpAmp to use.
 */
void AFE_OpAmpEnable(uint8_t opamp_index);

/**
 * @brief Power Disable of OPAMPs
 *
 * @param opamp_index     Index of OpAmp to use.
 */
void AFE_OpAmpDisable(uint8_t opamp_index);

/**
 * @brief Setup and activate an interrupt for an OpAmp in comparator mode
 *
 * @param opamp_index Index for the opamp comparator to use.
 * @param intr_cb     Function pointer to callback function.  
 *                        If NULL pointer is passed, CPU interrupt is not activated and PMU interrupt will be activated
 * @param cb_arg      Pointer passed to the callback function.
 * 
 */
void AFE_OpAmpSetupInt(uint8_t opamp_index, void(*intr_cb)(void *arg), void *cb_arg);

/**
 * @brief Setup of Low Power Comparators (LPC)
 *
 * @param lpc_index     Index for the comparator to use.
 * @param pos_input     MUXs of possible inputs for positive side of the comparator.
 * @param neg_input     MUXs of possible inputs for negative side of the comparator.
 * @param cmp_inmode    Comparator modes.
 *
 */
void AFE_LPCSetup(uint8_t lpc_index, mxc_lpc_pos_in_t pos_input, mxc_lpc_neg_in_t neg_input, mxc_afe_in_mode_comp_t cmp_inmode);

/**
 * @brief Power Enable of LPCs
 *
 * @param lpc_index     Index for the comparator to use.
 */
void AFE_LPCEnable(uint8_t lpc_index);

/**
 * @brief Power Disable of LPCs
 *
 * @param lpc_index     Index for the comparator to use.
 */
void AFE_LPCDisable(uint8_t lpc_index);

/**
 * @brief Configuration of Low Power Comparators (LPC)
 *
 * @param lpc_index     Index for the comparator to use.
 * @param cmp_bias      Set the power usage and reaction speed time
 * @param hysteresis    Set the magnitude of the comparator hysteresis
 * @param tp_polarity   Vp > Vn + Vhys = 0, Vp < Vn - Vhys = 1.
 *
 */
void AFE_LPCConfig(uint8_t lpc_index, mxc_afe_bias_mode_comp_t cmp_bias, mxc_afe_hyst_comp_t hysteresis, uint8_t tp_polarity);

/**
 * @brief Setup and activate an interrupt for a Low Power Comparator (LPC)
 *
 * @param lpc_index Index for the comparator to use.
 * @param intr_cb    Function pointer to callback function.  
 *                        If NULL pointer is passed, CPU interrupt is not activated and PMU interrupt will be activated
 * @param cb_arg     Pointer passed to the callback function.
 * 
 */
void AFE_LPCSetupInt(uint8_t lpc_index, void(*intr_cb)(void *arg), void *cb_arg);

/**
 * @brief Enable the internal ADC Voltage Reference
 *
 * @param adc_refsel     Value set to the internal ADC reference.
 */
void AFE_ADCVRefEnable(mxc_afe_ref_volt_sel_t adc_refsel);

/**
 * @brief Disable the internal ADC Voltage Reference, switches ADC reference voltage to external source.
 *
 * @param fast_power_down   Enable or disable the pull-down resistor on the voltage reference
 *
 */
void AFE_ADCVRefDisable(uint8_t fast_power_down);

/**
 * @brief Enable the internal DAC Voltage Reference
 *
 * @param dac_refsel     Value set to the internal DAC reference.
 * @param dacsel         Select internal source for the DAC reference.
 */
void AFE_DACVRefEnable(mxc_afe_ref_volt_sel_t dac_refsel, mxc_afe_dac_ref_t dacsel);

/**
 * @brief Disable the internal DAC Voltage Reference, switches DAC reference voltage to external source.
 *
 * @param fast_power_down   Enable or disable the pull-down resistor on the voltage reference
 *
 */
void AFE_DACVRefDisable(uint8_t fast_power_down);
 
/**
 * @brief Setup external bandgap reference voltage and adjust voltage 1.024V (2's complement) \n
 *    \f$1024 = Vrefadj \frac{87+v1extadj}{104 * v1extadj}\f$ \n
 *    Where \f$Vrefadj\f$ is on the external pin.
 *
 * @param v1extadj       Adjustment value
 */
void AFE_VRefExtBandgapSetup(uint8_t v1extadj);

/**
 * @brief Setup of Switch
 *
 * @param switch_index   Index of switch to set
 * @param state          Open or close switch.
 */
void AFE_SetSwitchState(uint8_t switch_index, mxc_afe_close_spst_t state);

/**
 * @brief Setup Switch Control Mode
 *
 * @param switch_index      Specifies the number of the switch being configured
 * @param switch_mode     Switch mode:  'software' or 'pulse train' control
 *
 */
void AFE_SetSwitchMode(uint8_t switch_index, mxc_adc_spst_sw_ctrl_t switch_mode);

/**
 * @brief Setup of LED current sink port.  See hardware
 * documentation for details on the current sink ports designed for
 * driving LEDs. 
 *
 * @param port_index          LED drive port number.
 * @param led_cfg             Configuration value.
 */
void AFE_LEDConfig(uint8_t port_index, mxc_afe_led_cfg_port_t led_cfg);

/**
 * @brief Setup of GND Switch on Positive Pad of Opamp
 *
 * @param opamp_index     Index of OpAmp to use.
 * @param state           Open or close the switch to ground.
 */
void AFE_GndSwitchSet(uint8_t opamp_index, mxc_afe_gnd_sel_opamp_t state);

/**
 * @brief NPAD Select for OpAmp
 *
 * @param opamp_index     Index of OpAmp to use.
 * @param npad_select     Select connection for the negative pad on the opamp.
 *
 */
void AFE_NpadSetup(uint8_t opamp_index, mxc_opamp_neg_pad_t npad_select);

/**
 * @}
 */
 
#endif /* _AFE_H_ */
