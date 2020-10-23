#include <stdlib.h>
#include "movement.h"
#include "common_inc.h"
#include "stepper.h"

xy_position_t	current_pos = {0};
cmd_t cmd_handler = {0};

static RetType bresenhamLine(int16_t abs_dscan, int16_t abs_dpick, uint8_t octant);
static uint8_t findOctant(int16_t dx, int16_t dy);
static xy_step_t convertOctant(xy_step_t source, uint8_t octant);
static RetType appendAndconvertStep(xy_step_t step, uint16_t len, uint8_t octant);
static RetType fillAllWithFixedStep(xy_step_t step, uint16_t len, uint8_t octant);
static RetType linearLine(int16_t dx, int16_t dy);
static RetType freeMove(int16_t dx, int16_t dy);

void stepper_test(void)
{
	RetType ret;
	uint16_t i;

	ret = find_idle_mission();
	if (ret != Ret_OK)
	{
		return;
	}

	set_speed_for_mission(SPEED_3);

	for (i = 0; i < 200; i++)
	{
		append_step_to_mission(STEP_FORWARD, STEP_FORWARD);
	}

	on_mission_ready();
	LED_BLUE_BLINK();
}

/* FULL STEP MODE
 * 1 step ~ 0.2 mm
 **/
static uint8_t findOctant(int16_t dx, int16_t dy)
{
	uint8_t octant;

	if (abs(dx) >= abs(dy))
	{
		if (dx >= 0)
		{
			if (dy >= 0)
			{
				octant = 0;
			}
			else
			{
				octant = 7;
			}
		}
		else
		{
			if (dy >= 0)
			{
				octant = 3;
			}
			else
			{
				octant = 4;
			}
		}
	}
	else
	{
		if (dx >= 0)
		{
			if (dy >= 0)
			{
				octant = 1;
			}
			else
			{
				octant = 6;
			}
		}
		else
		{
			if (dy >= 0)
			{
				octant = 2;
			}
			else
			{
				octant = 5;
			}
		}
	}

	return octant;
}

static xy_step_t convertOctant(xy_step_t source, uint8_t octant)
{
	xy_step_t dest = {STEP_NONE, STEP_NONE};

	switch (octant)
	{
	case 0:
		dest.step_x = source.step_x;
		dest.step_y = source.step_y;
		break;
	case 1:
		dest.step_x = source.step_y;
		dest.step_y = source.step_x;
		break;
	case 2:
		dest.step_x = MOVE_REVERSE(source.step_y);
		dest.step_y = source.step_x;
		break;
	case 3:
		dest.step_x = MOVE_REVERSE(source.step_x);
		dest.step_y = source.step_y;
		break;
	case 4:
		dest.step_x = MOVE_REVERSE(source.step_x);
		dest.step_y = MOVE_REVERSE(source.step_y);
		break;
	case 5:
		dest.step_x = MOVE_REVERSE(source.step_y);
		dest.step_y = MOVE_REVERSE(source.step_x);
		break;
	case 6:
		dest.step_x = source.step_y;
		dest.step_y = MOVE_REVERSE(source.step_x);
		break;
	case 7:
		dest.step_x = source.step_x;
		dest.step_y = MOVE_REVERSE(source.step_y);
		break;
	default:
		break;
	}

	return dest;
}

static RetType appendAndconvertStep(xy_step_t step, uint16_t len, uint8_t octant)
{
	xy_step_t final_step;
	RetType ret = Ret_NotOK;

	final_step = convertOctant(step, octant);
	ret = append_step_to_mission(final_step.step_x, final_step.step_y);

	return ret;
}

static RetType fillAllWithFixedStep(xy_step_t step, uint16_t len, uint8_t octant)
{
	xy_step_t final_step;
	RetType ret = Ret_NotOK;

	final_step = convertOctant(step, octant);

	while (len)
	{
		ret = append_step_to_mission(final_step.step_x, final_step.step_y);
		if (ret != Ret_OK)
		{
			break;
		}
	}

	return ret;
}

static RetType bresenhamLine(int16_t abs_dscan, int16_t abs_dpick, uint8_t octant)
{
	int16_t eps = 0;
	uint16_t i;
	xy_step_t step = {STEP_FORWARD, STEP_NONE};
	RetType ret = Ret_NotOK;

	if (abs_dscan < abs_dpick)
	{
		/*false input, Bresenham line constrain is dscan has to bigger or equal dpick*/
		return ret;
	}

	/*Note: num of loop??*/
	for (i = 0; i < abs_dscan; i++)
	{
		eps += abs_dpick;
		if ((eps << 1) >= abs_dscan)
		{
			step.step_y = STEP_FORWARD;
			eps -= abs_dscan;
		}
		else
		{
			step.step_y = STEP_NONE;
		}

		ret = appendAndconvertStep(step, octant);

		if (ret != Ret_OK)
		{
			/*error occur!, stop the thing*/
			break;
		}
	}
	return ret;
}

static RetType midPointArcOctant1(int16_t radius, step_t* ytable)
{

}
/*
 * Note: this is blocking function */
static RetType linearLine(int16_t dx, int16_t dy)
{
	int16_t abs_dx;
	int16_t abs_dy;
	xy_step_t fixedstep = {STEP_NONE, STEP_NONE};
	RetType ret = Ret_NotOK;
	uint8_t octant;

	if ((dx == 0) && (dy == 0))
	{
		return ret;
	}

	octant = findOctant(dx, dy);
	abs_dx = abs(dx);
	abs_dy = abs(dy);

	if (dx == 0)
	{
		/* vertical line */
		fixedstep.step_y = STEP_FORWARD;
		ret = fillAllWithFixedStep(fixedstep, abs_dy, octant);
	}
	else if (dy == 0)
	{
		/* horizon line */
		fixedstep.step_x = STEP_FORWARD;
		ret = fillAllWithFixedStep(fixedstep, abs_dx, octant);
	}
	else if (abs_dx == abs_dy)
	{
		/* 45 deg */
		fixedstep.step_x = STEP_FORWARD;
		fixedstep.step_y = STEP_FORWARD;
		ret = fillAllWithFixedStep(fixedstep, abs_dx, octant);
	}
	else
	{
		/* normal cases */
		ret = bresenhamLine(abs_dx, abs_dy, octant);
	}

	return ret;
}

static RetType freeMove(int16_t dx, int16_t dy)
{
	uint16_t absdx = abs(dx);
	uint16_t absdy = abs(dy);

	return Ret_OK;
}

static RetType cwArc()
void movement_bgtask(void)
{
	RetType ret;

	if (cmd_handler.status == CMD_STS_IDLE)
	{
		/*Terminate here since nothing to do*/
		return;
	}

	switch (cmd_handler.cmd)
	{
	case CMD_PEN_UP:
		break;
	case CMD_PEN_DOWN:
		break;
	case CMD_MOVE:
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			ret = freeMove(cmd_handler.X, cmd_handler.Y);
			if (ret == Ret_OK)
			{
				on_mission_ready();
				cmd_handler.status = CMD_STS_IDLE;
			}
			else
			{
				cmd_handler.status = CMD_STS_ERROR;
			}
		}
		break;
	case CMD_LINE:
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			ret = linearLine(cmd_handler.X, cmd_handler.Y);
			if (ret == Ret_OK)
			{
				on_mission_ready();
				cmd_handler.status = CMD_STS_IDLE;
			}
			else
			{
				cmd_handler.status = CMD_STS_ERROR;
			}
		}
		break;
	case CMD_CWARC:
		break;
	case CMD_CCWARC:
		break;
	default:
		break;
	}


}
