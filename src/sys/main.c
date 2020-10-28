
#include "os_service.h"
#include "common_inc.h"
#include "initialize.h"
#include "movement.h"



void main(void)
{
	/* SYSCLK = 168 MHz */
    /* HCLK = SYSCLK / 1 = 168 MHz*/     
    /* PCLK2 = HCLK / 2 = 84 MHz (APB2 peripheral clocks = 84 MHz, APB2 Timer clocks = 168 MHz) TIM1 TIM8*/  
    /* PCLK1 = HCLK / 4 = 42 MHz (APB1 peripheral clocks = 42 MHz, APB2 Timer clocks = 84 MHz)*/

	SystemInit();

	/* system init before OS come to run */
	Prj_InitBeforeOS();
	
	OS_initialize();
	
	/* system init before OS come to run */
	Prj_InitBeforeTaskRun();
	
	OS_start();
	
	/* system init after OS come to run */
	Prj_InitAfterTaskRun();
	
	while (1)
	{
		/* backgground tasks for such lowest prioroty */
		movement_bgtask();
	}
}

