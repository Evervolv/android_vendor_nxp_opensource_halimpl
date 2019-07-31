/*
 * Copyright (C) 2015-2019 NXP Semiconductors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _PHNXPNCIHAL_SELFTEST_H_
#define _PHNXPNCIHAL_SELFTEST_H_

#ifdef NXP_HW_SELF_TEST

#include <phNfcStatus.h>
#include <phNxpNciHal.h>
#include <phTmlNfc.h>

/* PRBS Generation type  */
typedef enum {
  NFC_FW_PRBS, /* FW software would generate the PRBS */
  NFC_HW_PRBS  /* Hardware would generate the PRBS */
} phNxpNfc_PrbsType_t;

/* Different HW PRBS types */
typedef enum { NFC_HW_PRBS9, NFC_HW_PRBS15 } phNxpNfc_PrbsHwType_t;
/* RF Technology */
typedef enum {
  NFC_RF_TECHNOLOGY_A,
  NFC_RF_TECHNOLOGY_B,
  NFC_RF_TECHNOLOGY_F,
} phNxpNfc_Tech_t;

/* Bit rates */
typedef enum {
  NFC_BIT_RATE_106,
  NFC_BIT_RATE_212,
  NFC_BIT_RATE_424,
  NFC_BIT_RATE_848,
} phNxpNfc_Bitrate_t;

typedef struct phAntenna_St_Resp {
  /* Txdo Raw Value*/
  uint16_t wTxdoRawValue;
  uint16_t wTxdoMeasuredRangeMin;            /*Txdo Measured Range Max */
  uint16_t wTxdoMeasuredRangeMax;            /*Txdo Measured Range Min */
  uint16_t wTxdoMeasuredTolerance;           /*Txdo Measured Range Tolerance */
                                             /* Agc Values */
  uint16_t wAgcValue;                        /*Agc Min Value*/
  uint16_t wAgcValueTolerance;               /*Txdo Measured Range*/
                                             /* Agc value with NFCLD */
  uint16_t wAgcValuewithfixedNFCLD;          /*Agc Value with Fixed NFCLD Max */
  uint16_t wAgcValuewithfixedNFCLDTolerance; /*Agc Value with Fixed NFCLD
                                                Tolerance */
  /* Agc Differential Values With Open/Short RM */
  uint16_t wAgcDifferentialWithOpen1;          /*Agc Differential With Open 1*/
  uint16_t wAgcDifferentialWithOpenTolerance1; /*Agc Differential With Open
                                                  Tolerance 1*/
  uint16_t wAgcDifferentialWithOpen2;          /*Agc Differential With Open 2*/
  uint16_t wAgcDifferentialWithOpenTolerance2; /*Agc Differential With Open
                                                  Tolerance 2*/
} phAntenna_St_Resp_t; /* Instance of Transaction structure */

/* NCI Commands */
#define NCI_CORE_RESET_NCI20_RSP   {0x40, 0x00, 0x01, 0x00}
#define NCI_CORE_RESET_NCI20_NTF   {0x60, 0x00, 0x09, 0x02, 0x00, 0x20, 0x04, 0x04, 0x51, 0x12, 0x01, 0x03}
#define NCI_CORE_INIT_NCI20_CMD    {0x20, 0x01, 0x02, 0x00, 0x00}
#define NCI_CORE_INIT_NCI20_RSP    {0x40, 0x01, 0x1E, 0x00}
#define NCI_CORE_INIT_NCI10_CMD    {0x20, 0x01, 0x00}
#define NCI20_CORE_RESET_RSP_LEN   0x01
#define NCI10_CORE_RESET_RSP_LEN   0x03
#define NCI_CORE_RESET_STATUS_OK   0x00
#define NCI_MSG_TYPE_MASK          0xF0

/* Proprietary Commands */
#define SYSTEM_SET_POWERMGT_CMD        {0x2F, 0x00, 0x01, 0x00}
#define SYSTEM_SET_POWERMGT_CMD_1      {0x2F, 0x00, 0x01, 0x01}
#define SYSTEM_SET_POWERMGT_RSP        {0x4F, 0x00, 0x01, 0x00}
#define SYSTEM_PROPRIETARY_ACT_CMD     {0x2F, 0x02, 0x00}
#define SYSTEM_PROPRIETARY_ACT_RSP     {0x4F, 0x02, 0x05, 0x00}
#define SYSTEM_TEST_ANTENNA_CMD_1      {0x2F, 0x3D, 0x05, 0x20, 0x01, 0x00, 0x00, 0x00}
#define SYSTEM_TEST_ANTENNA_RSP_1      {0x4F, 0x3D, 0x05, 0x00}
#define SYSTEM_TEST_ANTENNA_CMD_2      {0x2F, 0x3D, 0x02, 0x20, 0x01}
#define SYSTEM_TEST_ANTENNA_CMD_3      {0x2F, 0x3D, 0x02, 0x20, 0x00}
#define SYSTEM_TEST_ANTENNA_CMD_4      {0x2F, 0x3D, 0x05, 0x20, 0x00, 0x00, 0x00, 0x00}
#define SYSTEM_TEST_ANTENNA_CMD_5      {0x2F, 0x3D, 0x02, 0x01, 0x80}
#define SYSTEM_TEST_ANTENNA_RSP_2      {0x4F, 0x3D, 05}
#define SYSTEM_TEST_ANTENNA_CMD_6      {0x2F, 0x3D, 0x04, 0x08, 0x8C, 0x60, 0x03}
#define SYSTEM_TEST_ANTENNA_CMD_7      {0x2F, 0x3D, 0x04, 0x02, 0xC8, 0x60, 0x03}
#define SYSTEM_TEST_ANTENNA_CMD_8      {0x2F, 0x3D, 0x04, 0x02, 0xCD, 0x60, 0x03}
#define SYSTEM_TEST_ANTENNA_CMD_9      {0x2F, 0x3D, 0x04, 0x04, 0x20, 0x08, 0x20}

/*******************************************************************************
 **
 ** Function         phNxpNciHal_TestMode_open
 **
 ** Description      It opens the physical connection with NFCC (pn547) and
 **                  creates required client thread for operation.
 **
 ** Returns          NFCSTATUS_SUCCESS if successful,otherwise NFCSTATUS_FAILED.
 **
 ******************************************************************************/

NFCSTATUS phNxpNciHal_TestMode_open(void);

/*******************************************************************************
 **
 ** Function         phNxpNciHal_TestMode_close
 **
 ** Description      This function close the NFCC interface and free all
 **                  resources.
 **
 ** Returns          None.
 **
 ******************************************************************************/

void phNxpNciHal_TestMode_close(void);

/*******************************************************************************
 **
 ** Function         phNxpNciHal_SwpTest
 **
 ** Description      Test function to validate the SWP line. SWP line number is
 **                  is sent as parameter to the API.
 **
 ** Returns          NFCSTATUS_SUCCESS if successful,otherwise NFCSTATUS_FAILED.
 **
 ******************************************************************************/

NFCSTATUS phNxpNciHal_SwpTest(uint8_t swp_line);

/*******************************************************************************
 **
 ** Function         phNxpNciHal_PrbsTestStart
 **
 ** Description      Test function start RF generation for RF technology and bit
 **                  rate. RF technology and bit rate are sent as parameter to
 **                  the API.
 **
 ** Returns          NFCSTATUS_SUCCESS if RF generation successful,
 **                  otherwise NFCSTATUS_FAILED.
 **
 ******************************************************************************/
NFCSTATUS phNxpNciHal_PrbsTestStart(phNxpNfc_PrbsType_t prbs_type,
                                    phNxpNfc_PrbsHwType_t hw_prbs_type,
                                    phNxpNfc_Tech_t tech,
                                    phNxpNfc_Bitrate_t bitrate);

/*******************************************************************************
 **
 ** Function         phNxpNciHal_PrbsTestStop
 **
 ** Description      Test function stop RF generation for RF technology started
 **                  by phNxpNciHal_PrbsTestStart.
 **
 ** Returns          NFCSTATUS_SUCCESS if operation successful,
 **                  otherwise NFCSTATUS_FAILED.
 **
 ******************************************************************************/

NFCSTATUS phNxpNciHal_PrbsTestStop();

/*******************************************************************************
**
** Function         phNxpNciHal_AntennaSelfTest
**
** Description      Test function to validate the Antenna's discrete
**                  components connection.
**
** Returns          NFCSTATUS_SUCCESS if successful,otherwise NFCSTATUS_FAILED.
**
*******************************************************************************/

NFCSTATUS phNxpNciHal_AntennaSelfTest(phAntenna_St_Resp_t* phAntenna_St_Resp);

/*******************************************************************************
**
** Function         phNxpNciHal_RfFieldTest
**
** Description      Test function performs RF filed test.
**
** Returns          NFCSTATUS_SUCCESS if successful,otherwise NFCSTATUS_FAILED.
**
*******************************************************************************/

NFCSTATUS phNxpNciHal_RfFieldTest(uint8_t on);

/*******************************************************************************
 **
 ** Function         phNxpNciHal_DownloadPinTest
 **
 ** Description      Test function to validate the FW download pin connection.
 **
 ** Returns          NFCSTATUS_SUCCESS if successful,otherwise NFCSTATUS_FAILED.
 **
 ******************************************************************************/

NFCSTATUS phNxpNciHal_DownloadPinTest(void);

#endif /* _NXP_HW_SELF_TEST_H_ */
#endif /* _PHNXPNCIHAL_SELFTEST_H_ */
