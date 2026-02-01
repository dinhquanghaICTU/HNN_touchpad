#ifndef __HARDWARE_H__      
#define __HARDWARE_H__

#include "tl_common.h"

#define MAX_TOUCHPAD      3
#define TOUCHPAD_IDLE     0
#define TOUCHPAD_ACTIVE   1

#define TOUCHPAD_1        GPIO_PB4
#define TOUCHPAD_2        GPIO_PB5
#define TOUCHPAD_3        GPIO_PB6

#define LED_STT           GPIO_PD4   // GREEN
#define LED_PAD_1         GPIO_PC1
#define LED_PAD_2         GPIO_PC4   // RED
#define LED_PAD_3         GPIO_PD2



void hnn_btn_init(u32 pin);
u32 hnn_read_gpio_btn(u32 pin);
void hnn_hardware_init(void);

#endif // __HARDWARE_H__