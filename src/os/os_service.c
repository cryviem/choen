
#include "ee.h"
#include "dmacfg.h"
#include "app_control.h"
#include "common_inc.h"
#include "uartcfg.h"

#if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED)
#include "port.h"

#define BUTTON_FILTERTIME						10

void prc_buttonstatus_v(void);
extern void timer_start(void);
extern void timer_start_dma(void);
#endif /* #if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED) */

extern void timer_status_check(void);

#define DIR_ON()					GPIOC->BSRRL |= 0x00000004
#define DIR_OFF()					GPIOC->BSRRH |= 0x00000004
#define DIR_TOGGLE()				GPIOC->ODR ^= 0x00000004

#define STEP_ON()					GPIOC->BSRRL |= 0x00000008
#define STEP_OFF()					GPIOC->BSRRH |= 0x00000008
#define STEP_TOGGLE()				GPIOC->ODR ^= 0x00000008

uint16_t counter = 0;
/* ISR */
ISR2(systick_handler)
{
	CounterTick(OSMainCounter);
}

/* task 2ms 
priority: 0xF0 --> lowest
 */
TASK(TaskOS_2ms)
{
	//counter++;
	LED_BLUE_BLINK();
	STEP_TOGGLE();
	//if (counter > )
}

/* task 5ms
priority: 0xFA --> highest
 */
TASK(TaskOS_5ms)
{
	dmaproc_updatestatus();
	uart_sts_update_task();
}

/* task 10ms
priority: 0xF9 --> second
 */
TASK(TaskOS_10ms)
{

#if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED)
	prc_buttonstatus_v();
#endif /* #if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED) */
	uart_main_task();

}

/* task 20ms 
priority: 0xF8 --> third
 */
TASK(TaskOS_20ms)
{

}

/* task 50ms 
priority: 0xF7 --> fourth
 */
TASK(TaskOS_50ms)
{

}

/* task 100ms 
priority: 0xF6 --> fifth
 */
TASK(TaskOS_100ms)
{

}

/* task 500ms 
priority: 0xF5 --> sixth
 */
TASK(TaskOS_500ms)
{
//	print_text("TEST LOG:\n");
//	print_num(-2536);
//	print_text("\n");
//	print_num(126536);
	//print_text("\n");
	//print_num(00126536);
	//print_text("\n");
	//print_num(-000126536);
}

void OS_initialize(void)
{
	EE_system_init();
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();

	SetRelAlarm(AlarmOS_2ms, 10, 6);
	SetRelAlarm(AlarmOS_5ms, 10, 5);
	SetRelAlarm(AlarmOS_10ms, 12, 10);
	SetRelAlarm(AlarmOS_20ms, 14, 20);
	SetRelAlarm(AlarmOS_50ms, 16, 50);
	SetRelAlarm(AlarmOS_100ms, 18, 100);
	SetRelAlarm(AlarmOS_500ms, 22, 500);

}

void OS_start(void)
{
	EE_systick_start();
}

#if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED)
void prc_buttonstatus_v(void)
{

	static uint8_t eventcnt;

	if (PORT_PIN_LEVEL_HIGH == Port_ReadPin(PORT_A_PIN_0))
	{
		eventcnt++;
	}
	else
	{
		eventcnt = 0;
	}

	if (eventcnt > BUTTON_FILTERTIME)
	{
		LED_RED_BLINK();
		DIR_TOGGLE();
		/* button pressed detected */
		eventcnt = 0;
	}

}
#endif /* #if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED) */
