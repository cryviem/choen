#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

/*file movement.h*/
#include "common_inc.h"

/* 1 step = 0.2 mm*/
#define RESLUTION						1/5

#define	X_AXIS_LIMIT_MM					240
#define	Y_AXIS_LIMIT_MM					240

#define	X_AXIS_LIMIT_STEP				(X_AXIS_LIMIT_MM/RESLUTION)
#define	Y_AXIS_LIMIT_STEP				(Y_AXIS_LIMIT_MM/RESLUTION)

typedef struct {
	uint16_t	x_pos;
	uint16_t	y_pos;
} xy_position_t;

/* CONFIG AREA */
extern void stepper_test(void);

#endif /*_MOVEMENT_H_*/
