#include "shell.h"

/**
 * our_get_environ - This returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **our_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = our_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * our_unsetenv - This Remove an environment variable
 * @info: This Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int our_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = our_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = our_delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * our_setenv - This Initialize a new environment variable,
 * @info: This is the Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int our_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(our_strlen(var) + our_strlen(value) + 2);
	if (!buf)
		return (1);
	our_strcpy(buf, var);
	our_strcat(buf, "=");
	our_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = our_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

