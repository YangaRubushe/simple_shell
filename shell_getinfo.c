#include "shell.h"

/**
 * shell_ clear_info - initializes info_t struct
 * @info: struct address
 */
void shell_clear_info(shell_info_t *info)
{
        info->arg = NULL;
        info->argv = NULL;
        info->path = NULL;
        info->argc = 0;
}

/**
 * shell_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void shell_set_info(shell_info_t *info, char **av)
{
        int i = 0;

        info->fname = av[0];
        if (info->arg)
        {
                info->argv = strtow(info->arg, " \t");
                if (!info->argv)
                {

                        info->argv = malloc(sizeof(char *) * 2);
                        if (info->argv)
                        {
                                info->argv[0] = shell_string_duplicate(info->arg);
                                info->argv[1] = NULL;
                        }
                }
                for (i = 0; info->argv && info->argv[i]; i++)
                        ;
                info->argc = i;

                shell_replace_aliases(info);
                shell_replace_variables(info);
        }
}

/**
 * shell_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void shell_free_info(shell_info_t *info, int all)
{
        ffree(info->argv);
        info->argv = NULL;
        info->path = NULL;
        if (all)
        {
                if (!info->cmd_buffer)
                        free(info->arg);
                if (info->env)
                        free_list(&(info->env));
                if (info->history)
                        free_list(&(info->history));
                if (info->alias)
                        free_list(&(info->alias));
                ffree(info->environ);
                info->environ = NULL;
                bfree((void **)info->cmd_buffer);
                if (info->readfd > 2)
                        close(info->read_fd);
                shell_putchar(BUFFER_FLUSH);
        }
}
