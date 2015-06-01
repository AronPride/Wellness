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

/* $Revision: 3368 $ $Date: 2014-10-20 17:30:52 -0500 (Mon, 20 Oct 2014) $ */

#ifndef _PMU_H
#define _PMU_H

#include "pmu_regs.h"

/**
 * @file  pmu.h
 * @addtogroup pmu Peripheral Management Unit
 * @{
 * @brief This is the high level API for the peripheral management unit module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */


/* public opcodes
 *
 */
#define PMU_MOVE_OP     0x0
#define PMU_WRITE_OP    0x1
#define PMU_WAIT_OP     0x2
#define PMU_JUMP_OP     0x3
#define PMU_LOOP_OP     0x4
#define PMU_POLL_OP     0x5
#define PMU_BRANCH_OP   0x6
#define PMU_TRANSFER_OP 0x7

#define PMU_INTERRUPT_BIT 0x008
#define PMU_STOP_BIT      0x010
#define PMU_READ_16_BIT   0x020
#define PMU_READ_32_BIT   0x040
#define PMU_READ_INC_BIT  0x080
#define PMU_WRITE_16_BIT  0x100
#define PMU_WRITE_32_BIT  0x200
#define PMU_WRITE_INC_BIT 0x400
#define PMU_CONT_BIT_BIT  0x800
#define PMU_COUNTER1      0x020
#define PMU_POLL_AND      0x080

#define PMU_INT_POS    (3)
#define PMU_STOP_POS   (4)
#define PMU_READS_POS  (5)
#define PMU_READI_POS  (7)
#define PMU_WRITES_POS (8)
#define PMU_WRITEI_POS (10)
#define PMU_CONT_POS   (11)
#define PMU_LEN_POS    (12)
#define PMU_TX_BS_POS  (26)

/* The macros like the one below are designed to help build static PMU programs
 *  as arrays of 32bit words.
 */
#define PMU_IS(interrupt, stop) (interrupt<<PMU_INT_POS) | (stop<<PMU_STOP_POS)

typedef struct pmu_move_des_t {
    uint32_t op_code   : 3; /* 0x0 */
    uint32_t interrupt : 1;
    uint32_t stop      : 1;
    uint32_t read_size : 2;
    uint32_t read_inc  : 1;
    uint32_t write_size: 2;
    uint32_t write_inc : 1;
    uint32_t cont      : 1;
    uint32_t length    : 20;
    
    uint32_t write_address;
    uint32_t read_address;
} pmu_move_des_t;
#define PMU_MOVE(i, s, rs, ri, ws, wi, c, length, wa, ra) \
    (PMU_MOVE_OP | PMU_IS(i,s) | rs | ri | ws | wi | c | (length << PMU_LEN_POS)), wa, ra

/* new_value = value | (old_value & ~ mask)  */
typedef struct pmu_write_des_t {
    uint32_t op_code   : 3; /* 0x1 */
    uint32_t interrupt : 1;
    uint32_t stop      : 1;
    uint32_t           : 3;
    uint32_t write_size: 2; /* this should not be anything but 0x2; only 32-bit works */
    uint32_t           :22;
    
    uint32_t write_address;
    uint32_t value;
    uint32_t mask;
} pmu_write_des_t;
#define PMU_WRITE(i, s, a, v, m) (PMU_WRITE_OP | PMU_IS(i,s) | PMU_WRITE_32_BIT), a, v, m

typedef struct pmu_wait_des_t {
    uint32_t op_code   : 3; /* 0x2 */
    uint32_t interrupt : 1;
    uint32_t stop      : 1;
    uint32_t           :27;
    
    uint32_t mask1;
    uint32_t mask2;
} pmu_wait_des_t;
#define PMU_WAIT(i, s, wbit) (PMU_WAIT_OP | (i<<PMU_INT_POS) | (s<<PMU_STOP_POS)), \
        ((wbit<32)?(1<<wbit):0), ((wbit>31)?(1<<(wbit-32)):0) 


typedef struct pmu_jump_des_t {
    uint32_t op_code   : 3; /* 0x3 */
    uint32_t interrupt : 1;
    uint32_t stop      : 1;
    uint32_t           : 27;

    uint32_t address;
} pmu_jump_des_t;
#define PMU_JUMP(i, s, a) (PMU_JUMP_OP | (i<<PMU_INT_POS) | (s<<PMU_STOP_POS)), a

typedef struct pmu_loop_des_t {
    uint32_t op_code    : 3; /* 0x4 */
    uint32_t interrupt  : 1;
    uint32_t stop       : 1;
    uint32_t counter    : 2;
    uint32_t            : 25;
    
    uint32_t address;
} pmu_loop_des_t;
#define PMU_LOOP(i, s, c, a) (PMU_LOOP_OP | (i<<PMU_INT_POS) | (s<<PMU_STOP_POS) | (c==1?PMU_COUNTER1:0)), a

typedef struct pmu_poll_des_t {
    uint32_t op_code    : 3; /* 0x5 */
    uint32_t interrupt  : 1;
    uint32_t stop       : 1;
    uint32_t read_size  : 2;
    uint32_t and        : 1;
    uint32_t            :24;

    uint32_t poll_addr;
    uint32_t data;
    uint32_t mask;
    uint32_t poll_interval;
} pmu_poll_des_t;
#define PMU_POLL(i, s, a, adr, d, m, per) (PMU_POLL_OP | PMU_IS(i,s) | PMU_READ_32_BIT | (a=1?PMU_POLL_AND:0)), adr, d, m, per

typedef struct pmu_branch_des_t {
    uint32_t op_code    : 3; /* 0x6 */
    uint32_t interrupt  : 1;
    uint32_t stop       : 1;
    uint32_t read_size  : 2;
    uint32_t and        : 1;
    uint32_t            :24;

    uint32_t poll_addr;
    uint32_t data;
    uint32_t mask;
    uint32_t address;
} pmu_branch_des_t;
#define PMU_BRANCH(i, s, a, adr, d, m, badr) \
    (PMU_BRANCH_OP | PMU_IS(i,s) | PMU_READ_32_BIT | (a=1?PMU_POLL_AND:0)), adr, d, m, badr

typedef struct pmu_transfer_des_t {
    uint32_t op_code    : 3; /* 0x7 */
    uint32_t interrupt  : 1;
    uint32_t stop       : 1;
    uint32_t rd_size    : 2;
    uint32_t rd_inc     : 1;
    uint32_t wr_size    : 2;
    uint32_t wr_inc     : 1;
    uint32_t            : 1;
    uint32_t tx_length  :20;

    uint32_t wr_address;
    uint32_t rd_address;
    uint32_t int_mask0;

    uint32_t int_mask1  :18;
    uint32_t            : 8;
    uint32_t burst_size : 6;
} pmu_transfer_des_t;
#define PMU_TRANSFER(i, s, rs, ri, ws, wi, l, wa, ra, wbit, b) \
    (PMU_TRANSFER_OP | PMU_IS(i,s) | rs | ri | ws | wi | (l << PMU_LEN_POS)), wa, ra, \
        ((wbit<32)?(1<<wbit):0), (((wbit>31)?(1<<(wbit-32)):0) | (b << PMU_TX_BS_POS))


/**
 * @brief Request and lock a PMU channel.
           The channel will be automatically free when the PMU program completes with the
           'stop' bit set in the final op-code of the PMU program.
 
 * @return The next available channel in a stack fashion, or -1 if none are available
 *
 */
int8_t PMU_GetChannel(void);

/**
 * @brief Start a PMU program on a channel.
 * 
 * @param channel  Channel that will run the PMU program.
 * @param opcode   Pointer to the first opcode of the PMU program.
 * @param intr_cb  Callback function to be called for every opcode that has the interrupt bit set.
                      The arguments to the callback function include a void pointer specified in the
                      next arg to this func cb_arg, and a single bit value of 1 if the interrupt opcode
                      has the stop bit set indicating completion of this PMU program.
                      If the channel was allocated with PMU_GetChannel(), having the 'stop' bit set in an
                      opcode will automatically free the channel.
 * @param cb_arg   Pointer to be passed to the interrupt callback function.
 *
 * @return 0 => Success. Non zero => error condition.
 *
 */
int32_t PMU_Start(int8_t channel, const void *opcode, void(*intr_cb)(int32_t exit_status, void *cb_arg), void *cb_arg);

/**
 * @brief Set a loop counter value on a channel
 *
 * @param channel      Channel number to set the value on.
 * @param counter_num  Counter number for the channel, (0 or 1).
 * @param value        Loop count value.
 */
void PMU_SetCounter(int8_t channel, int8_t counter_num, uint16_t value);

/**
 * @brief Stop a running channel.  This will de-assert the enable bit on the channel and stop
            the running PMU program at the current op-code.  The PMU interrupt will not get
            set and the int_cb function will not be called.
 *
 * @param channel Channel to stop.
 */
void PMU_Stop(int8_t channel);


/**
 * @}
 */

#endif /* _PMU_H */
