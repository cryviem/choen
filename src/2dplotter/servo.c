
#include "servo.h"

#include "common_inc.h"

/* General configuration*/

const uint16_t move_table[SERVO_MOVE_INVALID] =
{
		100,	/* 0 deg */
		150,	/* 90 deg */
		200		/* 180 deg */
};

void servo_init(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	SERVO_REG->CR1 |= TIM_CR1_ARPE;

	/* CR2 reset value: 0x0000 */

	/* Set counting clock to 100 kHz */
	/* Counting clock: 84 MHz / (839 + 1) = 100 kHz T = 10 us*/
	SERVO_REG->PSC = 839;

	/* Set control frequency: 50 Hz -> T = 20 ms*/
	SERVO_REG->ARR = 2000;

	/* Starting duty 1 ms --> 0 deg*/
	SERVO_REG->CCR1 = 100;

	/* CCMR1 reset value: 0x0000 */
	/* set channel to PWM1 */
	SERVO_REG->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE);

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	SERVO_REG->CCER |= TIM_CCER_CC1E;

	SERVO_REG->EGR |= TIM_EGR_UG;
	//while (SERVO_REG->EGR & TIM_EGR_UG);

	/* Start counting */
	SERVO_REG->CR1 |= TIM_CR1_CEN;
}

void servo_move(servo_movement_t move)
{
	if (move < SERVO_MOVE_INVALID)
	{
		SERVO_REG->CCR1 = move_table[move];
	}
}

void servo_test(void)
{
	static uint8_t state = 0;

	if (state == 1)
	{
		servo_move(SERVO_MOVE_90DEG);
		state = 2;
	}
	else if (state == 2)
	{
		servo_move(SERVO_MOVE_180DEG);
		state = 0;
	}
	else
	{
		servo_move(SERVO_MOVE_0DEG);
		state = 1;
	}
}
