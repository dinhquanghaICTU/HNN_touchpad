#include "hardware.h"
#include "drivers.h"
#include "tl_common.h"
#include "../middle/led/m_led.h"
#include "../middle/button/m_button.h"
#include "../HNN_config.h"

void hnn_led_init(void){
    gpio_set_func(LED_STT, AS_GPIO);
    gpio_set_output_en(LED_STT, 1);
    gpio_write(LED_STT, 0); 

    gpio_set_func(LED_PAD_1, AS_GPIO);
    gpio_set_output_en(LED_PAD_1, 1);
    gpio_write(LED_PAD_1, 0); 

    gpio_set_func(LED_PAD_2, AS_GPIO);
    gpio_set_output_en(LED_PAD_2, 1);
    gpio_write(LED_PAD_2, 0); 

    gpio_set_func(LED_PAD_3, AS_GPIO);
    gpio_set_output_en(LED_PAD_3, 1);
    gpio_write(LED_PAD_3, 0); 
}


void hnn_btn_init(u32 pin){
    gpio_set_func(pin, AS_GPIO);
    gpio_set_input_en(pin, 1);
    gpio_setup_up_down_resistor(pin, PM_PIN_PULLUP_10K);
}

u32 hnn_read_gpio_btn(u32 pin){
    return gpio_read(pin);  
}

void hnn_hardware_init(void){

    hnn_led_init();
    hnn_button_init();
}