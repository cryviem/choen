#ifndef	_DMACFG_H_
#define _DMACFG_H_

/*file: dmacfg.h*/
#include "dmacore.h"
#include "common_inc.h"

typedef enum {
	DMA_HANDLER_TIM3CH2,
	DMA_HANDLER_UART1TX,
	DMA_HANDLER_UART1RX,
	DMA_HANDLER_INVALID
} dma_handler_id_en;

extern void dmaproc_updatestatus(void);
extern dma_StatusEN dma_getstatus(dma_handler_id_en id);
extern RetType dma_transfer(dma_handler_id_en id, uint32_t memadr, uint16_t size);
extern void dma_cleanup(dma_handler_id_en id);
extern void dma_stop(dma_handler_id_en id);
extern void dma_reset(dma_handler_id_en id);
extern void dma_init(void);
extern uint32_t dma_getNDTR(dma_handler_id_en id);

#endif /*_DMACFG_H_*/
