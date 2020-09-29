
#include "dmacfg.h"
#include "common_inc.h"

/* test on timer 2*/
/* clock source 84 MHz*/
/* AF pin table */
/*
				TIM2
TIM2_CH1: PA15
TIM2_CH2:	PA1, PB3
TIM2_CH3:	PA2, PB10
TIM2_CH4: PA3, PB11

TIM2_ETR: PA15
TIM2_CH1_ETR: PA0, PA5
*/

/*
				TIM4
TIM4_CH1: 	PD12
TIM4_CH2:	PD13
TIM4_CH3:	PD14
TIM4_CH4: 	PD15
*/

typedef enum {
	TIM_STOPPED,
	TIM_RUNNING
}timer_state_en;

timer_state_en tim_sts = TIM_STOPPED;

TIM_TypeDef * const reg = (TIM_TypeDef*)TIM4_BASE;

uint16_t cfg_data[10] = {0x6848, 0x6848, 0x7848, 0x7848, 0x7848, 0x6858, 0x6858, 0x6858, 0x6858, 0x6858};

void timer_start(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	reg->CR1 |= TIM_CR1_ARPE;
	
	/* CR2 reset value: 0x0000 */
	
	/* Prescale, make timer run at lowest frequency to easy debug */
	/* Counting clock: 84 MHz / (65535 + 1) = 1281 Hz T = 0.7802 ms*/
	//reg->PSC = 65535;
	/* Counting clock: 84 MHz / (41999 + 1) = 2000 Hz T = 0.5 ms*/
	reg->PSC = 41999;
	
	/* ARR, use full range for easy debug*/
	
	/* To count 20000, take 10s*/
	reg->ARR = 20000;

	/* CCMR1 reset value: 0x0000 */
	/* Set OC1PE to 1*/
	reg->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);

	/* Set OC1M to 110: PWM1, Active as long as CNT < CCR1 */
	reg->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	
	/* CCR1 set to 50% of ARR: 10000*/
	/* Expect to have 50% pulse at the begin of cycle */
	reg->CCR1 = 10000;
	reg->CCR2 = 15000;
	
	/* consider if we have to set UG bit and wait it clear to update register */
	
	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	reg->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);
	
	/* Start counting */
	reg->CR1 |= TIM_CR1_CEN;
}

void timer_start_dma(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	reg->CR1 |= TIM_CR1_ARPE;

	/* CR2 reset value: 0x0000 */

	/* Counting clock: 84 MHz / (65535 + 1) = 1281 Hz T = 0.7802 ms*/
	//reg->PSC = 65535;
	/* Counting clock: 84 MHz / (41999 + 1) = 2000 Hz T = 0.5 ms*/
	reg->PSC = 41999;

	/* To count 20000, take 10s*/
	reg->ARR = 20000;

	/* CCR1 set to 50% of ARR: 10000, use for DMA update data*/
	/* Expect to have 50% pulse at the begin of cycle */
	reg->CCR1 = 10000;

	/* CCR1 set to 25% of ARR: 10000, use for pulse output*/
	reg->CCR2 = 5000;

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	reg->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

	/* CCMR1 reset value: 0x0000 */
	/* Set OC1PE to 1*/
	reg->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE);

	/* Set OC1M to 100: Force Low, by default */
	/* Set OC2M to 110: PWM1, Active as long as CNT < CCR2 */
	reg->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);

	/* DCR reset value: 0x0000 */
	/* Set DBA to 6 (00110), start from CCMR1*/
	/* Set DBL to 0 (00000), 1 transfer*/
	reg->DCR |= (TIM_DCR_DBA_2 | TIM_DCR_DBA_1);

	dma_transfer(DMA_HANDLER_TIM4CH1, (uint32_t)&cfg_data, 10);

	/* DIER reset value: 0x0000 */
	/* Enable CC1 DMA request*/
	reg->DIER |= TIM_DIER_CC1DE;

	/* Start counting */
	reg->CR1 |= TIM_CR1_CEN;
	tim_sts = TIM_RUNNING;
	print_text("timer dma start\n");
}

void timer_status_check(void)
{
	dma_StatusEN dma_status;

	if (TIM_RUNNING == tim_sts)
	{
		dma_status = dma_getstatus(DMA_HANDLER_TIM4CH1);

		switch (dma_status)
		{
		case DMA_Status_NotStarted:
			break;
		case DMA_Status_Triggered:
			break;
		case DMA_Status_InProcess:
			break;
		case DMA_Status_Error:
			//LED_RED_BLINK();
			reg->DIER &= (~TIM_DIER_CC1DE);
			reg->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER_TIM4CH1);
			break;
		case DMA_Status_Completed:

			reg->DIER &= (~TIM_DIER_CC1DE);
			reg->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER_TIM4CH1);
			break;
		}
	}
}
