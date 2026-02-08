
#include "../led/m_led.h"
#include "tlkapi_debug.h"
#include "../../hardware/hardware.h"
#include "../../third_party/lib_button/app_btn.h"
#include "../../HNN_config.h"
#include "../../app/app_touchpad.h"
#include "../../app/app.h"

extern void hnn_btn_init(u32 pin); 
extern u32 hnn_read_gpio_btn(u32 pin);


uint8_t g_btn_filter_cnt;


static void on_btn_pressed(int pin, int evt, void *user);
static void on_btn_released(int pin, int evt, void *user);

static uint32_t hnn_get_tick_ms(void)
{
    return clock_time() / SYSTEM_TIMER_TICK_1MS;
}

static app_btn_hw_config_t s_btn_hw[] = {
    { TOUCHPAD_1, TOUCHPAD_ACTIVE, TOUCHPAD_ACTIVE, 0, 0 },  
    { TOUCHPAD_2, TOUCHPAD_ACTIVE, TOUCHPAD_ACTIVE, 0, 0 },
    { TOUCHPAD_3, TOUCHPAD_ACTIVE, TOUCHPAD_ACTIVE, 0, 0 },
};


void hnn_button_init(void)
{
    g_btn_filter_cnt = 3;
    app_btn_config_t cfg = {
        .config        = s_btn_hw,
        .btn_count     = sizeof(s_btn_hw)/sizeof(s_btn_hw[0]),  
        .get_tick_cb   = hnn_get_tick_ms,
        .btn_initialize = (app_btn_initialize_cb)hnn_btn_init,
        .btn_read       = (app_btn_get_level_cb)hnn_read_gpio_btn,
    };

    app_btn_initialize(&cfg);
    app_btn_register_callback(APP_BTN_EVT_PRESSED,  on_btn_pressed,  NULL);
    app_btn_register_callback(APP_BTN_EVT_RELEASED, on_btn_released, NULL);
}

static void on_btn_pressed(int pin, int evt, void *user)
{
    (void)evt; (void)user;
    u8 touchpad1_val = 0;
    u8 touchpad2_val = 0;
    u8 touchpad3_val = 0;

    if (pin == TOUCHPAD_1) {
        tlkapi_printf(DEBUG_TOUCHPAD, "TOUCHPAD_1\r\n");
        led_togle(LED_PAD_1);
        touchpad1_val = 1;  
    } else if (pin == TOUCHPAD_2) {
        // tlkapi_printf(DEBUG_TOUCHPAD, "Ota new======================================================\r\n");
        tlkapi_printf(DEBUG_TOUCHPAD, " TOUCHPAD_2\r\n");
        led_togle(LED_PAD_2);
        touchpad2_val = 1;  
    } else if (pin == TOUCHPAD_3) {
        tlkapi_printf(DEBUG_TOUCHPAD, " TOUCHPAD_3\r\n");
        led_togle(LED_PAD_3);
        touchpad3_val = 1;  
    } else {
        return;  
    }
   


     #if (UNCLOCK_ADV_RUNTILE)
        u8 led1 = led_get_state(LED_PAD_1);
        u8 led2 = led_get_state(LED_PAD_2);
        u8 led3 = led_get_state(LED_PAD_3);
        update_adv_data_with_runtitle(led1, led2, led3);
        touchpad_send_notify(led1, led2, led3);
    #endif
}

static void on_btn_released(int pin, int evt, void *user)
{
    (void)evt; (void)user;
    u8 touchpad1_val = 0;
    u8 touchpad2_val = 0;
    u8 touchpad3_val = 0;

    if (pin == TOUCHPAD_1) {
        touchpad1_val = 0;  
    } else if (pin == TOUCHPAD_2) {
        touchpad2_val = 0;  
    } else if (pin == TOUCHPAD_3) {
        touchpad3_val = 0;  
    } else {
        return;  
    }
    // touchpad_send_notify(touchpad1_val, touchpad2_val, touchpad3_val);
    // #if (UNCLOCK_ADV_RUNTILE)
    //     u8 led1 = led_get_state(LED_PAD_1);
    //     u8 led2 = led_get_state(LED_PAD_2);
    //     u8 led3 = led_get_state(LED_PAD_3);
    //     update_adv_data_with_runtitle(touchpad1_val, touchpad2_val, touchpad3_val);
    // #endif
}

void hnn_button_poll(void)
{
    app_btn_scan(NULL);
}
