
/* File: app_control.h */
/* Type: user specific */

#ifndef _APP_CONTROL_H_
#define _APP_CONTROL_H_

#include "common_inc.h"

/* green - orange - red - blue integrated lamps 
   >include remapping.h for macro support
	 >SYSCFG_GPIO_D should be used.
	 >port config table should included 
		PORT_D_PIN_12
		PORT_D_PIN_13
		PORT_D_PIN_14
		PORT_D_PIN_15 */
#define SYSCFG_LAMPS_SUPPORT			  SYSCFG_NOT_USED

/* integrated user button 
	 >SYSCFG_GPIO_A should be used.
	 >port config table should included
		PORT_A_PIN_0
	 >in process.h:
		filter time should be taken care
		call back function should be defined*/
#define SYSCFG_BUTTON_SUPPORT			  SYSCFG_USED

/* CLOCK SOURCE CONTROL TABLE */

/* GPIO*/
#define SYSCFG_GPIO_A								SYSCFG_USED
#define SYSCFG_GPIO_B								SYSCFG_USED
#define SYSCFG_GPIO_C								SYSCFG_USED
#define SYSCFG_GPIO_D								SYSCFG_USED
#define SYSCFG_GPIO_E								SYSCFG_NOT_USED
#define SYSCFG_GPIO_F								SYSCFG_NOT_USED
#define SYSCFG_GPIO_G								SYSCFG_NOT_USED
#define SYSCFG_GPIO_H								SYSCFG_NOT_USED
#define SYSCFG_GPIO_I								SYSCFG_NOT_USED

/* TIMER */
#define SYSCFG_TIM_1								SYSCFG_NOT_USED
#define SYSCFG_TIM_2								SYSCFG_NOT_USED
#define SYSCFG_TIM_3								SYSCFG_NOT_USED
#define SYSCFG_TIM_4								SYSCFG_USED
#define SYSCFG_TIM_5								SYSCFG_NOT_USED
#define SYSCFG_TIM_6								SYSCFG_NOT_USED
#define SYSCFG_TIM_7								SYSCFG_NOT_USED
#define SYSCFG_TIM_8								SYSCFG_NOT_USED
#define SYSCFG_TIM_9								SYSCFG_NOT_USED
#define SYSCFG_TIM_10								SYSCFG_NOT_USED
#define SYSCFG_TIM_11							  	SYSCFG_NOT_USED
#define SYSCFG_TIM_12							  	SYSCFG_NOT_USED
#define SYSCFG_TIM_13							  	SYSCFG_NOT_USED
#define SYSCFG_TIM_14							  	SYSCFG_NOT_USED

/* UART*/
#define SYSCFG_USART_1								SYSCFG_USED
#define SYSCFG_USART_2								SYSCFG_NOT_USED
#define SYSCFG_USART_3								SYSCFG_NOT_USED
#define SYSCFG_UART_4							  	SYSCFG_NOT_USED
#define SYSCFG_UART_5							  	SYSCFG_NOT_USED
#define SYSCFG_USART_6								SYSCFG_NOT_USED

/* I2C */
#define SYSCFG_I2C_1							  	SYSCFG_NOT_USED
#define SYSCFG_I2C_2							  	SYSCFG_NOT_USED
#define SYSCFG_I2C_3							  	SYSCFG_NOT_USED

/* SPI */
#define SYSCFG_SPI_1							  	SYSCFG_NOT_USED
#define SYSCFG_SPI_2							  	SYSCFG_NOT_USED
#define SYSCFG_SPI_3							  	SYSCFG_NOT_USED

/* CAN */
#define SYSCFG_CAN_1							  	SYSCFG_NOT_USED
#define SYSCFG_CAN_2							  	SYSCFG_NOT_USED

/* ADC */
#define SYSCFG_ADC_1							  	SYSCFG_NOT_USED
#define SYSCFG_ADC_2							  	SYSCFG_NOT_USED
#define SYSCFG_ADC_3							  	SYSCFG_NOT_USED

/* DAC */
#define SYSCFG_DAC							    	SYSCFG_NOT_USED

/* DMA */
#define SYSCFG_DMA_1								SYSCFG_USED
#define SYSCFG_DMA_2								SYSCFG_USED

/* CRC */
#define SYSCFG_CRC									SYSCFG_NOT_USED

/* SRAM*/
#define SYSCFG_SRAM1								SYSCFG_NOT_USED
#define SYSCFG_SRAM2								SYSCFG_NOT_USED

/* ETHERNET */
#define SYSCFG_ETH_MAC								SYSCFG_NOT_USED
#define SYSCFG_ETH_MAC_TX							SYSCFG_NOT_USED
#define SYSCFG_ETH_MAC_RX							SYSCFG_NOT_USED
#define SYSCFG_ETH_MAC_PTP							SYSCFG_NOT_USED

/* USB */
#define SYSCFG_OTG_HS								SYSCFG_NOT_USED
#define SYSCFG_OTG_HS_ULPI							SYSCFG_NOT_USED

/* UNKNOWN */
#define SYSCFG_FLITF								SYSCFG_NOT_USED
#define SYSCFG_PWR									SYSCFG_NOT_USED
#define SYSCFG_SDIO									SYSCFG_NOT_USED
#define SYSCFG_SYSCFG								SYSCFG_NOT_USED
#define SYSCFG_WWDG									SYSCFG_NOT_USED
#define SYSCFG_BKPSRAM								SYSCFG_NOT_USED
#define SYSCFG_CCMDATARAMEN							SYSCFG_NOT_USED

#endif /* _APP_CONTROL_H_ */
