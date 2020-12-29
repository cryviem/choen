//Choen
#ifndef	PORT_PORT_H_
#define PORT_PORT_H_

#include "common_inc.h"

// ----- Port_ConfigType->PinNumber definitions -----
#define PIN_0                 0
#define PIN_1                 1
#define PIN_2                 2
#define PIN_3                 3
#define PIN_4                 4
#define PIN_5                 5
#define PIN_6                 6
#define PIN_7                 7
#define PIN_8                 8
#define PIN_9                 9
#define PIN_10                10
#define PIN_11                11
#define PIN_12                12
#define PIN_13                13
#define PIN_14                14
#define PIN_15                15
//----------------------------------------------------

// ----- Port_ConfigType->PortName definitions -----
#define PORT_A								0
#define PORT_B								1
#define PORT_C								2
#define PORT_D								3
#define PORT_E								4
#define PORT_F								5
#define PORT_G								6
#define PORT_H								7
#define PORT_I								8
//--------------------------------------------------

	//-Port A definitions---------
#define	PORT_A_PIN_0										0x00
#define	PORT_A_PIN_1										0x01
#define	PORT_A_PIN_2										0x02
#define	PORT_A_PIN_3										0x03
#define	PORT_A_PIN_4										0x04
	// miss 5
#define	PORT_A_PIN_6										0x06
#define	PORT_A_PIN_7										0x07
#define	PORT_A_PIN_8										0x08
#define	PORT_A_PIN_9										0x09
#define	PORT_A_PIN_10										0x0A
	// miss 11, 12
#define	PORT_A_PIN_13										0x0D
#define	PORT_A_PIN_14										0x0E
#define	PORT_A_PIN_15										0x0F
	//----------------------------
	//-Port B definitions---------
#define	PORT_B_PIN_0										0x10
#define	PORT_B_PIN_1										0x11
#define	PORT_B_PIN_2										0x12
#define	PORT_B_PIN_3										0x13
#define	PORT_B_PIN_4										0x14
#define	PORT_B_PIN_5										0x15
#define	PORT_B_PIN_6										0x16
#define	PORT_B_PIN_7										0x17
#define	PORT_B_PIN_8										0x18
#define	PORT_B_PIN_9										0x19
#define	PORT_B_PIN_10										0x1A
#define	PORT_B_PIN_11										0x1B
#define	PORT_B_PIN_12										0x1C
#define	PORT_B_PIN_13										0x1D
#define	PORT_B_PIN_14										0x1E
#define	PORT_B_PIN_15										0x1F
	//----------------------------
	//-Port C definitions---------
#define	PORT_C_PIN_0										0x20
#define	PORT_C_PIN_1										0x21
#define	PORT_C_PIN_2										0x22
#define	PORT_C_PIN_3										0x23
#define	PORT_C_PIN_4										0x24
#define	PORT_C_PIN_5										0x25
#define	PORT_C_PIN_6										0x26
#define	PORT_C_PIN_7										0x27
#define	PORT_C_PIN_8										0x28
#define	PORT_C_PIN_9										0x29
#define	PORT_C_PIN_10										0x2A
#define	PORT_C_PIN_11										0x2B
#define	PORT_C_PIN_12										0x2C
#define	PORT_C_PIN_13										0x2D
#define	PORT_C_PIN_14										0x2E
#define	PORT_C_PIN_15										0x2F
	//----------------------------
	//-Port D definitions---------
#define	PORT_D_PIN_0										0x30
#define	PORT_D_PIN_1										0x31
#define	PORT_D_PIN_2										0x32
#define	PORT_D_PIN_3										0x33
#define	PORT_D_PIN_4										0x34
#define	PORT_D_PIN_5										0x35
#define	PORT_D_PIN_6										0x36
#define	PORT_D_PIN_7										0x37
#define	PORT_D_PIN_8										0x38
#define	PORT_D_PIN_9										0x39
#define	PORT_D_PIN_10										0x3A
#define	PORT_D_PIN_11										0x3B
#define	PORT_D_PIN_12										0x3C
#define	PORT_D_PIN_13										0x3D
#define	PORT_D_PIN_14										0x3E
#define	PORT_D_PIN_15										0x3F
	//----------------------------
	//-Port E definitions---------
#define	PORT_E_PIN_0										0x40
#define	PORT_E_PIN_1										0x41
#define	PORT_E_PIN_2										0x42
#define	PORT_E_PIN_3										0x43
#define	PORT_E_PIN_4										0x44
#define	PORT_E_PIN_5										0x45
#define	PORT_E_PIN_6										0x46
#define	PORT_E_PIN_7										0x47
#define	PORT_E_PIN_8										0x48
#define	PORT_E_PIN_9										0x49
#define	PORT_E_PIN_10										0x4A
#define	PORT_E_PIN_11										0x4B
#define	PORT_E_PIN_12										0x4C
#define	PORT_E_PIN_13										0x4D
#define	PORT_E_PIN_14										0x4E
#define	PORT_E_PIN_15										0x4F
	//----------------------------
	//-Port F definitions---------							0x5x
	//----------------------------
	//-Port G definitions---------							0x6x
	//----------------------------
	//-Port H definitions---------
#define	PORT_H_PIN_0										0x70
#define	PORT_H_PIN_1										0x71
	//----------------------------
#define	PORT_ENDFLAG										0xFF
/*--NUMBER OF PINS USED --*/


#define	PORT_GETPORT(x)									((x & 0xF0) >> 4)
#define	PORT_GETPIN(x)									(x & 0x0F)

// ----- Port_ConfigType->PinHWType definitions -----
#define	PORT_PIN_HW_PUSHPULL 						0x00
#define	PORT_PIN_HW_OPENDRAIN  					0x01
#define	PORT_PIN_HW_DEFAULT  						PORT_PIN_HW_PUSHPULL
//---------------------------------------------------

// ----- Port_ConfigType->PinHWPuPd definitions -----
#define	PORT_PIN_HW_PULL_UP  						0x01
#define	PORT_PIN_HW_PULL_DOWN  					0x02
#define	PORT_PIN_HW_NO_PUPD  						0x00
//---------------------------------------------------

typedef enum {
	PORT_PIN_MODE_DIO, 
	PORT_PIN_MODE_SYSTEM, 												//	AF0	
	PORT_PIN_MODE_TIM_1_2,												//  AF1
	PORT_PIN_MODE_TIM_3_5,												//  AF2
	PORT_PIN_MODE_TIM_8_11,												//	AF3
	PORT_PIN_MODE_I2C_1_3,												//  AF4
	PORT_PIN_MODE_SPI_1_2,												//	AF5
	PORT_PIN_MODE_SPI_3,												//	AF6
	PORT_PIN_MODE_USART_1_3,											//	AF7
	PORT_PIN_MODE_USART_4_6,											//	AF8
	PORT_PIN_MODE_CAN_TIM_12_14,										//	AF9
	PORT_PIN_MODE_USB_OTG,												//	AF10
	PORT_PIN_MODE_ETH,													//	AF11
	PORT_PIN_MODE_FSMC_SDIO_OTG_HS,										//	AF12
	PORT_PIN_MODE_DCMI,													//	AF13
	PORT_PIN_MODE_EVENTOUT,												//	AF15
} Port_PinModeType;

typedef enum {
	PORT_PIN_IN,
	PORT_PIN_OUT,
	PORT_PIN_BIDIR
} Port_PinDirectionType;

typedef enum {
	PORT_PIN_LEVEL_LOW,
	PORT_PIN_LEVEL_HIGH,
	PORT_PIN_LEVEL_DONTCARE
} Port_PinLevelValueType;



typedef struct {
	// specific
	uint8_t											PortPinName;
	uint8_t											PinHWType;
	uint8_t											PinHWPuPd;
	// standard
	Port_PinModeType								PinMode;
	Port_PinDirectionType							PinDirection;
	Port_PinLevelValueType							PinInitValue;
} Port_ConfigType;

/*----------------------------------------------------------------------------------------*/
/*function declaration*/
void Port_Init(const Port_ConfigType* ConfigPtr);

Port_PinModeType Port_GetPinMode(const Port_ConfigType* ConfigPtr, uint8_t PinName);
Port_PinDirectionType Port_GetPinDirection(const Port_ConfigType* ConfigPtr, uint8_t PinName);

void Port_WritePort(uint8_t PortId, uint16_t Level);
void Port_WritePin(uint8_t PinID, Port_PinLevelValueType Level);
uint16_t Port_ReadPort(uint8_t PortId);
Port_PinLevelValueType Port_ReadPin(uint8_t PinID);

#endif	//PORT_H
