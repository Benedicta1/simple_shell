#include "shell.h"


/**
 * our_eputs - This prints an input string
 * @str: This is the string to be printed
 * Return: Prints Nothing
 */

void our_eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		our_eputchar(str[a]);
		a++;
	}
}

/**
 * our_eputchar - This writes the character c to stderr
 * @c: This is the character to print
 * Return: On success 1.
 */

int our_eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}

	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}


/**
 * our_putfd - This writes the character c to given fd
 * @c: This is the character to print
 * @fd: This is the file desceiptor to write to
 * Return: On success 1.
 */

int our_putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;

	return (1);
}


/**
 * our_putsfd - This prints an input string
 * @str: This is the string to be printed
 * @fd: This is the file descriptor to write to
 * Return: The number of chars put
 */

int our_putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += our_putfd(*str++, fd);
	}
	return (a);
}
