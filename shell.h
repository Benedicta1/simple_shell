#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int our_putchar(char c);
void our_puts(char *str);
int our_strlen(char *s);
char *our_strdup(char *str);
char *our_concat_all(char *name, char *sep, char *value);

char **our_splitstring(char *str, const char *delim);
void our_execute(char **argv);
void *our_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


extern char **environ;

/**
 * struct list_path - This is a linked list that contains the PATH directories
 * @dir: This contains the directory in path
 * @p: This is the pointer to the next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


char *our_getenv(const char *name);
list_path *add_node_end(list_path **head, char *str);
list_path *linkpath(char *path);
char *our_which(char *filename, list_path *head);

/**
 * struct mybuild - This is a pointer to function with
 * corresponding buildin command
 * @name: This is a build in command
 * @func: This executes the build in command
 */
typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;

void(*our_checkbuild(char **arv))(char **arv);
int our_atoi(char *s);
void our_exitt(char **arv);
void our_env(char **arv);
void our_setenv(char **arv);
void our_unsetenv(char **arv);

void our_freearv(char **arv);
void our_free_list(list_path *head);


#endif

