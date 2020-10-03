#include "common_inc.h"
#include "stepper.h"
#include "movement.h"

step_t x_list[10] = {STEP_FORWARD, STEP_FORWARD, STEP_FORWARD, STEP_NONE, STEP_BACKWARD, STEP_BACKWARD, STEP_BACKWARD, STEP_BACKWARD, STEP_FORWARD, STEP_FORWARD};
step_t y_list[10] = {STEP_BACKWARD, STEP_BACKWARD, STEP_BACKWARD, STEP_NONE, STEP_FORWARD, STEP_FORWARD, STEP_FORWARD, STEP_FORWARD, STEP_BACKWARD, STEP_BACKWARD};

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

	for (i = 0; i < 10; i++)
	{
		append_step_to_mission(x_list[i], y_list[i]);
	}

	on_mission_ready();
	LED_BLUE_BLINK();
}
