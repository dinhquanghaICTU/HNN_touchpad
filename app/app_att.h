/********************************************************************************************************
 * @file    app_att.h
 *
 * @brief   This is the header file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2020
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef APP_ATT_H_
#define APP_ATT_H_

#include "../app_config.h"

///////////////////////////////////// ATT  HANDLER define ///////////////////////////////////////
typedef enum
{
    ATT_H_START = 0,

    GenericAccess_PS_H,
    GenericAccess_DeviceName_CD_H,
    GenericAccess_DeviceName_DP_H,
    GenericAccess_Appearance_CD_H,
    GenericAccess_Appearance_DP_H,
    CONN_PARAM_CD_H,
    CONN_PARAM_DP_H,

    GenericAttribute_PS_H,
    GenericAttribute_ServiceChanged_CD_H,
    GenericAttribute_ServiceChanged_DP_H,
    GenericAttribute_ServiceChanged_CCB_H,
    
    BATT_PS_H,
    BATT_LEVEL_INPUT_CD_H,
    BATT_LEVEL_INPUT_DP_H,
    BATT_LEVEL_INPUT_CCB_H,


    TOUCHPAD_NOTIFY_PS_H,
    TOUCHPAD_NOTIFY_CD_H,
    TOUCHPAD_NOTIFY_DP_H,
    TOUCHPAD_NOTIFY_CCB_H,
    
    TOUCHPAD_WRITE_PS_H,
    TOUCHPAD_WRITE_CD_H,
    TOUCHPAD_WRITE_DP_H,

#if (BLE_OTA_SERVER_ENABLE)
   
    OTA_PS_H,
    OTA_CMD_OUT_CD_H,
    OTA_CMD_OUT_DP_H,
    OTA_CMD_INPUT_CCB_H,
    OTA_CMD_OUT_DESC_H,
#endif

    ATT_END_H,
} ATT_HANDLE;

void my_att_init(void);

/**
 * @brief      This function is used to handle touchpad write characteristic
 * @param[in]  p - GATT data buffer pointer of write_req or write_cmd
 * @return     0
 */
extern u8 touchpadNotifyCCC[2];
int touchpadwritehandle(void * p);

#endif /* APP_ATT_H_ */
