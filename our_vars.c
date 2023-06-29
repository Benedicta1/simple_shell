#include "shell.h"

/**
 * our_is_chain - This test if current char in buffer
 * is a chain delimeter
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int our_is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * our_check_chain - This checks if we should continue chaining
 * based on last status
 * @info: This is the parameter struct
 * @buf: This is the char buffer
 * @p: This is the address of current position in buf
 * @i: This is the starting position in buf
 * @len: This is the length of buf
 *
 * Return: Void
 */
void our_check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * our_replace_alias - This replaces an aliases in the tokenized string
 * @info: This is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = our_strchr(node->str, '=');
		if (!p)
			return (0);
		p = our_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * our_replace_vars - This replaces vars in the tokenized string
 * @info: This is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!our_strcmp(info->argv[a], "$?"))
		{
			our_replace_string(&(info->argv[a]),
					our_strdup(our_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!our_strcmp(info->argv[a], "$$"))
		{
			our_replace_string(&(info->argv[a]),
					our_strdup(our_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			our_replace_string(&(info->argv[a]),
					our_strdup(our_strchr(node->str, '=') + 1));
			continue;
		}
		our_replace_string(&info->argv[a], our_strdup(""));

	}
	return (0);
}

/**
 * our_replace_string - This replaces the string
 * @old: This is the address of old string
 * @new: This is a new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
