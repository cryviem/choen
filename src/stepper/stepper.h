
#include "common_inc.h"

/* CONFIG AREA */

#define TIM_REG							TIM4

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
	uint16_t				data[STEPPER_MISSION_MAX_SIZE]
}stepper_mission_t;
