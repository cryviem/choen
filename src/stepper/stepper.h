#ifndef _STEPPER_H_
#define _STEPPER_H_

#include "common_inc.h"

/* CONFIG AREA */

#define	TIMER_TYPE_BASIC				0
#define	TIMER_TYPE_ADVANCED				1
#define	TIMER_TYPE						TIMER_TYPE_ADVANCED

#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
#define TIM_REG							TIM1
#define DMA_HANDLER						DMA_HANDLER_TIM4CH1
#else
#define TIM_REG							TIM4
#define DMA_HANDLER						DMA_HANDLER_TIM4CH1
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

#define STEPPER_MISSION_MAX_SIZE					2048
/* ---------------- */


typedef enum {
	SPEED_0,
	SPEED_1,
	SPEED_2,
	SPEED_3,
	SPEED_4,
	SPEED_INVALID
}stepper_speed_t;

typedef enum {
	SM_IDLE,
	SM_WORKING,
	SM_ERROR
}state_machine_t;




#endif /*_STEPPER_H_*/
