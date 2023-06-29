#include "shell.h"

/**
 * our_strcpy - This copies a string
 * @dest: This is the destination
 * @src: This is the source
 *
 * Return: pointer to destination
 */
char *our_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * our_strdup - This duplicates a string
 * @str: This is the string to duplicate
 *
 * Return: This points to the duplicated string
 */
char *our_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * our_puts - This prints an input string
 * @str: This is the string to be printed
 *
 * Return: This presents Nothing
 */
void our_puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		our_putchar(str[a]);
		a++;
	}
}

/**
 * our_putchar - This writes the character c to stdout
 * @c: This is  character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int our_putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

