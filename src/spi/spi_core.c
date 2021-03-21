/*
	* spi_core.c
	*
	*  Created on: June 23, 2018
	*  Author: Mr.A
*/
#include "common_inc.h"
#include "spi_core.h"
#include "spi_cfg.h"
#include "dmacfg.h"
/*	PRIVATE VARIABLE DECLARATION BEGIN*/
/*	PRIVATE VARIABLE DECLARATION END*/

/*	PRIVATE FUNCTION DECLARATION BEGIN*/

/*	PRIVATE FUNCTION DECLARATION END*/

/* refer: reference manual 28.3.3 */
static void spi_subinit(const spi_cfg_type* cfgtable)
{
	
	SPI_TypeDef *l_reg;
	uint16_t	tmpu16;
	
	l_reg = cfgtable->reg;
	
	/*clear all cfg regs*/
	l_reg->CR1 = 0x0000;
	l_reg->CR2 = 0x0000;
	
	/* baudrate configure */
	tmpu16 = (uint16_t)cfgtable->baudrate;
	if (tmpu16 >= SPI_BR_INVALID)
	{
		/* baudrate invalid */
		return;
	}
	
	tmpu16 = tmpu16 << 3;
	l_reg->CR1 |= tmpu16;
	
	/* polarity and phase configure */
	tmpu16 = (uint16_t)cfgtable->clkmode;
	if (tmpu16 >= SPI_CLKMODE_INVALID)
	{
		/* baudrate invalid */
		return;
	}
	
	l_reg->CR1 |= tmpu16;
	
	switch (cfgtable->optype)
	{
		case SPI_OPTYPE_FULLDUPLEX:
		case SPI_OPTYPE_TXONLY:
			/*clear BIDIMODE and RXONLY bits*/
			/*cleared from above*/
			break;
		case SPI_OPTYPE_BIDIREC_TXFIRST:
			/*set BIDIMODE and BIDIOE bits*/
			l_reg->CR1 |= (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE);
			break;
		case SPI_OPTYPE_BIDIREC_RXFIRST:
			/*set BIDIMODE bit*/
			l_reg->CR1 |= SPI_CR1_BIDIMODE;
			break;
		case SPI_OPTYPE_RXONLY:
			l_reg->CR1 |= SPI_CR1_RXONLY;
			break;
		default:

			break;
	}

	/* Data frame format configure */
	if (cfgtable->is16bDFFsp == FALSE)
	{
		l_reg->CR1 &= ~SPI_CR1_DFF;
	}
	else
	{
		l_reg->CR1 |= SPI_CR1_DFF;
	}
	
	/* MSB or LSB should go first */
	if (cfgtable->isLSBgofirst == FALSE)
	{
		l_reg->CR1 &= ~SPI_CR1_LSBFIRST;
	}
	else
	{
		l_reg->CR1 |= SPI_CR1_LSBFIRST;
	}
	
	/*NSS configure*/
	if (cfgtable->isHWCSused)
	{
		/*make sure SSM bit is clear to choose Hardware management*/
		l_reg->CR1 &= ~SPI_CR1_SSM;
		/*set SSOE bit to ENABLE output on NSS pin*/
		l_reg->CR2 |= SPI_CR2_SSOE;
	}
	else
	{
		/*setup to keep master mode*/
		l_reg->CR1 |= SPI_CR1_SSM;
		l_reg->CR1 |= SPI_CR1_SSI;
	}
	/*make sure FRF bit is clear to choose Motorola mode*/
	/*trusted*/

	/*Set MSTR bit to choose master role*/
	l_reg->CR1 |= SPI_CR1_MSTR;
}

void spicore_init(const spi_cfg_type* spicfg, spi_hdl_type* spihandler)
{
	uint8_t	l_index;
	
	/*clear the handler before initialization*/
	pf_memset(spihandler, 0, sizeof(spi_hdl_type));

	for (l_index = 0; l_index < SPI_HANDLER_INVALID; l_index++)
	{
		/* call sub init function for spi hardware initialization */
		spi_subinit(&spicfg[l_index]);

		/* initialize handlers*/
		spihandler[l_index].cfgtable = &spicfg[l_index];
		spihandler[l_index].txbox.status = SPI_TXSTS_OFF;
		spihandler[l_index].rxbox.status = SPI_RXSTS_OFF;
	}
}

RetType spicore_transmit(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len)
{

	if (!SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		/*spi channel disabled*/
		return Ret_NotOK;
	}

	if (hdler->txbox.status == SPI_TXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYNOR)
	{
		/* busy transmitting*/
		return Ret_NotOK;
	}

	if (len == 0)
	{
		/* invalid data length*/
		return Ret_NotOK;
	}
	
	/* save data to handler*/
	hdler->txbox.reqid = reqid;
	hdler->txbox.pnor_databuf = pdata;
	hdler->txbox.nor_len = len;
	
	/* do the first transmission*/
	hdler->cfgtable->reg->DR = (SPI_IS_16BFORMAT(hdler->cfgtable->reg)? *((uint16_t*)pdata) : *((uint8_t*)pdata));
	hdler->txbox.nor_cnt = 1;

	hdler->txbox.status = SPI_TXSTS_BUSYNOR;
	return Ret_OK;
}

RetType spicore_transmit_dma(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len)
{
	if (!SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		/*spi channel disabled*/
		return Ret_NotOK;
	}

	if (hdler->txbox.status == SPI_TXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYNOR)
	{
		/* busy transmitting*/
		return Ret_NotOK;
	}

	/* start DMA stream */
	if (Ret_OK == dma_transfer(hdler->cfgtable->dma_tx_id, (uint32_t) pdata, len))
	{
		/* trigger DMA successfully - go to other state*/
		hdler->txbox.reqid = reqid;
		SPI_TXDMA_ENABLE(hdler->cfgtable->reg);
		hdler->txbox.status = SPI_TXSTS_BUSYDMA;
		return Ret_OK;
	}
	else
	{
		return Ret_NotOK;
	}
}

RetType spicore_receive_dma(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len)
{
	if (!SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		/*spi channel disabled*/
		return Ret_NotOK;
	}

	if (hdler->rxbox.status == SPI_RXSTS_BUSYDMA)
	{
		/* busy transmitting*/
		return Ret_NotOK;
	}

	if (len == 0)
	{
		/*length invalid*/
		return Ret_NotOK;
	}

	/* Do clear OVR flag*/
	SPI_CLEAR_OVR_FLAG(hdler->cfgtable->reg);

	/* start DMA stream */
	if (Ret_OK == dma_transfer(hdler->cfgtable->dma_rx_id, (uint32_t) pdata, len))
	{
		/* trigger DMA successfully - go to other state*/
		hdler->rxbox.reqid = reqid;
		hdler->rxbox.tarlen = len;
		SPI_RXDMA_ENABLE(hdler->cfgtable->reg);
		hdler->rxbox.status = SPI_RXSTS_BUSYDMA;
		return Ret_OK;
	}
	else
	{
		return Ret_NotOK;
	}
}

RetType spicore_fullduplex_work_dma(spi_hdl_type* hdler, uint16_t reqid, void* ptxdata, void* prxdata, uint16_t len)
{
	if (!SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		/*spi channel disabled*/
		return Ret_NotOK;
	}

	if (hdler->txbox.status == SPI_TXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYNOR || hdler->rxbox.status == SPI_RXSTS_BUSYDMA)
	{
		/* busy*/
		return Ret_NotOK;
	}
	/* Do clear OVR flag*/
	SPI_CLEAR_OVR_FLAG(hdler->cfgtable->reg);

	/* Setup DMA for receiving */
	if (Ret_NotOK == dma_transfer(hdler->cfgtable->dma_rx_id, (uint32_t) prxdata, len))
	{
		return Ret_NotOK;
	}

	hdler->rxbox.reqid = reqid;
	hdler->rxbox.tarlen = len;
	SPI_RXDMA_ENABLE(hdler->cfgtable->reg);
	hdler->rxbox.status = SPI_RXSTS_BUSYDMA;

	/* Setup DMA for transmitting */
	if (Ret_NotOK == dma_transfer(hdler->cfgtable->dma_tx_id, (uint32_t) ptxdata, len))
	{
		SPI_RXDMA_DISABLE(hdler->cfgtable->reg);
		hdler->rxbox.status = SPI_RXSTS_IDLE;
		dma_reset(hdler->cfgtable->dma_rx_id);
		return Ret_NotOK;
	}
	/* trigger DMA successfully - go to other state*/
	hdler->txbox.reqid = reqid;
	SPI_TXDMA_ENABLE(hdler->cfgtable->reg);
	hdler->txbox.status = SPI_TXSTS_BUSYDMA;
	return Ret_OK;
}

RetType spicore_bidirec_setup_tx(spi_hdl_type* hdler)
{
	if (hdler->rxbox.status == SPI_RXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYNOR)
	{
		/* busy transmitting*/
		return Ret_NotOK;
	}
	
	if (SPI_GETFLAG(hdler->cfgtable->reg, SPI_SR_BSY))
	{
		/* busy flag set*/
		return Ret_NotOK;
	}
	
	/* Now, it's safe to disable SPI channel for re-cfg*/
	if (SPI_READ_BIDIOE(hdler->cfgtable->reg))
	{
		return Ret_OK;
	}
	
	if (SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		SPI_DISABLE(hdler->cfgtable->reg);
		SPI_SET_BIDIOE(hdler->cfgtable->reg);
		SPI_ENABLE(hdler->cfgtable->reg);
	}
	else
	{
		SPI_SET_BIDIOE(hdler->cfgtable->reg);
	}

	return Ret_OK;
}

RetType spicore_bidirec_setup_rx(spi_hdl_type* hdler)
{
	if (hdler->rxbox.status == SPI_RXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYDMA || hdler->txbox.status == SPI_TXSTS_BUSYNOR)
	{
		/* busy transmitting*/
		return Ret_NotOK;
	}
	
	if (SPI_GETFLAG(hdler->cfgtable->reg, SPI_SR_BSY))
	{
		/* busy flag set*/
		return Ret_NotOK;
	}
	
	/* Now, it's safe to disable SPI channel for re-cfg*/
	if (!SPI_READ_BIDIOE(hdler->cfgtable->reg))
	{
		return Ret_OK;
	}
	
	if (SPI_IS_ENABLE(hdler->cfgtable->reg))
	{
		SPI_DISABLE(hdler->cfgtable->reg);
		SPI_CLEAR_BIDIOE(hdler->cfgtable->reg);
		SPI_ENABLE(hdler->cfgtable->reg);
	}
	else
	{
		SPI_CLEAR_BIDIOE(hdler->cfgtable->reg);
	}
	
	return Ret_OK;
}

RetType spicore_bidirec_is_tx(spi_hdl_type* hdler)
{
	if (SPI_READ_BIDIOE(hdler->cfgtable->reg))
	{
		return Ret_OK;
	}
	else
	{
		return Ret_NotOK;
	}
}

void spicore_start(spi_hdl_type* hdler, spi_run_type run)
{
	
	SPI_ENABLE(hdler->cfgtable->reg);
	
	switch (run)
	{
		case SPI_SW_FULL:
			hdler->rxbox.status = SPI_RXSTS_IDLE;
			hdler->txbox.status = SPI_TXSTS_IDLE;
			break;
		
		case SPI_SW_TX:
			hdler->rxbox.status = SPI_RXSTS_OFF;
			hdler->txbox.status = SPI_TXSTS_IDLE;
			break;
		
		case SPI_SW_RX:
			hdler->rxbox.status = SPI_RXSTS_IDLE;
			hdler->txbox.status = SPI_TXSTS_OFF;
			break;
	}
}

void spicore_stop(spi_hdl_type* hdler)
{
	SPI_DISABLE(hdler->cfgtable->reg);
	hdler->rxbox.status = SPI_RXSTS_OFF;
	hdler->txbox.status = SPI_TXSTS_OFF;
}

void spiproc_maintask(spi_hdl_type* hdler)
{
	SPI_TypeDef *l_reg;
	uint16_t	tmpu16;

	l_reg = hdler->cfgtable->reg;
	
	if (SPI_IS_ENABLE(l_reg))
	{
		/* TX SECTION - BEGIN ***********************************/
		if (hdler->txbox.status == SPI_TXSTS_BUSYDMA)
		{
			switch(dma_getstatus(hdler->cfgtable->dma_tx_id))
			{
			case DMA_Status_Error:
			{
				/* error occurred from DMA - reset DMA state anyway */
				dma_cleanup(hdler->cfgtable->dma_tx_id);
				SPI_TXDMA_DISABLE(l_reg);
				/* go to error state */
				hdler->txbox.status = SPI_TXSTS_ERROR;
				break;
			}
			case DMA_Status_Completed:
			{
				if (SPI_GETFLAG(l_reg, SPI_SR_TXE))
				{
					/* make DMA ready for new transfer */
					dma_cleanup(hdler->cfgtable->dma_tx_id);
					SPI_TXDMA_DISABLE(l_reg);
					/* back to the IDLE state */
					hdler->txbox.status = SPI_TXSTS_IDLE;
					/* call transmitted indication with respective request id */
					if (hdler->cfgtable->cbftable.spi_txindcn_cb != NULL)
					{
						hdler->cfgtable->cbftable.spi_txindcn_cb(hdler->txbox.reqid);
					}

				}
				break;
			}
			case DMA_Status_NotStarted:
			{
				/*unexpected case: add lamp to check*/
				SPI_TXDMA_DISABLE(l_reg);
				hdler->txbox.status = SPI_TXSTS_ERROR;
				break;
			}
			default:
			{
				/* triggered and in process states - just wait */
				break;
			}
			}
		}
		else if (hdler->txbox.status == SPI_TXSTS_BUSYNOR)
		{
			if (SPI_GETFLAG(l_reg, SPI_SR_TXE))
			{
				if (hdler->txbox.nor_cnt < hdler->txbox.nor_len)
				{
					/*put the next byte to DR reg*/
					l_reg->DR = (SPI_IS_16BFORMAT(l_reg)? \
					*((uint16_t*)hdler->txbox.pnor_databuf + hdler->txbox.nor_cnt) : \
					*((uint8_t*)hdler->txbox.pnor_databuf + hdler->txbox.nor_cnt));
					
					hdler->txbox.nor_cnt++;
				}
				else
				{
					/* well done, go to idle*/
					hdler->txbox.status = SPI_TXSTS_IDLE;
					/* call transmitted indication with respective request id */
					if (hdler->cfgtable->cbftable.spi_txindcn_cb != NULL)
					{
						hdler->cfgtable->cbftable.spi_txindcn_cb(hdler->txbox.reqid);
					}		
				}
			}
		}
		else if (hdler->txbox.status == SPI_TXSTS_ERROR)
		{
			if (hdler->cfgtable->cbftable.spi_txerror_cb != NULL)
			{
				hdler->cfgtable->cbftable.spi_txerror_cb(hdler->txbox.reqid);
			}
			hdler->txbox.status = SPI_TXSTS_IDLE;
		}
		/* TX SECTION - END *************************************/

		/* RX SECTION - BEGIN ***********************************/
		if (hdler->rxbox.status == SPI_RXSTS_BUSYDMA)
		{
			switch(dma_getstatus(hdler->cfgtable->dma_rx_id))
			{
			case DMA_Status_Error:
			{
				/* error occurred from DMA - reset DMA state anyway */
				dma_cleanup(hdler->cfgtable->dma_rx_id);
				SPI_RXDMA_DISABLE(l_reg);
				/* go to error state */
				hdler->rxbox.status = SPI_RXSTS_ERROR;
				break;
			}
			case DMA_Status_Completed:
			{
				/* make DMA ready for new transfer */
				dma_cleanup(hdler->cfgtable->dma_rx_id);
				SPI_RXDMA_DISABLE(l_reg);
				
				/* call received notification with respective request id and quantity of received data */
				if (hdler->cfgtable->cbftable.spi_rxcplt_cb != NULL)
				{
					tmpu16 = dma_getNDTR(hdler->cfgtable->dma_rx_id);
					tmpu16 = hdler->rxbox.tarlen - tmpu16;
					hdler->cfgtable->cbftable.spi_rxcplt_cb(hdler->rxbox.reqid, tmpu16);
				}

				/* back to the IDLE state */
				hdler->rxbox.status = SPI_RXSTS_IDLE;

				break;
			}
			case DMA_Status_NotStarted:
			{
				/*unexpected case: add lamp to check*/
				SPI_RXDMA_DISABLE(l_reg);
				hdler->rxbox.status = SPI_RXSTS_ERROR;
				break;
			}
			default:
			{
				/* triggered and in process states - just wait */
				break;
			}
			}
		}
		else if (hdler->rxbox.status == SPI_RXSTS_ERROR)
		{
			if (hdler->cfgtable->cbftable.spi_rxerror_cb != NULL)
			{
				hdler->cfgtable->cbftable.spi_rxerror_cb(hdler->rxbox.reqid);
			}
			hdler->rxbox.status = SPI_RXSTS_IDLE;
		}
		/* RX SECTION - END *************************************/
	}
}




