#include "shell.h"

/**
 * our_is_cmd - This determines if a file is an executable command
 * @info: This is the info struct
 * @path: This is the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int our_is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * our_dup_chars - This duplicates the characters
 * @pathstr: This is the PATH string
 * @start: This is the starting index
 * @stop: This is the stopping index
 *
 * Return: pointer to new buffer
 */
char *our_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[k++] = pathstr[a];
	buf[k] = 0;
	return (buf);
}

/**
 * our_find_path - This finds this cmd in the PATH string
 * @info: This is the info struct
 * @pathstr: This is the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *our_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((our_strlen(cmd) > 2) && our_starts_with(cmd, "./"))
	{
		if (our_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = our_dup_chars(pathstr, curr_pos, i);
			if (!*path)
				our_strcat(path, cmd);
			else
			{
				our_strcat(path, "/");
				our_strcat(path, cmd);
			}
			if (our_is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

