#include "shell.h"

/**
 * our_myenv - This prints the current environment
 * @info: This is a structure containing potential arguments.
 * Return: Always 0
 */
int our_myenv(info_t *info)
{
	our_print_list_str(info->env);
	return (0);
}

/**
 * our_getenv - This gets the value of an environ variable
 * @info: This is a structure containing potential arguments.
 * @name: env var name
 *
 * Return: This returns the value
 */
char *our_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = our_starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * our_mysetenv - This initialize a new environment variable.
 * @info: This is a structure containing potential arguments.
 *  Return: Always 0
 */
int our_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		our_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (our_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * our_myunsetenv - This removes an environment variable
 * @info: This is a structure containing potential arguments.
 * Return: Always 0
 */
int our_myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		our_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		our_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * our_populate_env_list - This populates env linked list
 * @info: This is the structure containing potential arguments.
 * Return: Always 0
 */
int our_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}

