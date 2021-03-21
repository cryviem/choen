#ifndef _PRINT_H_
#define _PRINT_H_

/* file: print.h */
#include "common_inc.h"

extern void print_text(char *str);
extern void print_num(int32_t value);
extern uint8_t int2str(char* des, int32_t value);
	
#endif /* _PRINT_H_ */
