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

/* $Revision: 2599 $ $Date: 2014-07-11 13:52:26 -0500 (Fri, 11 Jul 2014) $ */

#include <stdint.h>
#include <string.h>

#include "mxc_config.h"
#include "dac.h"
#include "pmu.h"

void DAC_Enable(uint32_t dac_index, mxc_dac_pwr_mode_t power_mode)
{
    mxc_dac_regs_t* this_dac = (mxc_dac_regs_t*)MXC_DAC_GET_BASE(dac_index);
    mxc_dac_ctrl0_t ctrl0 = this_dac->ctrl0_f;

    ctrl0.reset = 1;
    ctrl0.clock_gate_en = 1;
    ctrl0.power_on = 1;
    ctrl0.power_mode_1_0 = (power_mode & 0x3);
    ctrl0.power_mode_2 = (power_mode >> 2);

    this_dac->ctrl0_f = ctrl0;
    return;
}

void DAC_Disable(uint32_t dac_index)
{
    mxc_dac_regs_t* this_dac = (mxc_dac_regs_t*)MXC_DAC_GET_BASE(dac_index);
    mxc_dac_ctrl0_t ctrl0 = this_dac->ctrl0_f;

    ctrl0.reset = 1;
    ctrl0.clock_gate_en = 0;
    ctrl0.power_on = 0;
    ctrl0.power_mode_1_0 = 0;
    ctrl0.power_mode_2 = 0;
    this_dac->ctrl0_f = ctrl0;

    return;
}

void DAC_SetRate(uint32_t dac_index, uint16_t rate, mxc_dac_interp_mode_t interp_mode)
{
    mxc_dac_ctrl0_t ctrl0 = MXC_DAC_GET_DAC(dac_index)->ctrl0_f;
    mxc_dac_rate_t rate_reg = MXC_DAC_GET_DAC(dac_index)->rate_f;

    ctrl0.interp_mode = interp_mode;
    rate_reg.rate_cnt = rate;

    MXC_DAC_GET_DAC(dac_index)->ctrl0_f = ctrl0;
    MXC_DAC_GET_DAC(dac_index)->rate_f = rate_reg;
}

void DAC_SetStartMode(uint32_t dac_index, mxc_dac_start_mode_t start_mode)
{
    mxc_dac_ctrl0_t ctrl0 = MXC_DAC_GET_DAC(dac_index)->ctrl0_f;
    ctrl0.start_mode = start_mode;
    MXC_DAC_GET_DAC(dac_index)->ctrl0_f = ctrl0;

}

/* setup a repeat patern that can loop */
int32_t DAC_PatternConfig(uint32_t dac_index, dac_transport_t *dac_out, const void *data, uint32_t samples, uint16_t loops, void(*done_cb)(int32_t exit_status, void *done_arg), void *done_cb_arg)
{
    uint8_t pmu_data_width;
    uint32_t fifo_address = MXC_DAC_GET_FIFO(dac_index); 
    uint8_t wait_fifo_bit = MXC_DAC_GET_PMU_FIFO_IRQ(dac_index);
    uint8_t sample_width  = MXC_DAC_GET_WIDTH(dac_index);
    
    if(!MXC_DAC_GET_BASE(dac_index))
        return -1;
    
    memset(dac_out, 0, sizeof(dac_transport_t));
    dac_out->base_reg = (mxc_dac_regs_t*)MXC_DAC_GET_BASE(dac_index);
    dac_out->done_cb = done_cb;
    dac_out->done_cb_arg = done_cb_arg;
    
    switch((samples * sample_width) & 0x3)
    {
        case 0:
            pmu_data_width = 2; /* 32bit */
            break;
        case 2:
            pmu_data_width = 1; /* 16bit */
            break;
        default:
            pmu_data_width = 0; /* 8bit */
            break;
    }
    
    /* set op codes for the PMU */
    dac_out->transfer.op_code = PMU_TRANSFER_OP;
    dac_out->transfer.rd_size = pmu_data_width;
    dac_out->transfer.wr_size = sample_width-1;
    dac_out->transfer.rd_inc = 1;
    dac_out->transfer.tx_length = samples*sample_width;
    dac_out->transfer.rd_address = (uint32_t)data;
    dac_out->transfer.wr_address = fifo_address;
    dac_out->transfer.int_mask0 = 1 << wait_fifo_bit;
    
    /* set, 'almost empty' to 1/4 FIFO */
    dac_out->transfer.burst_size =  (MXC_CFG_DAC_FIFO_DEPTH >> 2) + (MXC_CFG_DAC_FIFO_DEPTH >> 1); 

    if(loops) {
        /* fixed number of patterns */
        dac_out->loops = loops;
        dac_out->loop.op_code = PMU_LOOP_OP;
        dac_out->loop.address = (uint32_t)&dac_out->transfer;
        dac_out->loop.interrupt = 1;
        dac_out->loop.stop = 1;
    }
    else
    {
        /* jump to repeat pattern */
        dac_out->jump.op_code = PMU_JUMP_OP;
        dac_out->jump.address = (uint32_t)&dac_out->transfer;
    }
    
    return 0;
}

int32_t DAC_PatternStart(dac_transport_t *dac_out)
{
    volatile mxc_dac_regs_t *dac_index_base;
    mxc_dac_ctrl0_t ctrl_reg;
    mxc_dac_ctrl1_int_t int_reg;
    int8_t channel;

    /* get base register space from transport struct */
    dac_index_base = dac_out->base_reg;

    /* get PMU channel */
    channel = PMU_GetChannel();

    if(channel < 0) {
        return -1;
    }
    
    /* set fifo flags */    
    ctrl_reg = dac_index_base->ctrl0_f;
    ctrl_reg.op_mode = MXC_E_DAC_OP_MODE_CONTINUOUS;
    ctrl_reg.cpu_start = 1;
    ctrl_reg.fifo_clear = 1;
    
     /* AE=1/4, allow a burst of 3/4 FIFO */
    ctrl_reg.fifo_ae_cnt = MXC_CFG_DAC_FIFO_DEPTH >> 2;

    /* set interrupts on for PMU and debug */
    int_reg = dac_index_base->ctrl1_int_f;
    int_reg.out_done_en = 1; int_reg.almost_empty_en = 1;
    
    dac_out->transfer.interrupt = 0;
    dac_out->transfer.stop = 0;

    /* yes, this will clear any pending interrupts */
    dac_index_base->ctrl1_int_f = int_reg;
    dac_index_base->ctrl0_f = ctrl_reg;
    
    if(dac_out->loops)
        PMU_SetCounter(channel, 0, dac_out->loops);
    
    /* start PMU */
    PMU_Start(channel, dac_out, dac_out->done_cb, dac_out->done_cb_arg);
    
    return 0;
}

void DAC_PatternStop(dac_transport_t *transport)
{
    uint32_t trans_op;
    
    /* must set the stop and interupt bits in one operation */
    memcpy(&trans_op, &transport->transfer, sizeof(uint32_t));
    trans_op |= 0x000018;
    memcpy(&transport->transfer, &trans_op, sizeof(uint32_t));

    return;
}

int32_t DAC_SetOutput(uint8_t dac_index, uint32_t value)
{
    mxc_dac_ctrl0_t ctrl_data;

    uint8_t width = MXC_DAC_GET_WIDTH(dac_index);
    uint32_t fifo_address = MXC_DAC_GET_FIFO(dac_index); 
    
    /* turn off interrupts */
    MXC_DAC_GET_DAC(dac_index)->ctrl1_int = 0;
    ctrl_data = MXC_DAC_GET_DAC(dac_index)->ctrl0_f;
    ctrl_data.cpu_start = 1;
    ctrl_data.fifo_clear = 1;
    ctrl_data.reset = 1;
    ctrl_data.clock_gate_en = 1;
    ctrl_data.power_on = 1;
    ctrl_data.op_mode = MXC_E_DAC_OP_MODE_FIFO;

    MXC_DAC_GET_DAC(dac_index)->ctrl0_f = ctrl_data;

    switch (width)
    {
        case 1:
            *(volatile uint8_t*)fifo_address = value;
            break;
        case 2:
            value = value << 4;
            *(volatile uint16_t*)fifo_address = value;
            break;
        default:
            return -1;
    }
    
    return 0;
}

int32_t DAC_SetOutputRaw(uint8_t dac_index, uint32_t value)
{
    mxc_dac_ctrl0_t ctrl_data;
    uint8_t width = MXC_DAC_GET_WIDTH(dac_index);
    uint32_t fifo_address = MXC_DAC_GET_FIFO(dac_index);

    /* turn off interrupts */
    MXC_DAC_GET_DAC(dac_index)->ctrl1_int = 0;
    ctrl_data = MXC_DAC_GET_DAC(dac_index)->ctrl0_f;
    ctrl_data.cpu_start = 1;
    ctrl_data.fifo_clear = 1;
    ctrl_data.reset = 1;
    ctrl_data.clock_gate_en = 1;
    ctrl_data.power_on = 1;
    ctrl_data.op_mode = MXC_E_DAC_OP_MODE_FIFO;

    MXC_DAC_GET_DAC(dac_index)->ctrl0_f = ctrl_data;

    switch (width)
    {
        case 1:
            *(volatile uint8_t*)fifo_address = value;
            break;
        case 2:
            *(volatile uint16_t*)fifo_address = value;
            break;
        default:
            return -1;
    }

    return 0;
}
