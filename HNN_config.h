
#ifndef __HNN_CONFIG_H__

#define __HNN_CONFIG_H__

#define DEBUG_TOUCHPAD   1   
#define UNCLOCK_ADV_RUNTILE 1 


#define SET_ADV_3S  1


#if DEBUG_TOUCHPAD
    #define TP_DBG(fmt, ...)  tlkapi_printf(APP_LOG_EN, "[TP] " fmt "\n", ##__VA_ARGS__)
#else
    #define TP_DBG(fmt, ...)  do{}while(0)
#endif



#endif // __HNN_CONFIG_H__