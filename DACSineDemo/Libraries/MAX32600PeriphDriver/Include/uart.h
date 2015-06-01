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

#ifndef _UART_H
#define _UART_H

#include "uart_regs.h"

/**
 * @file  uart.h
 * @addtogroup uart UART
 * @{
 * @brief This is the high level API for the universal asynchronous receiver/transmitter module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

/**
 * @brief Setup a uart for transfer with standard UART parameters
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 * @param baud            Baud rate (57600, 9600, etc..)  The baud rate is calculated as a relation to system clock.
 *                        If the system clock changes, it will affect the baud rate.
 * @param parity_enable   Enable or disable parity. (TRUE/FALSE)
 * @param parity_mode     odd = 0; even = 1.
 * @param flow_control    Enable or disable hardware flow control. (TRUE/FALSE)
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t UART_Config(uint32_t uart_index, uint32_t baud, uint8_t parity_enable, uint8_t parity_mode, uint8_t flow_control);

/**
 * @brief Write data to the UART TX fifo.  Returns after all data has been submitted to the FIFO
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 * @param data            Pointer to the transmit data buffer.
 * @param length          Length of data buffer and number of bytes to transmit.
 *
 * @return number of bytes written to fifo.
 */
int32_t UART_Write(uint32_t uart_index, const uint8_t *data, uint32_t length);

/**
 * @brief Write data to the UART TX fifo asynchronously
 *           Returns immediately and allows data to be sent to TX FIFO as allowed.
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 * @param data            Pointer to the transmit data buffer.
 * @param length          Length of data buffer and number of bytes to transmit.
 * @param tx_done_cb      Callback for when all data has been sent to the FIFO (optional; NULL is valid)
 * @param ret_code        Callback argument; number of bytes sent or -1 for error condition
 *
 * @return number of bytes written to fifo.
 */
int32_t UART_WriteAsync(uint32_t uart_index, const uint8_t *data, uint32_t length, void(*tx_done_cb)(int32_t ret_code));

/**
 * @brief Read data from the UART RX fifo.
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 * @param data            Pointer to location data will be placed.
 * @param length          Maximum number of bytes to read.
 *
 * @return Number of bytes read. 
 */
int32_t UART_Read(uint32_t uart_index, uint8_t *data, uint32_t length);

/**
 * @brief Read data from the UART receiver in an asynchronous manner.
 *          This function will return immediately and it will setup
 *          the UART for interrupt level time to populate read_count
 *          bytes into the data_buffer and call the rx_cb function
 *          when read_count bytes are received.
 *           
 * If this function is called with NULL as rx_cb, it will clear any rx
 *          callback and disable interrupt level reading from UART
 *          FIFO.
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 * @param data            Pointer to received data allocation
 * @param length          Number of bytes to populate in data_buffer
 * @param rx_cb           Function called at interrupt level when read_count bytes are populated into data_buffer
 * @param ret_code        Number of bytes received or -1 for error condition
 *
 */
void UART_ReadAsync(uint32_t uart_index, uint8_t *data, uint32_t length, void(*rx_cb)(int32_t ret_code));

/**
 * @brief Check to see if the UART has any bytes in its receive FIFO.
 *
 * @param uart_index      Index of UART to configure. (0,1, etc...)
 *
 * @return Number of bytes in receive FIFO.
 */
int32_t UART_Poll(uint32_t uart_index);

/**
 * @}
 */

#endif /* _UART_H */
