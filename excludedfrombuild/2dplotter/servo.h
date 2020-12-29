#ifndef _SERVO_H_
#define _SERVO_H_

/*file servo.h*/
#include "common_inc.h"

/* CONFIG AREA */

/* timer14
 * PINs: 	CC1 PA7
*/
#define SERVO_REG							TIM14

typedef enum {
	SERVO_MOVE_0DEG,
	SERVO_MOVE_90DEG,
	SERVO_MOVE_180DEG,
	SERVO_MOVE_INVALID
} servo_movement_t;

extern void servo_init(void);
extern void servo_move(servo_movement_t move);
extern void servo_test(void);

#endif /*_SERVO_H_*/
