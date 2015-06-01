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

/* $Revision: 2905 $ $Date: 2014-08-05 17:18:09 -0500 (Tue, 05 Aug 2014) $ */

#ifndef _DAC_H
#define _DAC_H

#include "dac_regs.h"
#include "pmu.h"

/**
 * @file  dac.h
 * @addtogroup dac DAC
 * @{
 * @brief This is the high level API for the digital-to-analog converter module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 *
 * When using the DAC in periodic output mode to push wave-form patterns
 * out, the following equation will apply for setting the pattern
 * output rate \n
 *
 * \f$T_{out} = \frac{N_s*N_i*(N_r+2)}{F_c}\f$ \n\n
 * Where: \n 
 * \f$N_s\f$ => Number of samples in a period as set in DAC_PatternConfig() \n
 * \f$N_i\f$ => Interpolation rate set in DAC_SetRate()\n
 * \f$N_r\f$ => DAC rate as set in DAC_SetRate()\n
 * \f$F_c\f$ => DAC clock rate, normally system clock.  Can be divided
 * by using CLOCKMAN clock dividers.\n\n
 *
 */

/**
 * @brief Defines the DAC power modes. Intermediate values are only applicable to 12-bit DAC instances.
 */
typedef enum {
    /** Power Level OFF  (Disabled) */
    MXC_E_DAC_PWR_MODE_OFF  = 0,
    /** Power Level 0 (48uA) */
    MXC_E_DAC_PWR_MODE_LVL0 = 1,
    /** Power Level 1 (130uA) */
    MXC_E_DAC_PWR_MODE_LVL1 = 3,
    /** Power Level 2 (210uA) */
    MXC_E_DAC_PWR_MODE_LVL2 = 5,
    /** Power Level FullPwr (291uA) */
    MXC_E_DAC_PWR_MODE_FULL = 7,
} mxc_dac_pwr_mode_t;


typedef struct {
    pmu_transfer_des_t transfer;
    union { /* either loops fixed number, or jump forever */
        pmu_loop_des_t loop;
        pmu_jump_des_t jump;
    };
    mxc_dac_regs_t *base_reg;
    void(*done_cb)(int32_t exit_status, void *done_arg);
    void *done_cb_arg;
    uint16_t loops;
    uint8_t dac_port;
} dac_transport_t;

/**
 * @brief Sets the power mode for the selected DAC instance
 *
 * @param dac_index     DAC index number
 * @param power_mode    Set or disable DAC power
 *
 */
void DAC_Enable(uint32_t dac_index, mxc_dac_pwr_mode_t power_mode);

/**
 * @brief Power down the selected DAC instance
 *
 * @param dac_index     DAC index number
 *
 */
void DAC_Disable(uint32_t dac_index);


/**
 * @brief Set values in the DAC registers related to output rates for use in a periodic mode.
 *
 * @param dac_index     DAC index number
 * @param rate          Delay between output samples in the output FIFO, see hardware docs
 * @param interp_mode   Level of interpolation between real points
 *
 */
void DAC_SetRate(uint32_t dac_index, uint16_t rate, mxc_dac_interp_mode_t interp_mode);

/**
 * @brief Set the start mode on the selected DAC instance. The start mode determines which 
 *             source will trigger the start of the DAC pattern output.
 *
 * @param dac_index     DAC index number
 * @param start_mode    Device or module that will start the DAC output
 *
 */
void DAC_SetStartMode(uint32_t dac_index, mxc_dac_start_mode_t start_mode);

/**
 * @brief This will setup a single and re-usable output object for the DAC output port.
 *            The return pointer is allocated with malloc() and can be later released using free().  
 *            Calling this function does not access the DAC hardware directly; instead, this function 
 *            loads all the information into a RAM buffer for later use by the PMU to transfer the
 *            pattern into the DAC FIFO.  For cases where multiple patterns are used in an
 *            application, this function can be called separately for each different pattern.  Then, the 
 *            handle of the desired pattern can be passed to DAC_PatternStart() to start that pattern.
 *
 * @param dac_index     DAC index number
 * @param dac_handle    Pointer to an uninitialized state structure, this function will fill-in the correct fields. 
 * @param data          Pointer to the beginning of the sample pattern
 *                          in memory, needs to be at least samples*2 bytes long
 * @param samples       number of samples to output in a single pass (UI/wave)
 * @param loops         number of times to repeat pattern, 0: forever or until DAC_PatternStop() is called
 * @param done_cb       (OPTIONAL, set to 'NULL' if not used) pointer to a callback function to be called
 *                          when the pattern output has completed
 * @param done_cb_arg   (OPTIONAL, set to 'NULL' if not used) pointer to data to be given to
 *                          the 'done' callback function
 * @param exit_status   If done_cb callback function is used, exit_status => 0; pattern pushed to DAC FIFO 
 *                           to completion without error. exit_status => -X; PMU or FIFO error.
 *
 * @return   0 on success.
 *           
 */
int32_t DAC_PatternConfig(uint32_t dac_index, dac_transport_t *dac_handle, const void *data, uint32_t samples, uint16_t loops, void(*done_cb)(int32_t exit_status, void *done_cb_arg), void *done_cb_arg);

/**
 * @brief Starts a DAC pattern output process using a handle previously returned by 
 *        DAC_PatternConfig().  The pattern is transmitted to the selected DAC FIFO
 *        using a dynamically allocated PMU channel.  The PMU channel will free itself 
 *        once the pattern is stopped, either because DAC_PatternStop() was called 
 *        or because the number of output loops defined by the 'loops' parameter in 
 *        DAC_PatternStart() have completed.
 *        Once the pattern output has started, the CPU is not needed to continue the 
 *        pattern generation, which leaves the CPU free to perform other tasks or 
 *        wait in sleep mode (LP2) until the pattern has completed.
 *
 * @param transport  Return handle from a call to DAC_PatternConfig().
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t DAC_PatternStart(dac_transport_t *transport);

/**
 * @brief Stop a running DAC output pattern that was configured with a loop count of 0 (repeat indefinitely).
 *
 * @param transport  Return handle from a call to DAC_PatternConfig().
 */
void DAC_PatternStop(dac_transport_t *transport);

/**
 * @brief Directly set the DAC to an exact value
 *
 * @param dac_index DAC index number
 * @param value     Exact value to set the DAC output DC level
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t DAC_SetOutput(uint8_t dac_index, uint32_t value);

/**
 * @brief Directly set the DAC to an exact value
 *
 * @param dac_index DAC index number
 * @param value     FIF0 value to set the DAC output DC level
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t DAC_SetOutputRaw(uint8_t dac_index, uint32_t value);
/**
 * @}
 */

#endif /* _DAC_H */
