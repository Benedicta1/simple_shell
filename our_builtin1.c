#include "shell.h"

/**
 *our_myhistory - This displays the history list.
 * @info: This is a structure containing potential arguments.
 * Used to maintain constant function prototype.
 *  Return: This should always be  0
 */
int our_myhistory(info_t *info)
{
	our_print_list(info->history);
	return (0);
}

/**
 * our_unset_alias - This sets alias to string
 * @info: This is a parameter struct
 * @str: This is the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int our_unset_alias(info_t *info, char *str)
{
	char *a, b;
	int ret;

	a = strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	ret = our_delete_node_at_index(&(info->alias),
		our_get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (ret);
}

/**
 * our_set_alias - This sets the alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int our_set_alias(info_t *info, char *str)
{
	char *a;

	a = our_strchr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (our_unset_alias(info, str));

	our_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * our_print_alias - This prints an alias string
 * @node: This is the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int our_print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = our_strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		our_putchar(*a);
		our_putchar('\'');
		our_puts(b + 1);
		our_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * our_myalias - This mimics the alias builtin (man alias)
 * @info: This is a structure containing potential arguments.
 * used to maintain constant function prototype.
 *  Return: Always 0
 */
int our_myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			our_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = our_strchr(info->argv[a], '=');
		if (p)
			our_set_alias(info, info->argv[a]);
		else
			our_print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}

