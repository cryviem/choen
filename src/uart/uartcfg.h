#ifndef _UARTCFG_H_
#define _UARTCFG_H_

#include "common_inc.h"

typedef enum {
	UART_HANDLER_1,
	UART_HANDLER_INVALID
} uart_handler_id_en;


extern void uart_init(void);
extern void uart_start(void);
extern void uart_main_task(void);
extern void uart_sts_update_task(void);

#endif	/*_UARTCFG_H_*/
