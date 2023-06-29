#include "shell.h"

/**
 * our_memset - This fills memory with a constant byte
 * @s: This is the pointer to the memory area
 * @b: This is the byte to fill *s with
 * @n: This is the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *our_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * our_ffree - This frees a string of strings
 * @pp: This is string of strings
 */
void our_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * our_realloc - This reallocates a block of memory
 * @ptr: This is apointer to previous malloc'ated block
 * @old_size: This is a byte size of previous block
 * @new_size: This is a byte size of new block
 *
 * Return: This points to the ol'block nameen.
 */
void *our_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

