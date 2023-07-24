#ifndef MY_PRINTF
#define MY_PRINTF

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>


struct convert
{
	char *sym;
	int (*f)(va_list);
};
typedef struct convert conver_t;


int _putchar(char c);
int _printf(const char *format, ...);
int p_char(va_list);
int p_string(va_list args);
int p_percent(va_list);

#endif
