
#include "stepper.h"
#include "common_inc.h"
#include "port.h"

/* General configuration*/

void stepper_init(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	STEPPER_REG->CR1 |= TIM_CR1_ARPE;

	/* CR2 reset value: 0x0000 */

	/* Set counting clock to 100 kHz */
	/* Counting clock: 84 MHz / (839 + 1) = 100 kHz T = 10 us*/
	STEPPER_REG->PSC = 839;

	/* Set control frequency: 200 Hz -> T = 5 ms*/
	STEPPER_REG->ARR = 500;

	/* Starting duty 1 ms --> 0 deg*/
	STEPPER_REG->CCR1 = 2;

	/* CCMR1 reset value: 0x0000 */
	/* set channel to PWM1 */
	STEPPER_REG->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE);

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	STEPPER_REG->CCER |= TIM_CCER_CC1E;

	STEPPER_REG->EGR |= TIM_EGR_UG;
	//while (STEPPER_REG->EGR & TIM_EGR_UG);

	/* Start counting */
	STEPPER_REG->CR1 |= TIM_CR1_CEN;
}

static void increase_f(void)
{

	STEPPER_REG->ARR -= 20;
}

static void decrease_f(void)
{
	STEPPER_REG->ARR += 20;
}

void stepper_event(void)
{
	uint32_t tmp;

	if (PORT_PIN_LEVEL_HIGH == Port_ReadPin(PORT_A_PIN_4))
	{
		increase_f();
	}
	else
	{
		decrease_f();
	}

	tmp = (uint32_t)100000 / STEPPER_REG->ARR;

	print_num(tmp);
}

