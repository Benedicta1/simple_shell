#include "shell.h"

/**
 * our_clear_info - This initializez the info_t structure
 * @info: The structure address
 */

void our_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * our_set_info - This initailizes the info_t structure
 * @info: The structure address
 * @av: This is the argument vector
 */

void our_set_info(info_t *info, char **av)
{
	int a = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = our_strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = our_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (a = 0; info->argv && info->argv[a]; a++)
			;
		info->argc = a;
		our_replace_alias(info);
		our_replace_vars(info);
	}
}

/**
 * our_free_info - This frees the structure fields
 * @info: The structure address
 * @all: This is true if frreing all fields
 * Return: Nothing
 */

void our_free_info(info_t *info, int all)
{
	our_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			our_free_list(&(info->env));
		if (info->history)
			our_free_list(&(info->history));
		if (info->alias)
			our_free_list(&(info->alias));
		our_ffree(info->environ);
		info->environ = NULL;

		our_bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		our_putchar(BUF_FLUSH);
	}
}

