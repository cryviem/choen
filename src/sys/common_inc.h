#ifndef _COMMON_INC_H_
#define _COMMON_INC_H_

#include "stm32f4xx.h"
#include "print.h"

/* common values */
#define SYSCFG_NOT_USED										0
#define SYSCFG_USED											1

#define FALSE												((uint8_t)0)
#define TRUE												(!FALSE)

#ifndef NULL
#define NULL												((void*)0)
#endif

#define __IO												volatile

#define UNUSED(x) ((void)(x))

#define MIN(a, b)						(a <= b)? a:b
#define MAX(a, b)						(a >= b)? a:b

#define LED_GREEN_ON()					GPIOD->BSRRL |= 0x00001000
#define LED_GREEN_OFF()					GPIOD->BSRRH |= 0x00001000
#define LED_GREEN_BLINK()				GPIOD->ODR ^= 0x00001000

#define LED_ORANGE_ON()					GPIOD->BSRRL |= 0x00002000
#define LED_ORANGE_OFF()				GPIOD->BSRRH |= 0x00002000
#define LED_ORANGE_BLINK()				GPIOD->ODR ^= 0x00002000

#define LED_RED_ON()					GPIOD->BSRRL |= 0x00004000
#define LED_RED_OFF()					GPIOD->BSRRH |= 0x00004000
#define LED_RED_BLINK()					GPIOD->ODR ^= 0x00004000

#define LED_BLUE_ON()					GPIOD->BSRRL |= 0x00008000
#define LED_BLUE_OFF()					GPIOD->BSRRH |= 0x00008000
#define LED_BLUE_BLINK()				GPIOD->ODR ^= 0x00008000

typedef enum {
	Ret_NotOK,
	Ret_OK
} RetType;

extern void pf_memset(void *s, uint8_t c, uint16_t n);
extern void pf_memcpy(void *des, void *src, uint16_t n);
extern uint16_t pf_strlen(uint8_t *str);

#endif /* _COMMON_INC_H_ */
