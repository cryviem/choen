
#include "common_inc.h"
#include "dmacfg.h"
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
#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Counting clock: 168 MHz / (1679 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 1679;
#else
	/* Counting clock: 84 MHz / (839 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 839;
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

}


RetType stepper_mission_start(stepper_mission_t* mission)
{

	if (STEPPER_READY != mission->status)
	{
		return Ret_NotOK;
	}

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

	/* Update rate configuration */
#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Only advance timers support this feature*/
	TIM_REG->RCR = mission->update_rate;
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

	dma_transfer(DMA_HANDLER, (uint32_t)mission->data, mission->len);

	/* DIER reset value: 0x0000 */
	/* Enable CC1 DMA request*/
	TIM_REG->DIER |= TIM_DIER_CC2DE;

	/* Generate CC2 event to let DMA update register for the first time */
	TIM_REG->EGR |= TIM_EGR_CC2G;

	while (TIM_REG->EGR & TIM_EGR_CC2G); //wait for DMA update CCMR1 and CCMR2 finish

	/* Start counting */
	TIM_REG->CR1 |= TIM_CR1_CEN;
	print_text("stepper > mission start\n");
	mission->status = STEPPER_WORKING;
	return Ret_OK;
}

void stepper_status_check(stepper_mission_t* mission)
{
	dma_StatusEN dma_status;

	if (STEPPER_WORKING == mission->status)
	{
		dma_status = dma_getstatus(DMA_HANDLER);

		switch (dma_status)
		{
		case DMA_Status_NotStarted:
			/* Abnormal case */
			break;
		case DMA_Status_Triggered:
			break;
		case DMA_Status_InProcess:
			break;
		case DMA_Status_Error:
			print_text("stepper > dma error\n");
			TIM_REG->DIER &= (~TIM_DIER_CC2DE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			mission->status = STEPPER_ERROR;
			break;
		case DMA_Status_Completed:
			print_text("stepper > dma completed\n");
			TIM_REG->DIER &= (~TIM_DIER_CC2DE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			mission->status = STEPPER_IDLE;
			break;
		}
	}
	else if (STEPPER_ERROR == mission->status)
	{
		/* error treatment */
		mission->status = STEPPER_IDLE;
	}
}
