#include "common_inc.h"
#include "stepper.h"
#include "movement.h"

stepper_mission_t mission_pool[MISSION_POOL_SIZE];
cmd_status_t cmd_status = CMD_IDLE;
uint8_t mission_index = 0;
uint16_t step_index = 0;
uint16_t pre_x_reg = 0x4848, pre_y_reg = 0x4848;


RetType create_mission(void)
{
	uint8_t i;
	RetType ret = Ret_NotOK;

	for (i = 0; i < MISSION_POOL_SIZE; i++)
	{
		if (STEPPER_IDLE == mission_pool[i].status)
		{
			ret = i;
			mission_pool[i].status = STEPPER_LOCKED;
			mission_pool[i].speed = SPEED_0;
			mission_pool[i].update_rate = 0;
			mission_pool[i].len = 0;
			mission_index = i;
			step_index = 0;
			cmd_status = CMD_CALCULATING;
			ret = Ret_OK;
		}
	}

	return ret;
}


RetType append_mission_step(step_t stepx, step_t stepy)
{
	uint16_t x_reg, y_reg;
	if (CMD_CALCULATING != cmd_status)
	{
		return Ret_NotOK;
	}

	if (step_index >= (STEPPER_MISSION_MAX_SIZE - 2))
	{
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
		y_reg = (pre_y_reg & 0xFF00) + 0x0048;
		break;
	}

	mission_pool[mission_index].data[step_index] = x_reg;
	step_index++;
	mission_pool[mission_index].data[step_index] = y_reg;
	step_index++;

	pre_x_reg = x_reg;
	pre_y_reg = y_reg;
}

RetType execute_mission(void)
{
	if (CMD_CALCULATING != cmd_status)
	{
		return Ret_NotOK;
	}

	if (step_index >= (STEPPER_MISSION_MAX_SIZE - 2))
	{
		return Ret_NotOK;
	}
}

