#include <stdlib.h>
#include "movement.h"
#include "common_inc.h"
#include "stepper.h"

xy_position_t	current_pos = {0};
cmd_t cmd_handler = {0};

static RetType bresenhamPositiveSmallSlope(int16_t dscan, int16_t dpick, uint8_t inverse);
static RetType bresenhamNegativeSmallSlope(int16_t dscan, int16_t dpick, uint8_t inverse);
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

static RetType bresenhamPositiveSmallSlope(int16_t dscan, int16_t dpick, uint8_t inverse)
{
	int16_t eps = 0;
	uint16_t i;
	step_t pick_axis = STEP_NONE;
	RetType ret = Ret_NotOK;

	if (dscan > 0)
	{
		/* increasing direction */
		for (i = 0; i <= dscan; i++)
		{
			eps += dpick;
			if ((eps << 1) >= dscan)
			{
				pick_axis = STEP_FORWARD;
				eps -= dscan;
			}
			else
			{
				pick_axis = STEP_NONE;
			}

			if (inverse)
			{
				/**/
				ret = append_step_to_mission(pick_axis, STEP_FORWARD);
			}
			else
			{
				ret = append_step_to_mission(STEP_FORWARD, pick_axis);
			}

			if (ret != Ret_OK)
			{
				/*error occur!, stop the thing*/
				break;
			}
		}
	}
	else if (dscan < 0)
	{
		/* decreasing direction */
		dscan = abs(dscan);

		for (i = 0; i <= dscan; i++)
		{
			eps += dpick;
			if ((eps << 1) >= dscan)
			{
				pick_axis = STEP_FORWARD;
				eps -= dscan;
			}
			else
			{
				pick_axis = STEP_NONE;
			}

			if (inverse)
			{
				/**/
				ret = append_step_to_mission(pick_axis, STEP_BACKWARD);
			}
			else
			{
				ret = append_step_to_mission(STEP_BACKWARD, pick_axis);
			}

			if (ret != Ret_OK)
			{
				/*error occur!, stop the thing*/
				break;
			}
		}
	}
	else
	{
		/*scan1 == scan2 should never happen here, if yes, error returns back*/
	}

	return ret;
}

static RetType bresenhamNegativeSmallSlope(int16_t dscan, int16_t dpick, uint8_t inverse)
{
	int16_t eps = 0;
	uint16_t i;
	step_t pick_axis = STEP_NONE;
	RetType ret = Ret_NotOK;

	if (dscan > 0)
	{
		/* increasing direction */
		for (i = 0; i <= dscan; i++)
		{
			eps += dpick;
			if (((eps << 1) + dscan) <= 0)
			{
				pick_axis = STEP_BACKWARD;
				eps += dscan;
			}
			else
			{
				pick_axis = STEP_NONE;
			}

			if (inverse)
			{
				/**/
				ret = append_step_to_mission(pick_axis, STEP_FORWARD);
			}
			else
			{
				ret = append_step_to_mission(STEP_FORWARD, pick_axis);
			}

			if (ret != Ret_OK)
			{
				/*error occur!, stop the thing*/
				break;
			}
		}
	}
	else if (dscan < 0)
	{
		/* decreasing direction */
		dscan = abs(dscan);

		for (i = 0; i <= dscan; i++)
		{
			eps += dpick;
			if (((eps << 1) + dscan) <= 0)
			{
				pick_axis = STEP_BACKWARD;
				eps += dscan;
			}
			else
			{
				pick_axis = STEP_NONE;
			}

			if (inverse)
			{
				/**/
				ret = append_step_to_mission(pick_axis, STEP_BACKWARD);
			}
			else
			{
				ret = append_step_to_mission(STEP_BACKWARD, pick_axis);
			}

			if (ret != Ret_OK)
			{
				/*error occur!, stop the thing*/
				break;
			}
		}
	}
	else
	{
		/*scan1 == scan2 should never happen here, if yes, error returns back*/
	}

	return ret;
}

/*
 * Note: this is blocking function */
static RetType linearLine(int16_t dx, int16_t dy)
{
	uint16_t i;

	step_t dir = STEP_NONE;
	RetType ret = Ret_NotOK;

	if (dx == 0)
	{
		/* vertical line*/
		if (dy > 0)
		{
			/*y move forward*/
			dir = STEP_FORWARD;
		}
		else
		{
			dir = STEP_BACKWARD;
		}

		for (i = 0; i <= abs(dy); i++)
		{
			ret = append_step_to_mission(STEP_NONE, dir);
			if (ret != Ret_OK)
			{
				break;
			}
		}
	}
	else if (dy == 0)
	{
		/* horizon line*/
		if (dx > 0)
		{
			dir = STEP_FORWARD;
		}
		else
		{
			dir = STEP_BACKWARD;
		}

		for (i = 0; i <= abs(dx); i++)
		{
			ret = append_step_to_mission(dir, STEP_NONE);
			if (ret != Ret_OK)
			{
				break;
			}
		}
	}
	else
	{
		if (abs(dx) >= abs(dy))
		{
			/*small slope*/
			if (dy > 0)
			{
				/*positive slope*/
				ret = bresenhamPositiveSmallSlope(dx, dy, FALSE);
			}
			else
			{
				/*negative slope*/
				ret = bresenhamNegativeSmallSlope(dx, dy, FALSE);
			}
		}
		else
		{
			/*big slope*/
			if (dx > 0)
			{
				/*positive slope*/
				ret = bresenhamPositiveSmallSlope(dy, dx, TRUE);
			}
			else
			{
				/*negative slope*/
				ret = bresenhamNegativeSmallSlope(dy, dx, TRUE);
			}
		}
	}

	return ret;
}

static RetType freeMove(int16_t dx, int16_t dy)
{
	uint16_t absdx = abs(dx);
	uint16_t absdy = abs(dy);

	return Ret_OK;
}


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
