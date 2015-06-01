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

/* $Revision: 3496 $ $Date: 2014-11-10 13:20:26 -0600 (Mon, 10 Nov 2014) $ */

#ifndef _SPI_H
#define _SPI_H

#include "spi_regs.h"

/**
 * @file  spi.h
 * @addtogroup spi SPI
 * @{
 * @brief This is the high level API for the serial peripheral interface module
 *        of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */

typedef union
{
    struct
    {
        uint16_t direction   : 2;
        uint16_t unit        : 2;
        uint16_t size        : 5;
        uint16_t width       : 2;
        uint16_t alt_clk     : 1;
        uint16_t flow_ctrl   : 1;
        uint16_t deassert_ss : 1;
        uint16_t : 2;
    };
    uint16_t info;
} spi_header_t;

typedef struct
{
    mxc_spi_mstr_cfg_t mstr;
    mxc_spi_ss_sr_polarity_t ss_sr;
    mxc_spi_gen_ctrl_t gen;
    mxc_spi_spcl_ctrl_t spcl;
    uint16_t port;

    const uint8_t *tx_buf;
    uint32_t tx_index;
    uint32_t tx_size;
    void(*tx_handler)(int32_t ret_status);
    uint8_t *rx_buf;
    uint32_t rx_index;
    uint32_t rx_size;
    void(*rx_handler)(uint32_t rx_bytes);

    spi_header_t header;
    int16_t temp_tx_index;
    int16_t temp_rx_index;
    uint16_t temp_size;
    uint8_t last;
} spi_slave_t;


/**
 * @brief Initialize SPI slave handle.
 *
 * @param slave         Pointer to spi_slave_t
 * @param port          Port to configure (0, 1, etc...)
 *
 */
void SPI_Config(spi_slave_t *slave, uint8_t port);

/**
 * @brief Set up SPI clocks.
 *
 * @param slave         Pointer to spi_slave_t
 * @param clk_high      Number of system clock ticks that SPI clock will be high
 * @param clk_low       Number of system clock ticks that SPI clock will be low
 * @param alt_clk_high  Number of system clock ticks that SPI clock will be high
 * @param alt_clk_low   Number of system clock ticks that SPI clock will be low
 * @param polarity      Clock polarity
 * @param phase         Clock phase
 */
void SPI_ConfigClock(spi_slave_t *slave, uint8_t clk_high, uint8_t clk_low, uint8_t alt_clk_high, uint8_t alt_clk_low, uint8_t polarity, uint8_t phase);

/**
 * @brief Set up SPI slave select signals.
 *
 * @param slave         Pointer to spi_slave_t
 * @param slave_select  Slave select index
 * @param polarity      Polarity of slave select signal (0: active low; 1: active high)
 * @param act_delay     Delay between slave select assert and active SPI clock
 * @param inact_delay   Delay between active SPI clock and slave select deassert
 */
void SPI_ConfigSlaveSelect(spi_slave_t *slave, uint8_t slave_select, uint8_t polarity, uint8_t act_delay, uint8_t inact_delay);

typedef enum {
    MXC_E_SPI_PAGE_SIZE_4B = 0,
    MXC_E_SPI_PAGE_SIZE_8B,
    MXC_E_SPI_PAGE_SIZE_16B,
    MXC_E_SPI_PAGE_SIZE_32B,
} spi_page_size_t;

/**
 * @bried Set up SPI page size.
 *
 * @param slave         Pointer to spi_slave_t
 * @param unit          Page size
 */
void SPI_ConfigPageSize(spi_slave_t *slave, spi_page_size_t size);

typedef enum {
    MXC_E_SPI_FLOW_CTRL_NONE = 0,
    MXC_E_SPI_FLOW_CTRL_SR,
    MXC_E_SPI_FLOW_CTRL_MISO,
} spi_flow_ctrl_t;

/**
 * @brief Set up SPI special configuration
 *
 * @param slave             Pointer to spi_slave_t
 * @param flow_ctrl         Flow control mode
 * @param polarity          Flow control polarity (0: active low; 1: active high)
 * @param ss_sample_mode    When asserted SDIO is driven prior to slave select assertion
 * @param out_val           Output value for SDIO prior to slave select assertion
 * @param drv_mode          Select which SDIO is driven prior to slave select assertion (0: MOSI, 1: MISO)
 * @param three_wire        Enable 3 wire mode (MISO and MOSI tied together)
 */
void SPI_ConfigSpecial(spi_slave_t *slave, spi_flow_ctrl_t flow_ctrl, uint8_t polarity, uint8_t ss_sample_mode_en, uint8_t out_val, uint8_t drv_mode, uint8_t three_wire);

/**
 * @brief Get the current MISO status
 *
 * @param slave         Pointer to spi_slave_t
 *
 * @return current MISO status (0: active low; 1: active high)
 */
uint8_t SPI_WaitFlowControl(spi_slave_t *slave);

typedef enum {
    MXC_E_SPI_MODE_4_WIRE = 0,
    MXC_E_SPI_MODE_DUAL,
    MXC_E_SPI_MODE_QUAD
} spi_mode_t;

typedef enum {
    MXC_E_SPI_UNIT_BITS = 0,
    MXC_E_SPI_UNIT_BYTES,
    MXC_E_SPI_UNIT_PAGES
} spi_size_unit_t;

/**
 * @brief Read from and/or write to a SPI slave, return immediately,
 *        let the transmission be handled by the ISR and hardware FIFOs
 *
 * @param slave         Pointer to spi_slave_t
 * @param tx_buf        Pointer to the buffer containing data to send
 * @param tx_size       Size of the data to send
 * @param tx_handler    Callback function to be called when data is finished being written to FIFO
 * @param ret_status    Argument to the callback function for return status; 0 => success.
 * @param rx_buf        Pointer to the buffer of receiving data
 * @param rx_size       Size of the data to read
 * @param rx_handler    Callback function to be called when data is finished being read from FIFO
 * @param ret_size      Size of the data read
 * @param unit          Unit for the size parameters
 * @param mode          Mode for the SPI transaction
 * @param alt_clk       Use alternate clock if asserted
 * @param last          If asserted SPI port will be cleaned up and slave select deasserted
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t SPI_TransmitAsync(spi_slave_t *slave, \
                       const uint8_t *tx_buf, uint32_t tx_size, void(*tx_handler)(int32_t ret_status), \
                       uint8_t *rx_buf, uint32_t rx_size, void(*rx_handler)(uint32_t ret_size), \
                       spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last);

/**
 * @brief Read from and/or write to a SPI slave
 *
 * @param slave         Pointer to spi_slave_t
 * @param tx_buf        Pointer to the buffer containing data to send
 * @param tx_size       Size of the data to send (maximum is 32)
 * @param ret_status    Argument to the callback function for return status; 0 => success.
 * @param rx_buf        Pointer to the buffer of receiving data
 * @param rx_size       Size of the data to read (maximum is 32)
 * @param unit          Unit for the size parameters
 * @param mode          Mode for the SPI transaction
 * @param alt_clk       Use alternate clock if asserted
 * @param last          If asserted SPI port will be cleaned up and slave select deasserted
 *
 * @return 0 => Success. Non zero => error condition.
 */
int32_t SPI_Transmit(spi_slave_t *slave, \
                  const uint8_t *tx_buf, uint32_t tx_size, \
                  uint8_t *rx_buf, uint32_t rx_size, \
                  spi_size_unit_t unit, spi_mode_t mode, uint8_t alt_clk, uint8_t last);

/**
 * @}
 */

#endif /* _SPI_H */
