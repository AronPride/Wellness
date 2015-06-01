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

/* $Revision: 2905 $ $Date: 2014-08-05 16:18:09 -0600 (Tue, 05 Aug 2014) $ */

#ifndef _IOMAN_H
#define _IOMAN_H

#include "ioman_regs.h"

/**
 * @file  ioman.h
 * @addtogroup ioman IO MUX
 * @{
 * @brief High level API to program the IO pin matrix manager
 *         of the MAX32600 family of ARM Cortex based embedded microcontrollers.
 */


/**
 * @brief Set the pin mapping of SPI0 module
 *
 * @param map       Select pinmapping for all enabled SPI pins
 * @param core_io   Request SPI mode for SCLK, SDIO(0) and SDIO(1)
 * @param ss0       Request slave select 0 active out
 * @param ss1       Request slave select 1 active out
 * @param ss2       Request slave select 2 active out
 * @param ss3       Request slave select 3 active out
 * @param ss4       Request slave select 4 active out
 * @param sr0       Request sr0 for flow control
 * @param sr1       Request sr1 for flow control
 * @param quad      Request quad IO
 * @param fast      Request fast mode
 *
 */
uint32_t IOMAN_SPI0(ioman_mapping_t map, uint8_t core_io, 
                    uint8_t ss0, uint8_t ss1, uint8_t ss2, uint8_t ss3, uint8_t ss4,
                    uint8_t sr0, uint8_t sr1,
                    uint8_t quad, uint8_t fast);

/**
 * @brief Set the pin mapping of SPI1 module
 *
 * @param map       Select pinmapping for all enabled SPI pins
 * @param core_io   Request SPI mode for SCLK, SDIO(0) and SDIO(1)
 * @param ss0       Request slave select 0 active out
 * @param ss1       Request slave select 1 active out
 * @param ss2       Request slave select 2 active out
 * @param ss3       Request slave select 3 active out
 * @param ss4       Request slave select 4 active out
 * @param sr0       Request sr0 for flow control
 * @param sr1       Request sr1 for flow control
 * @param quad      Request quad IO
 * @param fast      Request fast mode
 *
 */
uint32_t IOMAN_SPI1(ioman_mapping_t map, uint8_t core_io, 
                    uint8_t ss0, uint8_t ss1, uint8_t ss2, uint8_t ss3, uint8_t ss4,
                    uint8_t sr0, uint8_t sr1,
                    uint8_t quad, uint8_t fast);

/**
 * @brief Set the pin mapping of SPI2 module
 *
 * @param map       Select pinmapping for all enabled SPI pins
 * @param core_io   Request SPI mode for SCLK, SDIO(0) and SDIO(1)
 * @param ss0       Request slave select 0 active out
 * @param ss1       Request slave select 1 active out
 * @param ss2       Request slave select 2 active out
 * @param ss3       Request slave select 3 active out
 * @param ss4       Request slave select 4 active out
 * @param sr0       Request sr0 for flow control
 * @param sr1       Request sr1 for flow control
 * @param quad      Request quad IO
 * @param fast      Request fast mode
 *
 */
uint32_t IOMAN_SPI2(ioman_mapping_t map, uint8_t core_io, 
                    uint8_t ss0, uint8_t ss1, uint8_t ss2, uint8_t ss3, uint8_t ss4,
                    uint8_t sr0, uint8_t sr1,
                    uint8_t quad, uint8_t fast);

/**
 * @brief Set the pin mapping of the UART0 module
 *
 * @param map        Set the pin mapping for all configured UART pins
 * @param tr         Request TX and RX pins
 * @param cts        Request CTS pin
 * @param rts        Request RTS pin
 *
 */
uint32_t IOMAN_UART0(ioman_mapping_t map, uint8_t tr, uint8_t cts, uint8_t rts);

/**
 * @brief Set the pin mapping of the UART1 module
 *
 * @param map        Set the pin mapping for all configured UART pins
 * @param tr         Request TX and RX pins
 * @param cts        Request CTS pin
 * @param rts        Request RTS pin
 *
 */
uint32_t IOMAN_UART1(ioman_mapping_t map, uint8_t tr, uint8_t cts, uint8_t rts);

/**
 * @brief Set the pin mapping for I2C master 0 module
 * 
 * @param map        Set the pin mapping for all configured I2CM pins
 * @param mstr_io    Request master mode for SCK and SDA pins.
 *
 */
uint32_t IOMAN_I2CM0(ioman_mapping_t map, uint8_t mstr_io);

/**
 * @brief Set the pin mapping for I2C master 1 module
 * 
 * @param map        Set the pin mapping for all configured I2CM pins
 * @param mstr_io    Request master mode for SCK and SDA pins.
 *
 */
uint32_t IOMAN_I2CM1(ioman_mapping_t map, uint8_t mstr_io);

/**
 * @brief Set the pin mapping for I2C slave module
 *
 * @param map        Set the pin mapping for all configured I2C slave pins
 * @param slave_io   Request slave mode for SCK and SDA pins.
 *
 */
uint32_t IOMAN_I2CS0(ioman_mapping_t map, uint8_t slave_io);

/**
 * @brief Set the pin mapping for current drive module
 *
 * @param p0    Request pin pair for current drive port 0
 * @param p1    Request pin pair for current drive port 1
 * @param p2    Request pin pair for current drive port 2
 * @param p3    Request pin pair for current drive port 3
 * @param p4    Request pin pair for current drive port 4
 * @param p5    Request pin pair for current drive port 5 
 * @param p6    Request pin pair for current drive port 6
 * @param p7    Request pin pair for current drive port 7
 *
 */
uint32_t IOMAN_CRNT(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, 
                    uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7);
/**
 * @brief Set the mode value for selected port(s) pin(s) in the current drive module
 *
 * @param p0    Set current mode for pin selected in port 0
 * @param p1    Set current mode for pin selected in port 1
 * @param p2    Set current mode for pin selected in port 2
 * @param p3    Set current mode for pin selected in port 3
 * @param p4    Set current mode for pin selected in port 4
 * @param p5    Set current mode for pin selected in port 5
 * @param p6    Set current mode for pin selected in port 6
 * @param p7    Set current mode for pin selected in port 7
 *
 */
uint32_t IOMAN_CRNTMode(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, 
                        uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7);

/**
 * @brief Set the pin mapping of the LCD module
 *
 * @param s0    Set LCD SEG mode for GPIO[55:24]
 * @param s1    Set LCD SEG mode for GPIO[63:56]
 *
 */
uint32_t IOMAN_LCD(uint32_t m, uint32_t s0, uint32_t s1);

/**
 * @}
 */


/* All the function prototyps above are implimented as macros below. 
 * This allows these simple functions to become one direct register write,
 * and the above protos are for simplicity in doxygen.
 */
#define IOMAN_SPI0(m, c, ss0, ss1, ss2, ss3, ss4, sr0, sr1, q, f)   \
    MXC_IOMAN->spi0_req_f = (mxc_ioman_spi0_req_t) {                \
        .mapping_sel = m,                                           \
        .core_io_req = c,                                           \
        .ss0_io_req = ss0,                                          \
        .ss1_io_req = ss1,                                          \
        .ss2_io_req = ss2,                                          \
        .ss3_io_req = ss3,                                          \
        .ss4_io_req = ss4,                                          \
        .sr0_io_req = sr0,                                          \
        .sr1_io_req = sr1,                                          \
        .quad_io_req = q,                                           \
        .fast_mode = f };

#define IOMAN_SPI1(m, c, ss0, ss1, ss2, ss3, ss4, sr0, sr1, q, f)   \
    MXC_IOMAN->spi1_req_f = (mxc_ioman_spi1_req_t) {                \
        .mapping_sel = m,                                           \
        .core_io_req = c,                                           \
        .ss0_io_req = ss0,                                          \
        .ss1_io_req = ss1,                                          \
        .ss2_io_req = ss2,                                          \
        .ss3_io_req = ss3,                                          \
        .ss4_io_req = ss4,                                          \
        .sr0_io_req = sr0,                                          \
        .sr1_io_req = sr1,                                          \
        .quad_io_req = q,                                           \
        .fast_mode = f };

#define IOMAN_SPI2(m, c, ss0, ss1, ss2, ss3, ss4, sr0, sr1, q, f)   \
    MXC_IOMAN->spi2_req_f = (mxc_ioman_spi2_req_t) {                \
        .mapping_sel = m,                                           \
        .core_io_req = c,                                           \
        .ss0_io_req = ss0,                                          \
        .ss1_io_req = ss1,                                          \
        .ss2_io_req = ss2,                                          \
        .ss3_io_req = ss3,                                          \
        .ss4_io_req = ss4,                                          \
        .sr0_io_req = sr0,                                          \
        .sr1_io_req = sr1,                                          \
        .quad_io_req = q,                                           \
        .fast_mode = f };

#define IOMAN_UART0(m, t, c, r)                        \
    MXC_IOMAN->uart0_req_f =  (mxc_ioman_uart0_req_t){ \
        .mapping_sel = m,                              \
        .tr_io_req = t,                                \
        .cts_io_req = c,                               \
        .rts_io_req = r };

#define IOMAN_UART1(m, t, c, r)                        \
    MXC_IOMAN->uart1_req_f =  (mxc_ioman_uart1_req_t){ \
        .mapping_sel = m,                              \
        .tr_io_req = t,                                \
        .cts_io_req = c,                               \
        .rts_io_req = r };

#define IOMAN_I2CM0(m, io) \
    MXC_IOMAN->i2cm0_req_f = (mxc_ioman_i2cm0_req_t) { \
        .mapping_sel = m,                              \
        .mstr_io_req = io };

#define IOMAN_I2CM1(m, io) \
    MXC_IOMAN->i2cm1_req_f = (mxc_ioman_i2cm1_req_t) { \
        .mapping_sel = m,                              \
        .mstr_io_req = io };

#define IOMAN_I2CS0(m, io) \
    MXC_IOMAN->i2cs0_req_f = (mxc_ioman_i2cs0_req_t) { \
        .mapping_sel = m,                              \
        .slave_io_req = io };

#define IOMAN_CRNT(p0, p1, p2, p3, p4, p5, p6, p7) \
    MXC_IOMAN->crnt_req_f = (mxc_ioman_crnt_req_t) { \
        .io_req_crnt0 = p0,                          \
        .io_req_crnt1 = p1,                          \
        .io_req_crnt2 = p2,                          \
        .io_req_crnt3 = p3,                          \
        .io_req_crnt4 = p4,                          \
        .io_req_crnt5 = p5,                          \
        .io_req_crnt6 = p6,                          \
        .io_req_crnt7 = p7, };

#define IOMAN_CRNTMode(p0, p1, p2, p3, p4, p5, p6, p7)  \
    MXC_IOMAN->crnt_mode_f = (mxc_ioman_crnt_mode_t) {  \
        .io_crnt0 = p0,                                 \
        .io_crnt1 = p1,                                 \
        .io_crnt2 = p2,                                 \
        .io_crnt3 = p3,                                 \
        .io_crnt4 = p4,                                 \
        .io_crnt5 = p5,                                 \
        .io_crnt6 = p6,                                 \
        .io_crnt7 = p7, };

#define IOMAN_LCD(m, s0, s1)                    \
    (MXC_IOMAN->lcd_com_req = m) |              \
    (MXC_IOMAN->lcd_seg_req0 = s0) |            \
    (MXC_IOMAN->lcd_seg_req1 = s1)



#endif /* _IOMAN_H */
