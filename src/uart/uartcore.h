
#ifndef _UARTCORE_H_
#define _UARTCORE_H_

#include "common_inc.h"
#include "dmacfg.h"

/* Derived from stm32f4 lib */

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            (((_PCLK_)*25U)/(4U*(_BAUD_)))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        (((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            (((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U)) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             (((_PCLK_)*25U)/(2U*(_BAUD_)))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         (((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             (((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U)) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))
																												
/* uart flags definition */
#define UART_FLAG_CTS									((uint32_t) 0x00000200)		/* currently not supported */
#define UART_FLAG_LBD									((uint32_t) 0x00000100)		/* LIN break detected on line - currently not supported */
#define UART_FLAG_TXE									((uint32_t) 0x00000080)		/* set when tx data was moved to shift reg, ready to store next tx one - reset by a write to DR */
#define UART_FLAG_TC									((uint32_t) 0x00000040)		/* set when tx data sent on bus (TXE already set before) - reset by a read to SR + a write to DR or set 0 by sw*/
#define UART_FLAG_RXNE									((uint32_t) 0x00000020)		/* set when rx data was moved to DR and ready to take by sw - reset by a read to DR or set 0 by sw*/
#define UART_FLAG_IDLE									((uint32_t) 0x00000010)		/* detect bus are free - reset by a read to SR + a read to DR*/
#define UART_FLAG_ORE									((uint32_t) 0x00000008)		/* set when another rx data ready in shift reg  but current data in DR has not been taken by sw (RXNE is 1) - reset by a read to SR + a read to DR*/
#define UART_FLAG_NF									((uint32_t) 0x00000004)		/* noise detect on rx frame - reset by a read to SR + a read to DR - currently not supported */
#define UART_FLAG_FE									((uint32_t) 0x00000002)		/* currently not supported */
#define UART_FLAG_PE									((uint32_t) 0x00000001)		/* parity error - reset b a read to SR + a read or write to DR - sw must wait until RXNE is 1 before clear PE*/
#define UART_FLAG_MASK									((uint32_t) 0x000003FF)
#define UART_GET_FLAG(__HANDLE__, __FLAG__) 			(((__HANDLE__->SR) & ((__FLAG__) & UART_FLAG_MASK)) == ((__FLAG__) & UART_FLAG_MASK))
#define UART_CLEAR_FLAG(__HANDLE__, __FLAG__)			__HANDLE__->SR &= ~__FLAG__

#define UART_CLEAR_IDLE_FLAG(__HANDLE__)\
  do{                                 \
    __IO uint32_t tmpreg = 0x00U;     \
    tmpreg = (__HANDLE__)->SR;       	\
    tmpreg = (__HANDLE__)->DR;       	\
    UNUSED(tmpreg);                   \
  } while(0)
	
#define UART_CR1_UE										((uint32_t) 0x00002000)
#define UART_ENABLE(__HANDLE__)							__HANDLE__->CR1 |= UART_CR1_UE
#define UART_DISABLE(__HANDLE__)						__HANDLE__->CR1 &= ~UART_CR1_UE
#define UART_IS_ENABLE(__HANDLE__)						(__HANDLE__->CR1 & UART_CR1_UE)

#define UART_CR1_TE										((uint32_t) 0x00000008)
#define UART_TX_ENABLE(__HANDLE__)						__HANDLE__->CR1 |= UART_CR1_TE
#define UART_TX_DISABLE(__HANDLE__)						__HANDLE__->CR1 &= ~UART_CR1_TE
#define UART_IS_TXENABLE(__HANDLE__)					(__HANDLE__->CR1 & UART_CR1_TE)

#define UART_CR1_RE										((uint32_t) 0x00000004)
#define UART_RX_ENABLE(__HANDLE__)						__HANDLE__->CR1 |= UART_CR1_RE
#define UART_RX_DISABLE(__HANDLE__)						__HANDLE__->CR1 &= ~UART_CR1_RE
#define UART_IS_RXENABLE(__HANDLE__)					(__HANDLE__->CR1 & UART_CR1_RE)

#define UART_CR3_DMAT									((uint32_t) 0x00000080)
#define UART_DMATX_ENABLE(__HANDLE__)					__HANDLE__->CR3 |= UART_CR3_DMAT
#define UART_DMATX_DISABLE(__HANDLE__)					__HANDLE__->CR3 &= ~UART_CR3_DMAT
#define UART_IS_DMATXENABLE(__HANDLE__)					(__HANDLE__->CR3 & UART_CR3_DMAT)

#define UART_CR3_DMAR									((uint32_t) 0x00000040)
#define UART_DMARX_ENABLE(__HANDLE__)					__HANDLE__->CR3 |= UART_CR3_DMAR
#define UART_DMARX_DISABLE(__HANDLE__)					__HANDLE__->CR3 &= ~UART_CR3_DMAR
#define UART_IS_DMARXENABLE(__HANDLE__)					(__HANDLE__->CR3 & UART_CR3_DMAR)

typedef enum {
	UART_TxSt_IDLE,
	UART_TxSt_TRGR,
	UART_TxSt_BUSY,
	UART_TxSt_ERROR
}	uart_TxStateType;

typedef enum {
	UART_RxSt_IDLE,
	UART_RxSt_BUSY,
	UART_RxSt_ERROR
}	uart_RxStateType;


/*
> isoversampling8sp : 
if TRUE: over sampling by 8 is supported --> advantage: increase the baudrate upto Fsrc/8
disadvantage: reduce the receiver tolerance to clock deviation 

if FALSE: over sampling by 16 is supported --> advantage: get maximum receiver tolerance to clock deviation
disadvantage: baudrate limits at Fsrc/16

*/																												
typedef struct {
	USART_TypeDef* 						channel;
	uint32_t 							baudrate;
	uint8_t								isoversampling8sp;
	dma_handler_id_en					dma_tx_id;
	dma_handler_id_en					dma_rx_id;
	void 								(*pRxCpltCbkFun)(uint16_t);
	uint16_t 							(*pIsPendingTxReqFun)(uint32_t*);
	uint16_t 							(*pGetSpaceRxDataFun)(uint32_t*);
	void 								(*pTxCpltCbkFun)(void);
} uart_cfgtype;

typedef struct {
	const uart_cfgtype*					cfg_table;
	volatile uart_TxStateType 			txstate;
	volatile uart_RxStateType 			rxstate;
} uart_handletype;




/* public function declare */
void uartcore_init(const uart_cfgtype* uartcfg, uart_handletype* uarthandler, uint8_t numOfInst);
void uartcore_mainprocess_cycle10ms(uart_handletype* uarthandler);
void uartcore_eventcheck_cycle5ms(uart_handletype* uarthandler);
#endif /* _P_UARTCORE_H_ */
