#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include "main.h"

int print_int(int num, char sign, char space)
{
	int count = 0;
	char buffer[12];
	int len = 0;

	if (num == INT_MIN)
	{
		count += write(1, "-2147483648", 11);
		return count;
	}

	if (num < 0)
	{
		count += write(1, "-", 1);
		num = -num;
	} else if (sign)
	{
		count += write(1, "+", 1);
	} else if (space)
	{
		count += write(1, " ", 1);
	}
	else if (num == 0)
	{
		count += write(1, "0", 1);
		return (count);
	}

	do {
		buffer[len++] = '0' + num % 10;
		num /= 10;
	} while (num > 0);

	while (len > 0)
		count += write(1, &buffer[--len], 1);

	return (count);
}

int _printInt(const char *format, ...)
{
	va_list args;
	int count = 0;

	if (format == NULL)
	{
		return -1;
	}

	va_start(args, format);
	for (; *format; format++)
	{
		if (*format == '%')
		{
			format++;

			if (*format == '\0')
			{
				return -1;
			}
			if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				char sign = 0;
				char space = 0;

				format--;
				while (*++format == '+' || *format == ' ')
					sign = (*format == '+') ? 1 : 0;

				count += print_int(num, sign, space);
			}
			else
			{
				count += write(1, "%", 1);
				count += write(1, format, 1);
			}
		}
		else
		{
			count += write(1, format, 1);
		}
	}
	va_end(args);
	return count;
}
