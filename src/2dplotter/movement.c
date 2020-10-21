#include "../2dplotter/movement.h"

#include "common_inc.h"

#include "../2dplotter/stepper.h"

xy_position_t	current_pos = {0};

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
