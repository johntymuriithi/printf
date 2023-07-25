#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include "main.h"
/**
 * print_int - The function handles d and i specifiers
 *@num: The integer to be printed
 *@sign: The sign of the integer
 *@space: The space between the integer
 *
 *Return: Return count.
 */

int print_int(int num, char sign, char space)
{
	int count = 0;
	char buffer[12];
	int len = 0;

	if (num == INT_MIN)
	{
		count += write(1, "-2147483648", 11);
		return (count);
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
