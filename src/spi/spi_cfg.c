/*
	* spi_cfg.c
	*
	*  Created on: March 06, 2019
	*  Author: Mr.A
*/

#include "spi_core.h"
#include "dmacore.h"
#include "spi_cfg.h"


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
		SPI_CHNL_2,
		SPI_BR_DIV8,			/* 42/8= 5.12 Mhz */
		SPI_CLKMODE_0,
		SPI_OPTYPE_BIDIREC_TXFIRST,
		FALSE,
		FALSE,
		FALSE,
		0,
		0,
		{
			NULL,
			NULL,
			NULL,
			NULL
		}
	},
};


spi_hdl_type spi_ramtable[SPI_HANDLER_INVALID] = {0};
