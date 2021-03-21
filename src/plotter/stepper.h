#ifndef _STEPPER_H_
#define _STEPPER_H_

/*file servo.h*/
#include "common_inc.h"

/* CONFIG AREA */

/* timer14
 * PINs: 	CC1 PA7
*/
#define STEPPER_REG							TIM14

extern void stepper_init(void);
extern void stepper_event(void);


#endif /*_STEPPER_H_*/
