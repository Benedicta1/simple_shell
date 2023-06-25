#include "shell.h"

/**
* checkbuild - This checks if the command is a buildin
* @arv: This is an array of arguments
* Return: This is a pointer to function that takes arv and returns void
*/
void(*our_checkbuild(char **arv))(char **arv)
{
	int a, b;
	mybuild H[] = {
		{"exit", our_exitt},
		{"env", our_env},
		{"setenv", our_setenv},
		{"unsetenv", our_unsetenv},
		{NULL, NULL}
	};

	for (a = 0; H[a].name; a++)
	{
		b = 0;
		if (H[a].name[b] == arv[0][b])
		{
			for (b = 0; arv[0][b]; b++)
			{
				if (H[a].name[b] != arv[0][b])
					break;
			}
			if (!arv[0][b])
				return (H[a].func);
		}
	}
	return (0);
}

