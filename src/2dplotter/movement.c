#include <stdlib.h>
#include <math.h>
#include "movement.h"
#include "common_inc.h"
#include "stepper.h"

xy_position_t	current_pos = {0};
cmd_t cmd_handler = {0};

int16_t circle_y_data[MAX_STEP_PER_CIRCLE_OCTANT];
uint16_t circle_x_cnt = 0;

static RetType bresenhamLine(int16_t abs_dscan, int16_t abs_dpick, uint8_t octant);
static uint8_t findOctant(int16_t dx, int16_t dy);
static uint16_t findindex(xy_position_t pos, uint8_t octant);
static xy_step_t convertStepFromToOctant0(xy_step_t source, uint8_t octant);
static xy_position_t convertPosFromOctant1(xy_position_t source, uint8_t octant);
static xy_position_t convertPosToOctant1(xy_position_t source, uint8_t octant);
static RetType appendAndconvertStep(xy_step_t step, uint8_t octant);
static RetType fillAllWithFixedStep(xy_step_t step, uint16_t len, uint8_t octant);
static RetType linearLine(int16_t dx, int16_t dy);
static RetType freeMove(int16_t dx, int16_t dy);
static RetType posToStep(uint16_t start_idx, uint16_t stop_idx, uint8_t octant, uint8_t start_flag);
static RetType cwArc(xy_position_t begin, xy_position_t end);
static RetType ccwArc(xy_position_t begin, xy_position_t end);
static RetType cwcircle(xy_position_t begin);
static RetType ccwcircle(xy_position_t begin);
static void midPointArcOctant1(uint16_t radius);
static RetType arc(xy_position_t center, xy_position_t end, uint8_t opt);

void stepper_test(void)
{
	if (cmd_handler.status == CMD_STS_IDLE)
	{
		cmd_handler.cmd = CMD_CWCIRCLE;
		cmd_handler.I = 50;
		cmd_handler.J = 0;
		cmd_handler.status = CMD_STS_CALCULATING;
		LED_BLUE_BLINK();
	}

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

static xy_step_t convertStepFromToOctant0(xy_step_t source, uint8_t octant)
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

static xy_position_t convertPosFromOctant1(xy_position_t source, uint8_t octant)
{
	xy_position_t dest = {0, 0};

		switch (octant)
		{
		case 0:
			dest.x = source.y;
			dest.y = source.x;
			break;
		case 1:
			dest.x = source.x;
			dest.y = source.y;
			break;
		case 2:
			dest.x = -1*source.x;
			dest.y = source.y;
			break;
		case 3:
			dest.x = -1*source.y;
			dest.y = source.x;
			break;
		case 4:
			dest.x = -1*source.y;
			dest.y = -1*source.x;
			break;
		case 5:
			dest.x = -1*source.x;
			dest.y = -1*source.y;
			break;
		case 6:
			dest.x = source.x;
			dest.y = -1*source.y;
			break;
		case 7:
			dest.x = source.y;
			dest.y = -1*source.x;
			break;
		default:
			break;
		}

		return dest;
}

static xy_position_t convertPosToOctant1(xy_position_t source, uint8_t octant)
{
	xy_position_t dest = {0, 0};

		switch (octant)
		{
		case 0:
			dest.x = source.y;
			dest.y = source.x;
			break;
		case 1:
			dest.x = source.x;
			dest.y = source.y;
			break;
		case 2:
			dest.x = -1*source.x;
			dest.y = source.y;
			break;
		case 3:
			dest.x = source.y;
			dest.y = -1*source.x;
			break;
		case 4:
			dest.x = -1*source.y;
			dest.y = -1*source.x;
			break;
		case 5:
			dest.x = -1*source.x;
			dest.y = -1*source.y;
			break;
		case 6:
			dest.x = source.x;
			dest.y = -1*source.y;
			break;
		case 7:
			dest.x = -1*source.y;
			dest.y = source.x;
			break;
		default:
			break;
		}

		return dest;
}


static RetType appendAndconvertStep(xy_step_t step, uint8_t octant)
{
	xy_step_t final_step;
	RetType ret = Ret_NotOK;

	final_step = convertStepFromToOctant0(step, octant);
	ret = append_step_to_mission(final_step.step_x, final_step.step_y);

	return ret;
}

static RetType fillAllWithFixedStep(xy_step_t step, uint16_t len, uint8_t octant)
{
	xy_step_t final_step;
	uint16_t cnt = len;
	RetType ret = Ret_NotOK;

	final_step = convertStepFromToOctant0(step, octant);

	while (cnt)
	{
		ret = append_step_to_mission(final_step.step_x, final_step.step_y);
		if (ret != Ret_OK)
		{
			break;
		}
		cnt--;
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

static void midPointArcOctant1(uint16_t radius)
{
	int16_t x = 0;
	int16_t y = radius;
	int16_t fm = 1 - (int16_t)radius;

	while (x <= y)
	{
		circle_y_data[x] = y;

		if (fm < 0)
		{
			fm += 2*x + 3;
		}
		else
		{
			fm += 2*(x - y) + 5;
			y--;
		}
		x++;
	}

	circle_x_cnt = (uint16_t)x;
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
	else if (abs_dx > abs_dy)
	{
		/* normal cases */
		ret = bresenhamLine(abs_dx, abs_dy, octant);
	}
	else
	{
		ret = bresenhamLine(abs_dy, abs_dx, octant);
	}

	return ret;
}

static RetType freeMove(int16_t dx, int16_t dy)
{
	uint16_t absdx = abs(dx);
	uint16_t absdy = abs(dy);

	return Ret_OK;
}

static uint16_t findindex(xy_position_t pos, uint8_t octant)
{
	xy_position_t octant1pos;

	octant1pos = convertPosToOctant1(pos, octant);

	if (octant1pos.x > circle_x_cnt)
	{
		/* error case*/
		return CALC_INVALID_NUM;
	}

	if (abs(octant1pos.y - circle_y_data[octant1pos.x]) <= CALC_TOLERENCE)
	{
		/* found the point */
		return octant1pos.x;
	}

	return CALC_INVALID_NUM;
}

static RetType posToStep(uint16_t start_idx, uint16_t stop_idx, uint8_t octant, uint8_t start_flag)
{
	uint16_t idx = start_idx;
	xy_position_t source, dest;
	static xy_position_t pre_pos;
	step_t x, y;
	RetType ret = Ret_OK;

	if (start_flag == TRUE)
	{
		/*first point of arc, save as pre_pos for next reference*/
		source.x = start_idx;
		source.y = circle_y_data[start_idx];
		pre_pos = convertPosFromOctant1(source, octant);

		/*move to next item*/
		if (start_idx < stop_idx)
		{
			idx++;
		}
		else if (start_idx > stop_idx)
		{
			idx--;
		}
	}

	while (idx != stop_idx)
	{
		source.x = idx;
		source.y = circle_y_data[idx];
		dest = convertPosFromOctant1(source, octant);

		switch (dest.x - pre_pos.x)
		{
		case 0:
			x = STEP_NONE;
			break;
		case 1:
			x = STEP_FORWARD;
			break;
		case -1:
			x = STEP_BACKWARD;
			break;
		}

		switch (dest.y - pre_pos.y)
		{
		case 0:
			y = STEP_NONE;
			break;
		case 1:
			y = STEP_FORWARD;
			break;
		case -1:
			y = STEP_BACKWARD;
			break;
		}

		ret = append_step_to_mission(x, y);

		if (ret != Ret_OK)
		{
			break;
		}

		/*update pre_pos*/
		pre_pos = dest;

		if (start_idx < stop_idx)
		{
			idx++;
		}
		else if (start_idx > stop_idx)
		{
			idx--;
		}
	}
	return ret;
}

static RetType cwArc(xy_position_t begin, xy_position_t end)
{
	uint8_t begin_oct, end_oct, cur_oct;
	uint16_t begin_idx, end_idx;
	RetType ret = Ret_NotOK;

	begin_oct = findOctant(begin.x, begin.y);
	begin_idx = findindex(begin, begin_oct);

	end_oct = findOctant(end.x, end.y);
	end_idx = findindex(end, end_oct);

	if ((begin_oct == end_oct) && ((((begin_oct % 2) != 0) && (end_idx >= begin_idx)) || (((begin_oct % 2) == 0) && (end_idx <= begin_idx))))
	{
		ret = posToStep(begin_idx, end_idx, begin_oct, TRUE);
	}
	else
	{
		if ((begin_oct % 2) != 0)
		{
			 ret = posToStep(begin_idx, (circle_x_cnt - 2), begin_oct, TRUE);
		}
		else
		{
			ret = posToStep(begin_idx, 1, begin_oct, TRUE);
		}

		if (ret != Ret_OK) return ret;

		if (begin_oct == 0)
		{
			cur_oct = 7;
		}
		else
		{
			cur_oct = begin_oct - 1;
		}


		while (cur_oct != end_oct)
		{
			if ((cur_oct % 2) != 0)
			{
				ret = posToStep(0, (circle_x_cnt - 2), cur_oct, FALSE);
			}
			else
			{
				ret = posToStep((circle_x_cnt - 1), 1, cur_oct, FALSE);
			}

			if (ret != Ret_OK) return ret;


			if (cur_oct == 0)
			{
				cur_oct = 7;
			}
			else
			{
				cur_oct--;
			}
		}

		if ((end_oct % 2) != 0)
		{
			ret = posToStep(0, end_idx, end_oct, FALSE);
		}
		else
		{
			ret = posToStep((circle_x_cnt - 1), end_idx, end_oct, FALSE);
		}
	}

	return ret;
}

static RetType ccwArc(xy_position_t begin, xy_position_t end)
{
	uint8_t begin_oct, end_oct, cur_oct;
	uint16_t begin_idx, end_idx;
	RetType ret = Ret_NotOK;

	begin_oct = findOctant(begin.x, begin.y);
	begin_idx = findindex(begin, begin_oct);

	end_oct = findOctant(end.x, end.y);
	end_idx = findindex(end, end_oct);

	if ((begin_oct == end_oct) && ((((begin_oct % 2) == 0) && (end_idx >= begin_idx)) || (((begin_oct % 2) != 0) && (end_idx <= begin_idx))))
	{
		ret = posToStep(begin_idx, end_idx, begin_oct, TRUE);
	}
	else
	{
		if ((begin_oct % 2) == 0)
		{
			 ret = posToStep(begin_idx, (circle_x_cnt - 2), begin_oct, TRUE);
		}
		else
		{
			ret = posToStep(begin_idx, 1, begin_oct, TRUE);
		}

		if (ret != Ret_OK) return ret;

		if (begin_oct == 7)
		{
			cur_oct = 0;
		}
		else
		{
			cur_oct = begin_oct + 1;
		}

		while (cur_oct != end_oct)
		{
			if ((cur_oct % 2) == 0)
			{
				ret = posToStep(0, (circle_x_cnt - 2), cur_oct, FALSE);
			}
			else
			{
				ret = posToStep((circle_x_cnt - 1), 1, cur_oct, FALSE);
			}

			if (ret != Ret_OK) return ret;

			cur_oct++;
			if (cur_oct > 7)
			{
				cur_oct = 0;
			}
		}

		if ((end_oct % 2) == 0)
		{
			ret = posToStep(0, end_idx, end_oct, FALSE);
		}
		else
		{
			ret = posToStep((circle_x_cnt - 1), end_idx, end_oct, FALSE);
		}
	}

	return ret;
}

static RetType cwcircle(xy_position_t begin)
{
	uint8_t begin_oct, cur_oct;
	uint16_t begin_idx;
	RetType ret = Ret_NotOK;

	begin_oct = findOctant(begin.x, begin.y);
	begin_idx = findindex(begin, begin_oct);

	if ((begin_oct % 2) != 0)
	{
		 ret = posToStep(begin_idx, (circle_x_cnt - 2), begin_oct, TRUE);
	}
	else
	{
		ret = posToStep(begin_idx, 1, begin_oct, TRUE);
	}

	if (ret != Ret_OK) return ret;

	if (begin_oct == 0)
	{
		cur_oct = 7;
	}
	else
	{
		cur_oct = begin_oct - 1;
	}

	while (cur_oct != begin_oct)
	{
		if ((cur_oct % 2) != 0)
		{
			ret = posToStep(0, (circle_x_cnt - 2), cur_oct, FALSE);
		}
		else
		{
			ret = posToStep((circle_x_cnt - 1), 1, cur_oct, FALSE);
		}

		if (ret != Ret_OK) return ret;

		if (cur_oct == 0)
		{
			cur_oct = 7;
		}
		else
		{
			cur_oct--;
		}
	}

	if ((begin_oct % 2) != 0)
	{
		ret = posToStep(0, begin_idx, begin_oct, FALSE);
	}
	else
	{
		ret = posToStep((circle_x_cnt - 1), begin_idx, begin_oct, FALSE);
	}

	return ret;
}

static RetType ccwcircle(xy_position_t begin)
{
	uint8_t begin_oct, cur_oct;
	uint16_t begin_idx;
	RetType ret = Ret_NotOK;

	begin_oct = findOctant(begin.x, begin.y);
	begin_idx = findindex(begin, begin_oct);

	if ((begin_oct % 2) == 0)
	{
		 ret = posToStep(begin_idx, (circle_x_cnt - 2), begin_oct, TRUE);
	}
	else
	{
		ret = posToStep(begin_idx, 1, begin_oct, TRUE);
	}

	if (ret != Ret_OK) return ret;

	if (begin_oct == 7)
	{
		cur_oct = 0;
	}
	else
	{
		cur_oct = begin_oct + 1;
	}

	while (cur_oct != begin_oct)
	{
		if ((cur_oct % 2) == 0)
		{
			ret = posToStep(0, (circle_x_cnt - 2), cur_oct, FALSE);
		}
		else
		{
			ret = posToStep((circle_x_cnt - 1), 1, cur_oct, FALSE);
		}

		if (ret != Ret_OK) return ret;

		cur_oct++;
		if (cur_oct > 7)
		{
			cur_oct = 0;
		}
	}

	if ((begin_oct % 2) == 0)
	{
		ret = posToStep(0, begin_idx, begin_oct, FALSE);
	}
	else
	{
		ret = posToStep((circle_x_cnt - 1), begin_idx, begin_oct, FALSE);
	}

	return ret;
}
/*
 * center [dx, dy]: relative position of center point from current
 * end [dx, dy]: relative position of end point from current*/
static RetType arc(xy_position_t center, xy_position_t end, uint8_t opt)
{
	xy_position_t beginc = {0};
	xy_position_t endc = {0};
	uint16_t r0, r1;
	uint32_t tmp;
	RetType ret = Ret_NotOK;

	beginc.x = 0 - center.x;
	beginc.y = 0 - center.y;
	tmp = (uint32_t)(beginc.x * beginc.x + beginc.y * beginc.y);
	r0 = (uint16_t)SquareRootRounded(tmp);

	if ((opt == ARC_CW_PARTLYCIRCLE) || (opt == ARC_CW_PARTLYCIRCLE))
	{
		endc.x = end.x - center.x;
		endc.y = end.y - center.y;
		tmp = (uint32_t)(endc.x * endc.x + endc.y * endc.y);
		r1 = (uint16_t)SquareRootRounded(tmp);

		/* we should see not much differences between r0 and r1*/
		tmp = r0 - r1;
		if ((CALC_TOLERENCE_NEG >= tmp) && (CALC_TOLERENCE <= tmp))
		{
			/* big tolerance */
			return ret;
		}
	}


	/*fill data to circle_y_data[] and circle_x_cnt*/
	midPointArcOctant1(r0);

	switch (opt)
	{
	case ARC_CW_PARTLYCIRCLE:
		ret = cwArc(beginc, endc);
		break;
	case ARC_CW_FULLCIRCLE:
		ret = cwcircle(beginc);
		break;
	case ARC_CCW_PARTLYCIRCLE:
		ret = ccwArc(beginc, endc);
		break;
	case ARC_CCW_FULLCIRCLE:
		ret = ccwcircle(beginc);
		break;
	default:
		break;
	}

	return ret;
}

void movement_bgtask(void)
{
	RetType ret;
	xy_position_t center, end;

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
			set_speed_for_mission(SPEED_3);
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
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			set_speed_for_mission(SPEED_3);
			center.x = cmd_handler.I;
			center.y = cmd_handler.J;
			end.x = cmd_handler.X;
			end.y = cmd_handler.Y;

			ret = arc(center, end, ARC_CW_PARTLYCIRCLE);

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
	case CMD_CCWARC:
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			set_speed_for_mission(SPEED_3);
			center.x = cmd_handler.I;
			center.y = cmd_handler.J;
			end.x = cmd_handler.X;
			end.y = cmd_handler.Y;

			ret = arc(center, end, ARC_CCW_PARTLYCIRCLE);

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
	case CMD_CWCIRCLE:
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			set_speed_for_mission(SPEED_3);
			center.x = cmd_handler.I;
			center.y = cmd_handler.J;
			end.x = CALC_INVALID_NUM;
			end.y = CALC_INVALID_NUM;

			ret = arc(center, end, ARC_CW_FULLCIRCLE);

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
	case CMD_CCWCIRCLE:
		ret = find_idle_mission();
		if (ret == Ret_OK)
		{
			set_speed_for_mission(SPEED_3);
			center.x = cmd_handler.I;
			center.y = cmd_handler.J;
			end.x = CALC_INVALID_NUM;
			end.y = CALC_INVALID_NUM;

			ret = arc(center, end, ARC_CCW_FULLCIRCLE);

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
	default:
		break;
	}


}
