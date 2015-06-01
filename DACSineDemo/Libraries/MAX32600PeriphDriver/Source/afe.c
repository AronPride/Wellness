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

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>

#include "afe.h"
#include "adc.h"

void AFE_OpAmpSetup(uint8_t opamp_index, mxc_opamp_mode_t mode, mxc_opamp_pos_in_t p_input, mxc_opamp_neg_in_t n_input, mxc_afe_in_mode_opamp_t opamp_inmode)
{
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;
    mxc_afe_ctrl3_t afe_ctrl3 = MXC_AFE->ctrl3_f;
    mxc_afe_ctrl4_t afe_ctrl4 = MXC_AFE->ctrl4_f;
    mxc_afe_ctrl5_t afe_ctrl5 = MXC_AFE->ctrl5_f;

    if (opamp_index == 0)
    {
        afe_ctrl5.op_cmp0 = mode;

        switch (p_input){
            case MXC_E_AFE_OPAMP_POS_IN_PAD_INxP:
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO_HIZ:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_HIZ;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO0:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO0;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO1:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO1;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO2:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO2;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO3:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO3;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P_INxP:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P_INxP:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            default:
                afe_ctrl4.p_in_sel_opamp0 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
        }

        switch (n_input){
            case MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN:
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_OUTx:
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_OUT;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            default:
                afe_ctrl4.n_in_sel_opamp0 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
        }

        switch(opamp_inmode){
            case MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH:
                afe_ctrl3.en_p_in_opamp0 = 1;
                afe_ctrl3.en_n_in_opamp0 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_NCH:
                afe_ctrl3.en_p_in_opamp0 = 0;
                afe_ctrl3.en_n_in_opamp0 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_PCH:
                afe_ctrl3.en_p_in_opamp0 = 1;
                afe_ctrl3.en_n_in_opamp0 = 0;
                break;
        }
    }

    if (opamp_index == 1)
    {
        afe_ctrl5.op_cmp1 = mode;

        switch (p_input){
            case MXC_E_AFE_OPAMP_POS_IN_PAD_INxP:
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO_HIZ:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_HIZ;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO0:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO0;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO1:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO1;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO2:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO2;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO3:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO3;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P_INxP:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P_INxP:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            default:
                afe_ctrl4.p_in_sel_opamp1 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
        }

        switch (n_input){
            case MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN:
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_OUTx:
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_OUT;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            default:
                afe_ctrl4.n_in_sel_opamp1 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
        }

        switch(opamp_inmode){
            case MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH:
                afe_ctrl3.en_p_in_opamp1 = 1;
                afe_ctrl3.en_n_in_opamp1 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_NCH:
                afe_ctrl3.en_p_in_opamp1 = 0;
                afe_ctrl3.en_n_in_opamp1 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_PCH:
                afe_ctrl3.en_p_in_opamp1 = 1;
                afe_ctrl3.en_n_in_opamp1 = 0;
                break;
        }
    }

    if (opamp_index == 2)
    {
        afe_ctrl5.op_cmp2 = mode;

        switch (p_input){
            case MXC_E_AFE_OPAMP_POS_IN_PAD_INxP:
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO_HIZ:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_HIZ;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO0:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO0;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO1:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO1;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO2:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO2;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO3:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO3;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P_INxP:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P_INxP:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            default:
                afe_ctrl4.p_in_sel_opamp2 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
        }

        switch (n_input){
            case MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN:
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_OUTx:
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_OUT;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            default:
                afe_ctrl4.n_in_sel_opamp2 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;
        }

        switch(opamp_inmode){
            case MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH:
                afe_ctrl3.en_p_in_opamp2 = 1;
                afe_ctrl3.en_n_in_opamp2 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_NCH:
                afe_ctrl3.en_p_in_opamp2 = 0;
                afe_ctrl3.en_n_in_opamp2 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_PCH:
                afe_ctrl3.en_p_in_opamp2 = 1;
                afe_ctrl3.en_n_in_opamp2 = 0;
                break;
        }
    }

    if (opamp_index == 3)
    {
        afe_ctrl5.op_cmp3 = mode;

        switch (p_input){
            case MXC_E_AFE_OPAMP_POS_IN_PAD_INxP:
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO_HIZ:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_HIZ;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO0:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO0;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO1:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO1;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO2:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO2;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_SNO3:
                afe_ctrl2.sno_or_sel = MXC_E_AFE_SNO_OR_SEL_SNO3;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_SNO_OR;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0P_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC0N_INxP:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1P_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC1N_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC2P_INxP:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            case MXC_E_AFE_OPAMP_POS_IN_DAC3P_INxP:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_DAC_OR_AND_INPLUS;
                break;
            default:
                afe_ctrl4.p_in_sel_opamp3 = MXC_E_AFE_P_IN_SEL_OPAMP_INPLUS;
        }

        switch (n_input){
            case MXC_E_AFE_OPAMP_NEG_IN_PAD_INxN:
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_OUTx:
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_OUT;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM_HIZ_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_HIZ;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM0_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM0;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM1_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM1;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM2_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM2;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            case MXC_E_AFE_OPAMP_NEG_IN_SCM3_INxN:
                afe_ctrl2.scm_or_sel = MXC_E_AFE_SCM_OR_SEL_SCM3;
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_SCM_OR_AND_INMINUS;
                break;
            default:
                afe_ctrl4.n_in_sel_opamp3 = MXC_E_AFE_N_IN_SEL_OPAMP_INMINUS;

        }

        switch(opamp_inmode){
            case MXC_E_AFE_IN_MODE_OPAMP_NCH_PCH:
                afe_ctrl3.en_p_in_opamp3 = 1;
                afe_ctrl3.en_n_in_opamp3 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_NCH:
                afe_ctrl3.en_p_in_opamp3 = 0;
                afe_ctrl3.en_n_in_opamp3 = 1;
                break;
            case MXC_E_AFE_IN_MODE_OPAMP_PCH:
                afe_ctrl3.en_p_in_opamp3 = 1;
                afe_ctrl3.en_n_in_opamp3 = 0;
                break;
        }

    }

    MXC_AFE->ctrl2_f = afe_ctrl2;
    MXC_AFE->ctrl3_f = afe_ctrl3;
    MXC_AFE->ctrl4_f = afe_ctrl4;
    MXC_AFE->ctrl5_f = afe_ctrl5;
}

void AFE_OpAmpEnable(uint8_t opamp_index)
{
    mxc_afe_ctrl3_t afe_ctrl3 = MXC_AFE->ctrl3_f;
    mxc_afe_ctrl5_t afe_ctrl5 = MXC_AFE->ctrl5_f;
    if (opamp_index == 0 )
    {
        afe_ctrl3.pu_opamp0 = 1;
        if ((afe_ctrl3.en_p_in_opamp0 == 0) & (afe_ctrl3.en_n_in_opamp0 == 0))
        {
        afe_ctrl3.en_p_in_opamp0 = 1;
        afe_ctrl3.en_n_in_opamp0 = 1;
        }
        if (afe_ctrl5.op_cmp0 == 1)
        {
            ADC_Enable();
        }
    }
    if (opamp_index == 1 )
    {
        afe_ctrl3.pu_opamp1 = 1;
        if ((afe_ctrl3.en_p_in_opamp1 == 0) & (afe_ctrl3.en_n_in_opamp1 == 0))
        {
        afe_ctrl3.en_p_in_opamp1 = 1;
        afe_ctrl3.en_n_in_opamp1 = 1;
        }
        if (afe_ctrl5.op_cmp1 == 1)
        {
            ADC_Enable();
        }
    }
    if (opamp_index == 2 )
    {
        afe_ctrl3.pu_opamp2 = 1;
        if ((afe_ctrl3.en_p_in_opamp2 == 0) & (afe_ctrl3.en_n_in_opamp2 == 0))
        {
            afe_ctrl3.en_p_in_opamp2 = 1;
            afe_ctrl3.en_n_in_opamp2 = 1;
        }
        if (afe_ctrl5.op_cmp2 == 1)
        {
            ADC_Enable();
        }
    }
    if (opamp_index == 3 )
    {
        afe_ctrl3.pu_opamp3 = 1;
        if ((afe_ctrl3.en_p_in_opamp3 == 0) & (afe_ctrl3.en_n_in_opamp3 == 0))
        {
        afe_ctrl3.en_p_in_opamp3 = 1;
        afe_ctrl3.en_n_in_opamp3 = 1;
        }
        if (afe_ctrl5.op_cmp3 == 1)
        {
            ADC_Enable();
        }
    }


    MXC_AFE->ctrl3_f = afe_ctrl3;
}

void AFE_OpAmpDisable(uint8_t opamp_index)
{
    mxc_afe_ctrl3_t afe_ctrl3 = MXC_AFE->ctrl3_f;
    if (opamp_index == 0 )
    {
        afe_ctrl3.pu_opamp0 = 0;
    }
    if (opamp_index == 1 )
    {
        afe_ctrl3.pu_opamp1 = 0;
    }
    if (opamp_index == 2 )
    {
        afe_ctrl3.pu_opamp2 = 0;
    }
    if (opamp_index == 3 )
    {
        afe_ctrl3.pu_opamp3 = 0;
    }


    MXC_AFE->ctrl3_f = afe_ctrl3;
}

void AFE_LPCEnable(uint8_t lpc_index)
{
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;
    if (lpc_index == 0 )
    {
        afe_ctrl2.poweru_comp0 = 1;
    }
    if (lpc_index == 1 )
    {
        afe_ctrl2.poweru_comp1 = 1;
    }
    if (lpc_index == 2 )
    {
        afe_ctrl2.poweru_comp2 = 1;
    }
    if (lpc_index == 3 )
    {
        afe_ctrl2.poweru_comp3 = 1;
    }

    MXC_AFE->ctrl2_f = afe_ctrl2;
    ADC_Enable();
}

void AFE_LPCDisable(uint8_t lpc_index)
{
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;
    if (lpc_index == 0 )
    {
        afe_ctrl2.poweru_comp0 = 0;
    }
    if (lpc_index == 1 )
    {
        afe_ctrl2.poweru_comp1 = 0;
    }
    if (lpc_index == 2 )
    {
        afe_ctrl2.poweru_comp2 = 0;
    }
    if (lpc_index == 3 )
    {
        afe_ctrl2.poweru_comp3 = 0;
    }

    MXC_AFE->ctrl2_f = afe_ctrl2;
}

void AFE_LPCSetup(uint8_t lpc_index, mxc_lpc_pos_in_t pos_input, mxc_lpc_neg_in_t neg_input,mxc_afe_in_mode_comp_t cmp_inmode)
{
    mxc_afe_ctrl0_t afe_ctrl0 = MXC_AFE->ctrl0_f;
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;
    mxc_afe_ctrl5_t afe_ctrl5 = MXC_AFE->ctrl5_f;
    if (lpc_index == 0)
    {
        afe_ctrl0.in_mode_comp0 = cmp_inmode;
        switch (pos_input){
            case MXC_E_AFE_LPC_POS_IN_PAD_INxP:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_SCMx:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P;
                break;
            case MXC_E_AFE_LPC_POS_IN_LED_OBS_PORT:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P_AND_INxP:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            default:
                afe_ctrl5.pos_in_sel_comp0 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
        }

        switch (neg_input){
            case MXC_E_AFE_LPC_NEG_IN_PAD_INxN:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_SNOx:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_SNO;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P;
                break;
            case MXC_E_AFE_LPC_NEG_IN_LED_OBS_PORT:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_INxN:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_SNO:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO;
                break;
            default:
                afe_ctrl5.neg_in_sel_comp0 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
        }




    }
    if (lpc_index == 1)
    {
        afe_ctrl0.in_mode_comp1 = cmp_inmode;
        switch (pos_input){
            case MXC_E_AFE_LPC_POS_IN_PAD_INxP:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_SCMx:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P;
                break;
            case MXC_E_AFE_LPC_POS_IN_LED_OBS_PORT:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P_AND_INxP:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            default:
                afe_ctrl5.pos_in_sel_comp1 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
        }

        switch (neg_input){
            case MXC_E_AFE_LPC_NEG_IN_PAD_INxN:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_SNOx:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_SNO;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P;
                break;
            case MXC_E_AFE_LPC_NEG_IN_LED_OBS_PORT:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_INxN:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_SNO:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO;
                break;
            default:
                afe_ctrl5.neg_in_sel_comp1 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
        }

    }
    if (lpc_index == 2)
    {
        afe_ctrl0.in_mode_comp2 = cmp_inmode;
        switch (pos_input){
            case MXC_E_AFE_LPC_POS_IN_PAD_INxP:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_SCMx:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P;
                break;
            case MXC_E_AFE_LPC_POS_IN_LED_OBS_PORT:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P_AND_INxP:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            default:
                afe_ctrl5.pos_in_sel_comp2 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
        }

        switch (neg_input){
            case MXC_E_AFE_LPC_NEG_IN_PAD_INxN:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_SNOx:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_SNO;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P;
                break;
            case MXC_E_AFE_LPC_NEG_IN_LED_OBS_PORT:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_INxN:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_SNO:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO;
                break;
            default:
                afe_ctrl5.neg_in_sel_comp2 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
        }


    }
    if (lpc_index == 3)
    {
        afe_ctrl0.in_mode_comp3 = cmp_inmode;
        switch (pos_input){
            case MXC_E_AFE_LPC_POS_IN_PAD_INxP:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_SCMx:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P;
                break;
            case MXC_E_AFE_LPC_POS_IN_LED_OBS_PORT:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_INxP:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC3P_AND_INxP:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC3P_AND_INPLUS;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1P_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            case MXC_E_AFE_LPC_POS_IN_DAC1N_AND_SCM:
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_DAC1_AND_SCM;
                break;
            default:
                afe_ctrl5.pos_in_sel_comp3 = MXC_E_AFE_POS_IN_SEL_COMP_INPLUS;
        }

        switch (neg_input){
            case MXC_E_AFE_LPC_NEG_IN_PAD_INxN:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_SNOx:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_SNO;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P;
                break;
            case MXC_E_AFE_LPC_NEG_IN_LED_OBS_PORT:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_LED_OBS_PORT;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0P_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC0N_AND_INxN:
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC0_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_INxN:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_INMINUS;
                break;
            case MXC_E_AFE_LPC_NEG_IN_DAC2P_AND_SNO:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_DAC2P_AND_SNO;
                break;
            default:
                afe_ctrl5.neg_in_sel_comp3 = MXC_E_AFE_NEG_IN_SEL_COMP_INMINUS;
        }

    }

    MXC_AFE->ctrl0_f = afe_ctrl0;
    MXC_AFE->ctrl2_f = afe_ctrl2;
    MXC_AFE->ctrl5_f = afe_ctrl5;
}

void AFE_LPCConfig(uint8_t lpc_index,mxc_afe_bias_mode_comp_t cmp_bias, mxc_afe_hyst_comp_t hysteresis, uint8_t tp_polarity)
{
    mxc_afe_ctrl0_t afe_ctrl0 = MXC_AFE->ctrl0_f;
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;

    if (lpc_index == 0)
    {

        afe_ctrl0.bias_mode_comp0 = cmp_bias;
        afe_ctrl2.hyst_comp0 = hysteresis;

        if (tp_polarity == 1)
        {
            afe_ctrl2.hy_pol_comp0 = 1;
        }
        else
        {
            afe_ctrl2.hy_pol_comp0 = 0;
        }

    }
    if (lpc_index == 1)
    {
        afe_ctrl0.bias_mode_comp1 = cmp_bias;
        afe_ctrl2.hyst_comp1 = hysteresis;

        if (tp_polarity == 1)
        {
            afe_ctrl2.hy_pol_comp1 = 1;
        }
        else
        {
            afe_ctrl2.hy_pol_comp1 = 0;
        }
    }
    if (lpc_index == 2)
    {

        afe_ctrl0.bias_mode_comp2 = cmp_bias;
        afe_ctrl2.hyst_comp2 = hysteresis;

        if (tp_polarity == 1)
        {
            afe_ctrl2.hy_pol_comp2 = 1;
        }
        else
        {
            afe_ctrl2.hy_pol_comp2 = 0;
        }
    }

    if (lpc_index == 3)
    {

        afe_ctrl0.bias_mode_comp3 = cmp_bias;
        afe_ctrl2.hyst_comp3 = hysteresis;

        if (tp_polarity == 1)
        {
            afe_ctrl2.hy_pol_comp3 = 1;
        }
        else
        {
            afe_ctrl2.hy_pol_comp3 = 0;
        }

    }

    MXC_AFE->ctrl0_f = afe_ctrl0;
    MXC_AFE->ctrl2_f = afe_ctrl2;
}

#define MXC_CFG_COMP_INSTANCES 8
typedef struct {
    void(*intr_cb)(void *arg);
    void *cb_arg;
} comp_interrupt_handler_t;
static comp_interrupt_handler_t _comp_intr_handler[MXC_CFG_COMP_INSTANCES];

static void _setup_comp_int(uint8_t comp_index, void(*intr_cb)(void *arg), void *cb_arg)
{
    uint32_t intr_reg_addr = (uint32_t)&MXC_AFE->intr;

    if(comp_index > MXC_CFG_COMP_INSTANCES)
        return;

    _comp_intr_handler[comp_index].intr_cb = intr_cb;
    _comp_intr_handler[comp_index].cb_arg = cb_arg;

    /* use bit-band method to be safe for setting interrup enable */
    BITBAND_SetBit(intr_reg_addr, (comp_index+24)); /* enable bits are 24-31*/
    NVIC_EnableIRQ(AFE_IRQn);
}

void AFE_OpAmpSetupInt(uint8_t opamp_index, void(*intr_cb)(void *arg), void *cb_arg)
{
    _setup_comp_int(opamp_index, intr_cb, cb_arg);
}

void AFE_LPCSetupInt(uint8_t lpc_index, void(*intr_cb)(void *arg), void *cb_arg)
{
    _setup_comp_int(lpc_index+4, intr_cb, cb_arg);
}

/* magic function name; automatically inserted into 'weak link' vector table */
void AFE_IRQHandler(void)
{
    int i;
    uint32_t int_reg = MXC_AFE->intr;

    /* clear all interrupts by writing back exact copy of register, status value is write '1' to clear */
    MXC_AFE->intr = int_reg;

    /* service all that were cleared */
    for(i=0; i<MXC_CFG_COMP_INSTANCES; i++)
    {
        comp_interrupt_handler_t *hnd = &_comp_intr_handler[i];
        if((int_reg & (1<<i)) && hnd->intr_cb) /* int flags are the first 8 bits */
            hnd->intr_cb(hnd->cb_arg);
    }
}

/*
 * The reference can rise quickly, but discharges to ground very slowly.
 * if the reference has been off, and fast_pwrdn no set (coast mode) for very long
 * the reference may have drifted towards VDD.  If so, set fast_pwrdn and discharge
 * the reference buffer cap.
 * Also, if the reference voltage is being reduced from it previous value,
 * set fast_pwrdn adn discharge teh reference buffer cap
 * After turning on the reference buffer, have to wait a little to charge the cap.
 * set fast power-down if not already, in case VREFADC has floated high
 */
void AFE_ADCVRefEnable(mxc_afe_ref_volt_sel_t adc_refsel)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;

    afe_ctrl1.ref_pu = 1;
    afe_ctrl1.refadc_fast_pwrdn_en = 0;
    afe_ctrl1.refadc_outen = 1;
    afe_ctrl1.adcrefsel = adc_refsel;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void AFE_ADCVRefDisable(uint8_t fast_power_down)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.refadc_outen = 0;
    if (!afe_ctrl1.refadc_outen && !afe_ctrl1.refdac_outen)
    {
        afe_ctrl1.refadc_fast_pwrdn_en = fast_power_down;
        afe_ctrl1.ref_pu = 0;
    }
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void AFE_DACVRefEnable(mxc_afe_ref_volt_sel_t dac_refsel, mxc_afe_dac_ref_t dacsel)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.ref_pu = 1;
    afe_ctrl1.refadc_fast_pwrdn_en = 0;
   
    if (dacsel == MXC_E_AFE_DAC_REF_REFDAC)
    {
        afe_ctrl1.refdac_outen = 1;
    }
    
    afe_ctrl1.dacrefsel = dac_refsel;
    afe_ctrl1.dacsel = dacsel;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void AFE_DACVRefDisable(uint8_t fast_power_down)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.refdac_outen = 0;
    if (!afe_ctrl1.refadc_outen && !afe_ctrl1.refdac_outen)
    {
        afe_ctrl1.refdac_fast_pwrdn_en = fast_power_down;
        afe_ctrl1.ref_pu = 0;
    }
    afe_ctrl1.dacsel = MXC_E_AFE_DAC_REF_REFADC;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}

void AFE_VRefExtBandgapSetup(uint8_t v1extadj)
{
    mxc_afe_ctrl1_t afe_ctrl1 = MXC_AFE->ctrl1_f;
    afe_ctrl1.bgextsel = 1;
    afe_ctrl1.v1extadj = v1extadj;
    MXC_AFE->ctrl1_f = afe_ctrl1;
}


#define CTRL3_CLOSE_SPST_OFFSET 20
void AFE_SetSwitchState(uint8_t switch_num, mxc_afe_close_spst_t state)
{
    if(switch_num > 3)
        return;

    if(state == MXC_E_AFE_CLOSE_SPST_SWITCH_CLOSE)
    {
        BITBAND_SetBit((uint32_t)&MXC_AFE->ctrl3, (CTRL3_CLOSE_SPST_OFFSET + switch_num));
    }
    else if(state == MXC_E_AFE_CLOSE_SPST_SWITCH_OPEN)
    {
        BITBAND_ClrBit((uint32_t)&MXC_AFE->ctrl3, (CTRL3_CLOSE_SPST_OFFSET + switch_num));
    }
}

#define INTR_SW_CTRL_OFFSET 16
void AFE_SetSwitchMode(uint8_t switch_num, mxc_adc_spst_sw_ctrl_t switch_mode)
{
    if(switch_num > 3)
        return;

    if(switch_mode == MXC_E_ADC_SPST_SW_CTRL_SOFTWARE)
    {
        BITBAND_ClrBit((uint32_t)&MXC_ADC->intr, (INTR_SW_CTRL_OFFSET + switch_num));
    }
    else if(switch_mode == MXC_E_ADC_SPST_SW_CTRL_PULSETRAIN)
    {
        BITBAND_SetBit((uint32_t)&MXC_ADC->intr, (INTR_SW_CTRL_OFFSET + switch_num));
    }
}

void AFE_LEDConfig(uint8_t port_index, mxc_afe_led_cfg_port_t led_cfg)
{
    mxc_afe_ctrl0_t afe_ctrl0 = MXC_AFE->ctrl0_f;

    if (port_index == 0)
    {
        afe_ctrl0.led_cfg_port0 = led_cfg;
    }

    if (port_index == 1)
    {
        afe_ctrl0.led_cfg_port1 = led_cfg;
    }

    MXC_AFE->ctrl0_f = afe_ctrl0;
}

void AFE_GndSwitchSet(uint8_t opamp_index, mxc_afe_gnd_sel_opamp_t state)
{
    mxc_afe_ctrl3_t afe_ctrl3 = MXC_AFE->ctrl3_f;
    if (opamp_index == 0)
    {
        afe_ctrl3.gnd_sel_opamp0 = state;
    }
    if (opamp_index == 1)
    {
        afe_ctrl3.gnd_sel_opamp1 = state;
    }
    if (opamp_index == 2)
    {
        afe_ctrl3.gnd_sel_opamp2 = state;
    }
    if (opamp_index == 3)
    {
        afe_ctrl3.gnd_sel_opamp3 = state;
    }

    MXC_AFE->ctrl3_f = afe_ctrl3;
}

void AFE_NpadSetup(uint8_t opamp_index, mxc_opamp_neg_pad_t npad_select)
{
    mxc_afe_ctrl4_t afe_ctrl4 = MXC_AFE->ctrl4_f;
    mxc_afe_ctrl2_t afe_ctrl2 = MXC_AFE->ctrl2_f;
    if (opamp_index == 0)
    {
        switch (npad_select)
        {
            case MXC_E_AFE_OPAMP_NEG_PAD_OFF:
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_LED_OBS_PORT:
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_a = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            default:
                afe_ctrl4.npad_sel_a = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
        }
    }
    if (opamp_index == 1)
    {
        switch (npad_select)
        {
            case MXC_E_AFE_OPAMP_NEG_PAD_OFF:
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_LED_OBS_PORT:
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_b = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            default:
                afe_ctrl4.npad_sel_b = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
        }
    }
    if (opamp_index == 2)
    {
        switch (npad_select)
        {
            case MXC_E_AFE_OPAMP_NEG_PAD_OFF:
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_LED_OBS_PORT:
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_c = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            default:
                afe_ctrl4.npad_sel_c = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
        }
    }
    if (opamp_index == 3)
    {
        switch (npad_select)
        {
            case MXC_E_AFE_OPAMP_NEG_PAD_OFF:
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_LED_OBS_PORT:
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC0N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC0;
                afe_ctrl2.dac0_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC1N_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC1;
                afe_ctrl2.dac1_sel = MXC_E_AFE_DACX_SEL_N;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC2P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC2P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            case MXC_E_AFE_OPAMP_NEG_PAD_DAC3P_AND_LED_OBS_PORT:
                afe_ctrl4.dac_sel_d = MXC_E_AFE_DAC_SEL_DAC3P;
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_DAC_OR_AND_LED_OBS_PORT;
                break;
            default:
                afe_ctrl4.npad_sel_d = MXC_E_AFE_NPAD_SEL_HIZ;
                break;
        }
    }

    MXC_AFE->ctrl2_f = afe_ctrl2;
    MXC_AFE->ctrl4_f = afe_ctrl4;
}
