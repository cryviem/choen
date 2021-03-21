#include "common_inc.h"
#include "console.h"
#include "fpga.h"

const console_table_t cmd_table[CMD_INVALID] =
{
		{"fpga_en",			fpga_enable},
		{"fpga_dis",		fpga_disable},
		{"fpga_db0",		fpga_send0},
		{"fpga_db1",		fpga_send1},
		{"fpga_onl1",		fpga_onled1},
		{"fpga_offl1",		fpga_offled1},
		{"fpga_circ",		fpga_circle},
		{"fpga_penup",		fpga_penup},
		{"fpga_pendown",	fpga_pendown}
};
