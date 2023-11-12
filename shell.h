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

/* Read/Write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Convert number */
#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

/* 1 if Using System getline */
#define USE_SYSTEM_GETLINE 0
#define USE_STR_TOKENIZER 0

/* History */
#define SHELL_HISTORY_FILE ".my_shell_shell_history"
#define SHELL_HISTORY_MAX 4096

extern char **shell_environ;

/**
 * struct shell_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct shell_liststr
{
    int num;
    char *str;
    struct shell_liststr *next;
} shell_list_t;

/**
 * struct shell_passinfo - contains pseudo-arguments
 * @arg: arguments contained in getline
 * @argv: an array of strings from arg
 * @path: a string path
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error for exits
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list of environment variables
 * @history: history node
 * @alias: alias node
 * @shell_environ: modified copy of environment
 * @env_changed: on if environment was changed
 * @status: the return status of the last executed command
 * @cmd_buffer: address of pointer
 * @cmd_buffer_type: COMMAND_type (||, &&, ;)
 * @read_fd: the file descriptor from which to read line input
 * @history_count: history line number count
 */
typedef struct shell_passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    shell_list_t *env;
    shell_list_t *history;
    shell_list_t *alias;
    char **shell_environ;
    int env_changed;
    int status;
    char **cmd_buffer;
    int cmd_buffer_type;
    int read_fd;
    int history_count;
} shell_info_t;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
 * struct shell_builtin - encapsulates a string and its corresponding function.
 * @type: the specific command string.
 * @func: the function associated with the command.
 */
typedef struct shell_builtin
{
    char *type;
    int (*func)(shell_info_t *);
} shell_builtin_table;

/* shell_shloop.c */
int hsh(shell_info_t *, char **);
int shell_find_builtin(shell_info_t *);
void shell_find_command(shell_info_t *);
void shell_fork_command(shell_info_t *);

/* shell_parser.c */
int shell_is_command(shell_info_t *, char *);
char *shell_duplicate_chars(char *, int, int);
char *shell_find_path(shell_info_t *, char *, char *);

/* shell_loophsh.c */
int shell_loophsh(char **);

/* shell_string1.c */
int shell_string_length(char *);
int shell_string_compare(char *, char *);
char *shell_starts_with(const char *, const char *);
char *shell_string_concat(char *, char *);

/* shell_string2.c */
char *shell_string_copy(char *, char *);
char *shell_string_duplicate(const char *);
void shell_puts(char *);
int shell_putchar(char);

/* shell_exit.c */
char *shell_string_copy_n(char *, char *, int);
char *shell_string_concat_n(char *, char *, int);
char *shell_string_find_char(char *, char);

/* shell_tokenizer.c */
char **shell_string_tokenize(char *, char *);
char **shell_string_tokenize2(char *, char);

/* shell_realloc.c */
char *shell_memory_set(char *, char, unsigned int);
void shell_free(char **);
void *shell_reallocate(void *, unsigned int, unsigned int);

/* shell_memory.c */
int shell_buffer_free(void **);

/* shell_atoi.c */
int shell_interactive(shell_info_t *);
int shell_is_delimiter(char, char *);
int shell_is_alpha(int);
int shell_ascii_to_integer(char *);

/* shell_errors1.c */
void shell_error_puts(char *);
int shell_error_putchar(char);
int shell_put_fd(char c, int fd);
int shell_puts_fd(char *str, int fd);

/* shell_errors2.c */
int shell_error_ascii_to_integer(char *);
void shell_print_error(shell_info_t *, char *);
int shell_print_decimal(int, int);
char *shell_convert_number(long int, int, int);
void shell_remove_comments(char *);

/* shell_builtin1.c */
int shell_exit(shell_info_t *);
int shell_change_directory(shell_info_t *);
int shell_help(shell_info_t *);

/* shell_builtin2.c */
int shell_history(shell_info_t *);
int shell_alias(shell_info_t *);
int shell_unset_alias(shell_info_t *, char *);
int shell_set_alias(shell_info_t *, char *);

/* shell_getline.c */
ssize_t shell_get_input(shell_info_t *);
int shell_get_line(shell_info_t *, char **, size_t *);
void shell_signal_interrupt_handler(int);

/* shell_getinfo.c */
void shell_clear_info(shell_info_t *);
void shell_set_info(shell_info_t *, char **);
void shell_free_info(shell_info_t *, int);

/* shell_environment.c */
char *shell_get_environment(shell_info_t *, const char *);
int shell_environment(shell_info_t *);
int shell_set_environment(shell_info_t *);
int shell_unset_environment(shell_info_t *);
int shell_populate_environment_list(shell_info_t *);

/* shell_getenv.c */
char **shell_get_shell_environment(shell_info_t *);
int shell_unset_environment_variable(shell_info_t *, char *);
int shell_set_environment_variable(shell_info_t *, char *, char *);

/* shell_history.c */
char *shell_get_history_file(shell_info_t *);
int shell_write_history(shell_info_t *);
int shell_read_history(shell_info_t *);
int shell_build_history_list(shell_info_t *, char *, int);
int shell_renumber_history(shell_info_t *);

/* shell_variables.c */
int shell_is_command_chain(shell_info_t *, char *, size_t *);
void shell_check_command_chain(shell_info_t *, char *, size_t *, size_t, size_t);
int shell_replace_aliases(shell_info_t *);
int shell_replace_variables(shell_info_t *);
int shell_replace_string(char **, char *);

/* shell_list1.c */
shell_list_t *shell_add_node(shell_list_t **, const char *, int);
shell_list_t *shell_add_node_end(shell_list_t **, const char *, int);
size_t shell_print_list_string(const shell_list_t *);
int shell_delete_node_at_index(shell_list_t **, unsigned int);
void shell_free_list(shell_list_t **);

/* shell_list2.c */
size_t shell_list_length(const shell_list_t *);
char **shell_list_to_strings(shell_list_t *);
size_t shell_print_list(const shell_list_t *);
shell_list_t *shell_node_starts_with(shell_list_t *, char *, char);
ssize_t shell_get_node_index(shell_list_t *, shell_list_t *);

#endif
