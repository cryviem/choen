#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/* file: console.h */

typedef enum
{
    CMD_FPGA_ENABLE,
	CMD_FPGA_DISABLE,
	CMD_FPGA_SEND_DB0,
	CMD_FPGA_SEND_DB1,
	CMD_FPGA_ONLED1,
	CMD_FPGA_OFFLED1,
	CMD_FPGA_CIRC,
	CMD_FPGA_PENUP,
	CMD_FPGA_PENDOWN,
	CMD_INVALID
}console_cmd_en;

typedef struct{
    char*      		string;
    void 			(*pfunc)(void);
}console_table_t;

extern void console_task(void);
	
#endif /* _CONSOLE_H_ */
