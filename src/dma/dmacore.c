
#include "dmacore.h"

#include "common_inc.h"


const dma_StreamRegST cnst_dma_reglib[] = {
	{DMA1, 0x00, DMA1_Stream0},
	{DMA1, 0x06, DMA1_Stream1},
	{DMA1, 0x10, DMA1_Stream2},
	{DMA1, 0x16, DMA1_Stream3},
	{DMA1, 0x80, DMA1_Stream4},
	{DMA1, 0x86, DMA1_Stream5},
	{DMA1, 0x90, DMA1_Stream6},
	{DMA1, 0x96, DMA1_Stream7},
	{DMA2, 0x00, DMA2_Stream0},
	{DMA2, 0x06, DMA2_Stream1},
	{DMA2, 0x10, DMA2_Stream2},
	{DMA2, 0x16, DMA2_Stream3},
	{DMA2, 0x80, DMA2_Stream4},
	{DMA2, 0x86, DMA2_Stream5},
	{DMA2, 0x90, DMA2_Stream6},
	{DMA2, 0x96, DMA2_Stream7}
};

/* private function begin */
static dma_StreamRegST getstreamreg(dma_StreamEN streamid);
static uint8_t isSRflagset(dma_StreamRegST streamreg, uint32_t flag);
static void clearSRflag(dma_StreamRegST streamreg, uint32_t flag);
static void streamsubinit(const dma_StreamCfgST* streamcfg, dma_StreamHandlerST* streamhler);
/* private function end */


static dma_StreamRegST getstreamreg(dma_StreamEN streamid)
{
	return cnst_dma_reglib[streamid];
}

static uint8_t isSRflagset(dma_StreamRegST streamreg, uint32_t flag)
{
	uint32_t	tmpreg = 0;
	uint8_t		actoffset;
	
	if (streamreg.offset < 0x80)
	{
		tmpreg = streamreg.status->LISR;
		actoffset = streamreg.offset;
	}
	else
	{
		tmpreg = streamreg.status->HISR;
		actoffset = streamreg.offset - 0x80;
	}	
	
	if (actoffset > 0)
	{
		tmpreg = (tmpreg >> actoffset);
	}
	
	if (tmpreg & flag)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static void clearSRflag(dma_StreamRegST streamreg, uint32_t flag)
{
	uint32_t	tmpreg = flag;
	uint8_t		actoffset = streamreg.offset;
	
	actoffset &= 0x7F;
	
	tmpreg = (uint32_t)(tmpreg << actoffset);
	
	if (streamreg.offset < 0x80)
	{
		streamreg.status->LIFCR |= tmpreg;
	}
	else
	{
		streamreg.status->HIFCR |= tmpreg;
	}	
}

static void streamsubinit(const dma_StreamCfgST* streamcfg, dma_StreamHandlerST* streamhler)
{
	dma_StreamRegST tmpreg;
	
	/* GET STREAM REG ADDRESS AND STORE INTO HANDLER STRUCT */
	/* Call one in initial time for a stream */
	/* get stream registers */	
	tmpreg = getstreamreg(streamcfg->streamid);
	
	/* store into handler */
	streamhler->reg = tmpreg;
	/********************************************************/
	
	/* DMA STREAM CONFIGURATION */
	/* disable DMA stream before configuration */
	ClearAndWaitUntilENCleared(tmpreg.control)
	/* Test point 1 begin - make sure ClearAndWaitUntilENCleared macro work properly */
	/* Test point 1 end */
	
	/* assign peripheral address to SxPAR */
	tmpreg.control->PAR = streamcfg->periphaddress;
	
	/* assign memory address to SxMA0R */
	tmpreg.control->M0AR = streamcfg->mem0address;
	
	/* assign memory address to SxMA1R */
	/* will be update later */
	
	/* configure DMA channel */
	DMA_CR_ChannelSelect(tmpreg.control, streamcfg->channelid);
	
	/* the bits that should reset by default */
	tmpreg.control->CR &= ~(DMA_CR_DoubleBufferModeSwitch + DMA_CR_PINCOS + DMA_CR_PeriphFlowControl);
	
	/* configure stream priority */
	DMA_CR_Priority_Cfg(tmpreg.control, streamcfg->priority);
	
	if (streamcfg->transfertype == DMA_TRANSTYPE_DIRECT)
	{
		/* FIFO will not be used */
		tmpreg.control->FCR &= ~DMA_FCR_DirectModeDisable;
		
		/* Make sure no FIFO error interrupt */
		tmpreg.control->FCR &= ~DMA_FCR_IntEn_FIFOError;
		
		DMA_CR_MBURST_Cfg(tmpreg.control, DMA_CR_MBURST_SINGLE);
		
		DMA_CR_PBURST_Cfg(tmpreg.control, DMA_CR_PBURST_SINGLE);
		
		DMA_CR_PSIZE_Cfg(tmpreg.control, streamcfg->periphsize);
		
		/* memory size need to be follow peripheral size in direct mode */
		DMA_CR_MSIZE_Cfg(tmpreg.control, streamcfg->periphsize);
	}
	else
	{
		/* burst mode */
	}
	
	/* configure transfer direction */
	DMA_CR_Direction_Cfg(tmpreg.control, streamcfg->direction);
	
	/* configure address increament */
	switch (streamcfg->addrincrement)
	{
		case DMA_ADDRINC_AllFixed:
		{
			tmpreg.control->CR &= ~(DMA_CR_MemPtrIncSupport + DMA_CR_PeriphPtrIncSupport);
			break;
		}

		case DMA_ADDRINC_AllInc:
		{
			tmpreg.control->CR |= (DMA_CR_MemPtrIncSupport + DMA_CR_PeriphPtrIncSupport);
			break;
		}
		
		case DMA_ADDRINC_PeriphFixedMemInc:
		{
			tmpreg.control->CR &= ~DMA_CR_PeriphPtrIncSupport;
			tmpreg.control->CR |= DMA_CR_MemPtrIncSupport;
			break;
		}
		
		case DMA_ADDRINC_PeriphIncMemFixed:
		{
			tmpreg.control->CR |= DMA_CR_PeriphPtrIncSupport;
			tmpreg.control->CR &= ~DMA_CR_MemPtrIncSupport;
			break;
		}
		
		default:
			break;
	}
	
	/* configure circular mode */
	if (streamcfg->circularenable == TRUE)
	{
		tmpreg.control->CR |= DMA_CR_CircularModeSupport;
	}
	else
	{
		tmpreg.control->CR &= ~DMA_CR_CircularModeSupport;
	}
}

void dmacore_init(const dma_StreamCfgST* dma_cfgtable, dma_StreamHandlerST* streamhlertb, uint16_t	numOfInst)
{
	uint16_t	l_index = 0;
	for (l_index = 0; l_index < numOfInst; l_index++)
	{
		streamsubinit(&dma_cfgtable[l_index], &streamhlertb[l_index]);
		streamhlertb[l_index].state = DMA_Status_NotStarted;
	}
}

RetType dmacore_starttransfer(dma_StreamHandlerST* streamhler, uint32_t memadr, uint16_t size)
{
	dma_StreamRegST tmpreg;
	tmpreg = streamhler->reg;
	
	if (streamhler->state != DMA_Status_NotStarted)
	{
		/* wrong state to start */
		return Ret_NotOK;
	}
		
	if ((tmpreg.control->CR & DMA_CR_StreamEnable) ==  DMA_CR_StreamEnable)
	{
		/* EN bit is currently set */
		return Ret_NotOK;
	}
	
	if ((memadr == 0) && (tmpreg.control->M0AR == 0))
	{
		/* mem address invalid */
		return Ret_NotOK;
	}
	
	/* clear status flag before starting a stream */
	clearSRflag(tmpreg, DMA_SR_MASK);
			
	/* set number of data items */
	tmpreg.control->NDTR = (uint32_t) size;
			
	/* set memory address */
	if (memadr != 0)
	{
		tmpreg.control->M0AR = memadr;
	}
	
	/* change handle state to triggered */
	streamhler->state = DMA_Status_Triggered;
		
	/* enable dma stream */
	tmpreg.control->CR |= DMA_CR_StreamEnable;
	return Ret_OK;
}

void dmacore_updatestatus_cycle5ms(dma_StreamHandlerST* streamhler)
{
	dma_StatusEN tmpstate = streamhler->state;
	dma_StreamRegST tmpreg;
	tmpreg = streamhler->reg;
	/* if TC is set and TE and DME are clear --> transfer complete*/
	
	if ((tmpstate == DMA_Status_Triggered) || (tmpstate == DMA_Status_InProcess))
	{
		if (isSRflagset(tmpreg, DMA_FLAG_TransferComplete))
		{
			tmpstate = DMA_Status_Completed;
		}
		else
		{
			tmpstate = DMA_Status_InProcess;
		}
		

		if (isSRflagset(tmpreg, (DMA_FLAG_TransferError | DMA_FLAG_DirectModeError | DMA_FLAG_FIFOError)))
		{
			tmpstate = DMA_Status_Error;
		}
		
		/* update handle state */
		streamhler->state = tmpstate;
	}
}

dma_StatusEN dmacore_getstreamstatus(dma_StreamHandlerST* streamhler)
{
	return streamhler->state;
}

void dmacore_finishjob(dma_StreamHandlerST* streamhler)
{
	if ((streamhler->state == DMA_Status_Error) || (streamhler->state == DMA_Status_Completed))
	{
		streamhler->reg.control->CR &= ~DMA_CR_StreamEnable;
		streamhler->state = DMA_Status_NotStarted;
	}
}

void dmacore_forcestop(dma_StreamHandlerST* streamhler)
{
	/* force DMA stream stop by application */
	streamhler->reg.control->CR &= ~DMA_CR_StreamEnable;
}

void dmacore_reset(dma_StreamHandlerST* streamhler)
{
		streamhler->reg.control->CR &= ~DMA_CR_StreamEnable;
		streamhler->state = DMA_Status_NotStarted;
}

