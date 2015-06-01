/*************************************************************************************************/
/*!
 *  \file   hci_tr.h
 *
 *  \brief  HCI transport interface.
 *
 *          $Date: 2012-04-30 21:15:31 -0700 (Mon, 30 Apr 2012) $
 *          $Revision: 309 $
 *
 *  Copyright (c) 2009 Wicentric, Inc., all rights reserved.
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
#ifndef HCI_TR_H
#define HCI_TR_H

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

void hciTrSendAclData(uint8_t *pAclData);
void hciTrSendCmd(uint8_t *pCmdData);
bool_t hciTrInit(uint8_t port, uint32_t baudRate, bool_t flowControl);
void hciTrShutdown(void);
void hciTrSerialRxIncoming(uint8_t *pBuf, uint8_t len);

#ifdef __cplusplus
};
#endif

#endif /* HCI_TR_H */
