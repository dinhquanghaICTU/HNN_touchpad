/********************************************************************************************************
 * @file    app_ui.c
 *
 * @brief   This is the source file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app.h"
#include "app_att.h"
#include "app_ui.h"
#include "../HNN_config.h"



#if (BLE_OTA_SERVER_ENABLE)
/**
 * @brief      this function is used to register the function for OTA start.
 * @param[in]  none
 * @return     none
 */
void app_enter_ota_mode(void)
{
	tlkapi_send_string_data(APP_OTA_LOG_EN, "[APP][OTA] enter ota mode\r\n", 0, 0);
	ota_is_working = 1;
	latest_user_event_tick = clock_time();
}


/**
 * @brief      this function is used to register the function for OTA end.
 * @param[in]  result - OTA result
 * @return     none
 */
void app_ota_end_result(int result)
{
	#if(0 && UI_LED_ENABLE)  //this is only for debug
		if(result == OTA_SUCCESS){  //led for debug: OTA success
			gpio_write(GPIO_LED_BLUE, 1);
			sleep_ms(300);
			gpio_write(GPIO_LED_BLUE, 0);
			sleep_ms(300);
			gpio_write(GPIO_LED_BLUE, 1);
			sleep_ms(300);
			gpio_write(GPIO_LED_BLUE, 0);

			/* attention that this log may lost, because MCU will reboot for successful OTA */
			//tlkapi_send_string_data(APP_OTA_LOG_EN, "[APP][OTA] ota success", &result, 1);
		}
		else{  //OTA fail
			gpio_write(GPIO_LED_BLUE, 1);
			sleep_ms(100);
			gpio_write(GPIO_LED_BLUE, 0);

			/* attention that this log may lost */
			//tlkapi_send_string_data(APP_OTA_LOG_EN, "[APP][OTA] ota fail", &result, 1);
		}
	#endif
}
#endif

