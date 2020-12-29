
#include "spi_core.h"
#include "spi_cfg.h"

static spi_hdl_type* spihdlsearch(spi_chnl_type chnl)
{
    uint8_t   indx;

    for (indx = 0; indx < C_SPI_NumofChannels; indx++)
    {
        if (spi_ramtable[indx].cfgtable->channel == chnl)
        {
            return &spi_ramtable[indx];
        }
    }

    return NULL;
}

void spiif_start(spi_chnl_type chnl, spi_run_type run)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        spi_start(hdler, run);
    }
}

void spiif_stop(spi_chnl_type chnl)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        spi_stop(hdler);
    }
}

RetType spiif_bidirec_setup_tx(spi_chnl_type chnl)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_bidirec_setup_tx(hdler);
    }
    else
    {
        return Ret_NotOK;
    }
    
}
RetType spiif_bidirec_setup_rx(spi_chnl_type chnl)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_bidirec_setup_rx(hdler);
    }
    else
    {
        return Ret_NotOK;
    }
}

RetType spiif_bidirec_is_tx(spi_chnl_type chnl)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_bidirec_is_tx(hdler);
    }
    else
    {
        return Ret_NotOK;
    }
}

RetType spiif_transmit(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_transmit(hdler, reqid, pdata, len);
    }
    else
    {
        return Ret_NotOK;
    }
}

RetType spiif_transmit_dma(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_transmit_dma(hdler, reqid, pdata, len);
    }
    else
    {
        return Ret_NotOK;
    }
}

RetType spiif_receive_dma(spi_chnl_type chnl, uint16_t reqid, void* pdata, uint16_t len)
{
    spi_hdl_type* hdler;
    hdler = spihdlsearch(chnl);
    if (hdler != NULL)
    {
        return spi_receive_dma(hdler, reqid, pdata, len);
    }
    else
    {
        return Ret_NotOK;
    }
}
