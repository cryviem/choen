#ifndef _STEPPER_H_
#define _STEPPER_H_

/*file stepper.h*/
#include "common_inc.h"

/* CONFIG AREA */
/* basic timer: 2, 3, 4, 5
 * clock source: 84 MHz
 * update rate is not supported */
#define	TIMER_TYPE_BASIC				0

/* advance timer: 1, 8
 * clock source: 168 MHz
 * update rate is supported */
#define	TIMER_TYPE_ADVANCED				1

#define	TIMER_TYPE						TIMER_TYPE_BASIC

#if (TIMER_TYPE == TIMER_TYPE_ADVANCED)
/* timer1
 * PINs: 	CC1 PA8		PE9
 * 			CC2 PA9		PE11
 * 			CC3 PA10	PE13
 * 			CC4 PA11	PE14
 * DMA:		DMA2 stream5 channel6
 */
#define TIM_REG							TIM1
#define DMA_HANDLER						DMA_HANDLER_TIM1UP
#else
/* timer3
 * PINs: 	CC1 PC6
 * 			CC2 PC7
 * 			CC3 PC8
 * 			CC4 PC9
 * DMA:		DMA1 stream2 channel5
 */
#define TIM_REG							TIM3
#define DMA_HANDLER						DMA_HANDLER_TIM3UP
#endif /*(TIMER_TYPE == TIMER_TYPE_ADVANCED)*/

#define STEPPER_MISSION_MAX_SIZE					2048
#define STEPPER_NUM_OF_MISSIONS						2
#define STEPPER_STEP_ZISE							50


/* ---------------- */

#define STEP_NONE					0
#define STEP_FORWARD				1
#define STEP_BACKWARD				2

typedef uint8_t step_t;

typedef enum {
	SPEED_0 = 0,
	SPEED_1,
	SPEED_2,
	SPEED_3,
	SPEED_4,
	SPEED_INVALID
}speed_t;

typedef enum {
	SM_IDLE,
	SM_WORKING,
	SM_ERROR
}state_machine_t;

typedef enum{
	STS_IDLE = 0,
	STS_BUSY = 1
} rd_wr_sts_t;

typedef struct {
	speed_t											speed;
	uint8_t											upd_rate;
	uint16_t 										actsize;
	uint16_t										data[STEPPER_MISSION_MAX_SIZE];
} mission_t;

typedef struct {
	mission_t 										mission[STEPPER_NUM_OF_MISSIONS];
	uint8_t 										wptr;
	uint8_t 										rptr;
	rd_wr_sts_t										wr_sts;
	rd_wr_sts_t										rd_sts;
} mission_pool_t;


extern void stepper_init(void);
extern void stepper_task(void);
extern RetType find_idle_mission(void);
extern mission_t* get_opened_mission(void);
extern RetType append_data_to_mission(uint16_t data);
extern RetType set_speed_for_mission(speed_t speed);
extern RetType set_upd_rate_for_mission(uint8_t update_rate);
extern void on_mission_ready(void);
extern RetType append_step_to_mission(step_t stepx, step_t stepy);
extern RetType stepper_rest(void);

/* timer1
 * PINs: 	CC1 PA8		PE9
 * 			CC2 PA9		PE11
 * 			CC3 PA10	PE13
 * 			CC4 PA11	PE14
 * DMA:		DMA2 stream5 channel6
 */
/* timer8
 * PINs: 	CC1 PC6
 * 			CC2 PC7
 * 			CC3 PC8
 * 			CC4 PC9
 * DMA:		DMA2 stream1 channel7
 */
/* timer3
 * PINs: 	CC1 PC6
 * 			CC2 PC7
 * 			CC3 PC8
 * 			CC4 PC9
 * DMA:		DMA1 stream2 channel5
 */
#endif /*_STEPPER_H_*/
