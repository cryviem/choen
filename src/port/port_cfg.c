//Choen

#include "port.h"
#include "app_control.h"

/* reference*/
//	uint8									PortPinName;
//	uint8									PinHWType;
//	uint8									PinHWPuPd;
//	// standard
//	Port_PinModeType						PinMode;
//	Port_PinDirectionType					PinDirection;
//	Port_PinLevelValueType					PinInitValue; 

const Port_ConfigType		User_PortConfig[] =
{
/*------THE BEGIN OF USER EDIT SECTION---------*/
#if (SYSCFG_LAMPS_SUPPORT == SYSCFG_USED)
	{
		PORT_D_PIN_12,								// LED GREEN
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,
		
		PORT_PIN_MODE_DIO,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,	
	},
	
	{
		PORT_D_PIN_13,								// LED ORANGE
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_DIO,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},

	{
		PORT_D_PIN_14,								// LED RED
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_DIO,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},

	{
		PORT_D_PIN_15,								// LED BLUE
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,
		
		PORT_PIN_MODE_DIO,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},
	#endif /* #if (SYSCFG_LAMPS_SUPPORT == SYSCFG_USED) */
	
	#if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED)
	{
		PORT_A_PIN_0,								// BUTTON
		PORT_PIN_HW_DEFAULT,
		PORT_PIN_HW_NO_PUPD,
		
		PORT_PIN_MODE_DIO,
		PORT_PIN_IN,
		PORT_PIN_LEVEL_DONTCARE,
	},
	#endif /* #if (SYSCFG_BUTTON_SUPPORT == SYSCFG_USED) */
	/*****************UART*********************/
	{
		PORT_B_PIN_6,								// USART1_TX
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_USART_1_3,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_DONTCARE,
	},
	{
		PORT_B_PIN_7,								// USART1_RX
		PORT_PIN_HW_DEFAULT,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_USART_1_3,
		PORT_PIN_IN,
		PORT_PIN_LEVEL_DONTCARE,
	},
	/****************SPI********************/
	{
		PORT_B_PIN_12,								// SPI2 NSS
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_SPI_1_2,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},
	{
		PORT_B_PIN_13,								// SPI2 CLK
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_SPI_1_2,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},
	{
		PORT_B_PIN_14,								// SPI2 MISO
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_SPI_1_2,
		PORT_PIN_IN,
		PORT_PIN_LEVEL_LOW,
	},
	{
		PORT_B_PIN_15,								// SPI2 MOSI
		PORT_PIN_HW_PUSHPULL,
		PORT_PIN_HW_NO_PUPD,

		PORT_PIN_MODE_SPI_1_2,
		PORT_PIN_OUT,
		PORT_PIN_LEVEL_LOW,
	},
/*------THE END OF USER EDIT SECTION---------*/
	{
		PORT_ENDFLAG,
		0xFF,
		0xFF,
		
		0xFF,
		0xFF,
		0xFF,	
	}
};

