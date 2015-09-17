#ifndef __RUAN_APP_MAIN_HEAD
#define __RUAN_APP_MAIN_HEAD

#define DEBUG_APP 1
#define log(format, ...) if( DEBUG_APP ) printf(format, ## __VA_ARGS__)

#define RADIO_USART_ID usart2_id
#define COPTER_USART_ID usart1_id
#define SBUS_USART_ID usart3_id

#endif
