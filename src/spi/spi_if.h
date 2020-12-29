#ifndef _SPI_IF_H_
#define _SPI_IF_H_

/*file: spi_if.h*/

#include "spi_core.h"

extern void spiif_start(spi_chnl_type chnl, spi_run_type run);
extern void spiif_stop(spi_chnl_type chnl);
extern RetType spiif_bidirec_setup_tx(spi_chnl_type chnl);
extern RetType spiif_bidirec_setup_rx(spi_chnl_type chnl);
extern RetType spiif_bidirec_is_tx(spi_chnl_type chnl);
extern RetType spiif_transmit(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len);
extern RetType spiif_transmit_dma(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len);
extern RetType spiif_receive_dma(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len);

#endif /*_SPI_IF_H_*/
