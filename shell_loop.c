#include "shell.h"

/**
 * hsh - This is the main shell loop
 * @info: This is the parameter & return info struct
 * @av: This is the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int builtin_ret = 0;

	while (a != -1 && builtin_ret != -2)
	{
		our_clear_info(info);
		if (our_interactive(info))
			our_puts("$ ");
		our_eputchar(BUF_FLUSH);
		a = our_get_input(info);
		if (a != -1)
		{
			our_set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (our_interactive(info))
			our_putchar('\n');
		our_free_info(info, 0);
	}
	our_write_history(info);
	our_free_info(info, 1);
	if (!our_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - This finds a builtin command
 * @info: This is the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 */
int find_builtin(info_t *info)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", our_myexit},
		{"env", our_myenv},
		{"help", our_myhelp},
		{"history", our_myhistory},
		{"setenv", our_mysetenv},
		{"unsetenv", our_myunsetenv},
		{"cd", our_mycd},
		{"alias", our_myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (our_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - This finds a command in PATH
 * @info: This is the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, k = 0; info->arg[a]; a++)
		if (!our_is_delim(info->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = our_find_path(info, our_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((our_interactive(info) || our_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && our_is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			our_print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - This forks a an exec thread to run cmd
 * @info:This is  the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, our_get_environ(info)) == -1)
		{
			our_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				our_print_error(info, "Permission denied\n");
		}
	}
}

