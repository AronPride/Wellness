/*************************************************************************************************/
/*!
 *  \file   hci_drv.c
 *
 *  \brief  HCI driver interface.
 *
 *          $Date: 2014-04-10 17:24:24 -0600 (Thu, 10 Apr 2014) $
 *          $Revision: 1118 $
 *
 *  Copyright (c) 2012 Wicentric, Inc., all rights reserved.
 *  Wicentric confidential and proprietary.
 *
 *  IMPORTANT.  Your use of this file is governed by a Software License Agreement
 *  ("Agreement") that must be accepted in order to download or otherwise receive a
 *  copy of this file.  You may not use or copy this file for any purpose other than
 *  as described in the Agreement.  If you do not agree to all of the terms of the
 *  Agreement do not use this file and delete all copies in your possession or control;
 *  if you do not have a copy of the Agreement, you must contact Wicentric, Inc. prior
 *  to any use, copying or further distribution of this software.
 */
/*************************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "wsf_types.h"
#include "wsf_os_int.h"
#include "hci_drv.h"
#include "hci_tr.h"
#include "spi.h"

#define FC_POLARITY       1

extern spi_slave_t ss;
extern uint8_t mainHciBuf[64];

typedef enum {
    HCI_CMD = 1,
    HCI_ACL_DATA,
    HCI_SCO_DATA,
    HCI_EVENT
} hci_packet_t;

static uint8_t tx[64];
static uint16_t tx_left;
static uint16_t tx_index;
static void spi_tx_cb(int32_t ret) 
{
    if(tx_left) {
        if(tx_left <= 32) {
            tx_left = 0;
            tx_index += tx_left;
            SPI_TransmitAsync(&ss, &tx[tx_index], tx_left, spi_tx_cb, NULL, 0, NULL, \
                              MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 1);
        }
        else {
            tx_left -= 32;
            tx_index += 32;
            SPI_TransmitAsync(&ss, &tx[tx_index], 32, spi_tx_cb, NULL, 0, NULL, \
                              MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 0);
        }
    }
}

/*************************************************************************************************/
/*!
 *  \fn     hciDrvWrite
 *
 *  \brief  Write data the driver.
 *
 *  \param  type     HCI packet type
 *  \param  len      Number of bytes to write.
 *  \param  pData    Byte array to write.
 *
 *  \return Return actual number of data bytes written.
 *
 *  \note   The type parameter allows the driver layer to prepend the data with a header on the
 *          same write transaction.
 */
/*************************************************************************************************/
uint16_t hciDrvWrite(uint8_t type, uint16_t len, uint8_t *pData)
{
    SPI_ConfigSpecial(&ss, MXC_E_SPI_FLOW_CTRL_MISO, FC_POLARITY, 1, 1, 1);
    while(SPI_Setup(&ss) == -1);

    memset(tx, 0, (len+1));
    tx[0] = type;
    memcpy(&tx[1], pData, len);

    tx_left = 0;
    tx_index = 0;

    if((len + 1) <= 32) { /* tx size is less or equal to 32 bytes */
        SPI_TransmitAsync(&ss, &tx[0], (len + 1), spi_tx_cb, NULL, 0, NULL, \
                          MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 1);
    }
    else if(!((len + 1) % 4)){ /* tx size is bigger than 32 bytes and the multiple by 4 */
        SPI_TransmitAsync(&ss, &tx[0], ((len + 1) / 4), spi_tx_cb, NULL, 0, NULL, \
                          MXC_E_SPI_UNIT_4B_PAGES, MXC_E_SPI_MODE_4_WIRE, 0, 1);
    }
    else { /* tx size is bigger than 32 bytes but not the multiple by 4 */
        tx_left = len - 32;
        tx_index += 32;
        SPI_TransmitAsync(&ss, &tx[0], 32, spi_tx_cb, NULL, 0, NULL,    \
                          MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 0);
    }
    return len;
}

static uint32_t rx_len;
static void spi_rx_cb(uint32_t rx_size)
{
    rx_len += rx_size;

    if(mainHciBuf[0] == HCI_EVENT)
    {
        if(mainHciBuf[3] != 0 || rx_size == mainHciBuf[2]) /* Finish reading */
        { 
            hciTrSerialRxIncoming(&mainHciBuf[0], rx_len);
            return;
        }
        else /* Keep reading the rest of the bytes according to mainHciBuf[2] */
        {
            SPI_TransmitAsync(&ss, NULL, 0, NULL, &mainHciBuf[3], mainHciBuf[2], spi_rx_cb, \
                              MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 1);
            return;
        }
    }
    else if(mainHciBuf[0] == HCI_ACL_DATA)
    {
        if(mainHciBuf[3] == 0) /* Read how many bytes left */
        {
            SPI_TransmitAsync(&ss, NULL, 0, NULL, &mainHciBuf[3], 2, spi_rx_cb, \
                              MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 0);
            return;
        }
        else if((mainHciBuf[5] == 0) && mainHciBuf[3]) /* Read the rest of the ACL data */
        {
            uint32_t size = (mainHciBuf[3] | mainHciBuf[4] << 8);

            SPI_TransmitAsync(&ss, NULL, 0, NULL, &mainHciBuf[5], size, spi_rx_cb, \
                              MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 1);
            return;
        }
        else 
        {
            hciTrSerialRxIncoming(&mainHciBuf[0], rx_len);
            return;
        }
    }
}

/*************************************************************************************************/
/*!
 *  \fn     hciDrvRead
 *
 *  \brief  Read data bytes from the driver.
 *
 *  \param  len      Number of bytes to read.
 *  \param  pData    Byte array to store data.
 *
 *  \return Return actual number of data bytes read.
 */
/*************************************************************************************************/
uint16_t hciDrvRead(uint16_t len, uint8_t *pData)
{
    rx_len = 0;
    SPI_TransmitAsync(&ss, NULL, 0, NULL, pData, 3, spi_rx_cb,          \
                      MXC_E_SPI_UNIT_BYTES, MXC_E_SPI_MODE_4_WIRE, 0, 0);

    return len;
}
