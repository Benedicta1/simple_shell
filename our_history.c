#include "shell.h"

/**
 * our_get_history_file - This gets the history file
 * @info: This is the parameter structure
 * Return: The allocated seing containing history file
 */

char *our_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = our_getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (our_strlen(dir) + our_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	our_strcpy(buf, dir);
	our_strcat(buf, "/");
	our_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * our_write_history - This ceates a file,or appends
 * to an existing file.
 * @info: This is the parameter structure
 * Return: 1 on success, error -1
 */

int our_write_history(info_t *info)
{
	ssize_t fd;
	char *filename = our_get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		our_putsfd(node->str, fd);
		our_putfd('\n', fd);
	}
	our_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * our_read_history - This reads the history from the file
 * @info: This is the parameter structure
 * Return: This is success on hiscount, 0 otherwise
 */


int our_read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = our_get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);

	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			our_build_history_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		our_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		our_delete_node_at_index(&(info->history), 0);
	our_renumber_history(info);
	return (info->histcount);
}

/**
 * our_build_history_list - This adds entry to a history linked list
 * @info: This is a structure containing potential arguments.
 * @buf: This represents the buffer
 * @linecount: This is the history linecount, hiscount
 * Return: This is always 0
 */


int our_build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)

		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * our_renumber_history - This renumbers the history linked list
 * after the changes.
 * @info: This structures potential arguments.
 * Return: The new histcount
 */

int our_renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}

	return (info->histcount = a);
}
