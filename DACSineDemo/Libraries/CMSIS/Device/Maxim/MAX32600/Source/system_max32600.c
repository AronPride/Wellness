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

/* $Revision: 4474 $ $Date: 2015-03-25 10:34:14 -0500 (Wed, 25 Mar 2015) $ */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "max32600.h"
#include "clkman_regs.h"
#include "pwrman_regs.h"
#include "ioman_regs.h"
#include "trim_regs.h"
#include "flc_regs.h"
#include "pwrseq_regs.h"
#include "dac_regs.h"

void DebugMon_Handler(void)
{
    __asm("BKPT 0");
}

void NMI_Handler(void)
{
#ifdef DEBUG_MODE
    printf("NMI\n");
#endif
    while(1)
        __WFI();
}

/*
 * TODO: 
 *
 * Expand debug printing information to include text of funct name
 * and location.  Print backtrace of stack.
 *
 */
#ifdef DEBUG_MODE
void FaultISR_C(uint32_t *hardfault_args)
{
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;

    volatile unsigned char mmsr;
    volatile unsigned char bfsr;
    volatile unsigned short ufsr;
    volatile unsigned int hfsr;

    stacked_r0 = ((unsigned int) hardfault_args[0]);
    stacked_r1 = ((unsigned int) hardfault_args[1]);
    stacked_r2 = ((unsigned int) hardfault_args[2]);
    stacked_r3 = ((unsigned int) hardfault_args[3]);
    stacked_r12 = ((unsigned int) hardfault_args[4]);
    stacked_lr = ((unsigned int) hardfault_args[5]);
    stacked_pc = ((unsigned int) hardfault_args[6]);
    stacked_psr = ((unsigned int) hardfault_args[7]);

    printf("\n\n[Hard fault handler - all numbers in hex]\n");
    printf("R0 = 0x%08x\n", stacked_r0);
    printf("R1 = 0x%08x\n", stacked_r1);
    printf("R2 = 0x%08x\n", stacked_r2);
    printf("R3 = 0x%08x\n", stacked_r3);
    printf("R12 = 0x%08x\n", stacked_r12);
    printf("LR [R14] = 0x%08x  subroutine call return address\n", stacked_lr);
    printf("PC [R15] = 0x%08x  program counter address\n", stacked_pc);
    printf("PSR = 0x%08x\n", stacked_psr);
    printf("MMAR = 0x%08x  memory manage fault address\n", (*((volatile unsigned int *) (0xE000ED34))));
    printf("BFAR = 0x%08x  bus fault address\n", (*((volatile unsigned int *) (0xE000ED38))));

    /***********************************************************************************************
     * Memory Management Fault Status Register: (0xE000ED28)
     * Bit    Name         Description
     *  7     MMARVALID    MMAR is valid (0x40)
     *  4     MSTKERR      Stacking error (0x10)
     *  3     MUNSTKERR    Unstacking error (0x8)
     *  1     DACCVIOL     Data access violation (0x2)
     *  0     IACCVIOL     Instruction access violation (0x1)
     ***********************************************************************************************/
    mmsr = (*((volatile unsigned char *) (0xE000ED28)));
    printf("MMSR = 0x%02x  ", mmsr);
    if (mmsr & 0x40)
        printf("MMARVALID: MMAR is valid  ");
    if (mmsr & 0x10)
        printf("MSTKERR: Stacking error\n");
    else if (mmsr & 0x8)
        printf("MUNSTKERR: Unstacking error\n");
    else if (mmsr & 0x2)
        printf("DACCVIOL: Data access violation\n");
    else if (mmsr & 0x1)
        printf("IACCVIOL: Instruction access violation\n");
    else
        printf("\n");

    /***********************************************************************************************
     * Bus Fault Status Register: (0xE000ED28)
     * Bit    Name         Description                           
     *  7     BFARVALID    BFAR is valid (0x80)
     *  4     STKERR       Stacking error (0x10)
     *  3     UNSTKERR     Unstacking error (0x8)
     *  2     IMPREISERR  Imprecise data access violation (0x4)
     *  1     PRECISERR    Precise data access violation (0x2)
     *  0     IBUSERR      Instruction access violation (0x1)
     ***********************************************************************************************/
    bfsr = (*((volatile unsigned char *) (0xE000ED29)));
    printf("BFSR = 0x%02x  ", bfsr);
    if (bfsr & 0x80)
        printf("BFARVALID: BFAR is valid  ");
    if (bfsr & 0x10)
        printf("STKERR: Stacking error\n");
    else if (bfsr & 0x8)
        printf("UNSTKERR: Unstacking error\n");
    else if (bfsr & 0x4)
        printf("IMPREISERR: Imprecise data access violation\n");
    else if (bfsr & 0x2)
        printf("PRECISERR: Precise data access violation\n");
    else if (bfsr & 0x1)
        printf("IBUSERR: Instruction access violation\n");
    else
        printf("\n");

    /***********************************************************************************************
     * Usage Fault Status Register: (0xE000ED2A)
     * Bit    Name         Description
     *  9     DIVBYZERO    Divide by zero will take place (0x200)
     *  8     UNALIGNED    Unaligned access will take place (0x100)
     *  3     NOCP         Attempt to execute a coprocessor instruction (0x8)
     *  2     INVPC        Attempt to do exception with bad value (0x4)
     *  1     INVSTATE     Attempt to switch to invalid state (0x2)
     *  0     UNDEFINSTR   Attempt to execute an undefined instruction (0x1)
     ***********************************************************************************************/
    ufsr = (*((volatile unsigned short *) (0xE000ED2A)));
    printf("UFSR = 0x%04x  ", ufsr);
    if (ufsr & 0x200)
        printf("DIVBYZERO: Divide by zero will take place\n");
    else if (ufsr & 0x100)
        printf("UNALIGNED: Unaligned access will take place\n");
    else if (ufsr & 0x8)
        printf("NOCP: Attempt to execute a coprocessor instruction\n");
    else if (ufsr & 0x4)
        printf("INVPC: Attempt to do exception with bad value\n");
    else if (ufsr & 0x2)
        printf("INVSTATE: Attempt to switch to invalid state\n");
    else if (ufsr & 0x1)
        printf("UNDEFINSTR: Attempt to execute an undefined instruction\n");
    else
        printf("\n");

    /***********************************************************************************************
     * Usage Fault Status Register: (0xE000ED2A)
     * Bit    Name         Description
     * 31     DEBUGEVT     Hard fault caused by debug event (0x8000_0000)
     * 30     FORCED       Hard fault caused by bus/memory management/usage fault (0x4000_0000)
     *  1     VECTBL       Hard fault caused by failed vector fetch (0x1)
     ***********************************************************************************************/
    hfsr = (*((volatile unsigned int *) (0xE000ED2C)));
    printf("HFSR = 0x%08x  ", hfsr);
    if (hfsr & 0x80000000)
        printf("DEBUGEVT: Hard fault caused by debug event\n");
    else if (hfsr & 0x40000000)
        printf("FORCED: Hard fault caused by bus/memory management/usage fault\n");
    else if (hfsr & 0x1)
        printf("VECTBL: Hard fault caused by failed vector fetch\n");
    else
        printf("\n");

    //printf ("AFSR = 0x%08x\n", (*((volatile unsigned int *)(0xE000ED3C))));
    //printf ("SCB_SHCSR = %x\n", SCB->SHCSR);

    while (1) ;  /* Spin so we can use a debugger to anlayzer the situation */
}
#else /* DEBUG_MODE */
void FaultISR_C(uint32_t *hardfault_args)
{
    /* spin so we can use a debugger to anlayze the situation */
    while(1);

    /* reset the system */
    //NVIC_SystemReset();
}
#endif /* DEBUG_MODE */

void HardFault_Handler(void)
{
    __asm(
        " TST LR, #4\n"
        " ITE EQ \n"
        " MRSEQ R0, MSP \n"
        " MRSNE R0, PSP \n"
        " B FaultISR_C \n");
}

void DefaultIRQ_Handler(void)
{
    #ifdef DEBUG_MODE
    printf("DF INT HANDLER\n");
    #endif

    /* spin so we can use a debugger to anlayze the situation */
    while(1);
}

/* Application developer should override where necessary with different external HFX source */
#ifndef __SYSTEM_HFX
#define __SYSTEM_HFX 8000000
#endif

uint32_t SystemCoreClock = 24000000;

void SystemCoreClockUpdate(void)
{
    mxc_clkman_clk_ctrl_t clkman_clk_ctrl = MXC_CLKMAN->clk_ctrl_f;

    switch (clkman_clk_ctrl.system_source_select)
    {
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO_DIV_8:
            SystemCoreClock = 3000000;
            break;
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_24MHZ_RO:
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_PLL_48MHZ_DIV_2:
            SystemCoreClock = 24000000;
            break;
        case MXC_E_CLKMAN_SYSTEM_SOURCE_SELECT_HFX:
            SystemCoreClock = __SYSTEM_HFX;
            break;
    }

    uint32_t shift = MXC_CLKMAN->clk_ctrl_0_system;
    if (shift)
    {
        SystemCoreClock = SystemCoreClock >> (shift - 1);
    }
}

/* not needed for production parts */
static void set_trim_regs(void)
{
    mxc_flc_ctrl_t flash_ctrl = MXC_FLC->ctrl_f;

    /* early development devices will not have a valid info-block */
    if(flash_ctrl.info_block_valid == 0)
    {
        /* typical trim values */
        MXC_TRIM->trim_reg_11 = 0xd1e80000;
        MXC_TRIM->trim_reg_12 = 0x0000cc30;
        MXC_TRIM->trim_reg_13 = 0x00000000;
        MXC_TRIM->trim_reg_14 = 0x00000000;
    }
}

/* power seq registers */
static void set_pwr_regs(void)
{
    uint32_t dac2trim =  MXC_DAC2->reg & 0xff00ffff;
    uint32_t dac3trim =  MXC_DAC3->reg & 0xff00ffff;
    dac2trim = dac2trim + MXC_TRIM->trim_reg_36;
    dac3trim = dac3trim + MXC_TRIM->trim_reg_37;
    MXC_PWRSEQ->reg5 = MXC_TRIM->trim_reg_13;
    MXC_PWRSEQ->reg6 = MXC_TRIM->trim_reg_14;
    MXC_DAC0->trm = MXC_TRIM->trim_reg_34;
    MXC_DAC1->trm = MXC_TRIM->trim_reg_35;
    MXC_DAC2->reg = dac2trim;
    MXC_DAC3->reg = dac3trim;
}

void SystemInit(void)
{
    set_trim_regs();  /* <- not needed for production parts, but harmless in production parts */
    set_pwr_regs();
    SystemCoreClockUpdate();
    MXC_PWRMAN->pwr_rst_ctrl_f = (mxc_pwrman_pwr_rst_ctrl_t) {
        .flash_active = 1,
        .sram_active = 1,
        .io_active = 1,
        .pullups_enabled = 1,
    };
}
