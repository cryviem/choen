#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "common_inc.h"

/* CONFIG AREA */

#define MISSION_POOL_SIZE					2

typedef enum {
	STEP_NONE,
	STEP_FORWARD,
	STEP_BACKWARD
} step_t;

typedef enum {
	CMD_IDLE,
	CMD_CALCULATING,
	CMD_MOVING,
} cmd_status_t;

#endif /*_MOVEMENT_H_*/
