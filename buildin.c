#include "shell.h"

/**
 *our_myexit - exits the shell
 * @info: This structure contains potential arguments.
 * Return: This exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int our_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = our_erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			our_print_error(info, "Illegal number: ");
			our_eputs(info->argv[1]);
			our_eputchar('\n');
			return (1);
		}
		info->err_num = our_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * our_mycd - This changes the current directory of the process
 * @info: This structure contains potential arguments.
 * Return: Always 0
 */
int our_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		our_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = our_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = our_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (our_strcmp(info->argv[1], "-") == 0)
	{
		if (!our_getenv(info, "OLDPWD="))
		{
			our_puts(s);
			our_putchar('\n');
			return (1);
		}
		our_puts(our_getenv(info, "OLDPWD=")), our_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = our_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		our_print_error(info, "can't cd to ");
		our_eputs(info->argv[1]), our_eputchar('\n');
	}
	else
	{
		our_setenv(info, "OLDPWD", our_getenv(info, "PWD="));
		our_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * our_myhelp - This changes the current directory of the process
 * @info: This structure contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int our_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	our_puts("help call works. Function not yet implemented \n");
	if (0)
		our_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

