#include "shell.h"

/**
 * **our_strtow - This splits a string into words.
 * @str: This is the input string
 * @d: This is the delimeter string
 * Return: This is a pointer to an array of strings,
 * or NULL on failure
 */

char **our_strtow(char *str, char *d)
{
	int a, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!our_is_delim(str[a], d) && (our_is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (our_is_delim(str[a], d))
			a++;
		k = 0;
		while (!our_is_delim(str[a + k], d) && str[a + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **our_strtow2 - This splits a string into words
 * @str: This is the input string
 * @d: This is the delimeter
 * Return: pointer to an array of strings, or NULL on failure
 */
char **our_strtow2(char *str, char d)
{
	int a, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		k = 0;
		while (str[a + k] != d && str[a + k] && str[a + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

