#include "common_inc.h"
#include "fpga.h"
#include "spi_cfg.h"

uint16_t dda0[11] = {	0x040B,	/* cmd */
						0,		/* mode */
						3200,	/* Px */
						1600,		/* Py */
						3200,	/* Q */
						500,	/* Fstart */
						2000,	/* Fcruise */
						500,	/* Fend */
						416,	/* Acc_fac */
						3200,	/* S_total */
						3184};	/* S_dec_from */

uint16_t circle0[11] = {	0x040B,	/* cmd */
						0x000B,		/* mode */
						800,	/* Px */
						0,		/* Py */
						800,	/* Q */
						500,	/* Fstart */
						2000,	/* Fcruise */
						500,	/* Fend */
						416,	/* Acc_fac */
						1256,	/* S_total */
						1240};	/* S_dec_from */

uint16_t circle1[11] = {	0x040B,	/* cmd */
						0x010E,		/* mode */
						0,	/* Px */
						800,		/* Py */
						800,	/* Q */
						500,	/* Fstart */
						2000,	/* Fcruise */
						500,	/* Fend */
						416,	/* Acc_fac */
						1256,	/* S_total */
						1240};	/* S_dec_from */

uint16_t circle2[11] = {	0x040B,	/* cmd */
						0x030B,		/* mode */
						800,	/* Px */
						0,		/* Py */
						800,	/* Q */
						500,	/* Fstart */
						2000,	/* Fcruise */
						500,	/* Fend */
						416,	/* Acc_fac */
						1256,	/* S_total */
						1240};	/* S_dec_from */

uint16_t circle3[11] = {	0x040B,	/* cmd */
						0x020E,		/* mode */
						0,	/* Px */
						800,		/* Py */
						800,	/* Q */
						500,	/* Fstart */
						2000,	/* Fcruise */
						500,	/* Fend */
						416,	/* Acc_fac */
						1256,	/* S_total */
						1240};	/* S_dec_from */

const uint16_t fpgaonled1 = 0x2301;
const uint16_t fpgaoffled1 = 0x2401;
const uint16_t fpgapenup = 0x0501;
const uint16_t fpgapendown = 0x0601;

uint8_t state = 0;
uint8_t busy_transmit = 0;

void spi_txcplt(uint16_t reqid)
{
	LED_GREEN_BLINK();
	busy_transmit = 0;
}

void spi_txerror(uint16_t reqid)
{

}

void fpga_send0(void)
{
	spi1_transmit_dma(123, &dda0, 11);

	//spi1_transmit(123, &spi_1cmd, 1);
}

void fpga_send1(void)
{
	FPGA_ENABLE();
	LED_BLUE_ON();

	spi1_transmit_dma(123, &dda0, 11);
}

void fpga_enable(void)
{
	FPGA_ENABLE();
	LED_BLUE_ON();
}

void fpga_disable(void)
{
	FPGA_DISABLE();
	LED_BLUE_OFF();
}

void fpga_onled1(void)
{
	spi1_transmit(123, &fpgaonled1, 1);
}

void fpga_offled1(void)
{
	spi1_transmit(123, &fpgaoffled1, 1);
}

void fpga_circle(void)
{
	if (state == 0)
	{
		state = 1;
	}
}

void fpga_task(void)
{
	switch (state)
	{
	case 1:
		if (IS_FPGA_READY() && (busy_transmit == 0))
		{
			spi1_transmit_dma(123, &circle0, 11);
			busy_transmit = 1;
			state = 2;
		}
		break;
	case 2:
		if (IS_FPGA_READY() && (busy_transmit == 0))
		{
			spi1_transmit_dma(123, &circle1, 11);
			busy_transmit = 1;
			state = 3;
		}
		break;
	case 3:
		if (IS_FPGA_READY() && (busy_transmit == 0))
		{
			spi1_transmit_dma(123, &circle2, 11);
			busy_transmit = 1;
			state = 4;
		}
		break;
	case 4:
		if (IS_FPGA_READY() && (busy_transmit == 0))
		{
			spi1_transmit_dma(123, &circle3, 11);
			busy_transmit = 1;
			state = 0;
		}
		break;
	}
}

void fpga_penup(void)
{
	spi1_transmit(123, &fpgapenup, 1);
}

void fpga_pendown(void)
{
	spi1_transmit(123, &fpgapendown, 1);
}
