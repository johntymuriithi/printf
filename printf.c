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

	if (str == NULL)
	{
		return (write(1, "null", 6));
	}
	while (str[len])
		len++;
	return (write(1, str, len));
}

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char ch, *str, percent;

	if (format == NULL)
	{
		return (-1);
	}

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
				count += print_string(str);
			}
			else if (*format == '%')
			{
				percent = '%';
				count += write(1, &percent, 1);
			}
			else
			{
				count += write(1, "%", 1);
				count += write(1, format, 1);
				/**count += write(1, format - 1, 1);*/
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
