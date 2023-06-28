#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - This is the singly linked list
 * @num: This is the number field
 * @str: This is a string
 * @next: This is points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct our_passinfo - This contains pseudo-arguements pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: This is a string generated from getline containing arguements
 * @argv: This is an array of strings generated from arg
 * @path: This is a string path for the current command
 * @argc: This is the argument count
 * @line_count: This is the the error count
 * @err_num: This is the error code for exit()s
 * @linecount_flag: This is the if on count this line of input
 * @fname: This is the program filename
 * @env: This is thelinked list local copy of environ
 * @environ: This is the custom modified copy of environ from LL env
 * @history: This is the history node
 * @alias: This is the alias node
 * @env_changed: on if environ was changed
 * @status: This is the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct our_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct our_builtin - this contains a builtin string and related function
 * @type: the builtin command flag
 * @func: it is the function
 */
typedef struct our_builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int our_is_cmd(info_t *, char *);
char *our_dup_chars(char *, int, int);
char *our_find_path(info_t *, char *, char *);

/* loophsh.c */
int our_loophsh(char **);

/* toem_errors.c */
void our_eputs(char *);
int our_eputchar(char);
int our_putfd(char c, int fd);
int our_putsfd(char *str, int fd);

/* toem_string.c */
int our_strlen(char *);
int our_strcmp(char *, char *);
char *our_starts_with(const char *, const char *);
char *our_strcat(char *, char *);

/* toem_string1.c */
char *our_strcpy(char *, char *);
char *our_strdup(const char *);
void our_puts(char *);
int our_putchar(char);

/* toem_exits.c */
char *our_strncpy(char *, char *, int);
char *our_strncat(char *, char *, int);
char *our_strchr(char *, char);

/* toem_tokenizer.c */
char **our_strtow(char *, char *);
char **our_strtow2(char *, char);

/* toem_realloc.c */
char *our_memset(char *, char, unsigned int);
void our_ffree(char **);
void *our_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int our_bfree(void **);

/* toem_atoi.c */
int our_interactive(info_t *);
int our_is_delim(char, char *);
int our_isalpha(int);
int our_atoi(char *);

/* toem_errors1.c */
int our_erratoi(char *);
void our_print_error(info_t *, char *);
int our_print_d(int, int);
char *our_convert_number(long int, int, int);
void our_remove_comments(char *);

/* toem_buildin.c */
int our_myexit(info_t *);
int our_mycd(info_t *);
int our_myhelp(info_t *);

/* toem_builtin1.c */
int our_myhistory(info_t *);
int our_myalias(info_t *);

/*toem_getline.c */
ssize_t our_get_input(info_t *);
int our_getline(info_t *, char **, size_t *);
void our_sigintHandler(int);

/* toem_getinfo.c */
void our_clear_info(info_t *);
void our_set_info(info_t *, char **);
void our_free_info(info_t *, int);

/* toem_environ.c */
char *our_getenv(info_t *, const char *);
int our_myenv(info_t *);
int our_mysetenv(info_t *);
int our_myunsetenv(info_t *);
int our_populate_env_list(info_t *);

/* toem_getenv.c */
char **our_get_environ(info_t *);
int our_unsetenv(info_t *, char *);
int our_setenv(info_t *, char *, char *);

/* toem_history.c */
char *our_get_history_file(info_t *info);
int our_write_history(info_t *info);
int our_read_history(info_t *info);
int our_build_history_list(info_t *info, char *buf, int linecount);
int our_renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t our_print_list_str(const list_t *);
int our_delete_node_at_index(list_t **, unsigned int);
void our_free_list(list_t **);

/* toem_lists1.c */
size_t our_list_len(const list_t *);
char **our_list_to_strings(list_t *);
size_t our_print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t our_get_node_index(list_t *, list_t *);

/* toem_vars.c */
int our_is_chain(info_t *, char *, size_t *);
void our_check_chain(info_t *, char *, size_t *, size_t, size_t);
int our_replace_alias(info_t *);
int our_replace_vars(info_t *);
int our_replace_string(char **, char *);

#endif

