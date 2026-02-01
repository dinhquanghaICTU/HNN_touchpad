#ifndef __APP_TOUCHPAD_H__  
#define __APP_TOUCHPAD_H__

#include "tl_common.h"


int touchpadwritehandle(void *p);
void handle_event( u8 touchpad1_val,u8 touchpad2_val,u8 touchpad3_val);
void touchpad_send_notify(u8 touchpad1_val, u8 touchpad2_val, u8 touchpad3_val);

#endif // __APP_TOUCHPAD_H__
