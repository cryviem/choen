
#include "common_inc.h"
#include "stepper.h"

/* Mapping
CC1			X_axis step
CC2			X_axis direction		+ 		update trigger
CC3			Y_axis step
CC4			Y_axis direction
*/

/* General configuration*/
void stepper_init(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	TIM_REG->CR1 |= TIM_CR1_ARPE;

	/* CR2 reset value: 0x0000 */

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	TIM_REG->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

	/* DCR reset value: 0x0000 */
	/* Set DBA to 6 (00110), start from CCMR1*/
	/* Set DBL to 0 (00001), 2 transfer*/
	TIM_REG->DCR |= (TIM_DCR_DBL_0 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1);

	/* Set counting clock to 100 kHz */
#if ((TIM_REG == TIM1) || (TIM_REG == TIM8))
	/* Counting clock: 168 MHz / (1679 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 1679;
#else
	/* Counting clock: 84 MHz / (839 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 839;
#endif

}


RetType stepper_mission_start(stepper_mission_t* mission)
{

	/* Speed configuration */
	switch (mission->speed)
	{
	case SPEED_0:
		/* 10 Hz */
		TIM_REG->ARR = 10000;
		TIM_REG->CCR1 = 50;
		TIM_REG->CCR2 = 5000;
		TIM_REG->CCR3 = 50;
		TIM_REG->CCR4 = 5000;
		break;
	case SPEED_1:
		/* 20 Hz */
		TIM_REG->ARR = 5000;
		TIM_REG->CCR1 = 50;
		TIM_REG->CCR2 = 2500;
		TIM_REG->CCR3 = 50;
		TIM_REG->CCR4 = 2500;
		break;
	case SPEED_2:
		/* 100 Hz */
		TIM_REG->ARR = 1000;
		TIM_REG->CCR1 = 50;
		TIM_REG->CCR2 = 500;
		TIM_REG->CCR3 = 50;
		TIM_REG->CCR4 = 500;
		break;
	case SPEED_3:
		/* 200 Hz */
		TIM_REG->ARR = 500;
		TIM_REG->CCR1 = 50;
		TIM_REG->CCR2 = 250;
		TIM_REG->CCR3 = 50;
		TIM_REG->CCR4 = 250;
		break;
	case SPEED_4:
		/* 1000 Hz */
		TIM_REG->ARR = 100;
		TIM_REG->CCR1 = 50;
		TIM_REG->CCR2 = 50;
		TIM_REG->CCR3 = 50;
		TIM_REG->CCR4 = 50;
		break;
	default:
		break;
	}



	dma_transfer(DMA_HANDLER_TIM4CH1, (uint32_t)&cfg_data, 10);

	/* DIER reset value: 0x0000 */
	/* Enable CC1 DMA request*/
	reg->DIER |= TIM_DIER_CC1DE;

	/* Generate CC2 event to let DMA update register for the first time */

	/* Start counting */
	reg->CR1 |= TIM_CR1_CEN;
	print_text("timer dma start\n");
}
