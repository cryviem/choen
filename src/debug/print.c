
#include "uart_if.h"

void print_text(char *str)
{
	uint8_t i;
	uint8_t* l_ptr;
	uint16_t len = pf_strlen(str);
	/* maximum string length is UART_TX_FRAME_SIZE * UART_TX_BUF_SIZE = 256 * 5 = 1280 bytes */
	for (i = 0; i < UART_TX_BUF_SIZE; i++)
	{
		if (len > UART_FRAME_SIZE)
		{
			if (Ret_OK == uartif_ReqWrTxBuff(&l_ptr))
			{
				pf_memcpy(l_ptr, &str[(UART_FRAME_SIZE*i)], UART_FRAME_SIZE);
				len -= UART_FRAME_SIZE;
				uartif_WrTxBuffCpltNotify(UART_FRAME_SIZE);
			}		
		}
		else
		{
			if (Ret_OK == uartif_ReqWrTxBuff(&l_ptr))
			{
				pf_memcpy(l_ptr, &str[(UART_FRAME_SIZE*i)], len);
				uartif_WrTxBuffCpltNotify(len);
			}		
			/* go out of loop*/
			break;
		}	
	}
}

uint8_t int2str(char* des, int32_t value)
{
	char digit[10], tmp, i, offset = 0, indx = 0;
	uint32_t remain;

	if (value < 0)
	{
		des[offset] = '-';
		offset++;
		remain = (uint32_t)((-1)*value);
	}
	else
	{
		remain = (uint32_t)value;
	}

	do 
	{
		tmp = remain % 10;
		remain = remain / 10;
		digit[indx] = tmp;
		indx++;
	}while (remain > 0);

	des[indx + offset] = '\n';
	des[indx + offset + 1] = 0x00;

	for (i = offset; i < (indx + offset); i++)
	{
		des[i] = digit[(indx + offset - i -1)] + 0x30;
	}	
	return (indx + offset + 1);
}

void print_num(int32_t value)
{
	char buf[20];

	int2str(buf, value);

	print_text(buf);
}

#if(0)
void print(const uint8_t* format,...)
{
	uint8_t prntbuf[(UART_FRAME_SIZE * UART_TX_BUF_SIZE)];
	uint16_t prntindx = 0, len;
	uint32_t d_tmp;
	va_list ap;

	va_start(ap, format);
	while (*format != 0x00)
	{
		/* loop to go through all character of format string */
		if (*format == '%')
		{
			/* found a replacement */

			format++;								// next character will be the format identifier

			switch (*format)
			{
			case 'c':
			{

				break;
			}

			case 'd':
			{
				d_tmp = va_arg(ap, int);
				len = uint2str(&prntbuf[prntindx], d_tmp);
				prntindx += len;
				break;
			}
			}
		}
		else
		{
			/* normal text */
			prntbuf[prntindx] = *format;
			prntindx++;
		}

		format++;
	}
	prntbuf[prntindx] = 0x00;
	va_end(ap);

	csprinttxt(prntbuf);
}
#endif
