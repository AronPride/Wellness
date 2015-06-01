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

/* $Revision: 4264 $ $Date: 2015-02-05 09:29:32 -0600 (Thu, 05 Feb 2015) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>

#include "power.h"
#include "clkman_regs.h"
#include "ioman_regs.h"
#include "rtc_regs.h"
#include "afe_regs.h"
#include "nvic_table.h"

static uint8_t pwr_mode = MXC_E_PWR_MODE_LP2;
static void (*wakeup_cb)(void) = NULL;
static void (*trippoint_cb)(void) = NULL;
uint32_t pwrman_f = 0;

void PWRMAN_IRQHandler(void){

    pwrman_f = MXC_PWRMAN->intfl;
    MXC_PWRMAN->intfl = pwrman_f;
    if (trippoint_cb)
    {
        trippoint_cb();
    }

}



void PWR_SetGPIOWUD(uint8_t port, uint8_t pin, uint8_t act_high)
{
    if (port < 4)
    {
        uint32_t req0 = MXC_IOMAN->wud_req0;
        req0 |= (1 << ((port << 3) + pin));
        MXC_IOMAN->wud_req0 = req0;
    }
    else
    {
        uint32_t req1 = MXC_IOMAN->wud_req1;
        req1 |= (1 << (((port - 4) << 3) + pin));
        MXC_IOMAN->wud_req1 = req1;
    }

    mxc_pwrman_wud_ctrl_t wud_ctrl = MXC_PWRMAN->wud_ctrl_f;
    wud_ctrl.pad_select = (port << 3) + pin;
    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_ACT_HI_LO;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;
    if (act_high) {
        MXC_PWRMAN->wud_pulse0 = 1;
    } else {
        MXC_PWRMAN->wud_pulse1 = 1;
    }

    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_CLEAR_SET;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;
    MXC_PWRMAN->wud_pulse1 = 1;
}

void PWR_ClearAllGPIOWUD(void)
{
    uint32_t wud_req0 = MXC_IOMAN->wud_req0;
    uint32_t wud_req1 = MXC_IOMAN->wud_req1;

    MXC_IOMAN->wud_req0 = 0xffffffff;
    MXC_IOMAN->wud_req1 = 0xffffffff;

    mxc_pwrman_wud_ctrl_t wud_ctrl = MXC_PWRMAN->wud_ctrl_f;
    wud_ctrl.pad_select = 0;
    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_CLEAR_SET;
    wud_ctrl.clear_all = 1;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;
    MXC_PWRMAN->wud_pulse0 = 1;
    wud_ctrl.clear_all = 0;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;

    MXC_IOMAN->wud_req0 = wud_req0;
    MXC_IOMAN->wud_req1 = wud_req1;
}

void PWR_ClearGPIOWUD(uint8_t port, uint8_t pin)
{
    mxc_pwrman_wud_ctrl_t wud_ctrl = MXC_PWRMAN->wud_ctrl_f;
    wud_ctrl.pad_select = (port << 3) + pin;
    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_CLEAR_SET;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;
    MXC_PWRMAN->wud_pulse0 = 1;

    if (port < 4)
    {
        uint32_t req0 = MXC_IOMAN->wud_req0;
        req0 &= ~(1 << ((port << 3) + pin));
        MXC_IOMAN->wud_req0 = req0;
    }
    else
    {
        uint32_t req1 = MXC_IOMAN->wud_req1;
        req1 &= ~(1 << (((port - 4) << 3) + pin));
        MXC_IOMAN->wud_req1 = req1;
    }
}

void PWR_SetCompWUD(uint8_t index, uint8_t rising_edge)
{
    uint32_t afe_ctrl0 = MXC_AFE->ctrl0;
    afe_ctrl0 |= 1 << ((index << 1) + 9);
    if (rising_edge) {
        afe_ctrl0 |= 1 << ((index << 1) + 8);
    }
    MXC_AFE->ctrl0 = afe_ctrl0;
}

void PWR_ClearAllCompWUD(void)
{
    uint32_t afe_ctrl0 = MXC_AFE->ctrl0;
    afe_ctrl0 |= 0xf0;
    afe_ctrl0 &= ~(0xff00);
    MXC_AFE->ctrl0 = afe_ctrl0;

    afe_ctrl0 &= ~(0xf0);
    MXC_AFE->ctrl0 = afe_ctrl0;
}

void PWR_ClearCompWUD(uint8_t index)
{
    uint32_t afe_ctrl0 = MXC_AFE->ctrl0;
    afe_ctrl0 |= 1 << (index + 4);
    afe_ctrl0 &= ~(1 << ((index << 1) + 9));
    MXC_AFE->ctrl0 = afe_ctrl0;

    afe_ctrl0 &= ~(1 << (index + 4));
    MXC_AFE->ctrl0 = afe_ctrl0;
}

void PWR_EnableGPIO(void)
{
    mxc_pwrman_pwr_rst_ctrl_t pwr_rst_ctrl = MXC_PWRMAN->pwr_rst_ctrl_f;
    pwr_rst_ctrl.io_active = 1;
    MXC_PWRMAN->pwr_rst_ctrl_f = pwr_rst_ctrl;

    mxc_pwrseq_reg1_t pwr_reg1 = MXC_PWRSEQ->reg1_f;
    pwr_reg1.pwr_gpio_freeze = 0;
    MXC_PWRSEQ->reg1_f = pwr_reg1;
}

void PWR_DisableGPIO(void)
{
    mxc_pwrseq_reg1_t pwr_reg1 = MXC_PWRSEQ->reg1_f;
    pwr_reg1.pwr_gpio_freeze = 1;
    MXC_PWRSEQ->reg1_f = pwr_reg1;

    mxc_pwrman_pwr_rst_ctrl_t pwr_rst_ctrl = MXC_PWRMAN->pwr_rst_ctrl_f;
    pwr_rst_ctrl.io_active = 0;
    MXC_PWRMAN->pwr_rst_ctrl_f = pwr_rst_ctrl;
}

void PWR_ClearFlags(void)
{
    mxc_rtctmr_ctrl_t rtc_ctrl = MXC_RTCTMR->ctrl_f;
    while (rtc_ctrl.pending)
        rtc_ctrl = MXC_RTCTMR->ctrl_f;
#ifndef ASYNC_FLAGS
    uint32_t flags = MXC_PWRSEQ->flags;
    MXC_PWRSEQ->flags = flags;
#endif
}


static void wakeup(void)
{
    if (wakeup_cb)
    {
        wakeup_cb();
    }
}

void PWR_SetMode(mxc_pwr_mode_t mode, void (*wakeup)(void))
{
    pwr_mode = mode;

    if (pwr_mode > MXC_E_PWR_MODE_LP1)
    {
        SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
        return;
    }

    wakeup_cb = wakeup;

    mxc_pwrseq_reg3_t pwr_reg3 = MXC_PWRSEQ->reg3_f;
    pwr_reg3.pwr_rosel_quick = 3;
    MXC_PWRSEQ->reg3_f = pwr_reg3;

    mxc_pwrseq_reg0_t pwr_reg0 = MXC_PWRSEQ->reg0_f;
    pwr_reg0.pwr_first_boot = 0;
    if (mode) {
        pwr_reg0.pwr_lp1 = 1;
    } else {
        pwr_reg0.pwr_lp1 = 0;
    }

    pwr_reg0.pwr_first_boot = 0;
    MXC_PWRSEQ->reg0_f = pwr_reg0;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

void PWR_Sleep(void)
{
    switch (pwr_mode)
    {
        case MXC_E_PWR_MODE_LP0:
            __SEV();
            __WFE(); /* hack to clear event latch per ARM support */
            __WFE(); /* deep sleep */
            break; /* reset here */
        case MXC_E_PWR_MODE_LP1:
            __SEV();
            __WFE();
            __WFE();
            wakeup();
            break;
        case MXC_E_PWR_MODE_LP2:
            __WFI();
            break;
        default: /* PWR_LP3 */
            break;
    }
}

void PWR_Init(void)
{
    PWR_EnableGPIO();
    PWR_ClearAllGPIOWUD();
    PWR_ClearAllCompWUD();

    uint32_t flags = MXC_PWRSEQ->flags;
    MXC_PWRSEQ->flags = flags;
}

void PWR_Enable(mxc_pwr_enable_t module)
{
    mxc_pwrman_pwr_rst_ctrl_t reg = MXC_PWRMAN->pwr_rst_ctrl_f;

    switch (module){
        case 0:
            reg.afe_powered = 1;
            break;
        case 1:
            reg.io_active = 1;
            break;
        case 2:
            reg.usb_powered = 1;
            break;
        case 3:
            reg.pullups_enabled = 1;
            break;
    }

    MXC_PWRMAN->pwr_rst_ctrl_f = reg;
}

void PWR_Disable(mxc_pwr_enable_t module)
{
    mxc_pwrman_pwr_rst_ctrl_t reg = MXC_PWRMAN->pwr_rst_ctrl_f;

    switch (module){
        case 0:
            reg.afe_powered = 0;
            break;
        case 1:
            reg.io_active = 0;
            break;
        case 2:
            reg.usb_powered = 0;
            break;
        case 3:
            reg.pullups_enabled = 0;
            break;
    }

    MXC_PWRMAN->pwr_rst_ctrl_f = reg;
}

#define TRICKLE_CHARGER_KEY 0xA0
void PWR_SetTrickleCharger(mxc_pwr_trickle_charger_t decode)
{
    uint8_t value = (TRICKLE_CHARGER_KEY | decode);
    mxc_pwrseq_reg1_t pwr_reg1 = MXC_PWRSEQ->reg1_f;
    pwr_reg1.pwr_trikl_chrg = value;
    MXC_PWRSEQ->reg1_f = pwr_reg1;
}

void PWR_EnableDevRun(mxc_pwr_device_t device)
{
    BITBAND_SetBit((uint32_t)&MXC_PWRSEQ->reg0, device);
}

void PWR_DisableDevRun(mxc_pwr_device_t device)
{
    BITBAND_ClrBit((uint32_t)&MXC_PWRSEQ->reg0, device);
}

void PWR_EnableDevSleep(mxc_pwr_device_t device)
{
    BITBAND_SetBit((uint32_t)&MXC_PWRSEQ->reg0, (device+1));
}

void PWR_DisableDevSleep(mxc_pwr_device_t device)
{
    BITBAND_ClrBit((uint32_t)&MXC_PWRSEQ->reg0, (device+1));
}

void PWR_EnableAllWakeupEvents(void)
{
    MXC_PWRSEQ->msk_flags = 0;
}

void PWR_DisableAllWakeupEvents(void)
{
    MXC_PWRSEQ->msk_flags = 0xffffffff;
}

void PWR_EnableWakeupEvent(mxc_pwr_event_t event)
{
    BITBAND_ClrBit((uint32_t)&MXC_PWRSEQ->msk_flags, event);
}

void PWR_DisableWakeupEvent(mxc_pwr_event_t event)
{
    BITBAND_SetBit((uint32_t)&MXC_PWRSEQ->msk_flags, event);
}

void PWR_SetTripPointVDD3(uint32_t vdd3,void (*trippoint)(void))
{

    trippoint_cb = trippoint;
    /* Enable SVM3 and SVM1 in RUN Mode */
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_SVM3);
    PWR_EnableDevRun(MXC_E_PWR_DEVICE_SVM1);

    /* set the VDD3 trip point/ warning level */
    mxc_pwrseq_reg2_t pwr_reg2 = MXC_PWRSEQ->reg2_f;
    pwr_reg2.pwr_w3 = vdd3;
    MXC_PWRSEQ->reg2_f = pwr_reg2;

    /* clear the PWRMAN Interrupts */
    pwrman_f = MXC_PWRMAN->intfl;
    MXC_PWRMAN->intfl = pwrman_f;

    /* Enable the Interrupt flag the VDD3 Warning Monitor */
    mxc_pwrman_inten_t vdd3_int = MXC_PWRMAN->inten_f;
    vdd3_int.v3_3_warning = 1;
    MXC_PWRMAN->inten_f = vdd3_int;

  /* Enabled the NVIC Interrupt, Interrupt Handler is  PWRMAN_IRQHandler*/
    NVIC_EnableIRQ(PWRMAN_IRQn);

}

void PWR_SetGPIOWeakDriver(uint8_t port, uint8_t pin, uint8_t act_high)
{
    if (port < 4)
    {
        uint32_t req0 = MXC_IOMAN->wud_req0;
        req0 |= (1 << ((port << 3) + pin));
        MXC_IOMAN->wud_req0 = req0;
    }
    else
    {
        uint32_t req1 = MXC_IOMAN->wud_req1;
        req1 |= (1 << (((port - 4) << 3) + pin));
        MXC_IOMAN->wud_req1 = req1;
    }

    mxc_pwrman_wud_ctrl_t wud_ctrl = MXC_PWRMAN->wud_ctrl_f;
    wud_ctrl.pad_select = (port << 3) + pin;

    // clear selected GPIO IO memory
    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_CLEAR_SET;
    MXC_PWRMAN->wud_pulse0 = 1;

    // configure only weak pull resistor
    wud_ctrl.pad_mode = MXC_E_PWRMAN_PAD_MODE_WEAK_HI_LO;
    MXC_PWRMAN->wud_ctrl_f = wud_ctrl;
    if (act_high) {
        MXC_PWRMAN->wud_pulse0 = 1;
    } else {
        MXC_PWRMAN->wud_pulse1 = 1;
    }

}

