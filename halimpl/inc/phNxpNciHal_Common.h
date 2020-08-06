/*
 * Copyright (C) 2010-2020 NXP Semiconductors
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

#ifndef _PHNXPNCIHAL__COMMON_H_
#define _PHNXPNCIHAL__COMMON_H_

#include <hardware/nfc.h>

#define NCI_MAX_DATA_LEN 300

#define NXP_AUTH_TIMEOUT_BUF_LEN 0x04

#define MAX_IOCTL_TRANSCEIVE_CMD_LEN 256
#define MAX_IOCTL_TRANSCEIVE_RESP_LEN 256

typedef enum {
  NFC_FORUM_PROFILE,
  EMV_CO_PROFILE,
  INVALID_PROFILe
} phNxpNciProfile_t;

typedef enum {
  HAL_STATUS_CLOSE = 0,
  HAL_STATUS_OPEN,
  HAL_STATUS_MIN_OPEN
} phNxpNci_HalStatus;

typedef struct phNxpNciInfo {
  uint8_t   nci_version;
  bool_t    wait_for_ntf;
  uint8_t   lastResetNtfReason;
}phNxpNciInfo_t;

typedef enum {
  GPIO_UNKNOWN = 0x00,
  GPIO_STORE = 0x01,
  GPIO_STORE_DONE = 0x02,
  GPIO_RESTORE = 0x10,
  GPIO_RESTORE_DONE = 0x20,
  GPIO_CLEAR = 0xFF
} phNxpNciHal_GpioInfoState;

typedef struct phNxpNciGpioInfo {
  phNxpNciHal_GpioInfoState state;
  uint8_t values[2];
} phNxpNciGpioInfo_t;


typedef void(phNxpNciHal_control_granted_callback_t)();
/* NCI Control structure */
typedef struct phNxpNciHal_Control {
  phNxpNci_HalStatus halStatus; /* Indicate if hal is open or closed */
  pthread_t client_thread;      /* Integration thread handle */
  uint8_t thread_running;       /* Thread running if set to 1, else set to 0 */
  phLibNfc_sConfig_t gDrvCfg;   /* Driver config data */

  /* Rx data */
  uint8_t* p_rx_data;
  uint16_t rx_data_len;

  /* Rx data */
  uint8_t* p_rx_ese_data;
  uint16_t rx_ese_data_len;
  /* libnfc-nci callbacks */
  nfc_stack_callback_t* p_nfc_stack_cback;
  nfc_stack_data_callback_t* p_nfc_stack_data_cback;

  /* control granted callback */
  phNxpNciHal_control_granted_callback_t* p_control_granted_cback;

  /* HAL open status */
  bool_t hal_open_status;

  bool_t is_wait_for_ce_ntf;

  /* HAL extensions */
  uint8_t hal_ext_enabled;

  /* Waiting semaphore */
  phNxpNciHal_Sem_t ext_cb_data;
  sem_t syncSpiNfc;

  uint16_t cmd_len;
  uint8_t p_cmd_data[NCI_MAX_DATA_LEN];
  uint16_t rsp_len;
  uint8_t p_rsp_data[NCI_MAX_DATA_LEN];

  /* retry count used to force download */
  uint16_t retry_cnt;
  uint8_t read_retry_cnt;
  phNxpNciInfo_t nci_info;
  uint8_t hal_boot_mode;
  tNFC_chipType chipType;
  /* to store and restore gpio values */
  phNxpNciGpioInfo_t phNxpNciGpioInfo;
  bool bIsForceFwDwnld;
  bool isHciCfgEvtRequested;
  bool_t fwdnld_mode_reqd;
} phNxpNciHal_Control_t;

typedef struct phNxpNciClock {
  bool_t isClockSet;
  uint8_t p_rx_data[20];
  bool_t issetConfig;
} phNxpNciClock_t;


typedef enum {
  EEPROM_RF_CFG,
  EEPROM_FW_DWNLD,
  EEPROM_WIREDMODE_RESUME_TIMEOUT,
  EEPROM_ESE_SVDD_POWER,
  EEPROM_ESE_POWER_EXT_PMU,
  EEPROM_PROP_ROUTING,
  EEPROM_ESE_SESSION_ID,
  EEPROM_SWP1_INTF,
  EEPROM_SWP1A_INTF,
  EEPROM_SWP2_INTF,
  EEPROM_NDEF_INTF_CFG,
  EEPROM_FLASH_UPDATE,
  EEPROM_AUTH_CMD_TIMEOUT,
  EEPROM_GUARD_TIMER,
  EEPROM_T4T_NFCEE_ENABLE,
  EEPROM_AUTONOMOUS_MODE,
  EEPROM_CE_PHONE_OFF_CFG,
} phNxpNci_EEPROM_request_type_t;


typedef struct phNxpNci_getCfg_info {
  bool_t isGetcfg;
  uint8_t total_duration[4];
  uint8_t total_duration_len;
  uint8_t atr_req_gen_bytes[48];
  uint8_t atr_req_gen_bytes_len;
  uint8_t atr_res_gen_bytes[48];
  uint8_t atr_res_gen_bytes_len;
  uint8_t pmid_wt[3];
  uint8_t pmid_wt_len;
  uint8_t auth_cmd_timeout[NXP_AUTH_TIMEOUT_BUF_LEN];
  uint8_t auth_cmd_timeoutlen;
} phNxpNci_getCfg_info_t;


/* NXP Poll Profile control structure */
typedef struct phNxpNciProfile_Control {
  phNxpNciProfile_t profile_type;
  uint8_t bClkSrcVal; /* Holds the System clock source read from config file */
  uint8_t
      bClkFreqVal;  /* Holds the System clock frequency read from config file */
  uint8_t bTimeout; /* Holds the Timeout Value */
  uint8_t clkReqDelay; /* Holds default delay time before start clock request*/
} phNxpNciProfile_Control_t;

typedef enum {
  phNxpNciHalNfc_e_SetIdleMode, /* Set the current mode of operation to Idle*/
  phNxpNciHalNfc_e_SetWiredMode,  /* Set the current mode of operation to Wired*/
} phNxpNfcHalEseState;

typedef enum {
  phNxpNfcHciInitStatus_e_Complete = 0x00,
  phNxpNfcHciInitStatus_e_Start = 0x01
} phNxpNfcHciInitStatus;

typedef struct phNxpNci_Extn_Cmd{
  uint16_t cmd_len;
  uint8_t p_cmd[MAX_IOCTL_TRANSCEIVE_CMD_LEN];
}phNxpNci_Extn_Cmd_t;

typedef struct phNxpNci_Extn_Resp{
  uint32_t status;
  uint16_t rsp_len;
  uint8_t p_rsp[MAX_IOCTL_TRANSCEIVE_RESP_LEN];
}phNxpNci_Extn_Resp_t;

typedef struct phNxpNci_EEPROM_info {
  uint8_t request_mode;
  phNxpNci_EEPROM_request_type_t request_type;
  uint8_t update_mode;
  uint8_t* buffer;
  uint8_t bufflen;
} phNxpNci_EEPROM_info_t;

struct phNxpNfcScrResetEmvcoCmd{
  uint64_t len;
  uint8_t cmd[10];
};

struct phNxpNfcHalConfig {
  uint8_t ese_listen_tech_mask;
  uint8_t default_nfcee_disc_timeout;
  uint8_t default_nfcee_timeout;
  uint8_t ese_wired_prt_mask;
  uint8_t uicc_wired_prt_mask;
  uint8_t wired_mode_rf_field_enable;
  uint8_t aid_block_route;
  uint8_t esePowerDhControl;
  uint8_t tagOpTimeout;
  uint8_t loaderServiceVersion;
  uint8_t defaultNfceeDiscTimeout;
  uint8_t dualUiccEnable;
  uint8_t ceRouteStrictDisable;
  uint32_t osDownloadTimeoutValue;
  uint8_t defaultAidRoute;
  uint8_t defaultAidPwrState;
  uint8_t defaultRoutePwrState;
  uint8_t defaultOffHostPwrState;
  uint8_t jcopDlAtBootEnable;
  uint8_t defaultNfceeTimeout;
  uint8_t nxpNfcChip;
  uint8_t coreScrnOffAutonomousEnable;
  uint8_t p61LsDefaultInterface;
  uint8_t p61JcopDefaultInterface;
  uint8_t agcDebugEnable;
  uint8_t felicaCltPowerState;
  uint32_t cmdRspTimeoutValue;
  uint8_t checkDefaultProtoSeId;
  uint8_t nfccPassiveListenTimeout;
  uint32_t nfccStandbyTimeout;
  uint32_t wmMaxWtxCount;
  uint32_t nfccRfFieldEventTimeout;
  uint8_t allowWiredInMifareDesfireClt;
  uint8_t dwpIntfResetEnable;
  uint8_t nxpLogHalLoglevel;
  uint8_t nxpLogExtnsLogLevel;
  uint8_t nxpLogTmlLogLevel;
  uint8_t nxpLogFwDnldLogLevel;
  uint8_t nxpLogNcixLogLevel;
  uint8_t nxpLogNcirLogLevel;
  uint8_t scrCfgFormat;
  uint8_t etsiReaderEnable;
  uint8_t techAbfRoute;
  uint8_t techAbfPwrState;
  uint8_t wTagSupport;
  uint8_t t4tNfceePwrState;
  phNxpNfcScrResetEmvcoCmd scrResetEmvco;
};

#endif
