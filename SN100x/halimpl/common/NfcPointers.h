/*
 * Copyright (c) 2018, 2020 The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "phNxpNciHal_Adaptation.h"  //NfcConfig, nfc_stack_callback_t*, nfc_stack_data_callback_t*
#include "phNxpNciHal_Common.h"
#include <stdint.h>

/* This struct of function pointers can be exported with extern "C" and used to
 * access member functions without modifying those functions to be external.
 */
typedef struct HAL_API_struct {
    // phNxpNciHal_open
    int(*phNxpNciHal_open)(nfc_stack_callback_t*, nfc_stack_data_callback_t*);
    // phNxpNciHal_write
    int(*phNxpNciHal_write)(uint16_t, const uint8_t*);
    // phNxpNciHal_core_initialized
    int(*phNxpNciHal_core_initialized)(uint8_t*);
    // phNxpNciHal_pre_discover
    int(*phNxpNciHal_pre_discover)(void);
    // phNxpNciHal_close
    int(*phNxpNciHal_close)(bool);
    // phNxpNciHal_control_granted
    int(*phNxpNciHal_control_granted)(void);
    // phNxpNciHal_power_cycle
    int(*phNxpNciHal_power_cycle)(void);
    // phNxpNciHal_reset_nfcee_session
    void(*phNxpNciHal_do_factory_reset)(void);
    // phNxpNciHal_configDiscShutdown
    int(*phNxpNciHal_configDiscShutdown)(void);
    // phNxpNciHal_getVendorConfig_V_1_1
    void(*phNxpNciHal_getVendorConfig)(android::hardware::nfc::V1_1::NfcConfig&);
    // phNxpNciHal_getVendorConfig_V_1_2
    void(*phNxpNciHal_getVendorConfig_1_2)(NfcConfig&);
    // phNxpNciHal_get_debug_status
    bool(*phNxpNciHal_get_debug_status)(void);
    // phNxpNciHal_getNfcChipId
    string(*phNxpNciHal_getNfcChipId)(void);
    // phNxpNciHal_getNfcFirmwareVersion
    string(*phNxpNciHal_getNfcFirmwareVersion)(void);
    // phNxpNciHal_getSystemProperty
    string(*phNxpNciHal_getSystemProperty)(string key);
    // phNxpNciHal_setSystemProperty
    bool(*phNxpNciHal_setSystemProperty)(string key, string value);
    // phNxpNciHal_resetEse
    NFCSTATUS(*phNxpNciHal_resetEse)(uint64_t resetType);
    // seteSEClientState
    void (*seteSEClientState)(uint8_t);
    // eSEClientUpdate_NFC_Thread
    void(*eSEClientUpdate_NFC_Thread)(void);
    // phNxpNciHal_Abort
    bool(*phNxpNciHal_Abort)(void);
    // phNxpNciHal_setNxpTransitConfig
    bool(*phNxpNciHal_setNxpTransitConfig)(char *);
    // getJcopUpdateRequired
    uint8_t(*getJcopUpdateRequired)(void);
    // getLsUpdateRequired
    uint8_t(*getLsUpdateRequired)(void);
    // phNxpNciHal_setEseState
    NFCSTATUS(*phNxpNciHal_setEseState)(phNxpNfcHalEseState);
    // phNxpHal_getchipType
    uint8_t(*phNxpHal_getchipType)(void);
    // phNxpNciHal_setNfcServicePid
    uint16_t(*phNxpNciHal_setNfcServicePid)(uint64_t);
    // phNxpNciHal_getEseState
    NFCSTATUS(*phNxpNciHal_getEseState)(void);
    // phNxpNciHal_ReleaseSVDDWait
    NFCSTATUS(*phNxpNciHal_ReleaseSVDDWait)(uint32_t);
    // phNxpNciHal_ReleaseDWPOnOffWait
    NFCSTATUS(*phNxpNciHal_ReleaseDWPOnOffWait)(uint32_t);
    // phNxpNciHal_getSPMStatus
    int(*phNxpNciHal_getSPMStatus)(uint32_t);
    // phNxpNciHal_hciInitUpdateState
    int32_t(*phNxpNciHal_hciInitUpdateState)(phNxpNfcHciInitStatus);
    // phNxpNciHal_hciInitUpdateStateComplete
    int32_t(*phNxpNciHal_hciInitUpdateStateComplete)(void);
    // phNxpNciHal_GetCachedNfccConfig
    void(*phNxpNciHal_GetCachedNfccConfig)(phNxpNci_getCfg_info_t *);
    // phNxpNciHal_getNxpConfig
    void(*phNxpNciHal_getNxpConfig)(phNxpNfcHalConfig *);
    // phNxpNciHal_nciTransceive
    void(*phNxpNciHal_nciTransceive)(phNxpNci_Extn_Cmd_t *, phNxpNci_Extn_Resp_t *);
} hal_api_struct_t;
