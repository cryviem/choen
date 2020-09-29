#ifndef _UART_IF_H_
#define _UART_IF_H_

#include "common_inc.h"

#define UART_FRAME_SIZE								256
#define UART_TX_BUF_SIZE							5
#define UART_RX_BUF_SIZE							5

/* Ring Buffer Operation types */
#define NO_OVERWRT									0x00		//Overwrite not allowed
#define OVERWRT										0x01		//Overwrite allowed.
#define UARTIF_RINGBUFF_TYPE						NO_OVERWRT

typedef enum{
	BUFF_WR_IDLE = 0,
	BUFF_WR_BUSY = 1
} buff_wr_sts_en;

typedef enum{
	BUFF_RD_IDLE = 0,
	BUFF_RD_BUSY = 1
} buff_rd_sts_en;

typedef struct {
	uint8_t											data[UART_FRAME_SIZE];
	uint16_t 										actsize;
} uartFrame_t;

typedef struct {
	uartFrame_t 									framebuff[UART_TX_BUF_SIZE];
	uint8_t 										wptr;
	uint8_t 										rptr;
	buff_wr_sts_en									wr_sts;
	buff_rd_sts_en									rd_sts;
} uartTxRingBuffer_t;

typedef struct {
	uartFrame_t 									framebuff[UART_RX_BUF_SIZE];
	uint8_t 										wptr;
	uint8_t 										rptr;
	buff_wr_sts_en									wr_sts;
	buff_rd_sts_en									rd_sts;
} uartRxRingBuffer_t;




void uartif_RxDMACompleteCbk(uint16_t numofitems);
uint16_t uartif_CheckPendingTxReq(uint32_t* memadr);
uint16_t uartif_GetSpace4RxData(uint32_t* memadr);

void uartif_ClearRingBuffs(void);

RetType uartif_ReqWrTxBuff(uint8_t** memadr);
void uartif_WrTxBuffCpltNotify(uint16_t actsize);
uint16_t uartif_ReqRdTxBuff(uint8_t** memadr);
void uartif_RdTxBuffCpltNotify(void);
	
RetType uartif_ReqWrRxBuff(uint8_t** memadr);
void uartif_WrRxBuffCpltNotify(uint16_t actsize);
uint16_t uartif_ReqRdRxBuff(uint8_t** memadr);
void uartif_RdRxBuffCpltNotify(void);

#endif /* _UART_IF_H_ */
