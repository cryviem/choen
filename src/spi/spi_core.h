/*
	* spi_core.h
	*
	*  Created on: June 23, 2018
	*  Author: Mr.A
*/

#ifndef _SPI_CORE_H_
#define _SPI_CORE_H_

#include "common_inc.h"
#include "dmacfg.h"


/* Pin mapping
SPI1:
 > NSS: PA4 ; PA15(jtag)
 > SCK: PA5 ; PB3(jtag)
 > MOSI: PA7 ; PB5
 > MISO: PA6 ; PB4(sys)
 
 SPI2:
 > NSS: PB9 ; PB12; PI0
 > SCK: PB10 ; PB13 ; PI1
 > MOSI: PB15(rtc) ; PC3 ; PI3
 > MISO: PB14 ; PC2 ; PI2
 
 SPI3:
 > NSS: PA4 ; PA15(jtag)
 > SCK: PB3(jtag) ; PC10
 > MOSI: PB5 ; PC12
 > MISO: PB4(sys) ; PC11
*/

#define SPI_BR_DIV2									0
#define SPI_BR_DIV4									1
#define SPI_BR_DIV8									2
#define SPI_BR_DIV16								3
#define SPI_BR_DIV32								4
#define SPI_BR_DIV64								5
#define SPI_BR_DIV128								6
#define SPI_BR_DIV256								7
#define SPI_BR_INVALID								8

#define SPI_CLKMODE_0									0					/*SCK is 0 when idle and data latching at rising edge*/
#define SPI_CLKMODE_1									1					/*SCK is 0 when idle and data latching at falling edge*/
#define SPI_CLKMODE_2									2					/*SCK is 1 when idle and data latching at falling edge*/
#define SPI_CLKMODE_3									3					/*SCK is 1 when idle and data latching at rising edge*/
#define SPI_CLKMODE_INVALID								4

#define SPI_OPTYPE_FULLDUPLEX												0					/*full duplex */
#define SPI_OPTYPE_BIDIREC_TXFIRST											1					/*half duplux - bidirectional with tx first*/
#define SPI_OPTYPE_BIDIREC_RXFIRST											2					/*half duplux - bidirectional with rx first*/
#define SPI_OPTYPE_RXONLY													3					/*half duplux - rx only*/
#define SPI_OPTYPE_TXONLY													4					/*half duplux - tx only*/
#define SPI_OPTYPE_INVALID													5

#define SPI_GETREG(_chnl_)												(SPI_TypeDef *)((_chnl_ == 1)? SPI1_BASE : ((_chnl_ == 2)? SPI2_BASE : ((_chnl_ == 3)? SPI3_BASE : 0)))

#define SPI_FLAG_MASK												(uint16_t)0x01FF
#define SPI_GETFLAG(__HANDLE__, __FLAG__) 							((__HANDLE__->SR & ((uint16_t)__FLAG__ & SPI_FLAG_MASK)) == ((uint16_t)__FLAG__ & SPI_FLAG_MASK))

#define SPI_ENABLE(__HANDLE__)										__HANDLE__->CR1 |= SPI_CR1_SPE
#define SPI_DISABLE(__HANDLE__)										__HANDLE__->CR1 &= ~SPI_CR1_SPE
#define SPI_IS_ENABLE(__HANDLE__)									(__HANDLE__->CR1 & SPI_CR1_SPE)

#define SPI_SET_BIDIOE(__HANDLE__)									__HANDLE__->CR1 |= SPI_CR1_BIDIOE
#define SPI_CLEAR_BIDIOE(__HANDLE__)								__HANDLE__->CR1 &= ~SPI_CR1_BIDIOE
#define SPI_READ_BIDIOE(__HANDLE__)									(__HANDLE__->CR1 & SPI_CR1_BIDIOE)

#define SPI_TXDMA_ENABLE(__HANDLE__)								__HANDLE__->CR2 |= SPI_CR2_TXDMAEN
#define SPI_TXDMA_DISABLE(__HANDLE__)								__HANDLE__->CR2 &= ~SPI_CR2_TXDMAEN
#define SPI_TXDMA_IS_ENABLE(__HANDLE__)								(__HANDLE__->CR2 & SPI_CR2_TXDMAEN)

#define SPI_RXDMA_ENABLE(__HANDLE__)								__HANDLE__->CR2 |= SPI_CR2_RXDMAEN
#define SPI_RXDMA_DISABLE(__HANDLE__)								__HANDLE__->CR2 &= ~SPI_CR2_RXDMAEN
#define SPI_RXDMA_IS_ENABLE(__HANDLE__)								(__HANDLE__->CR2 & SPI_CR2_RXDMAEN)

#define SPI_IS_16BFORMAT(__HANDLE__)								(__HANDLE__->CR1 & SPI_CR1_DFF)

#define SPI_CLEAR_OVR_FLAG(__HANDLE__)								while (0) \
																	{ uint16_t tmp = __HANDLE__->DR; \
																	  tmp = __HANDLE__->SR; }
typedef enum {
	SPI_SW_FULL,
	SPI_SW_TX,
	SPI_SW_RX
} spi_run_type;

typedef enum {
	SPI_TXSTS_OFF,
	SPI_TXSTS_IDLE,
	SPI_TXSTS_BUSYNOR,
	SPI_TXSTS_BUSYDMA,
	SPI_TXSTS_ERROR
} spi_txsts_type;

typedef enum {
	SPI_RXSTS_OFF,
	SPI_RXSTS_IDLE,
	SPI_RXSTS_BUSYDMA,
	SPI_RXSTS_ERROR
} spi_rxsts_type;

typedef struct {
	void (*spi_rxcplt_cb)(uint16_t, uint16_t);
	void (*spi_rxerror_cb)(uint16_t);
	void (*spi_txindcn_cb)(uint16_t);
	void (*spi_txerror_cb)(uint16_t);
} spi_cbktable_type;

typedef struct {
	SPI_TypeDef*						reg;
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

typedef struct {
	uint16_t									reqid;
	spi_txsts_type								status;
	void*										pnor_databuf;
	uint16_t									nor_len;
	uint16_t									nor_cnt;
} spi_tx_hdl_type;

typedef struct {
	uint16_t									reqid;
	spi_rxsts_type								status;
	uint16_t									tarlen;
} spi_rx_hdl_type;

typedef struct {
	const spi_cfg_type*							cfgtable;
	spi_tx_hdl_type								txbox;
	spi_rx_hdl_type								rxbox;
} spi_hdl_type;

extern void spicore_start(spi_hdl_type* hdler, spi_run_type run);
extern void spicore_stop(spi_hdl_type* hdler);
extern RetType spicore_bidirec_setup_tx(spi_hdl_type* hdler);
extern RetType spicore_bidirec_setup_rx(spi_hdl_type* hdler);
extern RetType spicore_bidirec_is_tx(spi_hdl_type* hdler);
extern void spicore_init(const spi_cfg_type* spicfg, spi_hdl_type* spihandler);
extern RetType spicore_transmit(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len);
extern RetType spicore_transmit_dma(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len);
extern RetType spicore_receive_dma(spi_hdl_type* hdler, uint16_t reqid, void* pdata, uint16_t len);
extern RetType spicore_fullduplex_work_dma(spi_hdl_type* hdler, uint16_t reqid, void* ptxdata, void* prxdata, uint16_t len);
extern void spiproc_maintask(spi_hdl_type* hdler);

#endif /* _SPI_CORE_H_ */
