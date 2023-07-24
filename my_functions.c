return (1);
}

int p_string(va_list args)
{
	int i;
	const char *s;

	s = va_arg(args, const char *);
	if (s == NULL)
		s = "(null)";
	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
	return (i);
}

int p_percent(__attribute__((unused)) va_list args)
{
	_putchar('%');
	return (1);
}


int p_integer(va_list args)
{
	int n;

	n = print_number(args);
	return (n);

}
