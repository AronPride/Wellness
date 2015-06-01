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

/* $Revision: 3277 $ $Date: 2014-10-02 13:39:01 -0500 (Thu, 02 Oct 2014) $ */

#include "mxc_config.h"

#include <stdint.h>
#include <string.h>

#include "flc.h"
#include "icc_regs.h"


int32_t FLC_Erase(uint32_t address, uint8_t erase_code, uint8_t unlock_key)
{
    if(!MXC_ICC->ctrl_stat_f.enable) {
        return -1;
    }

    mxc_flc_ctrl_t fcntl = MXC_FLC->ctrl_f;
    fcntl.erase_code = 0; /* clear erase code */
    fcntl.auto_incre_mode = 0; /* clear burst */
    MXC_FLC->ctrl_f = fcntl;

    fcntl.flsh_unlock = unlock_key;
    fcntl.erase_code = erase_code;
    MXC_FLC->ctrl_f = fcntl;

    MXC_FLC->faddr = (address & MXC_FLC_PAGE_ERASE_MSK); /* set bank address */

    fcntl = MXC_FLC->ctrl_f;
    fcntl.page_erase = 1; /* set and start erase operation */
    MXC_FLC->ctrl_f = fcntl;
    
    do {
        fcntl = MXC_FLC->ctrl_f;
    } while (fcntl.pending); /* wait until done */
    
    fcntl = MXC_FLC->ctrl_f;
    fcntl.erase_code = 0; /* lock flash */
    fcntl.flsh_unlock = 0;
    MXC_FLC->ctrl_f = fcntl;

    return 0;
}

int32_t FLC_WriteBlock(uint32_t address, const void *data, uint32_t length, uint8_t unlock_key)
{
    uint32_t *word = (uint32_t *) data;

    if(!MXC_ICC->ctrl_stat_f.enable) {
        return -1;
    }

    if(address & 3) { /* address needs to be aligned with word */
        return -1;
    }

    length = length & 0xfffffffc;

    mxc_flc_ctrl_t fcntl = MXC_FLC->ctrl_f;
    fcntl.erase_code = 0; /* clear erase code */
    fcntl.auto_incre_mode = 0; /* clear burst */
    MXC_FLC->ctrl_f = fcntl;

    fcntl.flsh_unlock = unlock_key; /* set unlock */
    MXC_FLC->ctrl_f = fcntl;

    while (length)
    {
        MXC_FLC->faddr = address;
        MXC_FLC->fdata = *word;
        
        fcntl = MXC_FLC->ctrl_f;
        fcntl.write = 1;
        MXC_FLC->ctrl_f = fcntl;

        address += 4;
        word++;
        length -= 4;

        do {
            fcntl = MXC_FLC->ctrl_f;
        } while (fcntl.pending);
    }

    fcntl = MXC_FLC->ctrl_f;
    fcntl.erase_code = 0; /* lock flash */
    fcntl.flsh_unlock = 0;
    MXC_FLC->ctrl_f = fcntl;

    return 0;
}
