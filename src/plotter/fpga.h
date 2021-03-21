#ifndef _FPGA_H_
#define _FPGA_H_

#include "port.h"

#define FPGA_ENABLE()					Port_WritePin(PORT_B_PIN_12, PORT_PIN_LEVEL_HIGH)
#define FPGA_DISABLE()					Port_WritePin(PORT_B_PIN_12, PORT_PIN_LEVEL_LOW)
#define IS_FPGA_READY()					(PORT_PIN_LEVEL_LOW == Port_ReadPin(PORT_B_PIN_14))
//#define READ_REQ_SET()					Port_WritePin(PORT_B_PIN_14, PORT_PIN_LEVEL_HIGH)
//#define READ_REQ_CLR()					Port_WritePin(PORT_B_PIN_14, PORT_PIN_LEVEL_LOW)

extern void spi_txcplt(uint16_t reqid);
extern void spi_txerror(uint16_t reqid);
extern void fpga_send0(void);
extern void fpga_send1(void);
extern void fpga_enable(void);
extern void fpga_disable(void);
extern void fpga_onled1(void);
extern void fpga_offled1(void);
extern void fpga_circle(void);
extern void fpga_task(void);
extern void fpga_penup(void);
extern void fpga_pendown(void);

#endif
