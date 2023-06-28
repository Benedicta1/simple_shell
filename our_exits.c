#include "shell.h"

/**
 **our_strncpy - This copies a string
 *@dest: is the destination string to be copied to
 *@src: is the source string
 *@n: This is the amount of characters to be copied
 *Return: is the concatenated string
 */
char *our_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **our_strncat - This concatenates two strings
 *@dest: This is the first string
 *@src: This is the second string
 *@n: the amount of bytes to be maximally used
 *Return: This concatenated string
 */
char *our_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **our_strchr - This locates a character in a string
 *@s: This is the string to be parsed
 *@c: This is the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *our_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

