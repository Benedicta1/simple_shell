#include "shell.h"

/**
 * our_erratoi - This converts a string to an integer
 * @s: This is the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int our_erratoi(char *s)
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * our_print_error - This prints an error message
 * @info: The parameter & return info struct
 * @estr: This string contains specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void our_print_error(info_t *info, char *estr)
{
	our_eputs(info->fname);
	our_eputs(": ");
	our_print_d(info->line_count, STDERR_FILENO);
	our_eputs(": ");
	our_eputs(info->argv[0]);
	our_eputs(": ");
	our_eputs(estr);
}

/**
 * our_print_d - This function prints a decimal (integer)
 * @input: This is the input
 * @fd: This is the file descriptor to write to
 *
 * Return: This is the number of characters printed
 */
int our_print_d(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int b, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = __putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (_abs_ / b)
		{
			__putchar('0' + current / b);
			count++;
		}
		current %= b;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * our_convert_number - This is a converter function, a clone of itoa
 * @num: Represents the number
 * @base: Represents the base
 * @flags: argument flags
 *
 * Return: string
 */
char *our_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * our_remove_comments - This function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void our_remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}

