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

/* $Revision: 2883 $ $Date: 2014-08-04 14:27:19 -0500 (Mon, 04 Aug 2014) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>

#include "gpio.h"
#include "nvic_table.h"

void GPIO_SetOutMode(uint8_t port, uint8_t pin, gpio_out_mode_t val)
{
    uint32_t temp = MXC_GPIO->out_mode[port];

    temp = (temp & ~(0xF << (pin * 4))) | (val << (pin * 4));
    MXC_GPIO->out_mode[port] = temp;
}

void GPIO_SetOutVal(uint8_t port, uint8_t pin, uint32_t val)
{
    if(val) {
        BITBAND_SetBit((uint32_t)&MXC_GPIO->out_val[port], pin);
    } else {
        BITBAND_ClrBit((uint32_t)&MXC_GPIO->out_val[port], pin);
    }
}

void GPIO_SetFuncSel(uint8_t port, uint8_t pin, uint8_t val)
{
    uint32_t temp = MXC_GPIO->func_sel[port];

    temp = (temp & ~(0xF << (pin*4))) | ((uint32_t)val << (pin*4));
    MXC_GPIO->func_sel[port] = temp;
}

void GPIO_SetInMode(uint8_t port, uint8_t pin, gpio_in_mode_t val)
{
    uint32_t temp = MXC_GPIO->in_mode[port];

    temp = (temp & ~(0xF << (pin*4))) | (val << (pin*4));
    MXC_GPIO->in_mode[port] = temp;
}

uint32_t GPIO_GetInVal(uint8_t port, uint8_t pin)
{
    return ((uint32_t)BITBAND_GetBit((uint32_t)&MXC_GPIO->in_val[port], pin));
}

static void GPIO_IRQ_Handler(uint8_t port);
static inline void gpio_0_handler(void) { GPIO_IRQ_Handler(0); };
static inline void gpio_1_handler(void) { GPIO_IRQ_Handler(1); };
static inline void gpio_2_handler(void) { GPIO_IRQ_Handler(2); };
static inline void gpio_3_handler(void) { GPIO_IRQ_Handler(3); };
static inline void gpio_4_handler(void) { GPIO_IRQ_Handler(4); };
static inline void gpio_5_handler(void) { GPIO_IRQ_Handler(5); };
static inline void gpio_6_handler(void) { GPIO_IRQ_Handler(6); };
static inline void gpio_7_handler(void) { GPIO_IRQ_Handler(7); };
static void (*gpio_handler[8])(void) =  { &gpio_0_handler, &gpio_1_handler, &gpio_2_handler, &gpio_3_handler, \
                                          &gpio_4_handler, &gpio_5_handler, &gpio_6_handler, &gpio_7_handler, };

static void (*gpio_0_irq_array[8])(void) = {0};
static void (*gpio_1_irq_array[8])(void) = {0};
static void (*gpio_2_irq_array[8])(void) = {0};
static void (*gpio_3_irq_array[8])(void) = {0};
static void (*gpio_4_irq_array[8])(void) = {0};
static void (*gpio_5_irq_array[8])(void) = {0};
static void (*gpio_6_irq_array[8])(void) = {0};
static void (*gpio_7_irq_array[8])(void) = {0};
static void (**gpio_irq_array[8])(void)  = { gpio_0_irq_array, gpio_1_irq_array, gpio_2_irq_array, \
                                             gpio_3_irq_array, gpio_4_irq_array, gpio_5_irq_array, \
                                             gpio_6_irq_array, gpio_7_irq_array };

static void GPIO_IRQ_Handler(uint8_t port)
{
    uint32_t i, irqs = MXC_GPIO->intfl[port];

    /* clear all IRQ's, they will all be serviced */
    MXC_GPIO->intfl[port] = irqs;

    for(i=0; i<8; i++) /* make sure to serve all irqs */
    {
        if((irqs & (0x1 << i)) && gpio_irq_array[port][i]) {
            gpio_irq_array[port][i](); /* call corresponding fn here. */
        }
    }
}

static void FreeIRQ(uint8_t port, uint8_t pin)
{
    if(gpio_irq_array[port][pin]) { /* de-register gpio irq */
        gpio_irq_array[port][pin] = 0;
    }

    BITBAND_ClrBit((uint32_t)&MXC_GPIO->inten[port], pin); /* disable irq */
}

static int RegisterIRQ(uint8_t port, uint8_t pin, void (*gpio_irq_cb)(void))
{
    gpio_irq_array[port][pin] = gpio_irq_cb; /* register gpio_irq_handler */
    NVIC_SetVector(gpio_handler[port], (IRQn_Type)(GPIO_P0_IRQn + port)); /* register irq */

    return 0;
}

void GPIO_SetIntMode(uint8_t port, uint8_t pin, gpio_int_mode_t val, void(*gpio_irq_cb)(void))
{
    uint32_t temp = MXC_GPIO->int_mode[port];

    temp = (temp & ~(0xF << (pin*4))) | (val << (pin*4));
    MXC_GPIO->int_mode[port] = temp;

    if(!val) {
        FreeIRQ(port, pin); /* disable gpio irq */
    } else {
        /* only set ARM interrupt if callback is specified */
        if(gpio_irq_cb) {
            RegisterIRQ(port, pin, gpio_irq_cb);
        }
        
        BITBAND_SetBit((uint32_t)&MXC_GPIO->inten[port], pin);
    }
}
