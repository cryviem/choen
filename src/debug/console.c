#include "common_inc.h"
#include "uart_if.h"
#include "console.h"

extern const console_table_t cmd_table[];


void console_task(void)
{
	uint8_t* l_ptr;
	uint16_t l_len;
	uint8_t i;

	/* check if received new command */
	l_len = uartif_ReqRdRxBuff(&l_ptr);
	if (l_len > 0)
	{
		/* bugfix: manually add null character at the end of string for pf_strcmp() work correctly
		 * since COM terminal software does not provided */
		*(l_ptr + l_len) = 0;
		/* bugfix end */

		for (i = 0; i < CMD_INVALID; i++)
		{
			if (0==pf_strcmp(cmd_table[i].string, (char*)l_ptr))
			{
				break;
			}
		}

		uartif_RdRxBuffCpltNotify();

		if ((i < CMD_INVALID)&&(cmd_table[i].pfunc != NULL))
		{
			cmd_table[i].pfunc();
		}
	}
}


