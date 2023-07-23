#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

int print_char(int c)
{
	return (write(1, &c, 1));
}

int print_string(const char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (write(1, str, len));
}

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char ch, *str, percent;

	va_start(args, format);
	for (; *format; format++)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
			{
				ch = va_arg(args, int);
				count += print_char(ch);
			}
			else if (*format == 's')
			{
				str = va_arg(args, char*);
				if (str)
				{
					count += print_string(str);
				}
				else
				{
					count += write(1, "(null)", 6);
				}
			}
			else if (*format == '%')
			{
				percent = '%';
				count += write(1, &percent, 1);
			}
		}
		else
		{
			count += write(1, format, 1);
		}
	}
	va_end(args);
	return (count);
}