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

/* $Revision: 2581 $ $Date: 2014-07-10 16:15:29 -0500 (Thu, 10 Jul 2014) $ */

#include "mxc_config.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "pmu.h"

typedef struct pmu_channel_state_t {
    void *done_cb_arg;
    void(*done_cb)(int32_t exit_status, void *arg);
} pmu_channel_state_t;

static pmu_channel_state_t pmu_channel_state[MXC_CFG_PMU_CHANNELS];

static uint32_t pmu_mutex = 0;
int8_t PMU_GetChannel(void)
{
    int8_t channel = 0;

    while(BITBAND_GetBit((uint32_t)&pmu_mutex, channel) != 0) {
        channel++;
    }

    if(channel > MXC_CFG_PMU_CHANNELS) {
        return -1;
    }    

    BITBAND_SetBit((uint32_t)&pmu_mutex, channel);
    
    return channel;
}

void PMU_FreeChannel(int8_t channel)
{
    BITBAND_ClrBit((uint32_t)&pmu_mutex, channel);
}

/* this is a fixed function name that the linker will automagically put in the ISR vector */
void PMU_IRQHandler(void)
{
    int i; 
    volatile mxc_pmu_bits_t *pmu_bits = (mxc_pmu_bits_t*)MXC_BASE_PMU_BITBAND;
    
    for(i=0; i<MXC_CFG_PMU_CHANNELS; i++)
    {
        if(pmu_bits->interrupt)
        {
            uint32_t stop_bit = pmu_bits->ll_stopped;
            //int32_t exit_status = -(pmu_bits->bus_error + (pmu_bits->to_stat << 1));
            
            /* make sure to get status bits before clearing the int; clearing the int clears status bits */
            pmu_bits->interrupt = 1;

            if(stop_bit) {
                PMU_FreeChannel(i);
            }
            
            if(pmu_channel_state[i].done_cb) {
                pmu_channel_state[i].done_cb(stop_bit, pmu_channel_state[i].done_cb_arg);
            }
        }
        pmu_bits++;
    }
}

int32_t PMU_Start(int8_t channel, const void *desc_list_address, void(*done_cb)(int32_t exit_status, void *arg), void *done_cb_arg)
{
    mxc_pmu_regs_t *pmu = (mxc_pmu_regs_t*)MXC_BASE_PMU0;
    mxc_pmu_regs_t *my_pmu = &pmu[channel];
    mxc_pmu_cfg_t cfg_start = my_pmu->cfg_f;
    
    /* is this channel already running? */
    if(cfg_start.enable) {
        return -1;
    }

    pmu_channel_state[channel].done_cb = done_cb;
    pmu_channel_state[channel].done_cb_arg = done_cb_arg;
    
    NVIC_EnableIRQ(PMU_IRQn);
    
    /* set flags */
    cfg_start.enable = 1;
    cfg_start.int_en = 1;
    cfg_start.burst_size = 0x10;

    /* set start op-code */
    my_pmu->dscadr = (uint32_t)desc_list_address;

    /* write back to register space */
    my_pmu->cfg_f = cfg_start;

    return 0;
}

void PMU_SetCounter(int8_t channel, int8_t counter_num, uint16_t value)
{
    mxc_pmu_regs_t *pmu = (mxc_pmu_regs_t*)MXC_BASE_PMU0;
    mxc_pmu_regs_t *my_pmu = &pmu[channel];
    mxc_pmu_loop_t my_loop = my_pmu->loop_f;

    if (counter_num) {
        my_loop.counter_1 = value;
    } else {
        my_loop.counter_0 = value;
    }
    
    my_pmu->loop_f = my_loop;
}
