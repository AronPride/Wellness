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

#ifndef _I2CM_H
#define _I2CM_H

#include "i2cm_regs.h"

/**
 * @file  i2cm.h
 * @addtogroup i2cm I2C Master
 * @{
 * @brief This is the high level API for the inter-integrated circuit master controller module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief speed option for i2c master
 */
typedef enum { 
    /** 100KHz */
    MXC_E_I2CM_SPEED_100KHZ = 0,
    /** 400KHz */
    MXC_E_I2CM_SPEED_400KHZ,
    /** 1MHz */
    MXC_E_I2CM_SPEED_1MHZ
} i2cm_speed_t;


/**
 * @brief This function initialize the I2C master device.
 * @param  index   index of I2C master.
 * @param  speed   speed of the I2C clock.  The output is only correct with a I2Cm clock of 24MHz.
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t I2CM_Init(uint8_t index, i2cm_speed_t speed);

/**
 * @brief This function performs a read transaction over I2C. A read transaction consists
 * of a write from cmd_data of length cmd_data_bytes followed by a read of length
 * read_data_bytes to read_data. If cmd_data_bytes is 0 then there will be neither
 * an initial write nor a repeated start condition transmitted.
 *
 * @param index             index of I2C master.
 * @param addr              address of I2C slave, driver will take care of the read/write bit.
 * @param cmd               command data buffer.
 * @param cmd_bytes         number of command data bytes to write to slave.
 * @param data              read data buffer.
 * @param data_bytes        number of bytes to read from slave following the command write (and repeated start).
 *
 * @return number of bytes read.
 */
int32_t I2CM_Read(uint8_t index, uint8_t addr, const uint8_t *cmd_data, uint32_t cmd_data_bytes, uint8_t *read_data, uint32_t read_data_bytes);

/**
 * @brief This function performs a write transaction over I2C. A write transaction consists
 * of a write from cmd_data of length cmd_data_bytes followed by a write from write_data
 * of length write_data_bytes. If either cmd_data_bytes or write_data_bytes is 0 then
 * there will be only a single write with no repeated start condition.
 *
 * @param index             index of I2C master.
 * @param addr              address of I2C slave, driver will take care of the read/write bit.
 * @param cmd               command data buffer.
 * @param cmd_bytes         number of command data bytes to write to slave.
 * @param data              write data buffer.
 * @param data_bytes        number of bytes to write to slave following the command write (and repeated start).
 *
 * @return number of bytes written.
 */
int32_t I2CM_Write(uint8_t index, uint8_t addr, const uint8_t *cmd_data, uint32_t cmd_data_bytes, const uint8_t *write_data, uint32_t write_data_bytes);

/**
 * @brief This function performs an asyncronized write transaction over I2C. A write transaction consists
 * of a write from cmd_data of length cmd_data_bytes followed by a write from write_data
 * of length write_data_bytes. If either cmd_data_bytes or write_data_bytes is 0 then
 * there will be only a single write with no repeated start condition.
 *
 * @param index             index of I2C master.
 * @param addr              address of I2C slave, driver will take care of the read/write bit.
 * @param cmd               command data buffer.
 * @param cmd_bytes         number of command data bytes to write to slave.
 * @param data              write data buffer.
 * @param data_bytes        number of bytes to write to slave following the command write (and repeated start).
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t I2CM_WriteAsync(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, const uint8_t *data, uint32_t data_bytes, void(*tx_done)(int32_t ret_status));

/**
 * @brief This function performs an asyncronized read transaction over I2C. A read transaction consists
 * of a write from cmd_data of length cmd_data_bytes followed by a read of length
 * read_data_bytes to read_data. If cmd_data_bytes is 0 then there will be neither
 * an initial write nor a repeated start condition transmitted.
 *
 * @param index             index of I2C master.
 * @param addr              address of I2C slave, driver will take care of the read/write bit.
 * @param cmd_data          command data buffer.
 * @param cmd_data_bytes    number of command data bytes to write to slave.
 * @param read_data         read data buffer.
 * @param read_data_bytes   number of bytes to read from slave following the command write (and repeated start).
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t I2CM_ReadAsync(uint8_t index, uint8_t addr, const uint8_t *cmd, uint32_t cmd_bytes, uint8_t *data, uint32_t data_bytes, void(*rx_handler)(int32_t rx_bytes));


/**
 * @}
 */

#endif /* _I2CM_H_ */
