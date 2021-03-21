/*
	* spi_cfg.h
	*
	*  Created on: March 06, 2019
	*  Author: Mr.A
*/

#ifndef _SPI_CFG_H_
#define _SPI_CFG_H_

#include "common_inc.h"

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

typedef enum {
	SPI_HANDLER_1,
	SPI_HANDLER_INVALID
} spi_handler_id_en;

extern void spi_init(void);
extern void spi_main_task(void);
extern void spi1_start_txonly(void);
extern void spi1_start_fullduplex(void);
extern void spi1_stop(void);
extern RetType spi1_transmit(uint16_t reqid, void* pdata, uint16_t len);
extern RetType spi1_transmit_dma(uint16_t reqid, void* pdata, uint16_t len);
extern RetType spi1_receive_dma(uint16_t reqid, void* pdata, uint16_t len);
extern RetType spi1_fullduplex_work_dma(uint16_t reqid, void* ptxdata, void* prxdata, uint16_t len);

#endif /* _SPI_CFG_H_ */
