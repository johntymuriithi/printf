#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_char - print character
 * @c: character itself
 *
 * Return: return character
 */
int print_char(int c)
{
	return (write(1, &c, 1));
}

/**
 * print_string - print string
 * @str: pointer to the string
 *
 * Return: return the formatted string
 */
int print_string(const char *str)
{
	int len = 0;

	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (str[len])
		len++;
	return (write(1, str, len));
}

/**
 * _printf - print the printf functionality
 * @format: pointer to the string
 *@...: aother arguments
 *
 * Return: return the number of words outputed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char ch, *str, percent = '%';

	if (format == NULL)
	{
		return (-1);
	}
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	va_start(args, format);
	for (; *format; format++)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (-1);
			else if (*format == 'c')
				count += print_char(va_arg(args, int));
			else if (*format == 's')
				count += print_string(va_arg(args, char*));
			else if (*format == '%')
				count += write(1, &percent, 1);
			else
			{
				count += write(1, "%", 1);
				count += write(1, format, 1);
			}
		}
		else
			count += write(1, format, 1);
	}
	va_end(args);
	return (count);
}
