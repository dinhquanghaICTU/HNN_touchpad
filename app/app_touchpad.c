#include "app_touchpad.h"
#include "tl_common.h"
#include "stack/ble/ble.h"
#include "../third_party/jsmn/jsmn.h"
#include "../HNN_config.h"
#include "../middle/led/m_led.h"
#include "app_att.h"
#include "app.h" 


//{"touchpad":{"touchpad1":0,"touchpad2":1,"touchpad3":0}

int touchpadwritehandle(void *p)
{
	rf_packet_att_write_t *pw = (rf_packet_att_write_t *)p;

	if (pw)
	{
		u8 len = pw->l2capLen - 3;

		if (len == 0 || len > 255)
		{
			tlkapi_printf(DEBUG_TOUCHPAD,"[ERROR] Invalid length: %d\n", len);
			return 0;
		}
		u8 *data = &pw->value;
		if (len == 0 || (data[0] != '{' && data[0] != '['))
		{
			return 0;
		}
		char json_str[256];
		memset(json_str, 0, sizeof(json_str));
		if (len < 256)
		{
			memcpy(json_str, data, len);
			json_str[len] = '\0';
		}

		jsmn_parser parser;
		jsmntok_t tokens[32];
		jsmn_init(&parser);

		int r = json_parser(json_str, &parser, tokens, 32);

		if (r > 0)
		{
			int touchpad_value_pos = get_pos_key(json_str, tokens, r, "touchpad");
			if (touchpad_value_pos > 0 && tokens[touchpad_value_pos].type == JSMN_OBJECT)
			{
				int num_items = tokens[touchpad_value_pos].size;
				int current_pos = touchpad_value_pos + 1;
				u8 touchpad1_val = 0;
				u8 touchpad2_val = 0;
				u8 touchpad3_val = 0;

				for (int i = 0; i < num_items && current_pos < r; i++)
				{

					if (tokens[current_pos].type == JSMN_STRING)
					{
						char key[32] = {0};
						int key_len = tokens[current_pos].end - tokens[current_pos].start;
						if (key_len < 32)
						{
							memcpy(key, json_str + tokens[current_pos].start, key_len);
							key[key_len] = '\0';
						}
						if (current_pos + 1 < r && tokens[current_pos + 1].type == JSMN_PRIMITIVE)
						{
							char value[16] = {0};
							int val_len = tokens[current_pos + 1].end - tokens[current_pos + 1].start;
							if (val_len < 16)
							{
								memcpy(value, json_str + tokens[current_pos + 1].start, val_len);
								value[val_len] = '\0';
							}

							u8 val = (u8)(value[0] - '0');
							if (memcmp(key, "touchpad1", 9) == 0)
							{
								touchpad1_val = val;
							}
							else if (memcmp(key, "touchpad2", 9) == 0)
							{
								touchpad2_val = val;
							}
							else if (memcmp(key, "touchpad3", 9) == 0)
							{
								touchpad3_val = val;
							}
							current_pos += 2;
						}
						else
						{
							current_pos++;
						}
					}
					else
					{
						current_pos++;
					}
				}

				tlkapi_printf("[TP] %d %d %d\r\n", touchpad1_val, touchpad2_val, touchpad3_val);
                handle_event(touchpad1_val, touchpad2_val, touchpad3_val);
			}
		}
	}
	return 0;
}

void handle_event( u8 touchpad1_val,u8 touchpad2_val,u8 touchpad3_val){
    if(touchpad1_val == 1){
        led_on(LED_PAD_1);
    }else if(touchpad1_val == 0){
        led_off(LED_PAD_1);
    }else{
        return;
    }

    if(touchpad2_val == 1){
        led_on(LED_PAD_2);
    }else if(touchpad2_val == 0){
        led_off(LED_PAD_2);
    }else{
        return;
    }

    if(touchpad3_val == 1){
        led_on(LED_PAD_3);
    }else if(touchpad3_val == 0){
        led_off(LED_PAD_3);
    }else{
        return;
    }
}

void touchpad_send_notify(u8 touchpad1_val, u8 touchpad2_val, u8 touchpad3_val)
{
	if(blc_ll_getCurrentState() != BLS_LINK_STATE_CONN) {
		tlkapi_printf(DEBUG_TOUCHPAD,"[TP] Not connected, cannot send notify\r\n");
		return;
	}	
	if(touchpadNotifyCCC[0] == 0 && touchpadNotifyCCC[1] == 0) {
		tlkapi_printf(DEBUG_TOUCHPAD,"[TP] CCC not enabled: [0]=0x%02x, [1]=0x%02x\r\n", touchpadNotifyCCC[0], touchpadNotifyCCC[1]);
		return; 
	}
	if(touchpadNotifyCCC[0] != 0x01) {
		tlkapi_printf(DEBUG_TOUCHPAD,"[TP] Notify not enabled: CCC[0]=0x%02x \r\n", touchpadNotifyCCC[0]);
		return;
	}
	char json_buf[128];
	memset(json_buf, 0, sizeof(json_buf));
	json_buf[0] = '{';
	json_buf[1] = '"';
	json_buf[2] = 't';
	json_buf[3] = '1';
	json_buf[4] = '"';
	json_buf[5] = ':';
	json_buf[6] = '0' + touchpad1_val;
	json_buf[7] = ',';
	json_buf[8] = '"';
	json_buf[9] = 't';
	json_buf[10] = '2';
	json_buf[11] = '"';
	json_buf[12] = ':';
	json_buf[13] = '0' + touchpad2_val;
	json_buf[14] = ',';
	json_buf[15] = '"';
	json_buf[16] = 't';
	json_buf[17] = '3';
	json_buf[18] = '"';
	json_buf[19] = ':';
	json_buf[20] = '0' + touchpad3_val;
	json_buf[21] = '}';
	json_buf[22] = '\0';
	
	int len = 21;  
	u8 ret = blc_gatt_pushHandleValueNotify(BLS_CONN_HANDLE, 0x0012, (u8 *)json_buf, len);
	if(ret != BLE_SUCCESS) {
		tlkapi_printf(DEBUG_TOUCHPAD,"[TP] Notify failed: ret=0x%02x\r\n", ret);
	} else {
		tlkapi_printf(DEBUG_TOUCHPAD,"[TP] Notify sent successfully\r\n");
	}
}
