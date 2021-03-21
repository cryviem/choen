
#include "stepper.h"

#include "common_inc.h"
#include "dmacfg.h"

/* Mapping
CC1			X_axis step
CC2			X_axis direction
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
	TIM_REG->CR2 |= TIM_CR2_CCDS;
	/* CCMR1 and CCMR2, reset value: 0x0000 */
	/* Set 4 channels to PWM2 */
	TIM_REG->CCMR1 = 0x7878;
	TIM_REG->CCMR2 = 0x7878;

	/* DCR reset value: 0x0000 */
	/* Set DBA to 11 (01011), start from ARR */
	/* Set DBL to 5 (00101), 6 transfers */
	/* Purpose: ARR-CCR1-CCR2-CCR3-CCR4 will be DMA feed every cycle */
	TIM_REG->DCR |= (TIM_DCR_DBL_2 |TIM_DCR_DBL_0 | TIM_DCR_DBA_3 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0);

	/* Set counting clock to 100 kHz */
#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Counting clock: 168 MHz / (1679 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 1679;
#else
	/* Counting clock: 84 MHz / (839 + 1) = 100 kHz T = 10 us*/
	TIM_REG->PSC = 839;
	//TIM_REG->PSC = 8399;	//T = 100 us for test purpose
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

	/*CCER reset value: 0x0000*/
	/* Active high, Enable output*/
	TIM_REG->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E);

}

void stepper_mission_start(mission_t* mission)
{
	/* Update rate configuration */
#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Only advance timers support this feature*/
	TIM_REG->RCR = mission->upd_rate;
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

	/* start dma work */
	dma_transfer(DMA_HANDLER, (uint32_t)mission->data, mission->actsize);

	/* DIER reset value: 0x0000 */
	/* Enable UEV DMA request*/
	TIM_REG->DIER |= TIM_DIER_UDE;

	/* Generate UG event to let DMA update register for the first time */
	TIM_REG->EGR |= TIM_EGR_UG;

	while (TIM_REG->EGR & TIM_EGR_UG); //wait for DMA update reg


#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
	/* Advance timer need to set MOE bit for output enabling */
	TIM_REG->BDTR |= TIM_BDTR_MOE;
#endif

	/* Start counting */
	TIM_REG->CR1 |= TIM_CR1_CEN;
}

void stepper_task(void)
{
	dma_StatusEN dma_status;
	mission_t* mission_ptr = NULL;

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
			print_text("stepper > dma error\n");
			TIM_REG->DIER &= (~TIM_DIER_UDE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			sm_state = SM_ERROR;
			break;

		case DMA_Status_Completed:
			print_text("stepper > dma completed\n");
			TIM_REG->DIER &= (~TIM_DIER_UDE);
			TIM_REG->CR1 &= (~TIM_CR1_CEN);
			dma_cleanup(DMA_HANDLER);
			on_mission_completed();
			sm_state = SM_IDLE;
			break;

		case DMA_Status_InProcess:
			/* just calm and wait */
			break;
		default:
			//DMA_Status_NotStarted
			//DMA_Status_Triggered
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

	static uint16_t pre_x_dir = 501;
	static uint16_t pre_y_dir = 501;

	if (mission_pool.wr_sts != STS_BUSY)
	{
		/* find_idle_mission() has NOT been called successfully before */
		return Ret_NotOK;
	}

	if (mission_pool.mission[mission_pool.wptr].actsize > (STEPPER_MISSION_MAX_SIZE - 6))
	{
		/* buffer is full */
		return Ret_NotOK;
	}

	/*
	 * slot 1: ARR
	 * slot 2: Unused.
	 * slot 3: CCR1 - X step
	 * slot 4: CCR2 - X dir
	 * slot 5: CCR3 - Y step
	 * slot 6: CCR4 - Y dir
	 * */

	/*ARR*/
	mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 500;
	mission_pool.mission[mission_pool.wptr].actsize +=2;

	/*CCR1&CCR2*/
	switch (stepx)
	{
	case STEP_FORWARD:
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 450;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 501;
		mission_pool.mission[mission_pool.wptr].actsize++;
		pre_x_dir = 500;
		break;
	case STEP_BACKWARD:
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 450;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 0;
		pre_x_dir = 0;
		mission_pool.mission[mission_pool.wptr].actsize++;
		break;
	default:
		/* logic to make dir pin not change unnecessary */
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 501;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = pre_x_dir;
		mission_pool.mission[mission_pool.wptr].actsize++;
		break;
	}

	/*CCR1&CCR2*/
	switch (stepy)
	{
	case STEP_FORWARD:
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 450;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 501;
		mission_pool.mission[mission_pool.wptr].actsize++;
		pre_y_dir = 500;
		break;
	case STEP_BACKWARD:
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 450;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 0;
		pre_y_dir = 0;
		mission_pool.mission[mission_pool.wptr].actsize++;
		break;
	default:
		/* logic to make dir pin not change unnecessary */
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = 501;
		mission_pool.mission[mission_pool.wptr].actsize++;
		mission_pool.mission[mission_pool.wptr].data[mission_pool.mission[mission_pool.wptr].actsize] = pre_y_dir;
		mission_pool.mission[mission_pool.wptr].actsize++;
		break;
	}

	return Ret_OK;
}

RetType stepper_rest(void)
{
	if ((mission_pool.rd_sts == STS_IDLE) && (mission_pool.wr_sts == STS_IDLE) && (mission_pool.rptr == mission_pool.wptr))
	{
		/* stepper is free*/
		return Ret_OK;
	}

	return Ret_NotOK;
}
