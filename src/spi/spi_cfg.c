/*
	* spi_cfg.c
	*
	*  Created on: March 06, 2019
	*  Author: Mr.A
*/

#include "spi_core.h"
#include "dmacore.h"
#include "spi_cfg.h"
#include "fpga.h"


/*	PRIVATE VARIABLE DECLARATION BEGIN*/
/*	PRIVATE VARIABLE DECLARATION END*/

/*	PRIVATE FUNCTION DECLARATION BEGIN*/

/*	PRIVATE FUNCTION DECLARATION END*/

/*
typedef struct {
	void (*spi_rxcplt_cb)(uint16_t);
} spi_cbktable_type;

typedef struct {
	spi_chnl_type						channel;
	uint8_t								baudrate;
	uint8_t								clkmode;
	uint8_t								optype;
	uint8_t								is16bDFFsp;
	uint8_t								isLSBgofirst;
	uint8_t								isHWCSused;
	dma_handler_id_en					dma_tx_id;
	dma_handler_id_en					dma_rx_id;
	spi_cbktable_type					cbftable;
} spi_cfg_type;
*/

/*	APB1 : SPI2-3				42 MHz
	APB2 : SPI1 				84 MHz*/

const spi_cfg_type spi_cfg_table[SPI_HANDLER_INVALID] = {
	{
		SPI2,						/* SPI2 */
		SPI_BR_DIV8,				/* 42/8= 5.12 Mhz */
		SPI_CLKMODE_1,				/* CPHA = 1; CPOL = 0 */
		SPI_OPTYPE_FULLDUPLEX,		/* full duplex mode */
		TRUE,						/* 16 bits format */
		FALSE,						/* MSB go first */
		TRUE,						/* HW CS is used */
		DMA_HANDLER_SPI2TX,			/*  */
		DMA_HANDLER_SPI2RX,			/*  */
		{
			&spi_rxcplt,
			NULL,
			NULL,
			NULL
		}
	},
};


spi_hdl_type spi_ramtable[SPI_HANDLER_INVALID] = {0};

/* Wrapper SPI CORE with specific configured data */
void spi_init(void)
{
	spicore_init(spi_cfg_table, spi_ramtable);
}

void spi1_start_fullduplex(void)
{
	spicore_start(&spi_ramtable[SPI_HANDLER_1], SPI_SW_FULL);
}

void spi1_stop(void)
{
	spicore_stop(&spi_ramtable[SPI_HANDLER_1]);
}

RetType spi1_transmit(uint16_t reqid, void* pdata, uint16_t len)
{
	return spicore_transmit(&spi_ramtable[SPI_HANDLER_1], reqid, pdata, len);
}

RetType spi1_transmit_dma(uint16_t reqid, void* pdata, uint16_t len)
{
	return spicore_transmit_dma(&spi_ramtable[SPI_HANDLER_1], reqid, pdata, len);
}

RetType spi1_receive_dma(uint16_t reqid, void* pdata, uint16_t len)
{
	return spicore_receive_dma(&spi_ramtable[SPI_HANDLER_1], reqid, pdata, len);
}

RetType spi1_fullduplex_work_dma(uint16_t reqid, void* ptxdata, void* prxdata, uint16_t len)
{
	return spicore_fullduplex_work_dma(&spi_ramtable[SPI_HANDLER_1], reqid, ptxdata, prxdata, len);
}
void spi_main_task(void)
{
	uint8_t indx;
	for (indx = 0; indx < SPI_HANDLER_INVALID; indx++)
	{
		spiproc_maintask(&spi_ramtable[indx]);
	}
}

