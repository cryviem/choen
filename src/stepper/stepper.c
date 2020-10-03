
#include "common_inc.h"
#include "dmacfg.h"
#include "stepper.h"

/* Mapping
CC1			X_axis step
CC2			X_axis direction		+ 		update trigger
CC3			Y_axis step
CC4			Y_axis direction
*/

state_machine_t sm_state = SM_IDLE;
mission_pool_t mission_pool = {0};

void stepper_mission_start(mission_t* mission);
mission_t* get_ready_mission(void);
void on_mission_completed(void);


/* General configuration*/
void stepper_init(void)
{
	/* CR1 reset value: 0x0000 */
	/* Enable auto reload the ARR register*/
	TIM_REG->CR1 |= TIM_CR1_ARPE;

	/* CR2 reset value: 0x0000 */

	//TIM_REG->CCMR1 = 0x4848;
	//TIM_REG->CCMR2 = 0x4848;

	TIM_REG->CCMR1 = 0x4848;
	TIM_REG->CCMR2 = 0x4848;



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
	//TIM_REG->PSC = 839;
	TIM_REG->PSC = 8399;	//T = 100 us for test purpose
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/



	pf_memset(&mission_pool, 0, sizeof(mission_pool));

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	TIM_REG->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);
	//TIM_REG->CCER |= (TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P | TIM_CCER_CC4P);
}

void stepper_mission_start(mission_t* mission)
{
	/* Speed configuration */
	switch (mission->speed)
	{
	case SPEED_0:
		/* 10 Hz */
		TIM_REG->ARR = 10000;
		TIM_REG->CCR2 = 5000;
		TIM_REG->CCR4 = 5000;
		break;
	case SPEED_1:
		/* 20 Hz */
		TIM_REG->ARR = 5000;
		TIM_REG->CCR2 = 2500;
		TIM_REG->CCR4 = 2500;
		break;
	case SPEED_2:
		/* 100 Hz */
		TIM_REG->ARR = 1000;
		TIM_REG->CCR2 = 500;
		TIM_REG->CCR4 = 500;
		break;
	case SPEED_3:
		/* 200 Hz */
		TIM_REG->ARR = 500;
		TIM_REG->CCR2 = 250;
		TIM_REG->CCR4 = 250;
		break;
	case SPEED_4:
		/* 1000 Hz */
		TIM_REG->ARR = 100;
		TIM_REG->CCR2 = 50;
		TIM_REG->CCR4 = 50;
		break;
	default:
		break;
	}

	TIM_REG->CCR1 = TIM_REG->ARR - STEPPER_STEP_ZISE;
	TIM_REG->CCR3 = TIM_REG->ARR - STEPPER_STEP_ZISE;

	//TIM_REG->CCMR1 = 0x4848;
	//TIM_REG->CCMR2 = 0x4848;

	/* Update rate configuration */
#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Only advance timers support this feature*/
	TIM_REG->RCR = mission->upd_rate;
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/
	dma_transfer(DMA_HANDLER, (uint32_t)mission->data, mission->actsize);

	/* DIER reset value: 0x0000 */
	/* Enable CC2 DMA request*/
	TIM_REG->DIER |= TIM_DIER_CC2DE;

	/* Generate CC2 event to let DMA update register for the first time */
	TIM_REG->EGR |= TIM_EGR_CC2G;

	while (TIM_REG->EGR & TIM_EGR_CC2G); //wait for DMA update CCMR1 and CCMR2 finish

	/* Start counting */
	TIM_REG->CR1 |= TIM_CR1_CEN;
}

void stepper_task(void)
{
	dma_StatusEN dma_status;
	mission_t* mission_ptr = NULL;
	static uint8_t debug = 0;

	switch (sm_state)
	{
	case SM_IDLE:
		/*looking for new mission come*/
		mission_ptr = get_ready_mission();

		if (NULL != mission_ptr)
		{

			stepper_mission_start(mission_ptr);
			print_text("stepper > mission start\n");
			sm_state = SM_WORKING;
		}
		break;

	case SM_WORKING:
		/*monitor dma work*/
		dma_status = dma_getstatus(DMA_HANDLER);

		switch (dma_status)
		{
		case DMA_Status_Error:
			LED_RED_BLINK();
			print_text("stepper > dma error\n");
			TIM_REG->DIER &= (~TIM_DIER_CC2DE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			sm_state = SM_ERROR;
			break;
		case DMA_Status_Completed:
			print_text("stepper > dma completed\n");
			TIM_REG->DIER &= (~TIM_DIER_CC2DE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			on_mission_completed();
			sm_state = SM_IDLE;
			break;
		case DMA_Status_InProcess:
			debug++;
			if (debug > 100)
			{
				print_num(dma_getNDTR(DMA_HANDLER));
				print_text("\n");
				debug = 0;
			}
			break;
		default:
			//DMA_Status_NotStarted
			//DMA_Status_Triggered
			//DMA_Status_InProcess

			break;
		}
		break;
	case SM_ERROR:
		/* temporary solution: abort the current, continue the next one*/
		on_mission_completed();
		sm_state = SM_IDLE;

		break;
	}
}

mission_t* get_ready_mission(void)
{
	uint8_t tmp;

	if (mission_pool.rd_sts != STS_IDLE)
	{
		/* last read process hasn't been done */
		return NULL;
	}

	if (mission_pool.rptr ==  mission_pool.wptr)
	{
		/* nothing new */
		return NULL;
	}

	tmp = mission_pool.rptr + 1;
	if (tmp >= STEPPER_NUM_OF_MISSIONS)
	{
		tmp = 0;
	}

	if ((tmp == mission_pool.wptr) && (mission_pool.wr_sts == STS_BUSY))
	{
		/*write process are ongoing on this buff*/
		print_text("ringbuff rd on wrbusy\n");
		return NULL;
	}

	mission_pool.rptr = tmp;
	mission_pool.rd_sts = STS_BUSY;

	return &mission_pool.mission[tmp];
}

void on_mission_completed(void)
{
	if (mission_pool.rd_sts != STS_BUSY)
	{
		/*unexpected behavior*/
		return;
	}
	LED_GREEN_BLINK();
	mission_pool.rd_sts = STS_IDLE;
}

RetType find_idle_mission(void)
{
	uint8_t tmp;

	if (mission_pool.wr_sts != STS_IDLE)
	{
		/* last write process hasn't been done */
		print_text("ringbuff wr busy\n");
		return Ret_NotOK;
	}

	tmp = mission_pool.wptr + 1;
	if (tmp >= STEPPER_NUM_OF_MISSIONS)
	{
		tmp = 0;
	}

	if (tmp ==  mission_pool.rptr)
	{
#if (1)	/* currently, Over-write is prohibited*/
		print_text("ringbuff full\n");
		return Ret_NotOK;
	}
#else	/*  */
		if (mission_pool.rd_sts != STS_IDLE)
		{
			/* read process is going on this frame --> ignore overwrite*/
			mission = NULL;
			return Ret_NotOK;
		}
		/* The oldest unread cell will be overwrite by new data, then move read pointer to next cell*/
		mission_pool.rptr = tmp + 1;
		if (mission_pool.rptr >= STEPPER_NUM_OF_MISSIONS)
		{
			mission_pool.rptr = 0;
		}
	}
#endif

	mission_pool.wptr = tmp;
	mission_pool.mission[tmp].actsize = 0;
	mission_pool.mission[tmp].speed = SPEED_0;
	mission_pool.mission[tmp].upd_rate = 0;
	mission_pool.wr_sts = STS_BUSY;
	return Ret_OK;
}

mission_t* get_opened_mission(void)
{

	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return NULL;
	}

	return &mission_pool.mission[mission_pool.wptr];
}

RetType append_data_to_mission(uint16_t data)
{
	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return Ret_NotOK;
	}

	if (mission_pool.mission[mission_pool.wptr].actsize > (STEPPER_MISSION_MAX_SIZE - 1))
	{
		/* buffer is full */
		return Ret_NotOK;
	}

	mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = data;
	mission_pool.mission[mission_pool.wptr].actsize++;
	return Ret_OK;
}

RetType set_speed_for_mission(speed_t speed)
{
	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return Ret_NotOK;
	}

	mission_pool.mission[mission_pool.wptr].speed = speed;

	return Ret_OK;
}

RetType set_upd_rate_for_mission(uint8_t update_rate)
{
	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return Ret_NotOK;
	}

	mission_pool.mission[mission_pool.wptr].upd_rate = update_rate;

	return Ret_OK;
}

void on_mission_ready(void)
{
	if (mission_pool.wr_sts != STS_BUSY)
	{
		/*unexpected behavior*/
		return;
	}

	mission_pool.wr_sts = STS_IDLE;
}

RetType append_step_to_mission(step_t stepx, step_t stepy)
{
	uint16_t x_reg, y_reg;

	static uint16_t pre_x_reg = 0x4848;
	static uint16_t pre_y_reg = 0x4848;

	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return Ret_NotOK;
	}

	if (mission_pool.mission[mission_pool.wptr].actsize > (STEPPER_MISSION_MAX_SIZE - 2))
	{
		/* buffer is full */
		return Ret_NotOK;
	}

	switch (stepx)
	{
	case STEP_FORWARD:
		x_reg = 0x4878;
		break;
	case STEP_BACKWARD:
		x_reg = 0x5878;
		break;
	default:
		/* logic to make dir pin not change unnecessary */
		x_reg = (pre_x_reg & 0xFF00) + 0x0048;
		break;
	}

	switch (stepy)
	{
	case STEP_FORWARD:
		y_reg = 0x4878;
		break;
	case STEP_BACKWARD:
		y_reg = 0x5878;
		break;
	default:
		/* logic to make dir pin not change unnecessary */
		y_reg = (pre_y_reg & 0xFF00) + 0x0048;
		break;
	}

	mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = x_reg;
	mission_pool.mission[mission_pool.wptr].actsize++;
	mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = y_reg;
	mission_pool.mission[mission_pool.wptr].actsize++;

	pre_x_reg = x_reg;
	pre_y_reg = y_reg;

	return Ret_OK;
}
