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

/* $Revision: 3545 $ $Date: 2014-11-11 18:20:37 -0600 (Tue, 11 Nov 2014) $ */

#ifndef _MXC_IOMAN_REGS_H_
#define _MXC_IOMAN_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif

/**
 * @file  ioman_regs.h
 * @addtogroup ioman IO MUX Manager
 * @{
 */

/**
 * @brief Pin mapping define values common to all modules
 */
typedef enum {
    /** Pin Mapping 'A' */
    MXC_E_IOMAN_MAPPING_A = 0,
    /** Pin Mapping 'B' */
    MXC_E_IOMAN_MAPPING_B,
    /** Pin Mapping 'C' */
    MXC_E_IOMAN_MAPPING_C,
    /** Pin Mapping 'D' */
    MXC_E_IOMAN_MAPPING_D,
    /** Pin Mapping 'E' */
    MXC_E_IOMAN_MAPPING_E,
    /** Pin Mapping 'F' */
    MXC_E_IOMAN_MAPPING_F,
    /** Pin Mapping 'G' */
    MXC_E_IOMAN_MAPPING_G,
    /** Pin Mapping 'H' */
    MXC_E_IOMAN_MAPPING_H,
} ioman_mapping_t;

/*
    Bitfield structs for registers in this module
*/


/*  Do not use the ioman_mapping_t typedef for the various
 *  'mapping_sel' and 'mapping_ack' below because they don't all
 *  conform to the size of the typedef.  The type checking for typedef
 *  should be handled at the API layer, not this reigster level.  This
 *  is a special case in the IOMAN definitions.
 * 
 */

typedef struct
{
    uint32_t wud_req_p0        : 8;
    uint32_t wud_req_p1        : 8;
    uint32_t wud_req_p2        : 8;
    uint32_t wud_req_p3        : 8;
} mxc_ioman_wud_req0_t;

typedef struct
{
    uint32_t wud_req_p4        : 8;
    uint32_t wud_req_p5        : 8;
    uint32_t wud_req_p6        : 8;
    uint32_t wud_req_p7        : 8;
} mxc_ioman_wud_req1_t;

typedef struct
{
    uint32_t wud_ack_p0        : 8;
    uint32_t wud_ack_p1        : 8;
    uint32_t wud_ack_p2        : 8;
    uint32_t wud_ack_p3        : 8;
} mxc_ioman_wud_ack0_t;

typedef struct
{
    uint32_t wud_ack_p4        : 8;
    uint32_t wud_ack_p5        : 8;
    uint32_t wud_ack_p6        : 8;
    uint32_t wud_ack_p7        : 8;
} mxc_ioman_wud_ack1_t;

typedef struct
{
    uint32_t ali_req_p0        : 8;
    uint32_t ali_req_p1        : 8;
    uint32_t ali_req_p2        : 8;
    uint32_t ali_req_p3        : 8;
} mxc_ioman_ali_req0_t;

typedef struct
{
    uint32_t ali_req_p4        : 8;
    uint32_t ali_req_p5        : 8;
    uint32_t ali_req_p6        : 8;
    uint32_t ali_req_p7        : 8;
} mxc_ioman_ali_req1_t;

typedef struct
{
    uint32_t ali_ack_p0        : 8;
    uint32_t ali_ack_p1        : 8;
    uint32_t ali_ack_p2        : 8;
    uint32_t ali_ack_p3        : 8;
} mxc_ioman_ali_ack0_t;

typedef struct
{
    uint32_t ali_ack_p4        : 8;
    uint32_t ali_ack_p5        : 8;
    uint32_t ali_ack_p6        : 8;
    uint32_t ali_ack_p7        : 8;
} mxc_ioman_ali_ack1_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t core_io_req       : 1;
    uint32_t                   : 3;

    uint32_t ss0_io_req        : 1;
    uint32_t ss1_io_req        : 1;
    uint32_t ss2_io_req        : 1;
    uint32_t ss3_io_req        : 1;
    uint32_t ss4_io_req        : 1;
    uint32_t                   : 3;

    uint32_t sr0_io_req        : 1;
    uint32_t sr1_io_req        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_req       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi0_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t core_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t ss0_io_ack        : 1;
    uint32_t ss1_io_ack        : 1;
    uint32_t ss2_io_ack        : 1;
    uint32_t ss3_io_ack        : 1;
    uint32_t ss4_io_ack        : 1;
    uint32_t                   : 3;
    uint32_t sr0_io_ack        : 1;
    uint32_t sr1_io_ack        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi0_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t core_io_req       : 1;
    uint32_t                   : 3;
    uint32_t ss0_io_req        : 1;
    uint32_t ss1_io_req        : 1;
    uint32_t ss2_io_req        : 1;
    uint32_t ss3_io_req        : 1;
    uint32_t ss4_io_req        : 1;
    uint32_t                   : 3;
    uint32_t sr0_io_req        : 1;
    uint32_t sr1_io_req        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_req       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi1_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t core_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t ss0_io_ack        : 1;
    uint32_t ss1_io_ack        : 1;
    uint32_t ss2_io_ack        : 1;
    uint32_t ss3_io_ack        : 1;
    uint32_t ss4_io_ack        : 1;
    uint32_t                   : 3;
    uint32_t sr0_io_ack        : 1;
    uint32_t sr1_io_ack        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi1_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t core_io_req       : 1;
    uint32_t                   : 3;
    uint32_t ss0_io_req        : 1;
    uint32_t ss1_io_req        : 1;
    uint32_t ss2_io_req        : 1;
    uint32_t ss3_io_req        : 1;
    uint32_t ss4_io_req        : 1;
    uint32_t                   : 3;
    uint32_t sr0_io_req        : 1;
    uint32_t sr1_io_req        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_req       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi2_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t core_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t ss0_io_ack        : 1;
    uint32_t ss1_io_ack        : 1;
    uint32_t ss2_io_ack        : 1;
    uint32_t ss3_io_ack        : 1;
    uint32_t ss4_io_ack        : 1;
    uint32_t                   : 3;
    uint32_t sr0_io_ack        : 1;
    uint32_t sr1_io_ack        : 1;
    uint32_t                   : 2;
    uint32_t quad_io_ack       : 1;
    uint32_t                   : 3;
    uint32_t fast_mode         : 1;
    uint32_t                   : 7;
} mxc_ioman_spi2_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t tr_io_req         : 1;
    uint32_t cts_io_req        : 1;
    uint32_t rts_io_req        : 1;
    uint32_t                   : 25;
} mxc_ioman_uart0_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t tr_io_ack         : 1;
    uint32_t cts_io_ack        : 1;
    uint32_t rts_io_ack        : 1;
    uint32_t                   : 25;
} mxc_ioman_uart0_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t tr_io_req         : 1;
    uint32_t cts_io_req        : 1;
    uint32_t rts_io_req        : 1;
    uint32_t                   : 25;
} mxc_ioman_uart1_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t tr_io_ack         : 1;
    uint32_t cts_io_ack        : 1;
    uint32_t rts_io_ack        : 1;
    uint32_t                   : 25;
} mxc_ioman_uart1_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t mstr_io_req       : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cm0_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t mstr_io_req       : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cm0_ack_t;

typedef struct
{
    uint32_t mapping_sel       : 3;
    uint32_t                   : 1;
    uint32_t slave_io_req      : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cs0_req_t;

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t slave_io_req      : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cs0_ack_t;

typedef struct
{
    uint32_t io_lcd_com_req    : 1;
    uint32_t                   : 31;
} mxc_ioman_lcd_com_req_t;

typedef struct
{
    uint32_t io_lcd_com_ack    : 1;
    uint32_t                   : 31;
} mxc_ioman_lcd_com_ack_t;

typedef struct
{
    uint32_t io_req_24         : 1;
    uint32_t io_req_25         : 1;
    uint32_t io_req_26         : 1;
    uint32_t io_req_27         : 1;
    uint32_t io_req_28         : 1;
    uint32_t io_req_29         : 1;
    uint32_t io_req_30         : 1;
    uint32_t io_req_31         : 1;
    uint32_t io_req_32         : 1;
    uint32_t io_req_33         : 1;
    uint32_t io_req_34         : 1;
    uint32_t io_req_35         : 1;
    uint32_t io_req_36         : 1;
    uint32_t io_req_37         : 1;
    uint32_t io_req_38         : 1;
    uint32_t io_req_39         : 1;
    uint32_t io_req_40         : 1;
    uint32_t io_req_41         : 1;
    uint32_t io_req_42         : 1;
    uint32_t io_req_43         : 1;
    uint32_t io_req_44         : 1;
    uint32_t io_req_45         : 1;
    uint32_t io_req_46         : 1;
    uint32_t io_req_47         : 1;
    uint32_t io_req_48         : 1;
    uint32_t io_req_49         : 1;
    uint32_t io_req_50         : 1;
    uint32_t io_req_51         : 1;
    uint32_t io_req_52         : 1;
    uint32_t io_req_53         : 1;
    uint32_t io_req_54         : 1;
    uint32_t io_req_55         : 1;
} mxc_ioman_lcd_seg_req0_t;

typedef struct
{
    uint32_t io_req_56         : 1;
    uint32_t io_req_57         : 1;
    uint32_t io_req_58         : 1;
    uint32_t io_req_59         : 1;
    uint32_t io_req_60         : 1;
    uint32_t io_req_61         : 1;
    uint32_t io_req_62         : 1;
    uint32_t io_req_63         : 1;
    uint32_t                   :24;
} mxc_ioman_lcd_seg_req1_t;

typedef struct
{
    uint32_t io_ack_24         : 1;
    uint32_t io_ack_25         : 1;
    uint32_t io_ack_26         : 1;
    uint32_t io_ack_27         : 1;
    uint32_t io_ack_28         : 1;
    uint32_t io_ack_29         : 1;
    uint32_t io_ack_30         : 1;
    uint32_t io_ack_31         : 1;
    uint32_t io_ack_32         : 1;
    uint32_t io_ack_33         : 1;
    uint32_t io_ack_34         : 1;
    uint32_t io_ack_35         : 1;
    uint32_t io_ack_36         : 1;
    uint32_t io_ack_37         : 1;
    uint32_t io_ack_38         : 1;
    uint32_t io_ack_39         : 1;
    uint32_t io_ack_40         : 1;
    uint32_t io_ack_41         : 1;
    uint32_t io_ack_42         : 1;
    uint32_t io_ack_43         : 1;
    uint32_t io_ack_44         : 1;
    uint32_t io_ack_45         : 1;
    uint32_t io_ack_46         : 1;
    uint32_t io_ack_47         : 1;
    uint32_t io_ack_48         : 1;
    uint32_t io_ack_49         : 1;
    uint32_t io_ack_50         : 1;
    uint32_t io_ack_51         : 1;
    uint32_t io_ack_52         : 1;
    uint32_t io_ack_53         : 1;
    uint32_t io_ack_54         : 1;
    uint32_t io_ack_55         : 1;
} mxc_ioman_lcd_seg_ack0_t;

typedef struct
{
    uint32_t io_ack_56         : 1;
    uint32_t io_ack_57         : 1;
    uint32_t io_ack_58         : 1;
    uint32_t io_ack_59         : 1;
    uint32_t io_ack_60         : 1;
    uint32_t io_ack_61         : 1;
    uint32_t io_ack_62         : 1;
    uint32_t io_ack_63         : 1;
    uint32_t                   :24;
} mxc_ioman_lcd_seg_ack1_t;

typedef struct
{
    uint32_t io_req_crnt0      : 1;
    uint32_t io_req_crnt1      : 1;
    uint32_t io_req_crnt2      : 1;
    uint32_t io_req_crnt3      : 1;
    uint32_t io_req_crnt4      : 1;
    uint32_t io_req_crnt5      : 1;
    uint32_t io_req_crnt6      : 1;
    uint32_t io_req_crnt7      : 1;
    uint32_t                   : 24;
} mxc_ioman_crnt_req_t;

typedef struct
{
    uint32_t io_ack_crnt0      : 1;
    uint32_t io_ack_crnt1      : 1;
    uint32_t io_ack_crnt2      : 1;
    uint32_t io_ack_crnt3      : 1;
    uint32_t io_ack_crnt4      : 1;
    uint32_t io_ack_crnt5      : 1;
    uint32_t io_ack_crnt6      : 1;
    uint32_t io_ack_crnt7      : 1;
    uint32_t                   : 24;
} mxc_ioman_crnt_ack_t;

typedef struct
{
    uint32_t io_crnt0          : 4;
    uint32_t io_crnt1          : 4;
    uint32_t io_crnt2          : 4;
    uint32_t io_crnt3          : 4;
    uint32_t io_crnt4          : 4;
    uint32_t io_crnt5          : 4;
    uint32_t io_crnt6          : 4;
    uint32_t io_crnt7          : 4;
} mxc_ioman_crnt_mode_t; 

typedef struct
{
    uint32_t mapping_sel       : 2;
    uint32_t                   : 2;
    uint32_t mstr_io_req       : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cm1_req_t; 

typedef struct
{
    uint32_t mapping_ack       : 2;
    uint32_t                   : 2;
    uint32_t mstr_io_req       : 1;
    uint32_t                   : 27;
} mxc_ioman_i2cm1_ack_t;  


typedef struct
{
    uint32_t padx_power_control     : 1;
    uint32_t                        : 3;
    uint32_t padx_gpio0_out_mode    : 2;
    uint32_t padx_gpio0_input_state : 1;
    uint32_t                        : 1;
    uint32_t padx_gpio1_out_mode    : 2;
    uint32_t padx_gpio1_input_state : 1;
    uint32_t                        : 21;
} mxc_ioman_padx_control_t; 



/*
   Typedefed structure(s) for module registers (per instance or section) with direct 32-bit
   register access along with union access to bit/bitfield struct (where defined).
*/

/*                                                          Offset   Register Description
                                                            ======   ========================================== */
typedef struct {
    union {
        __IO uint32_t wud_req0;                         /*  0x0000   Wakeup Detect Mode Request Register 0      */
        __IO mxc_ioman_wud_req0_t wud_req0_f;
    };
    union {
        __IO uint32_t wud_req1;                         /*  0x0004   Wakeup Detect Mode Request Register 1      */
        __IO mxc_ioman_wud_req1_t wud_req1_f;
    };
    union {
        __IO uint32_t wud_ack0;                         /*  0x0008   Wakeup Detect Mode Acknowledge Register 0  */
        __IO mxc_ioman_wud_ack0_t wud_ack0_f;
    };
    union {
        __IO uint32_t wud_ack1;                         /*  0x000C   Wakeup Detect Mode Acknowledge Register 1  */
        __IO mxc_ioman_wud_ack1_t wud_ack1_f;
    };
    union {
        __IO uint32_t ali_req0;                         /*  0x0010   Analog Input Request Register 0            */
        __IO mxc_ioman_ali_req0_t ali_req0_f;
    };
    union {
        __IO uint32_t ali_req1;                         /*  0x0014   Analog Input Request Register 1            */
        __IO mxc_ioman_ali_req1_t ali_req1_f;
    };
    union {
        __IO uint32_t ali_ack0;                         /*  0x0018   Analog Input Acknowledge Register 0        */
        __IO mxc_ioman_ali_ack0_t ali_ack0_f;
    };
    union {
        __IO uint32_t ali_ack1;                         /*  0x001C   Analog Input Acknowledge Register 1        */
        __IO mxc_ioman_ali_ack1_t ali_ack1_f;
    };
    union {
        __IO uint32_t spi0_req;                         /*  0x0020   SPI0 I/O Mode Request                      */
        __IO mxc_ioman_spi0_req_t spi0_req_f;
    };
    union {
        __IO uint32_t spi0_ack;                         /*  0x0024   SPI0 I/O Mode Acknowledge                  */
        __IO mxc_ioman_spi0_ack_t spi0_ack_f;
    };
    union {
        __IO uint32_t spi1_req;                         /*  0x0028   SPI1 I/O Mode Request                      */
        __IO mxc_ioman_spi1_req_t spi1_req_f;
    };
    union {
        __IO uint32_t spi1_ack;                         /*  0x002C   SPI1 I/O Mode Acknowledge                  */
        __IO mxc_ioman_spi1_ack_t spi1_ack_f;
    };
    union {
        __IO uint32_t spi2_req;                         /*  0x0030   SPI2 I/O Mode Request                      */
        __IO mxc_ioman_spi2_req_t spi2_req_f;
    };
    union {
        __IO uint32_t spi2_ack;                         /*  0x0034   SPI2 I/O Mode Acknowledge                  */
        __IO mxc_ioman_spi2_ack_t spi2_ack_f;
    };
    union {
        __IO uint32_t uart0_req;                        /*  0x0038   UART0 I/O Mode Request                     */
        __IO mxc_ioman_uart0_req_t uart0_req_f;
    };
    union {
        __IO uint32_t uart0_ack;                        /*  0x003C   UART0 I/O Mode Acknowledge                 */
        __IO mxc_ioman_uart0_ack_t uart0_ack_f;
    };
    union {
        __IO uint32_t uart1_req;                        /*  0x0040   UART1 I/O Mode Request                     */
        __IO mxc_ioman_uart1_req_t uart1_req_f;
    };
    union {
        __IO uint32_t uart1_ack;                        /*  0x0044   UART1 I/O Mode Acknowledge                 */
        __IO mxc_ioman_uart1_ack_t uart1_ack_f;
    };
    union {
        __IO uint32_t i2cm0_req;                        /*  0x0048   I2C Master 0 I/O Request                   */
        __IO mxc_ioman_i2cm0_req_t i2cm0_req_f;
    };
    union {
        __IO uint32_t i2cm0_ack;                        /*  0x004C   I2C Master 0 I/O Acknowledge               */
        __IO mxc_ioman_i2cm0_ack_t i2cm0_ack_f;
    };
    union {
        __IO uint32_t i2cs0_req;                        /*  0x0050   I2C Slave 0 I/O Request                    */
        __IO mxc_ioman_i2cs0_req_t i2cs0_req_f;
    };
    union {
        __IO uint32_t i2s0_ack;                         /*  0x0054   I2C Slave 0 I/O Acknowledge                 */
        __IO mxc_ioman_i2cs0_ack_t i2cs0_ack_f;
    };
    union {
        __IO uint32_t lcd_com_req;                      /*  0x0058   LCD COM Driver I/O Request                 */
        __IO mxc_ioman_lcd_com_req_t lcd_com_req_f;
    };
    union {
        __IO uint32_t lcd_com_ack;                      /*  0x005C   LCD COM Driver I/O Acknowledge             */
        __IO mxc_ioman_lcd_com_ack_t lcd_com_ack_f;
    };
    union {
        __IO uint32_t lcd_seg_req0;                     /*  0x0060   LCD SEG Driver I/O Request Register 0      */
        __IO mxc_ioman_lcd_seg_req0_t lcd_seg_req0_f;
    };
    union {
        __IO uint32_t lcd_seg_req1;                     /*  0x0064   LCD SEG Driver I/O Request Register 1      */
        __IO mxc_ioman_lcd_seg_req1_t lcd_seg_req1_f;
    };
    union {
        __IO uint32_t lcd_seg_ack0;                     /*  0x0068   LCD SEG Driver I/O Acknowledge Register 0  */
        __IO mxc_ioman_lcd_seg_ack0_t lcd_seg_ack0_f;
    };
    union {
        __IO uint32_t lcd_seg_ack1;                     /*  0x006C   LCD SEG Driver I/O Acknowledge Register 1  */
        __IO mxc_ioman_lcd_seg_ack1_t lcd_seg_ack1_f;
    };
    union {
        __IO uint32_t crnt_req;                         /*  0x0070   Current Drive I/O Request Register         */
        __IO mxc_ioman_crnt_req_t crnt_req_f;
    };
    union {
        __IO uint32_t io_crnt_ack;                      /*  0x0074   Current Drive I/O Acknowledge Register     */
        __IO mxc_ioman_crnt_ack_t crnt_ack_f;
    };
    union {
        __IO uint32_t crnt_mode;                        /*  0x0078   Current Drive I/O Mode Control             */
        __IO mxc_ioman_crnt_mode_t crnt_mode_f;
    };
    __IO uint32_t ali_connect0;                         /*  0x007C   Analog I/O Connection Control Register 0   */
    __IO uint32_t ali_connect1;                         /*  0x0080   Analog I/O Connection Control Register 1   */
    union {
        __IO uint32_t i2cm1_req;                        /*  0x0084   I2C Master 1 I/O Request                   */
        __IO mxc_ioman_i2cm1_req_t i2cm1_req_f;
    };
    union {
        __IO uint32_t i2cm1_ack;                        /*  0x0088   I2C Master 1 I/O Acknowledge               */
        __IO mxc_ioman_i2cm1_ack_t i2cm1_ack_f;
    };
} mxc_ioman_regs_t;


/*
   Register offsets for module IOMAN.
*/

#define MXC_R_IOMAN_OFFS_WUD_REQ0                 ((uint32_t)0x00000000UL)
#define MXC_R_IOMAN_OFFS_WUD_REQ1                 ((uint32_t)0x00000004UL)
#define MXC_R_IOMAN_OFFS_WUD_ACK0                 ((uint32_t)0x00000008UL)
#define MXC_R_IOMAN_OFFS_WUD_ACK1                 ((uint32_t)0x0000000CUL)
#define MXC_R_IOMAN_OFFS_ALI_REQ0                 ((uint32_t)0x00000010UL)
#define MXC_R_IOMAN_OFFS_ALI_REQ1                 ((uint32_t)0x00000014UL)
#define MXC_R_IOMAN_OFFS_ALI_ACK0                 ((uint32_t)0x00000018UL)
#define MXC_R_IOMAN_OFFS_ALI_ACK1                 ((uint32_t)0x0000001CUL)
#define MXC_R_IOMAN_OFFS_SPI0_REQ                 ((uint32_t)0x00000020UL)
#define MXC_R_IOMAN_OFFS_SPI0_ACK                 ((uint32_t)0x00000024UL)
#define MXC_R_IOMAN_OFFS_SPI1_REQ                 ((uint32_t)0x00000028UL)
#define MXC_R_IOMAN_OFFS_SPI1_ACK                 ((uint32_t)0x0000002CUL)
#define MXC_R_IOMAN_OFFS_SPI2_REQ                 ((uint32_t)0x00000030UL)
#define MXC_R_IOMAN_OFFS_SPI2_ACK                 ((uint32_t)0x00000034UL)
#define MXC_R_IOMAN_OFFS_UART0_REQ                ((uint32_t)0x00000038UL)
#define MXC_R_IOMAN_OFFS_UART0_ACK                ((uint32_t)0x0000003CUL)
#define MXC_R_IOMAN_OFFS_UART1_REQ                ((uint32_t)0x00000040UL)
#define MXC_R_IOMAN_OFFS_UART1_ACK                ((uint32_t)0x00000044UL)
#define MXC_R_IOMAN_OFFS_I2CM0_REQ                ((uint32_t)0x00000048UL)
#define MXC_R_IOMAN_OFFS_I2CM0_ACK                ((uint32_t)0x0000004CUL)
#define MXC_R_IOMAN_OFFS_I2CS0_REQ                ((uint32_t)0x00000050UL)
#define MXC_R_IOMAN_OFFS_I2SC0_ACK                ((uint32_t)0x00000054UL)
#define MXC_R_IOMAN_OFFS_LCD_COM_REQ              ((uint32_t)0x00000058UL)
#define MXC_R_IOMAN_OFFS_LCD_COM_ACK              ((uint32_t)0x0000005CUL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_REQ0             ((uint32_t)0x00000060UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_REQ1             ((uint32_t)0x00000064UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_ACK0             ((uint32_t)0x00000068UL)
#define MXC_R_IOMAN_OFFS_LCD_SEG_ACK1             ((uint32_t)0x0000006CUL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_REQ              ((uint32_t)0x00000070UL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_ACK              ((uint32_t)0x00000074UL)
#define MXC_R_IOMAN_OFFS_IO_CRNT_MODE             ((uint32_t)0x00000078UL)
#define MXC_R_IOMAN_OFFS_ALI_CONNECT0             ((uint32_t)0x0000007CUL)
#define MXC_R_IOMAN_OFFS_ALI_CONNECT1             ((uint32_t)0x00000080UL)
#define MXC_R_IOMAN_OFFS_I2CM1_REQ                ((uint32_t)0x00000084UL)
#define MXC_R_IOMAN_OFFS_I2CM1_ACK                ((uint32_t)0x00000088UL)


#ifdef __cplusplus
}
#endif

#endif   /* _MXC_IOMAN_REGS_H_ */

