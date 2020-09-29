#include "common_inc.h"
#include "uartcore.h"
#include "dmacfg.h"


/* private function declare begin */
static void subinit(const uart_cfgtype* uartcfg);
/* private function declare begin */

static void subinit(const uart_cfgtype* uartcfg)
{
	uint32_t regtmp;
	
	/* reset all the reg */
	uartcfg->channel->CR1 = 0x00000000;
	uartcfg->channel->CR2 = 0x00000000;
	uartcfg->channel->CR3 = 0x00000000;
	uartcfg->channel->BRR = 0x00000000;
	
	/* CR2 setting */
	/* LIN - sync communition are not supported by software */
	/* then keep CR2 as reset values */
	
	
	/* CR3 setting */
	/* keep CR3 at reset value */
	/* DMAT and DMAR must be 0 as init, they should be enable after DMA comp run */
	
	/* BBR setting */
	
	regtmp = 0x00000000;
	
	if (TRUE == uartcfg->isoversampling8sp)
	{
		if ((uartcfg->channel == USART1) || (uartcfg->channel == USART6))
		{
			/* USART1 and USART6 are belong APB2 which use PCLK2 = 84 MHz*/
			regtmp = UART_BRR_SAMPLING8(84000000, uartcfg->baudrate);
		}
		else
		{
			/* USART2, USART3, USART4, USART5 are belong APB1 which use PCLK1 = 42 MHz*/
			regtmp = UART_BRR_SAMPLING8(42000000, uartcfg->baudrate);
		}
	}
	else
	{
		if ((uartcfg->channel == USART1) || (uartcfg->channel == USART6))
		{
			/* USART1 and USART6 are belong APB2 which use PCLK2 = 84 MHz*/
			regtmp = UART_BRR_SAMPLING16(84000000, uartcfg->baudrate);
		}
		else
		{
			/* USART2, USART3, USART4, USART5 are belong APB1 which use PCLK1 = 42 MHz*/
			regtmp = UART_BRR_SAMPLING16(42000000, uartcfg->baudrate);
		}
	}
	
	uartcfg->channel->BRR = regtmp;
	
	/* CR1 setting */
	
	/* >TE RE bits are set 0 by default 
		>8 bits/frame is used
		>all interrupt sources are disabled 
		>UE bit is kept clear in this function, 
		it should be set by application 
	when they want to start communication*/
	
	regtmp = 0x00000000;
	
	if (TRUE == uartcfg->isoversampling8sp)
	{
		/* set OVER8 bit to 1*/
		regtmp |= 0x00008000;
	}
	
	uartcfg->channel->CR1 = regtmp;
	
}

void uartcore_init(const uart_cfgtype* uartcfg, uart_handletype* uarthandler, uint8_t numOfInst)
{
	uint8_t	l_index;
	
	for (l_index = 0; l_index < numOfInst; l_index++)
	{
		subinit(&uartcfg[l_index]);
		uarthandler[l_index].cfg_table = &uartcfg[l_index];
		uarthandler[l_index].txstate = UART_TxSt_IDLE;
		uarthandler[l_index].rxstate = UART_RxSt_IDLE;
	}
}

void uartcore_mainprocess_cycle10ms(uart_handletype* uarthandler)
{
	static uint16_t l_txdatalen_uw = 0; 
	uint16_t l_rxdatalen_uw = 0; 
	static uint16_t l_rxdatalenmax_uw = 0; 
	static uint32_t l_txmemadr_ul = 0;
	static uint32_t l_rxmemadr_ul = 0;
	USART_TypeDef* uart_reg = uarthandler->cfg_table->channel;
	
	if (UART_IS_ENABLE(uart_reg))
	{
		/*## TX PART ####################################################################*/
		if (UART_IS_TXENABLE(uart_reg))
		{
			switch (uarthandler->txstate)
			{
				case UART_TxSt_IDLE:
				{
					if (uarthandler->cfg_table->pIsPendingTxReqFun != NULL)
					{
						l_txdatalen_uw = 0;
						l_txmemadr_ul = 0;
						l_txdatalen_uw = uarthandler->cfg_table->pIsPendingTxReqFun(&l_txmemadr_ul);
						if ((l_txdatalen_uw > 0) && (l_txmemadr_ul != 0))
						{
							if (Ret_OK == dma_transfer(uarthandler->cfg_table->dma_tx_id, l_txmemadr_ul, l_txdatalen_uw))
							{
								UART_DMATX_ENABLE(uart_reg);
								uarthandler->txstate = UART_TxSt_BUSY;
								//uarthandler->txstate = UART_TxSt_TRGR;
							}
							else
							{
								/* wait for next cycle retry */
							}
						}
						else
						{
							/* wait for next cycle check */
						}
					}
					else
					{
						/* wait for manual trigger */
					}
					break;
				}
				case UART_TxSt_TRGR:
				{
					/* step2: enable DMA request from UART comp */
					UART_DMATX_ENABLE(uart_reg);
					uarthandler->txstate = UART_TxSt_BUSY;
					break;
				}
				case UART_TxSt_BUSY:
				{
					switch(dma_getstatus(uarthandler->cfg_table->dma_tx_id))
					{
						case DMA_Status_Error:
						{
							/* error occured from DMA - reset DMA state anyway */
							dma_cleanup(uarthandler->cfg_table->dma_tx_id);
							UART_DMATX_DISABLE(uart_reg);
							/* go to error state */
							uarthandler->txstate = UART_TxSt_ERROR;
							break;
						}
						case DMA_Status_Completed:
						{
							if (UART_GET_FLAG(uart_reg, UART_FLAG_TC))
							{
								/* complete successful a transmisson */
								UART_CLEAR_FLAG(uart_reg, UART_FLAG_TC);
								/* make DMA ready for new transfer */
								dma_cleanup(uarthandler->cfg_table->dma_tx_id);
								UART_DMATX_DISABLE(uart_reg);
								if (uarthandler->cfg_table->pTxCpltCbkFun !=NULL)
								{
									uarthandler->cfg_table->pTxCpltCbkFun();
								}						
								/* back to the IDLE state - ready for new uart transmission */
								uarthandler->txstate = UART_TxSt_IDLE;	
								//LED_GREEN_BLINK();
							}
							break;
						}
						case DMA_Status_NotStarted:
						{
							/*unexpected case: add lamp to check*/
							UART_DMATX_DISABLE(uart_reg);
							uarthandler->txstate = UART_TxSt_ERROR;
							
							break;
						}
						default:
						{
							/* triggered and in process states - just wait */
							break;
						}
					}
					break;
				}
				case UART_TxSt_ERROR:
				{
					/* Tx Error handling */
					/* retry to send this frame */
					//LED_RED_BLINK();
					if (Ret_OK == dma_transfer(uarthandler->cfg_table->dma_tx_id, l_txmemadr_ul, l_txdatalen_uw))
					{
						uarthandler->txstate = UART_TxSt_TRGR;
					}
					else
					{
						/* wait for next cycle retry */
					}
					break;
				}
				default:
				{
					break;
				}
			}
			
		}
		
		/*## RX PART ####################################################################*/
		if (UART_IS_RXENABLE(uart_reg))
		{
			switch(uarthandler->rxstate)
			{
				case UART_RxSt_IDLE:
				{
					/* clear IDLE flag*/
					UART_CLEAR_FLAG(uart_reg, UART_FLAG_IDLE);
					/* call DMA receive data in background until IDLE flag is get */
					l_rxmemadr_ul = 0;
					l_rxdatalenmax_uw = 0;
					l_rxdatalenmax_uw = uarthandler->cfg_table->pGetSpaceRxDataFun(&l_rxmemadr_ul);
					if ((l_rxdatalenmax_uw > 0) && (l_rxmemadr_ul != 0))
					{
						if (Ret_OK == dma_transfer(uarthandler->cfg_table->dma_rx_id, l_rxmemadr_ul, l_rxdatalenmax_uw))
						{
							/* trigger DMA successfully - go to other state*/
							UART_DMARX_ENABLE(uart_reg);
							uarthandler->rxstate = UART_RxSt_BUSY;
						}
						else
						{
							/* do something if trigger DMA fail - develop later*/
							/* current behavior: re-trigger until get success*/
						}
					}
					break;
				}
				
				case UART_RxSt_BUSY:
				{
					switch(dma_getstatus(uarthandler->cfg_table->dma_rx_id))
					{
						case DMA_Status_Error:
						{
							/* error occured from DMA - reset DMA state anyway */
							dma_cleanup(uarthandler->cfg_table->dma_rx_id);
							UART_DMARX_DISABLE(uart_reg);
							/* go to error state */
							uarthandler->rxstate = UART_RxSt_ERROR;
							break;
						}
						case DMA_Status_Completed:
						{
							/* get remaining data items */
							l_rxdatalen_uw = dma_getNDTR(uarthandler->cfg_table->dma_rx_id);
							/* calculate transfered items*/
							l_rxdatalen_uw = l_rxdatalenmax_uw - l_rxdatalen_uw;
							/* call rx complete cb function */
							if (uarthandler->cfg_table->pRxCpltCbkFun != NULL)
							{
								uarthandler->cfg_table->pRxCpltCbkFun(l_rxdatalen_uw);
							}						
							/* make DMA ready for new transfer */
							dma_cleanup(uarthandler->cfg_table->dma_rx_id);
							UART_DMARX_DISABLE(uart_reg);
							/* back to the IDLE state - ready for new uart transmission */
							uarthandler->rxstate = UART_RxSt_IDLE;	
							//LED_BLUE_BLINK();
							break;
						}
						case DMA_Status_NotStarted:
						{
							/*unexpected case: add lamp to check*/
							UART_DMARX_DISABLE(uart_reg);
							uarthandler->rxstate = UART_RxSt_ERROR;
							
							break;
						}
						default:
						{
							/* triggered and in process states - just wait */
							
							break;
						}
					}
					
					break;
				}
				
				case UART_RxSt_ERROR:
				{
					/* Error handling */
					//LED_RED_BLINK();
					if (Ret_OK == dma_transfer(uarthandler->cfg_table->dma_rx_id, l_rxmemadr_ul, l_rxdatalenmax_uw))
					{
						/* trigger DMA successfully - go to other state*/
						UART_DMARX_ENABLE(uart_reg);
						uarthandler->rxstate = UART_RxSt_BUSY;
					}
					else
					{
						/* do something if trigger DMA fail - develop later*/
						/* current behavior: re-trigger until get success*/
					}
					break;
				}							
			}
		}	
	}
}

void uartcore_eventcheck_cycle5ms(uart_handletype* uarthandler)
{
	USART_TypeDef* uart_reg = uarthandler->cfg_table->channel;
	/* task: check if the IDLE flag is set, then stop the DMA transfer */
	if (UART_IS_ENABLE(uart_reg) && UART_IS_RXENABLE(uart_reg))
	{
		if (uarthandler->rxstate == UART_RxSt_BUSY)
		{
			if (UART_GET_FLAG(uart_reg, UART_FLAG_IDLE))
			{
				UART_CLEAR_IDLE_FLAG(uart_reg);
				/* stop DMA receive data */
				dma_stop(uarthandler->cfg_table->dma_rx_id);
			}
		}
	}
	
}
