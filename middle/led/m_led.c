
#include "m_led.h"
#include "drivers.h"      
#include "tl_common.h"

#define MAX_LED_STATES 8
static u8 led_states[MAX_LED_STATES] = {0};
static u32 led_pins[MAX_LED_STATES] = {0};
static u8 led_count = 0;

static u8 find_led_index(u32 pin) {
    for (u8 i = 0; i < led_count; i++) {
        if (led_pins[i] == pin) return i;
    }
    if (led_count < MAX_LED_STATES) {
        led_pins[led_count] = pin;
        return led_count++;
    }
    return 0;
}

void led_on(u32 pin){
    gpio_set_output_en(pin, 1);
    gpio_write(pin, 1);
    led_states[find_led_index(pin)] = 1;
}

void led_off(u32 pin){
    gpio_set_output_en(pin, 1);
    gpio_write(pin, 0);
    led_states[find_led_index(pin)] = 0;
}

void led_togle(u32 pin){
    gpio_set_output_en(pin, 1);
    u8 idx = find_led_index(pin);
    led_states[idx] = !led_states[idx];
    gpio_write(pin, led_states[idx]);
}


u8 led_get_state(u32 pin){
    u8 idx = find_led_index(pin);
    if(idx < led_count) {
        return led_states[idx];
    }
    return 0;
}