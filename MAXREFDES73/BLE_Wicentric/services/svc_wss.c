/*************************************************************************************************/
/*!
 *  \file   svc_wss.c
 *        
 *  \brief  Example Weight Scale service implementation.
 *
 *          $Date: 2012-06-19 16:33:23 -0700 (Tue, 19 Jun 2012) $
 *          $Revision: 334 $
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

#include "wsf_types.h"
#include "att_api.h"
#include "wsf_trace.h"
#include "bstream.h"
#include "svc_ch.h"
#include "svc_wss.h"
#include "svc_cfg.h"

/**************************************************************************************************
  Macros
**************************************************************************************************/

/*! Characteristic read permissions */
#ifndef WSS_SEC_PERMIT_READ
#define WSS_SEC_PERMIT_READ (ATTS_PERMIT_READ | ATTS_PERMIT_READ_ENC)
#endif

/*! Characteristic write permissions */
#ifndef WSS_SEC_PERMIT_WRITE
#define WSS_SEC_PERMIT_WRITE  (ATTS_PERMIT_WRITE | ATTS_PERMIT_WRITE_ENC)
#endif

/**************************************************************************************************
 Service variables
**************************************************************************************************/

/* Weight scale service declaration */
static const uint8_t wssValSvc[] = {UINT16_TO_BYTES(ATT_UUID_WEIGHT_SCALE_SERVICE)};
static const uint16_t wssLenSvc = sizeof(wssValSvc);

/* Weight scale measurement characteristic */ 
static const uint8_t wssValWsmCh[] = {ATT_PROP_INDICATE, UINT16_TO_BYTES(WSS_WSM_HDL), UINT16_TO_BYTES(ATT_UUID_WEIGHT_SCALE_MEAS)};
static const uint16_t wssLenWsmCh = sizeof(wssValWsmCh);

/* Weight scale measurement */
/* Note these are dummy values */
static const uint8_t wssValWsm[] = {0};
static const uint16_t wssLenWsm = sizeof(wssValWsm);

/* Weight scale measurement client characteristic configuration */
static uint8_t wssValWsmChCcc[] = {UINT16_TO_BYTES(0x0000)};
static const uint16_t wssLenWsmChCcc = sizeof(wssValWsmChCcc);

/* Attribute list for WSS group */
static const attsAttr_t wssList[] =
{
  /* Weight scale service declaration */
  {
    attPrimSvcUuid, 
    (uint8_t *) wssValSvc,
    (uint16_t *) &wssLenSvc, 
    sizeof(wssValSvc),
    0,
    ATTS_PERMIT_READ
  },
  /* Weight scale measurement characteristic */ 
  {
    attChUuid,
    (uint8_t *) wssValWsmCh,
    (uint16_t *) &wssLenWsmCh,
    sizeof(wssValWsmCh),
    0,
    ATTS_PERMIT_READ
  },
  /* Weight scale measurement */
  {
    attWsmChUuid,
    (uint8_t *) wssValWsm,
    (uint16_t *) &wssLenWsm,
    sizeof(wssValWsm),
    0,
    0
  },
  /* Weight scale measurement client characteristic configuration */
  {
    attCliChCfgUuid,
    (uint8_t *) wssValWsmChCcc,
    (uint16_t *) &wssLenWsmChCcc,
    sizeof(wssValWsmChCcc),
    ATTS_SET_CCC,
    (ATTS_PERMIT_READ | WSS_SEC_PERMIT_WRITE)
  }
};

/* WSS group structure */
static attsGroup_t svcWssGroup =
{
  NULL,
  (attsAttr_t *) wssList,
  NULL,
  NULL,
  WSS_START_HDL,
  WSS_END_HDL
};

/*************************************************************************************************/
/*!
 *  \fn     SvcWssAddGroup
 *        
 *  \brief  Add the services to the attribute server.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcWssAddGroup(void)
{
  AttsAddGroup(&svcWssGroup);
}

/*************************************************************************************************/
/*!
 *  \fn     SvcWssRemoveGroup
 *        
 *  \brief  Remove the services from the attribute server.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcWssRemoveGroup(void)
{
  AttsRemoveGroup(WSS_START_HDL);
}

/*************************************************************************************************/
/*!
 *  \fn     SvcWssCbackRegister
 *        
 *  \brief  Register callbacks for the service.
 *
 *  \param  readCback   Read callback function.
 *  \param  writeCback  Write callback function.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcWssCbackRegister(attsReadCback_t readCback, attsWriteCback_t writeCback)
{
  svcWssGroup.readCback = readCback;
  svcWssGroup.writeCback = writeCback;
}
