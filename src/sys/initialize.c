
#include "dmacfg.h"
#include "port_cfg.h"
#include "app_control.h"
#include "common_inc.h"
#include "uartcfg.h"
#include "uart_if.h"
#include "spi_cfg.h"
#include "stepper.h"

/* PRIVATE FUNCTION DECLARE BEGIN */
static void pvt_clocksetting_v(void);
/* PRIVATE FUNCTION DECLARE END */


void Prj_InitBeforeOS(void)
{
	pvt_clocksetting_v();
	Port_Init(User_PortConfig);
	dma_init();
	uart_init();
	spi_init();
	//stepper_init();

}


void Prj_InitBeforeTaskRun(void)
{
	uartif_ClearRingBuffs();
	uart_channel1_start();
	spi1_start_txonly();
}

void Prj_InitAfterTaskRun(void)
{

}



static void pvt_clocksetting_v(void)
{
	RCC->AHB1ENR = (  			(uint32_t)0
								#if (SYSCFG_GPIO_A == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOAEN
								#endif
								#if (SYSCFG_GPIO_B == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOBEN
								#endif
								#if (SYSCFG_GPIO_C == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOCEN
								#endif
								#if (SYSCFG_GPIO_D == SYSCFG_USED)
									| RCC_AHB1ENR_GPIODEN
								#endif
								#if (SYSCFG_GPIO_E == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOEEN
								#endif
								#if (SYSCFG_GPIO_F == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOFEN
								#endif
								#if (SYSCFG_GPIO_G == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOGEN
								#endif
								#if (SYSCFG_GPIO_H == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOHEN
								#endif
								#if (SYSCFG_GPIO_I == SYSCFG_USED)
									| RCC_AHB1ENR_GPIOIEN
								#endif
								#if (SYSCFG_CRC == SYSCFG_USED)
									| RCC_AHB1ENR_CRCEN
								#endif
								#if (SYSCFG_BKPSRAM == SYSCFG_USED)
									| RCC_AHB1ENR_BKPSRAMEN
								#endif
								#if (SYSCFG_CCMDATARAMEN == SYSCFG_USED)
									| RCC_AHB1ENR_CCMDATARAMEN
								#endif
								#if (SYSCFG_DMA_1 == SYSCFG_USED)
									| RCC_AHB1ENR_DMA1EN
								#endif
								#if (SYSCFG_DMA_2 == SYSCFG_USED)
									| RCC_AHB1ENR_DMA2EN
								#endif
								#if (SYSCFG_ETH_MAC == SYSCFG_USED)
									| RCC_AHB1ENR_ETHMACEN
								#endif
								#if (SYSCFG_ETH_MAC_TX == SYSCFG_USED)
									| RCC_AHB1ENR_ETHMACTXEN
								#endif
								#if (SYSCFG_ETH_MAC_RX == SYSCFG_USED)
									| RCC_AHB1ENR_ETHMACRXEN
								#endif
								#if (SYSCFG_ETH_MAC_PTP == SYSCFG_USED)
									| RCC_AHB1ENR_ETHMACPTPEN
								#endif
								#if (SYSCFG_OTG_HS == SYSCFG_USED)
									| RCC_AHB1ENR_OTGHSEN
								#endif
								#if (SYSCFG_OTG_HS_ULPI == SYSCFG_USED)
									| RCC_AHB1ENR_OTGHSULPIEN
								#endif
								);

	/* Currently not supported */
	RCC->AHB2ENR = (uint32_t)0;

	/* Currently not supported */
	RCC->AHB3ENR = (uint32_t)0;

	RCC->APB1ENR = (  			(uint32_t)0
								#if (SYSCFG_TIM_2 == SYSCFG_USED)
									| RCC_APB1ENR_TIM2EN
								#endif
								#if (SYSCFG_TIM_3 == SYSCFG_USED)
									| RCC_APB1ENR_TIM3EN
								#endif
								#if (SYSCFG_TIM_4 == SYSCFG_USED)
									| RCC_APB1ENR_TIM4EN
								#endif
								#if (SYSCFG_TIM_5 == SYSCFG_USED)
									| RCC_APB1ENR_TIM5EN
								#endif
								#if (SYSCFG_TIM_6 == SYSCFG_USED)
									| RCC_APB1ENR_TIM6EN
								#endif
								#if (SYSCFG_TIM_7 == SYSCFG_USED)
									| RCC_APB1ENR_TIM7EN
								#endif
								#if (SYSCFG_TIM_12 == SYSCFG_USED)
									| RCC_APB1ENR_TIM12EN
								#endif
								#if (SYSCFG_TIM_13 == SYSCFG_USED)
									| RCC_APB1ENR_TIM13EN
								#endif
								#if (SYSCFG_TIM_14 == SYSCFG_USED)
									| RCC_APB1ENR_TIM14EN
								#endif
								#if (SYSCFG_WWDG == SYSCFG_USED)
									| RCC_APB1ENR_WWDGEN
								#endif
								#if (SYSCFG_SPI_2 == SYSCFG_USED)
									| RCC_APB1ENR_SPI2EN
								#endif
								#if (SYSCFG_SPI_3 == SYSCFG_USED)
									| RCC_APB1ENR_SPI3EN
								#endif
								#if (SYSCFG_USART_2 == SYSCFG_USED)
									| RCC_APB1ENR_USART2EN
								#endif
								#if (SYSCFG_USART_3 == SYSCFG_USED)
									| RCC_APB1ENR_USART3EN
								#endif
								#if (SYSCFG_UART_4 == SYSCFG_USED)
									| RCC_APB1ENR_UART4EN
								#endif
								#if (SYSCFG_UART_5 == SYSCFG_USED)
									| RCC_APB1ENR_UART5EN
								#endif
								#if (SYSCFG_I2C_1 == SYSCFG_USED)
									| RCC_APB1ENR_I2C1EN
								#endif
								#if (SYSCFG_I2C_2 == SYSCFG_USED)
									| RCC_APB1ENR_I2C2EN
								#endif
								#if (SYSCFG_I2C_3 == SYSCFG_USED)
									| RCC_APB1ENR_I2C3EN
								#endif
								#if (SYSCFG_CAN_1 == SYSCFG_USED)
									| RCC_APB1ENR_CAN1EN
								#endif
								#if (SYSCFG_CAN_2 == SYSCFG_USED)
									| RCC_APB1ENR_CAN2EN
								#endif
								#if (SYSCFG_PWR == SYSCFG_USED)
									| RCC_APB1ENR_PWREN
								#endif
								#if (SYSCFG_DAC == SYSCFG_USED)
									| RCC_APB1ENR_DACEN
								#endif
								);

	RCC->APB2ENR = (  			(uint32_t)0
								#if (SYSCFG_TIM_1 == SYSCFG_USED)
									| RCC_APB2ENR_TIM1EN
								#endif
								#if (SYSCFG_TIM_8 == SYSCFG_USED)
									| RCC_APB2ENR_TIM8EN
								#endif
								#if (SYSCFG_USART_1 == SYSCFG_USED)
									| RCC_APB2ENR_USART1EN
								#endif
								#if (SYSCFG_USART_6 == SYSCFG_USED)
									| RCC_APB2ENR_USART6EN
								#endif
								#if (SYSCFG_ADC_1 == SYSCFG_USED)
									| RCC_APB2ENR_ADC1EN
								#endif
								#if (SYSCFG_ADC_2 == SYSCFG_USED)
									| RCC_APB2ENR_ADC2EN
								#endif
								#if (SYSCFG_ADC_3 == SYSCFG_USED)
									| RCC_APB2ENR_ADC3EN
								#endif
								#if (SYSCFG_SDIO == SYSCFG_USED)
									| RCC_APB2ENR_SDIOEN
								#endif
								#if (SYSCFG_SPI_1 == SYSCFG_USED)
									| RCC_APB2ENR_SPI1EN
								#endif
								#if (SYSCFG_SYSCFG == SYSCFG_USED)
									| RCC_APB2ENR_SYSCFGEN
								#endif
								#if (SYSCFG_TIM_9 == SYSCFG_USED)
									| RCC_APB2ENR_TIM9EN
								#endif
								#if (SYSCFG_TIM_10 == SYSCFG_USED)
									| RCC_APB2ENR_TIM10EN
								#endif
								#if (SYSCFG_TIM_11 == SYSCFG_USED)
									| RCC_APB2ENR_TIM11EN
								#endif
								);
}
