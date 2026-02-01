#ifndef __M_LED_H__
#define __M_LED_H__

#include "../../hardware/hardware.h"

void led_on(u32 pin);
void led_off(u32 pin);
void led_togle(u32 pin);
u8 led_get_state(u32 pin);

#endif // __M_LED_H__
