#include "dmacfg.h"

#include "common_inc.h"


/*typedef struct {
	dma_StreamEN	streamid;
	uint8_t				channelid;
	uint8_t				circularenable;
	uint8_t				transfertype;
	uint8_t				priority;
	uint8_t				direction;
	uint8_t				periphsize;
	uint8_t				memsize;
	uint8_t				addrincrement;
	uint32_t			periphaddress;
	uint32_t			mem0address;
	uint32_t			mem1address;
	
} dma_StreamCfgST;*/
const dma_StreamCfgST user_dmacfgtable[DMA_HANDLER_INVALID] = {
#if(0)
	{
		DMA1_STREAM_6,
		1,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Mem2Periph,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&I2C1->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
	{
		DMA1_STREAM_0,
		1,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Periph2Mem,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&I2C1->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},	
	{				/*SPI2-RX*/
		DMA1_STREAM_3,
		0,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Periph2Mem,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&SPI2->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
	{				/*SPI2-TX*/
		DMA1_STREAM_4,
		0,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Mem2Periph,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&SPI2->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
#endif
	/**********STEPPER************/
	/* BASIC TIMER */
//	{
//		DMA1_STREAM_2,
//		5,
//		FALSE,
//		DMA_TRANSTYPE_DIRECT,
//		DMA_CR_Priority_High,
//		DMA_CR_DIR_Mem2Periph,
//		DMA_CR_PSIZE_16Bit,
//		DMA_CR_PSIZE_16Bit,
//		DMA_ADDRINC_PeriphFixedMemInc,
//		(uint32_t)&TIM3->DMAR,
//		(uint32_t)NULL,
//		(uint32_t)0x00
//	},
	/* ADVANED TIMER */
	{
		DMA2_STREAM_1,
		7,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Mem2Periph,
		DMA_CR_PSIZE_32Bit,
		DMA_CR_MSIZE_32Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&TIM8->DMAR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
	/************UART************/
	{
		DMA2_STREAM_7,
		4,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Mem2Periph,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&USART1->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
	{
		DMA2_STREAM_5,
		4,
		FALSE,
		DMA_TRANSTYPE_DIRECT,
		DMA_CR_Priority_High,
		DMA_CR_DIR_Periph2Mem,
		DMA_CR_PSIZE_8Bit,
		DMA_CR_MSIZE_8Bit,
		DMA_ADDRINC_PeriphFixedMemInc,
		(uint32_t)&USART1->DR,
		(uint32_t)NULL,
		(uint32_t)0x00
	},
};

/*typedef struct {
	dma_StreamEN	streamid;
	uint8_t				channelid;
	uint8_t				circularenable;
	uint8_t				transfertype;
	uint8_t				priority;
	uint8_t				direction;
	uint8_t				periphsize;
	uint8_t				memsize;
	uint8_t				addrincrement;
	uint32_t			periphaddress;
	uint32_t			mem0address;
	uint32_t			mem1address;

} dma_StreamCfgST;*/

dma_StreamHandlerST dma_ramtable[DMA_HANDLER_INVALID];


/* Wrapper DMA CORE with specific configured data */

void dmaproc_updatestatus(void)
{
	uint16_t indx;

	for (indx = 0; indx < DMA_HANDLER_INVALID; indx++)
	{
		dmacore_updatestatus_cycle5ms(&dma_ramtable[indx]);
	}
}

dma_StatusEN dma_getstatus(dma_handler_id_en id)
{
	dma_StatusEN ret = DMA_Status_Error;

	if (id < DMA_HANDLER_INVALID)
	{
		ret = dmacore_getstreamstatus(&dma_ramtable[id]);
	}
	return ret;
}

RetType dma_transfer(dma_handler_id_en id, uint32_t memadr, uint16_t size)
{
	RetType ret = Ret_NotOK;

	if (id < DMA_HANDLER_INVALID)
	{
		ret = dmacore_starttransfer(&dma_ramtable[id], memadr, size);
	}

	return ret;
}

void dma_cleanup(dma_handler_id_en id)
{
	if (id < DMA_HANDLER_INVALID)
	{
		dmacore_finishjob(&dma_ramtable[id]);
	}
}

void dma_stop(dma_handler_id_en id)
{
	if (id < DMA_HANDLER_INVALID)
	{
		dmacore_forcestop(&dma_ramtable[id]);
	}
}

void dma_reset(dma_handler_id_en id)
{
	if (id < DMA_HANDLER_INVALID)
	{
		dmacore_reset(&dma_ramtable[id]);
	}
}

void dma_init(void)
{
	dmacore_init(user_dmacfgtable, dma_ramtable, (uint16_t)DMA_HANDLER_INVALID);
}

uint32_t dma_getNDTR(dma_handler_id_en id)
{
	uint32_t ret = 0;

	if (id < DMA_HANDLER_INVALID)
	{
		ret = dma_ramtable[id].reg.control->NDTR;
	}

	return ret;
}
