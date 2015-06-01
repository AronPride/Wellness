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

/* $Revision: 3586 $ $Date: 2014-11-19 08:45:45 -0600 (Wed, 19 Nov 2014) $ */

#include "mxc_config.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pmu.h"
#include "adc.h"
#include "systick.h"

/* have PMU only move 3/4 fifo at a time */
#define ADC_MAX_PMU ((MXC_CFG_ADC_FIFO_DEPTH>>1) + (MXC_CFG_ADC_FIFO_DEPTH>>2))

int32_t ADC_CaptureConfig(adc_transport_t *adc_state, uint16_t *buf1, uint32_t buf1_samples,
                          uint16_t *buf2, uint32_t buf2_samples,
                          void(*done_cb)(int32_t exit_status, void *arg), void *done_cb_arg, uint8_t stop)
{
    uint32_t burst_size;
    adc_pmu_t *des1, *des2;
 
    memset(adc_state, 0, sizeof(adc_transport_t));

    des1 = &adc_state->des1;
    des2 = &adc_state->des2;

    adc_state->buf1 = (uint32_t)buf1;
    adc_state->buf2 = (uint32_t)buf2;

    adc_state->done_cb = done_cb;
    adc_state->done_cb_arg = done_cb_arg;

    adc_state->stop = stop;

    if(buf1_samples < ADC_MAX_PMU)
        burst_size = buf1_samples;
    else
        burst_size = ADC_MAX_PMU;

    /* setup PMU op-codes */
    memset(des1, 0, sizeof(adc_pmu_t));
    memset(des2, 0, sizeof(adc_pmu_t));
    des1->transfer.op_code = PMU_TRANSFER_OP;
    des1->transfer.interrupt = 1;
    des1->transfer.rd_size = 1;
    des1->transfer.wr_size = 1;
    des1->transfer.wr_inc = 1;
    des1->transfer.tx_length = buf1_samples*2;
    des1->transfer.wr_address = (uint32_t)buf1;
    des1->transfer.rd_address = MXC_BASE_ADC_FIFO;
    des1->transfer.int_mask0 = (1 << PMU_IRQ_ADC_DONE) | (1 << PMU_IRQ_ADC_FIFO_AF);
    des1->transfer.burst_size = burst_size;

    if(buf2 == NULL) 
    {
        /* single buffered, fixed samples */
        des1->transfer.stop = 1;
        adc_state->stop = 1; /* force stop bit for non double buffered requests */
        return 0;
    }

    /* jump to the second buffer */
    des1->jump.op_code = PMU_JUMP_OP;
    des1->jump.address = (uint32_t)&adc_state->des2;
    
    /* second transfer is the same with different write location/size */
    memcpy(des2, des1, sizeof(adc_pmu_t));
    des2->transfer.wr_address = (uint32_t)buf2;
    des2->transfer.tx_length = buf2_samples*2;

    if(stop) 
    {
        /* double buffered, fixed samples */
        des2->transfer.stop = 1;
        return 0;
    }

    /* continuous mode; jump to the first buffer */
    des2->jump.op_code = PMU_JUMP_OP;
    des2->jump.address = (uint32_t)&adc_state->des1;

    return 0;
}

void ADC_Enable(void)
{
    mxc_adc_ctrl0_t ctrl0 = MXC_ADC->ctrl0_f;
    mxc_adc_intr_t int_reg = MXC_ADC->intr_f;
    uint8_t temp;
	uint8_t temp2;

    ctrl0.cpu_adc_rst = 1;  /* self clearing */
    MXC_ADC->ctrl0_f = ctrl0;
 
    ctrl0.adc_en = 1;
    ctrl0.cpu_adc_strt = 0;
    ctrl0.adc_clk_en = 1;
    MXC_ADC->ctrl0_f = ctrl0;

    /* proper operation requires strobe of bipol enable;
       save and use previous set value */
    temp = ctrl0.bi_pol;
    ctrl0.bi_pol=0;
    MXC_ADC->ctrl0_f = ctrl0;
 
    ctrl0.bi_pol=temp;
    MXC_ADC->ctrl0_f = ctrl0;

    /* use 'done' flag for completion */
    int_reg.done_en = 1;
    int_reg.fifo_af_en = 1;
    int_reg.fifo_of_en = 1;

    /* writing back will clear any pending interrupts, yes we want this for reset / new capture */
    MXC_ADC->intr_f = int_reg;

    /*
     * take one 'dummy' sample to prime the system 
     * Note: discard first sample after changing to Bipolar=1 to clear an uninitialized switch in ADC
     */
    mxc_adc_ctrl0_t ctrl_reg = MXC_ADC->ctrl0_f;
	mxc_adc_tg_ctrl1_t tg_ctrl1 = MXC_ADC->tg_ctrl1_f;
	
	temp2 = tg_ctrl1.adc_brst_cnt;
    tg_ctrl1.adc_brst_cnt = 0;
    MXC_ADC->tg_ctrl1_f = tg_ctrl1;

    ADC_ManualRead();

    /* restore settings, restores startmode if it was not software */
    MXC_ADC->ctrl0_f = ctrl_reg;
	tg_ctrl1.adc_brst_cnt = temp2;
    MXC_ADC->tg_ctrl1_f = tg_ctrl1;

    return;
}

void ADC_Disable(void)
{
    mxc_adc_ctrl0_t ctrl0 = MXC_ADC->ctrl0_f;
    mxc_adc_intr_t int_reg = MXC_ADC->intr_f;

    /* write back interrupt register to clear */
    MXC_ADC->intr_f = int_reg;

    ctrl0.cpu_adc_rst = 0x1;
    ctrl0.adc_en = 0;
    ctrl0.cpu_adc_strt = 0;
    ctrl0.adc_clk_en = 0;
    MXC_ADC->ctrl0_f = ctrl0;

    return;
}

int32_t ADC_CaptureStart(adc_transport_t *adc_state)
{
    mxc_adc_ctrl0_t ctrl_reg = MXC_ADC->ctrl0_f;
    mxc_adc_tg_ctrl0_t tg_ctrl0 = MXC_ADC->tg_ctrl0_f;
    mxc_adc_tg_ctrl1_t tg_ctrl1 = MXC_ADC->tg_ctrl1_f;
    mxc_adc_intr_t int_reg = MXC_ADC->intr_f;
    adc_pmu_t  *des1 = &adc_state->des1;
    adc_pmu_t  *des2 = &adc_state->des2;
    int8_t pmu_channel = PMU_GetChannel();

    if(pmu_channel < 0)
        return -1;

    adc_state->pmu_channel = pmu_channel;
    
    /* the caller must set the adc_mode correctly to match this */
    if(adc_state->stop)
    {
        /* ADC_SMPLCNT_xx mode */
        tg_ctrl0.adc_smpl_cnt = (uint16_t)(des1->transfer.tx_length + des2->transfer.tx_length);
        MXC_ADC->tg_ctrl0_f = tg_ctrl0;
    }
    else
    {
        /* reset stop for cont transfer that may have been halted by ADC_CaptureStop */
        des2->jump.stop = 0;
    }

    /* setup interrupt register enable flags, 'almost full' and 'done' flags will be used */
    int_reg.fifo_af_en = 1;
    int_reg.fifo_of_en = 1; /* debug only, does not affect performance */
    int_reg.done_en = 1;

    /* writing back will clear any pending interrupts, yes we want this for reset / new capture */
    MXC_ADC->intr_f = int_reg;
    
    /* set almost full lower 4 bits (see HW docs) */
    tg_ctrl1.fifo_af_cnt = des1->transfer.burst_size & 0xf;
    MXC_ADC->tg_ctrl1_f = tg_ctrl1;

    /* start PMU */
    PMU_Start(pmu_channel, des1, adc_state->done_cb, adc_state->done_cb_arg);

    /* start ADC engine */
    ctrl_reg.cpu_dac_strt = 1;
    MXC_ADC->ctrl0_f = ctrl_reg;
    ctrl_reg.cpu_adc_strt = 1;
    MXC_ADC->ctrl0_f = ctrl_reg;

    return 0;
}

int32_t ADC_CaptureStop(adc_transport_t *adc_state)
{
    /* set the stop bit and let the PMU ISR do the rest */
    adc_pmu_t  *des2 = &adc_state->des2;    

    /* set the 'stop' bit the atomic way */
    BITBAND_SetBit((uint32_t)&des2->jump, PMU_STOP_POS);

    return 0;
}

/* non publicized API, useful in timer situations;  pulse train start would be better */
void ADC_CaptureTrigger(void)
{ 
    BITBAND_SetBit((uint32_t)&MXC_ADC->ctrl0, ADC_CTRL0_ADC_CPU_STRT_POS);
    return;
}

uint16_t ADC_ManualRead(void)
{
    mxc_adc_tg_ctrl0_t tg_ctrl0 = MXC_ADC->tg_ctrl0_f;
    mxc_adc_ctrl0_t ctrl_reg = MXC_ADC->ctrl0_f;
    mxc_adc_intr_t int_reg = MXC_ADC->intr_f;
    uint16_t value;

    /* force start mode software */
    ctrl_reg.adc_strt_mode = 0;

    ctrl_reg.cpu_adc_strt = 1;
    ctrl_reg.mode = MXC_E_ADC_MODE_SMPLCNT_FULL_RATE;

    /* just take one sample */
    tg_ctrl0.adc_smpl_cnt = 1;
    MXC_ADC->tg_ctrl0_f = tg_ctrl0;

    /* writing back int reg will clear any pending interrupts
       we want this for new capture */
    MXC_ADC->intr_f = int_reg;
    
    /* write back ctrl0 register, this will start the capture */
    MXC_ADC->ctrl0_f = ctrl_reg;

    do {
        int_reg = MXC_ADC->intr_f;  /* reread the register */
    } while(!int_reg.done);

    /* pull one sample from FIFO */
    value = *(volatile uint16_t*)MXC_BASE_ADC_FIFO;

    return value;
}

void ADC_SetRate(uint32_t pga_acq_cnt, uint32_t adc_acq_cnt, uint32_t pga_trk_cnt, uint32_t adc_slp_cnt)
{
    mxc_adc_tg_ctrl0_t tg_ctrl0 = MXC_ADC->tg_ctrl0_f;
    mxc_adc_tg_ctrl1_t tg_ctrl1 = MXC_ADC->tg_ctrl1_f;

    tg_ctrl1.adc_acq_cnt = adc_acq_cnt;
    tg_ctrl1.adc_sleep_cnt = adc_slp_cnt;
    tg_ctrl1.pga_acq_cnt = pga_acq_cnt;
    tg_ctrl0.pga_trk_cnt = pga_trk_cnt;

    MXC_ADC->tg_ctrl0_f = tg_ctrl0;
    MXC_ADC->tg_ctrl1_f = tg_ctrl1;
    return;
}

void ADC_SetMode(mxc_adc_mode_t adc_mode, mxc_adc_avg_mode_t filter_mode, uint32_t filter_val, mxc_adc_bi_pol_t bipolar_enable, mxc_adc_range_t bp_range)
{
    mxc_adc_ctrl0_t ctrl0 = MXC_ADC->ctrl0_f;
    mxc_adc_tg_ctrl1_t tg_ctrl1 = MXC_ADC->tg_ctrl1_f;

    ctrl0.mode = adc_mode;
    ctrl0.avg_mode = filter_mode;
    ctrl0.bi_pol = bipolar_enable;
    ctrl0.range = bp_range;

    tg_ctrl1.adc_brst_cnt = filter_val;

    MXC_ADC->ctrl0_f = ctrl0;
    MXC_ADC->tg_ctrl1_f = tg_ctrl1;

    return;
}

void ADC_SetMuxSel(mxc_adc_pga_mux_ch_sel_t mux_ch_sel, mxc_adc_pga_mux_diff_t mux_diff)
{
    mxc_adc_pga_ctrl_t pga_ctrl = MXC_ADC->pga_ctrl_f;

    pga_ctrl.mux_ch_sel = mux_ch_sel;
    pga_ctrl.mux_diff = mux_diff;

    MXC_ADC->pga_ctrl_f = pga_ctrl;

    return;
}

void ADC_SetPGAMode(uint32_t pga_bypass, mxc_adc_pga_gain_t pga_gain)
{
    mxc_adc_pga_ctrl_t pga_ctrl = MXC_ADC->pga_ctrl_f;
    
    pga_ctrl.cpu_pga_bypass = pga_bypass;
    pga_ctrl.gain = pga_gain;

    MXC_ADC->pga_ctrl_f = pga_ctrl;
    
    return;
}

void ADC_SetStartMode(mxc_adc_strt_mode_t adc_start_mode)
{
    mxc_adc_ctrl0_t ctrl0 = MXC_ADC->ctrl0_f;
    ctrl0.adc_strt_mode = adc_start_mode;
    MXC_ADC->ctrl0_f = ctrl0;
    return;
}

void ADC_SetScanCount(mxc_adc_scan_cnt_t scan_cnt)
{
    mxc_adc_ctrl1_t ctrl1 = MXC_ADCCFG->ctrl1_f;
    ctrl1.scan_cnt = scan_cnt;
    MXC_ADCCFG->ctrl1_f = ctrl1;
    
    return;
}

void ADC_SetScanDesc(uint8_t scan_desc_index, uint8_t mux_diff, uint8_t pga_gain, uint8_t mux_ch_sel)
{
    volatile mxc_adc_scan_t *scan_desc_reg;
    mxc_adc_scan_t scan_desc_ary;
    mxc_adc_scan_desc_t *this_desc;

    if(scan_desc_index < 4)
    {
        scan_desc_reg = &MXC_ADCCFG->scan1_f;
    }
    else
    {
        scan_desc_reg = &MXC_ADCCFG->scan2_f;
        scan_desc_index -= 4;
    }

    scan_desc_ary = *scan_desc_reg;
    this_desc = (mxc_adc_scan_desc_t*)&scan_desc_ary.adc_scan_desc[scan_desc_index];
    this_desc->mux_diff = mux_diff;
    this_desc->pga_gain = pga_gain;
    this_desc->mux_ch_sel = mux_ch_sel;
    *scan_desc_reg = scan_desc_ary;

    return;
}
