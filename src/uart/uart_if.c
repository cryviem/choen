
#include "common_inc.h"
#include "uart_if.h"

uartTxRingBuffer_t g_uartTxRingBuff_st;
uartRxRingBuffer_t g_uartRxRingBuff_st;

uint16_t uartif_CheckPendingTxReq(uint32_t* memadr)
{
	uint8_t* l_memadr_ptr;
	uint16_t l_actsize = 0;
	l_actsize = uartif_ReqRdTxBuff(&l_memadr_ptr);
	(*memadr) = (uint32_t)l_memadr_ptr;
	return l_actsize;
}

uint16_t uartif_GetSpace4RxData(uint32_t* memadr)
{
	uint8_t* l_memadr_ptr;
	if (Ret_OK == uartif_ReqWrRxBuff(&l_memadr_ptr))
	{
		(*memadr) = (uint32_t)l_memadr_ptr;
		return UART_FRAME_SIZE;
	}
	(*memadr) = 0;
	return 0;
}

void uartif_ClearRingBuffs(void)
{
	pf_memset(&g_uartTxRingBuff_st, 0x00, sizeof(g_uartTxRingBuff_st));
	pf_memset(&g_uartRxRingBuff_st, 0x00, sizeof(g_uartTxRingBuff_st));
}

RetType uartif_ReqWrTxBuff(uint8_t** memadr)
{
	uint8_t tmp;
	if (g_uartTxRingBuff_st.wr_sts != BUFF_WR_IDLE)
	{
		/* last write process hasn't been done */
		return Ret_NotOK;
	}
	
	tmp = g_uartTxRingBuff_st.wptr + 1;
	if (tmp >= UART_TX_BUF_SIZE)
	{
		tmp = 0;
	}
	
	if (tmp ==  g_uartTxRingBuff_st.rptr)
	{
#if (UARTIF_RINGBUFF_TYPE == NO_OVERWRT)
		return Ret_NotOK;
	}
#else	/* (UARTIF_RINGBUFF_TYPE == OVERWRT) */
		if (g_uartTxRingBuff_st.rd_sts != BUFF_RD_IDLE)
		{
			/* read process is going on this frame --> ignore overwrite*/
			return Ret_NotOK;
		}
		/* The oldest unread cell will be overwrite by new data, then move read pointer to next cell*/
		g_uartTxRingBuff_st.rptr = tmp + 1;	
		if (g_uartTxRingBuff_st.rptr >= UART_TX_BUF_SIZE)
		{
			g_uartTxRingBuff_st.rptr = 0;
		}
	}
#endif
	g_uartTxRingBuff_st.wptr = tmp;
	(*memadr) = g_uartTxRingBuff_st.framebuff[tmp].data;
	g_uartTxRingBuff_st.wr_sts = BUFF_WR_BUSY;
	return Ret_OK;
}

void uartif_WrTxBuffCpltNotify(uint16_t actsize)
{
	if (g_uartTxRingBuff_st.wr_sts != BUFF_WR_BUSY)
	{
		/*unexpected behavior*/
		return;
	}
	g_uartTxRingBuff_st.framebuff[g_uartTxRingBuff_st.wptr].actsize = actsize;
	g_uartTxRingBuff_st.wr_sts = BUFF_WR_IDLE;
}

uint16_t uartif_ReqRdTxBuff(uint8_t** memadr)
{
	uint8_t tmp;
	
	if (g_uartTxRingBuff_st.rd_sts != BUFF_RD_IDLE)
	{
		/* last read process hasn't been done */
		(*memadr) = NULL;
		return 0;
	}
	
	if (g_uartTxRingBuff_st.rptr ==  g_uartTxRingBuff_st.wptr)
	{
		/* nothing new */
		(*memadr) = NULL;
		return 0;
	}

	tmp = g_uartTxRingBuff_st.rptr + 1;
	if (tmp >= UART_TX_BUF_SIZE)
	{
		tmp = 0;
	}
	
	if ((tmp == g_uartTxRingBuff_st.wptr) && (g_uartTxRingBuff_st.wr_sts == BUFF_WR_BUSY))
	{
		/*write process are ongoing on this buf*/
		(*memadr) = NULL;
		return 0;
	}
	
	g_uartTxRingBuff_st.rptr = tmp;
	(*memadr) = g_uartTxRingBuff_st.framebuff[tmp].data;
	g_uartTxRingBuff_st.rd_sts = BUFF_RD_BUSY;
	return g_uartTxRingBuff_st.framebuff[tmp].actsize;

}

void uartif_RdTxBuffCpltNotify(void)
{
	if (g_uartTxRingBuff_st.rd_sts != BUFF_WR_BUSY)
	{
		/*unexpected behavior*/
		return;
	}
	g_uartTxRingBuff_st.rd_sts = BUFF_RD_IDLE;
}

RetType uartif_ReqWrRxBuff(uint8_t** memadr)
{
	uint8_t tmp;
	if (g_uartRxRingBuff_st.wr_sts != BUFF_WR_IDLE)
	{
		/* last write process hasn't been done */
		return Ret_NotOK;
	}
	
	tmp = g_uartRxRingBuff_st.wptr + 1;
	if (tmp >= UART_RX_BUF_SIZE)
	{
		tmp = 0;
	}
	
	if (tmp ==  g_uartRxRingBuff_st.rptr)
	{
#if (UARTIF_RINGBUFF_TYPE == NO_OVERWRT)
		return Ret_NotOK;
	}
#else	/* (UARTIF_RINGBUFF_TYPE == OVERWRT) */
		if (g_uartRxRingBuff_st.rd_sts != BUFF_RD_IDLE)
		{
			/* read process is going on this frame --> ignore overwrite*/
			return Ret_NotOK;
		}
		/* The oldest unread cell will be overwrite by new data, then move read pointer to next cell*/
		g_uartRxRingBuff_st.rptr = tmp + 1;	
		if (g_uartRxRingBuff_st.rptr >= UART_RX_BUF_SIZE)
		{
			g_uartRxRingBuff_st.rptr = 0;
		}
	}
#endif
	g_uartRxRingBuff_st.wptr = tmp;
	(*memadr) = g_uartRxRingBuff_st.framebuff[tmp].data;
	g_uartRxRingBuff_st.wr_sts = BUFF_WR_BUSY;
	return Ret_OK;
}

void uartif_WrRxBuffCpltNotify(uint16_t actsize)
{
	if (g_uartRxRingBuff_st.wr_sts != BUFF_WR_BUSY)
	{
		/*unexpected behavior*/
		return;
	}
	g_uartRxRingBuff_st.framebuff[g_uartRxRingBuff_st.wptr].actsize = actsize;
	g_uartRxRingBuff_st.wr_sts = BUFF_WR_IDLE;
}

uint16_t uartif_ReqRdRxBuff(uint8_t** memadr)
{
	uint8_t tmp;
	
	if (g_uartRxRingBuff_st.rd_sts != BUFF_RD_IDLE)
	{
		/* last read process hasn't been done */
		(*memadr) = NULL;
		return 0;
	}
	
	if (g_uartRxRingBuff_st.rptr ==  g_uartRxRingBuff_st.wptr)
	{
		/* nothing new */
		(*memadr) = NULL;
		return 0;
	}

	tmp = g_uartRxRingBuff_st.rptr + 1;
	if (tmp >= UART_RX_BUF_SIZE)
	{
		tmp = 0;
	}
	
	if ((tmp == g_uartRxRingBuff_st.wptr) && (g_uartRxRingBuff_st.wr_sts == BUFF_WR_BUSY))
	{
		/*write process are ongoing on this buf*/
		(*memadr) = NULL;
		return 0;
	}
	
	g_uartRxRingBuff_st.rptr = tmp;		
	(*memadr) = g_uartRxRingBuff_st.framebuff[tmp].data;
	g_uartRxRingBuff_st.rd_sts = BUFF_RD_BUSY;
	return g_uartRxRingBuff_st.framebuff[tmp].actsize;
}

void uartif_RdRxBuffCpltNotify(void)
{
	if (g_uartRxRingBuff_st.rd_sts != BUFF_WR_BUSY)
	{
		/*unexpected behavior*/
		return;
	}
	g_uartRxRingBuff_st.rd_sts = BUFF_RD_IDLE;
}
