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
	STEPPER_IDLE,
	STEPPER_READY,
	STEPPER_WORKING,
	STEPPER_ERROR
}stepper_status_t;

typedef struct {
	stepper_status_t		status;
	stepper_speed_t			speed;
	uint8_t					update_rate;
	uint16_t				data[STEPPER_MISSION_MAX_SIZE];
	uint16_t				len;
}stepper_mission_t;

#endif /*_STEPPER_H_*/
