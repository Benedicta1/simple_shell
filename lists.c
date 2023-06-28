#include "shell.h"

/**
 * add_node - This adds a node to the start of
 * the list
 * @head: This is the address of the pointer to the head node
 * @str: This is the str field of node
 * @num: This is the node indes used by history
 * Return: This returns the size of the list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	our_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = our_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - This adds a node to the end of the list
 * @head: This is the address of the pointer to
 * the head node.
 * @str: This is the str field of the node.
 * @num: This is the node index used by the hitory
 * Return: This returns the size of the list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);
	our_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = our_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * our_print_list_str - This prints only the str elements of a
 * list_t linked list
 * @h: This is the pointer to the fist node
 * Return: This returns the size of the list.
 */

size_t our_print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		our_puts(h->str ? h->str :
				"(nil)");
		our_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * our_delete_node_at_index - This deletes the node at a
 * given index
 * @head: This is the address of the pointer
 * to the first node
 * @index: The index of the node to delete
 * Return: 1 on success, 0 on failure
 */


int our_delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;

	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * our_free_list - This frees all nodes of a list
 * @head_ptr: This is the address of pointer to head node
 * Return: void
 */

void our_free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
