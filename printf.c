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
 * helper - print char and strings
 * @count: count number
 * @format: pointer to the string
 * @args: list og arguments
 *
 * Return: return -1 otherwise no return
 */
int helper(int *count, const char *format, va_list args)
{
	char *str;
	char ch, percent = '%';

	if (*format == '\0')
	{
		return (-1);
	}
	else if (*format == 'c')
	{
		ch = va_arg(args, int);
		*count += print_char(ch);
	}
	else if (*format == 's')
	{
		str = va_arg(args, char*);
		*count += print_string(str);
	}
	else if (*format == '%')
	{
		*count += write(1, &percent, 1);
	}
	else
	{
		*count += write(1, "%", 1);
		*count += write(1, format, 1);
	}
	return (0);
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
			helper(&count, format, args);
		}
		else
		{
			count += write(1, format, 1);
		}
	}
	va_end(args);
	return (count);
}
