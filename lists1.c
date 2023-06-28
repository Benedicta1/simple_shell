#include "shell.h"

/**
 * our_list_len - This determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t our_list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * our_list_to_strings - returns an array of strings of the list
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **our_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t h = our_list_len(head), j;
	char **strs;
	char *str;

	if (!head || !h)
		return (NULL);
	strs = malloc(sizeof(char *) * (h + 1));
	if (!strs)
		return (NULL);
	for (h = 0; node; node = node->next, h++)
	{
		str = malloc(our_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < h; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = our_strcpy(str, node->str);
		strs[h] = str;
	}
	strs[h] = NULL;
	return (strs);
}


/**
 * our_print_list - This prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t our_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		our_puts(our_convert_number(h->num, 10, 0));
		our_putchar(':');
		our_putchar(' ');
		our_puts(h->str ? h->str : "(nil)");
		our_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - This returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: This is the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = our_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * our_get_node_index - This gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t our_get_node_index(list_t *head, list_t *node)
{
	size_t s = 0;

	while (head)
	{
		if (head == node)
			return (s);
		head = head->next;
		s++;
	}
	return (-1);
}

