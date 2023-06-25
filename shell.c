#include "shell.h"

/**
 * sig_handler - This checks if Ctrl C is pressed
 * @sig_num: This is an integer
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		our_puts("\n#cisfun$ ");
	}
}

/**
* our_EOF - This handles the end of the  File
* @len: This is the return value of getline function
* @buff: This represent the buffer
 */
void our_EOF(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			our_puts("\n");
			free(buff);
		}
		exit(0);
	}
}
/**
  * our_isatty - This verify the terminal
  */

void our_isatty(void)
{
	if (isatty(STDIN_FILENO))
		our_puts("#cisfun$ ");
}
/**
 * main - This represent the Shell
 * Return: 0 if success
 */

int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **);

	signal(SIGINT, sig_handler);
	while (len != EOF)
	{
		our_isatty();
		len = getline(&buff, &size, stdin);
		our_EOF(len, buff);
		arv = our_splitstring(buff, " \n");
		if (!arv || !arv[0])
			execute(arv);
		else
		{
			value = getenv("PATH");
			head = linkpath(value);
			pathname =our_which(arv[0], head);
			f = our_checkbuild(arv);
			if (f)
			{
				free(buff);
				f(arv);
			}
			else if (!pathname)
				execute(arv);
			else if (pathname)
			{
				free(arv[0]);
				arv[0] = pathname;
				execute(arv);
			}
		}
	}
	our_free_list(head);
	our_freearv(arv);
	free(buff);
	return (0);
}
