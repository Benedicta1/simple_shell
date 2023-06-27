#include "shell.h"

/**
 * our_interactive - This returns true if shell is interactive mode
 * @info: This is a struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int our_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * our_is_delim - This checks if character is a delimeter
 * @c: This is the char to check
 * @delim: This is the delimeter string
 * Return: 1 if true, 0 if false
 */
int our_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * our_isalpha - This checks for alphabetic character
 * @c: This is the character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int our_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * our_atoi - This converts a string to an integer
 * @s: This is the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int our_atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

