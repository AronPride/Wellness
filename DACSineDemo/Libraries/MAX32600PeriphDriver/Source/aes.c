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

#include <string.h>    /* Included for memcpy() & #includes stddef for NULL */

#include "mxc_config.h"
#include "aes.h"
#include "nvic_table.h"

/* -- Driver configuration options -- */
/* #define this option to pre-clear AES engine output before new operation */
#undef MXC_OPT_AES_PRECLEAR_OUTPUT

/* Callback for asynchronous API */
static void (*aes_irq_handler)(void) = NULL;

mxc_aes_ret_t AES_SetKey(const uint8_t *key, mxc_aes_mode_t mode)
{
  /* Erase any existing key */
  MXC_AES_MEM->key[7] = MXC_AES_MEM->key[6] = MXC_AES_MEM->key[5] = MXC_AES_MEM->key[4] \
    = MXC_AES_MEM->key[3] = MXC_AES_MEM->key[2] = MXC_AES_MEM->key[1] = MXC_AES_MEM->key[0] \
    = 0x00000000;

  /* Load new key, based on key mode */
  switch (mode) {
    /* NOTE: These cases "fall-through", or have no break, on purpose! */
    case MXC_E_AES_MODE_256:
      MXC_AES_MEM->key[7] = key[28] + (key[29] << 8) + (key[30] << 16) + (key[31] << 24);
      MXC_AES_MEM->key[6] = key[24] + (key[25] << 8) + (key[26] << 16) + (key[27] << 24);

    case MXC_E_AES_MODE_192:
      MXC_AES_MEM->key[5] = key[20] + (key[21] << 8) + (key[22] << 16) + (key[23] << 24);
      MXC_AES_MEM->key[4] = key[16] + (key[17] << 8) + (key[18] << 16) + (key[19] << 24);

    case MXC_E_AES_MODE_128:
      MXC_AES_MEM->key[3] = key[12] + (key[13] << 8) + (key[14] << 16) + (key[15] << 24);
      MXC_AES_MEM->key[2] = key[8] + (key[9] << 8) + (key[10] << 16) + (key[11] << 24);
      MXC_AES_MEM->key[1] = key[4] + (key[5] << 8) + (key[6] << 16) + (key[7] << 24);
      MXC_AES_MEM->key[0] = key[0] + (key[1] << 8) + (key[2] << 16) + (key[3] << 24);

      /* This is the break for all cases above. */
      return MXC_E_AES_OK;
      break;

    default:
      return MXC_E_AES_ERR;
  }
}

mxc_aes_ret_t AES_AsyncSetup(const uint8_t *in, mxc_aes_mode_t mode, 
			     mxc_aes_dir_t dir, void (*cb)(void))
{
  /* Can't be Async w/o a callback */
  if (cb != NULL) {
    aes_irq_handler = cb;
  } else {
    return MXC_E_AES_ERR;
  }

  /* Install handler, and also enables interrupt */
  NVIC_SetVector(aes_irq_handler, AES_IRQn);

  /* Pass off to actual ECB operation */
  return AES_ECBOp(in, NULL, mode, dir);
}

mxc_aes_ret_t AES_ECBOp(const uint8_t *in, uint8_t *out, mxc_aes_mode_t mode, mxc_aes_dir_t dir)
{
  /* Output array can't be a NULL, unless we are in _ASYNC mode */
  if ((out == NULL) 
      && ((dir != MXC_E_AES_ENCRYPT_ASYNC) && (dir != MXC_E_AES_DECRYPT_ASYNC))) {
    return MXC_E_AES_ERR;
  }

  /* Another encryption is already in progress */
  if (MXC_AES->ctrl & MXC_F_AES_CTRL_START) {
    return MXC_E_AES_BUSY;
  }

  /* Clear any existing configuration */
  MXC_AES->ctrl = 0x00000000;

#ifdef MXC_OPT_AES_PRECLEAR_OUTPUT
  /* Remove any prior output from the engine */
  MXC_AES_MEM->out[3] = MXC_AES_MEM->out[2] = MXC_AES_MEM->out[1] = MXC_AES_MEM->out[0] \
    = 0x00000000;
#endif
  
  /* Select key size & direction
   *
   * Note: This is done first to detect argument errors, before sensitive data
   *  is loaded into AES_MEM block
   *
   */
  switch (mode) {
    case MXC_E_AES_MODE_128:
      MXC_AES->ctrl |= MXC_S_AES_CTRL_KEY_SIZE_128;
      break;

    case MXC_E_AES_MODE_192:
      MXC_AES->ctrl |= MXC_S_AES_CTRL_KEY_SIZE_192;
      break;

    case MXC_E_AES_MODE_256:
      MXC_AES->ctrl |= MXC_S_AES_CTRL_KEY_SIZE_256;
      break;

    default:
      return MXC_E_AES_ERR;
  }

  switch (dir) {
    case MXC_E_AES_ENCRYPT:
    case MXC_E_AES_ENCRYPT_ASYNC:
      MXC_AES->ctrl |= MXC_S_AES_CTRL_ENCRYPT_MODE;
      break;
      
    case MXC_E_AES_DECRYPT:
    case MXC_E_AES_DECRYPT_ASYNC:
      MXC_AES->ctrl |= MXC_S_AES_CTRL_DECRYPT_MODE;
      break;

    default:
      return MXC_E_AES_ERR;
  }

  /* If non-blocking mode has been selected, interrupts are automatically enabled */
  if ((dir == MXC_E_AES_ENCRYPT_ASYNC) || 
      (dir == MXC_E_AES_DECRYPT_ASYNC)) {
    MXC_AES->ctrl |= MXC_F_AES_CTRL_INTEN;
  }

  /* Load input into engine */
  MXC_AES_MEM->inp[3] = in[12] + (in[13] << 8) + (in[14] << 16) + (in[15] << 24);
  MXC_AES_MEM->inp[2] = in[8] + (in[9] << 8) + (in[10] << 16) + (in[11] << 24);
  MXC_AES_MEM->inp[1] = in[4] + (in[5] << 8) + (in[6] << 16) + (in[7] << 24);
  MXC_AES_MEM->inp[0] = in[0] + (in[1] << 8) + (in[2] << 16) + (in[3] << 24);

  /* Start operation */
  MXC_AES->ctrl |= MXC_F_AES_CTRL_START;
  
  /* Block, waiting on engine to complete, or fall through if non-blocking */
  if ((dir != MXC_E_AES_ENCRYPT_ASYNC) && 
      (dir != MXC_E_AES_DECRYPT_ASYNC)) {
    while (MXC_AES->ctrl & MXC_F_AES_CTRL_START) {
      /* Ensure that this wait loop is not optimized out */
      __NOP();
    }
    
    /* Get output from engine */
    if (AES_GetOutput(out) != MXC_E_AES_OK) {
      /* Unlike the asynchronous method, this should not have failed */
      return MXC_E_AES_ERR;
    }
  }
  
  return MXC_E_AES_OK;
}

mxc_aes_ret_t AES_GetOutput(uint8_t *out)
{
  
  /* Ensure valid output pointer */
  if (out == NULL) {
    return MXC_E_AES_ERR;
  }

  /* Don't read it out of the AES memory unless engine is idle */
  if (MXC_AES->ctrl & MXC_F_AES_CTRL_START) {
    return MXC_E_AES_BUSY;
  }

  /* Pull out result */
  out[15] = ((MXC_AES_MEM->out[3] & 0xff000000) >> 24);
  out[14] = ((MXC_AES_MEM->out[3] & 0x00ff0000) >> 16);
  out[13] = ((MXC_AES_MEM->out[3] & 0x0000ff00) >> 8);
  out[12] = (MXC_AES_MEM->out[3] & 0x000000ff);
  
  out[11] = ((MXC_AES_MEM->out[2] & 0xff000000) >> 24);
  out[10] = ((MXC_AES_MEM->out[2] & 0x00ff0000) >> 16);
  out[9] = ((MXC_AES_MEM->out[2] & 0x0000ff00) >> 8);
  out[8] = (MXC_AES_MEM->out[2] & 0x000000ff);
  
  out[7] = ((MXC_AES_MEM->out[1] & 0xff000000) >> 24);
  out[6] = ((MXC_AES_MEM->out[1] & 0x00ff0000) >> 16);
  out[5] = ((MXC_AES_MEM->out[1] & 0x0000ff00) >> 8);
  out[4] = (MXC_AES_MEM->out[1] & 0x000000ff);
  
  out[3] = ((MXC_AES_MEM->out[0] & 0xff000000) >> 24);
  out[2] = ((MXC_AES_MEM->out[0] & 0x00ff0000) >> 16);
  out[1] = ((MXC_AES_MEM->out[0] & 0x0000ff00) >> 8);
  out[0] = (MXC_AES_MEM->out[0] & 0x000000ff);

  /* Clear interrupt flag, write 1 to clear */
  MXC_AES->ctrl |= MXC_F_AES_CTRL_INTFL;

  return MXC_E_AES_OK;
}
