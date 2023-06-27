#include "shell.h"

/**
 *our_myhistory - displays the history list, one command by line, preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int our_myhistory(info_t *info)
{
	our_print_list(info->history);
	return (0);
}

/**
 * our_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int our_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = our_delete_node_at_index(&(info->alias),
		our_get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * our_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int our_set_alias(info_t *info, char *str)
{
	char *p;

	p = our_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (our_unset_alias(info, str));

	our_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * our_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int our_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = our_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		our_putchar(*a);
		our_putchar('\'');
		our_puts(p + 1);
		our_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * our_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int our_myalias(info_t *info)
{
	int i = 0;
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
	for (i = 1; info->argv[i]; i++)
	{
		p = our_strchr(info->argv[i], '=');
		if (p)
			our_set_alias(info, info->argv[i]);
		else
			our_print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

