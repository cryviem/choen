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

uint16_t pf_strlen(const char *str)
{
   //Avoiding crashes by initializing string to NULL
   if(str == NULL) //a very simple fix
      return 0;

   const char *p = str;

   while(*p != 0)
      p++;

   return p - str;
}
/* mem copy by dma for large data*/

int pf_strcmp(const char* str1, const char* str2)
{
    while((*str1!='\0') && (*str1==*str2))
    	str1++,str2++;

    return *(const unsigned char*)str1-*(const unsigned char*)str2;
}

/**
 * \brief    Fast Square root algorithm, with rounding
 *
 * This does arithmetic rounding of the result. That is, if the real answer
 * would have a fractional part of 0.5 or greater, the result is rounded up to
 * the next integer.
 *      - SquareRootRounded(2) --> 1
 *      - SquareRootRounded(3) --> 2
 *      - SquareRootRounded(4) --> 2
 *      - SquareRootRounded(6) --> 2
 *      - SquareRootRounded(7) --> 3
 *      - SquareRootRounded(8) --> 3
 *      - SquareRootRounded(9) --> 3
 *
 * \param[in] a_nInput - unsigned integer for which to find the square root
 *
 * \return Integer square root of the input value.
 */
uint32_t SquareRootRounded(uint32_t a_nInput)
{
    uint32_t op  = a_nInput;
    uint32_t res = 0;
    uint32_t one = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type


    // "one" starts at the highest power of four <= than the argument.
    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op = op - (res + one);
            res = res +  2 * one;
        }
        res >>= 1;
        one >>= 2;
    }

    /* Do arithmetic rounding to nearest integer */
    if (op > res)
    {
        res++;
    }

    return res;
}
