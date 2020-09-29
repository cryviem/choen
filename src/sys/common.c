#include "common_inc.h"

/* time consumtion notice*/
void pf_memset(void *s, uint8_t c, uint16_t n)
{
    uint8_t* p=s;
    while(n--)
		{
        *p++ = c;
		}
}

/* time consumtion notice*/
void pf_memcpy(void *des, void *src, uint16_t n)
{
	uint8_t* ldes = des;
	uint8_t* lsrc = src;

	while(n--)
	{
		*ldes++ = *lsrc++;
	}
}

uint16_t pf_strlen(uint8_t *str)
{
   //Avoiding crashes by initializing string to NULL
   if(str == NULL) //a very simple fix
      return 0;

   uint8_t *p = str;

   while(*p != 0)
      p++;

   return p - str;
}
/* mem copy by dma for large data*/
