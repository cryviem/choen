#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

/*file movement.h*/
#include "common_inc.h"
#include "stepper.h"

/* 1 step = 0.2 mm*/
#define RESLUTION						1/5

#define	X_AXIS_LIMIT_MM					240
#define	Y_AXIS_LIMIT_MM					240

#define	X_AXIS_LIMIT_STEP				(X_AXIS_LIMIT_MM/RESLUTION)
#define	Y_AXIS_LIMIT_STEP				(Y_AXIS_LIMIT_MM/RESLUTION)

#define MOVE_FORWARD(x)					(x == TRUE)? STEP_FORWARD:STEP_NONE
#define MOVE_BACKWARD(x)				(x == TRUE)? STEP_BACKWARD:STEP_NONE
#define MOVE_REVERSE(x)					(x == STEP_FORWARD)? STEP_BACKWARD:((x == STEP_BACKWARD)? STEP_FORWARD:STEP_NONE)

typedef struct {
	uint16_t	x;
	uint16_t	y;
} xy_position_t;

typedef struct {
	step_t	step_x;
	step_t	step_y;
} xy_step_t;

typedef enum {
	CMD_PEN_UP,
	CMD_PEN_DOWN,
	CMD_MOVE,
	CMD_LINE,
	CMD_CWARC,
	CMD_CCWARC,
	CMD_INVALID
} cmd_id_t;

typedef enum {
	CMD_STS_IDLE,
	CMD_STS_CALCULATING,
	CMD_STS_ERROR
} cmd_sts_t;

typedef struct {
	cmd_sts_t	status;
	cmd_id_t	cmd;
	int16_t		X;
	int16_t		Y;
	int16_t		I;
	int16_t		J;
	int16_t		F;
} cmd_t;

/* CONFIG AREA */
extern void stepper_test(void);

#endif /*_MOVEMENT_H_*/
