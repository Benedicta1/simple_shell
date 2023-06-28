#include "shell.h"

/**
 * our_input_buf - This buffers chained commands
 * @info: This is the parameter struct
 * @buf: This is the address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t our_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT,our_sigintHandler);
#if USE_GETLINE
		b = getline(buf, &len_p, stdin);
#else
		b = our_getline(info, buf, &len_p);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0'; /* remove trailing newline */
				b--;
			}
			info->linecount_flag = 1;
			our_remove_comments(*buf);
			our_build_history_list(info, *buf, info->histcount++);
			/* if (our_strchr(*buf, ';')) is this a command chain? */
			{
				*len = b;
				info->cmd_buf = buf;
			}
		}
	}
	return (b);
}

/**
 * our_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t our_get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	our_putchar(BUF_FLUSH);
	r = our_input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		our_check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (our_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (our_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * our_read_buf - This reads a buffer
 * @info: This is the parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t our_read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * our_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int our_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = our_read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = our_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = our_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		our_strncat(new_p, buf + i, k - i);
	else
		our_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * our_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void our_sigintHandler(__attribute__((unused))int sig_num)
{
	our_puts("\n");
	our_puts("$ ");
	our_putchar(BUF_FLUSH);
}

