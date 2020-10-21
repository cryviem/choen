//Choen

#include "port.h"

#include "common_inc.h"

/* local function declaration*/
void Port_SubInit( const Port_ConfigType* ConfigPtr);
GPIO_TypeDef * Port_BaseGetter(uint8_t PortID);

	
// standard api [AUTOSAR compliance]----------------------------------------

void Port_Init(const Port_ConfigType* ConfigPtr)
{
	uint8_t	l_index = 0;
	while (PORT_ENDFLAG != ConfigPtr[l_index].PortPinName)
	{
		Port_SubInit(&ConfigPtr[l_index]);
		l_index++;
	}
}
	
//--------------------------------------------------------------------------	


// not standard functions [developing...]-----------------------------------
Port_PinModeType Port_GetPinMode(const Port_ConfigType* ConfigPtr, uint8_t PinName)
{
	uint8_t	l_index = 0;
	while (PORT_ENDFLAG != ConfigPtr[l_index].PortPinName)
	{
		if (ConfigPtr[l_index].PortPinName == PinName)
		{
			return ConfigPtr[l_index].PinMode;
		}
		l_index++;
	}

	return 0xFF;								// no result
}

Port_PinDirectionType Port_GetPinDirection(const Port_ConfigType* ConfigPtr, uint8_t PinName)
{
	uint8_t	l_index = 0;
	while (PORT_ENDFLAG != ConfigPtr[l_index].PortPinName)
	{
		if (ConfigPtr[l_index].PortPinName == PinName)
		{
			return ConfigPtr[l_index].PinDirection;
		}
		l_index++;
	}

	return 0xFF;								// no result
}
//--------------------------------------------------------------------------

/*
 * 
 *
 *
 *
 */
Port_PinLevelValueType Port_ReadPin(uint8_t PinID)
{
	uint8_t l_PinNum = PORT_GETPIN(PinID);

	GPIO_TypeDef *l_Port_Handler = Port_BaseGetter(PORT_GETPORT(PinID));

	uint16_t l_PinValue;

	l_PinValue = (uint16_t) l_Port_Handler->IDR;

	if ( l_PinValue & ((uint16_t)(0x0001 << l_PinNum)))
	{
		return PORT_PIN_LEVEL_HIGH;
	}
	else
	{
		return PORT_PIN_LEVEL_LOW;
	}
}

/*	Note: ignored pin mode and direction checking due to optimize execute time.
 *
 *
 *
 */
uint16_t Port_ReadPort(uint8_t PortId)
{
	uint16_t l_PortValue = 0xFFFF;

	GPIO_TypeDef *l_Port_Handler = Port_BaseGetter((PortId & 0x0F));

	l_PortValue = (uint16_t) l_Port_Handler->IDR;

	return l_PortValue;

}


/*	Note: defect may comes because we define Dio_LevelType has only 2 values 0 and 1, other values will be belong
 * to STD_HIGH
 * Consider to use BSRR register
 * updated: currently use BSRR instead.
 *
 */
void Port_WritePin(uint8_t PinID, Port_PinLevelValueType Level)
{

	uint8_t l_PinNum = PORT_GETPIN(PinID);

	GPIO_TypeDef *l_Port_Handler = Port_BaseGetter(PORT_GETPORT(PinID));

	if (PORT_PIN_LEVEL_LOW == Level)
	{
		l_Port_Handler->BSRRH |= (uint16_t)(0x0001 << l_PinNum);
	}
	else
	{
		l_Port_Handler->BSRRL |= (uint16_t)(0x0001 << l_PinNum);
	}

}

/* Note:
 *
 *
 *
 */
void Port_WritePort(uint8_t PortId, uint16_t Level)
{

	GPIO_TypeDef *l_Port_Handler = Port_BaseGetter((PortId & 0x0F));

	l_Port_Handler->ODR = (uint16_t)Level;
}

// private function for local using-----------------------------------------
GPIO_TypeDef * Port_BaseGetter(uint8_t PortID)
	{
		GPIO_TypeDef * l_Port_Base = NULL;

		switch (PortID)
		{
			case PORT_A:	
				// Port A matched.
				l_Port_Base = (GPIO_TypeDef*) GPIOA_BASE;
				break;
			case PORT_B:
				// Port B matched.
				l_Port_Base = (GPIO_TypeDef*) GPIOB_BASE;
				break;
			case PORT_C:
				// Port C matched.
				l_Port_Base = (GPIO_TypeDef*) GPIOC_BASE;
				break;
			case PORT_D:
				// Port D matched.
				l_Port_Base = (GPIO_TypeDef*) GPIOD_BASE;
				break;
			case PORT_E:
				// Port E matched.
				l_Port_Base = (GPIO_TypeDef*) GPIOE_BASE;
				break;
			default:
				break;
		}
		return l_Port_Base;
	}
	
void Port_SubInit( const Port_ConfigType* ConfigPtr)
{
	uint8_t l_PinNum = PORT_GETPIN(ConfigPtr->PortPinName);
	GPIO_TypeDef *l_Port_Handler = Port_BaseGetter(PORT_GETPORT(ConfigPtr->PortPinName));
	
	// Reset all 
	l_Port_Handler->MODER &= ~((0x00000003) << (l_PinNum*2));
	l_Port_Handler->OTYPER &= ~((0x0001) << l_PinNum);
	l_Port_Handler->PUPDR &= ~((0x00000003) << (l_PinNum*2));
	l_Port_Handler->OSPEEDR &= ~((0x00000003) << (l_PinNum*2));
	
	switch (ConfigPtr->PinMode)
	{
		/*--------PORT_PIN_MODE_DIO INITIALIZATION-----------------------------*/
		case PORT_PIN_MODE_DIO:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000001) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				/* Set init level for output type DIO*/
				if (PORT_PIN_LEVEL_LOW == ConfigPtr->PinInitValue)
				{
					l_Port_Handler->BSRRH |= ((0x0001) << l_PinNum);
				}
				else if (PORT_PIN_LEVEL_HIGH == ConfigPtr->PinInitValue)
				{
					l_Port_Handler->BSRRL |= ((0x0001) << l_PinNum);
				}
				else
				{
					/*PORT_PIN_LEVEL_DONTCARE*/
				}
			}
			else
			{
				// reset state, no configuration needed.
				/* ??? for rx should test carefully */
			}
			break;
		/*--------PORT_PIN_MODE_USART_1_3 INITIALIZATION-----------------------------*/
		/*--------NOT TESTED YET-----------------------------------------------------*/
		case PORT_PIN_MODE_USART_1_3:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000007	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000007	<< ((l_PinNum & 0x07)*4));
			}
			break;
		/*--------PORT_PIN_MODE_SPI_1_2 INITIALIZATION-------------------------------*/
		/*--------NOT TESTED YET-----------------------------------------------------*/
		case PORT_PIN_MODE_SPI_1_2:										
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000005	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000005	<< ((l_PinNum & 0x07)*4));
			}
			break;
		/*--------PORT_PIN_MODE_SPI_3 INITIALIZATION---------------------------------*/
		/*--------NOT TESTED YET-----------------------------------------------------*/
		case PORT_PIN_MODE_SPI_3:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000006	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000006	<< ((l_PinNum & 0x07)*4));
			}
			break;
			
		case PORT_PIN_MODE_I2C_1_3:
		{
			l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
			l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
			l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));

			l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
			l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000004	<< ((l_PinNum & 0x07)*4));
		}
		break;
		
		case PORT_PIN_MODE_TIM_1_2:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000001	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000001	<< ((l_PinNum & 0x07)*4));
			}
			break;
			
			case PORT_PIN_MODE_TIM_3_5:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000002	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000002	<< ((l_PinNum & 0x07)*4));
			}
			break;
			
			case PORT_PIN_MODE_TIM_8_11:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000003	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				
				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000003	<< ((l_PinNum & 0x07)*4));
			}
			break;

			case PORT_PIN_MODE_CAN_TIM_12_14:
			if (PORT_PIN_OUT == ConfigPtr->PinDirection)
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));
				l_Port_Handler->OTYPER |= ((ConfigPtr->PinHWType) << l_PinNum);
				l_Port_Handler->OSPEEDR |= ((0x00000003) << (l_PinNum*2));

				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000009	<< ((l_PinNum & 0x07)*4));
			}
			else
			{
				l_Port_Handler->MODER |= ((0x00000002) << (l_PinNum*2));

				l_Port_Handler->AFR[l_PinNum >> 0x03] &= ~(0x0000000F << ((l_PinNum & 0x07)*4));
				l_Port_Handler->AFR[l_PinNum >> 0x03] |= (0x00000009	<< ((l_PinNum & 0x07)*4));
			}
			break;
		// will be updated in future ...
		default:
			break;	
	}
	
	// Configure PUPDR : base on PinHWPuPd
	l_Port_Handler->PUPDR |= ((ConfigPtr->PinHWPuPd) << (l_PinNum*2));
}
