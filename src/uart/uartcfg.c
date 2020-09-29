#include "uartcore.h"
#include "uartcfg.h"
#include "uart_if.h"

/*typedef struct {
	USART_TypeDef* 						channel;
	uint32_t 							baudrate;
	uint8_t								isoversampling8sp;
	dma_handler_id_en					dma_tx_id;
	dma_handler_id_en					dma_rx_id;
	void 								(*pRxCpltCbkFun)(uint16_t);
	uint16_t 							(*pIsPendingTxReqFun)(uint32_t*);
	uint16_t 							(*pGetSpaceRxDataFun)(uint32_t*);
	void 								(*pTxCpltCbkFun)(void);
} uart_cfgtype;*/
const uart_cfgtype uart_cfgtable[UART_HANDLER_INVALID] = {
	{
		USART1,
		115200,
		FALSE,
		DMA_HANDLER_UART1TX,
		DMA_HANDLER_UART1RX,
		&uartif_WrRxBuffCpltNotify,
		&uartif_CheckPendingTxReq,
		&uartif_GetSpace4RxData,
		&uartif_RdTxBuffCpltNotify,
	},
};

uart_handletype uart_ramtable[UART_HANDLER_INVALID];

/* Wrapper UART CORE with specific configured data */
void uart_init(void)
{
	uartcore_init(uart_cfgtable, uart_ramtable, UART_HANDLER_INVALID);
}

void uart_start(void)
{
	uint8_t indx;
	for (indx = 0; indx < UART_HANDLER_INVALID; indx++)
	{
		uartcore_mainprocess_cycle10ms(&uart_ramtable[indx]);
		UART_ENABLE(uart_cfgtable[indx].channel);
		UART_TX_ENABLE(uart_cfgtable[indx].channel);
	}
}
void uart_main_task(void)
{
	uint8_t indx;
	for (indx = 0; indx < UART_HANDLER_INVALID; indx++)
	{
		uartcore_mainprocess_cycle10ms(&uart_ramtable[indx]);
	}
}

void uart_sts_update_task(void)
{
	uint8_t indx;
	for (indx = 0; indx < UART_HANDLER_INVALID; indx++)
	{
		uartcore_eventcheck_cycle5ms(&uart_ramtable[indx]);
	}
}
