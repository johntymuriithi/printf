#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int print_char(char c)
{
	return (write(1, &c, 1));
}

int print_string(const char *str)
{
	int len = 0;

	while (str[len]) len++;
	return write(1, str, len);
}

int print_unsigned(unsigned int num)
{
	unsigned int temp = num;
	unsigned int divisor = 1;
	int digit_count = 1;

	while (temp / 10) {
		divisor *= 10;
		digit_count++;
		temp /= 10;
	}

	while (divisor) {
		char digit = '0' + (num / divisor);
		print_char(digit);
		num %= divisor;
		divisor /= 10;
	}

	return digit_count;
}

int print_hexadecimal(unsigned int num, int uppercase)
{
	char hex_chars[] = "0123456789abcdef";

	if (uppercase)
		hex_chars[10] = 'A', hex_chars[11] = 'B', hex_chars[12] = 'C',
			hex_chars[13] = 'D', hex_chars[14] = 'E', hex_chars[15] = 'F';

	unsigned int temp = num;
	unsigned int divisor = 1;
	int digit_count = 1;

	while (temp / 16)
	{
		divisor *= 16;
		digit_count++;
		temp /= 16;
	}
	while (divisor)
	{
		char digit = hex_chars[num / divisor];

		print_char(digit);
		num %= divisor;
		divisor /= 16;
	}

	return digit_count;
}

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);
	for (; *format; format++)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				count += print_char('%');
			}
			else if (*format == 'c')
			{
				char ch = va_arg(args, int);

				count += print_char(ch);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char*);

				if (str)
				{
					count += print_string(str);
				}
				else
				{
					count += write(1, "(null)", 6);
				}
			} else if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				if (num < 0)
				{
					count += print_char('-');
					num = -num;
				}
				count += print_unsigned((unsigned int)num);
			}
			else if (*format == 'u')
			{
				unsigned int num = va_arg(args, unsigned int);

				count += print_unsigned(num);
			}
			else if (*format == 'o')
			{
				unsigned int num = va_arg(args, unsigned int);

				int digit_count = print_unsigned(num);
				count += digit_count;
			}
			else if (*format == 'x' || *format == 'X')
			{
				int uppercase = (*format == 'X');
				unsigned int num = va_arg(args, unsigned int);
				int digit_count = print_hexadecimal(num, uppercase);

				count += digit_count;
			}
			else if (*format == 'p')
			{
				void *ptr = va_arg(args, void*);
				unsigned long long int num = (unsigned long long int)ptr;

				count += write(1, "0x", 2);
				count += print_hexadecimal(num, 0);
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
