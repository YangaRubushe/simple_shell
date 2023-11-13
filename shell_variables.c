#include "shell.h"

/**
 * shell_is_command_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if cahin delimeter, otherwise 0
 */
int shell_is_command_chain(shell_info_t *info, char *buf, size_t *p)
{
        size_t j = *p;

        if (buf[j] == '|' && buf[j + 1] == '|')
        {
                buf[j] = 0;
                j++;
                info->cmd_buffer_type = COMMAND_OR;
        }
        else if (buf[j] == '&' && buf[j + 1] == '&')
        {
                buf[j] = 0;
                j++;
                info->cmd_buffer_type = COMMAND_AND;
        }
        else if (buf[j] == ';')
        {
                buf[j] = 0;
                info->cmd_buffer_type = COMMAND_CHAIN;
        }
        else
                return (0);
        *p = j;
        return (1);
}

/**
 * shell_check_command_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void shell_check_command_chain(shell_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (info->cmd_buffer_type == COMMAND_AND)
        {
                if (info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }
        if (info->cmd_buffer_type == COMMAND_OR)
        {
                if (!info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }

        *p = j;
}

/**
 * shell_replace_aliases - replaces an aliases in the tokenized
 * @info: the parameter struct
 *
 * Return: 1 replace, 0 otherwise
 */
int shell_replace_aliases(shell_info_t *info)
{
        int i;
        shell_list_t *node;
        char *p;

        for (i = 0; i < 10; i++)
        {
                node = shell_node_starts_with(info->alias, info->argv[0], '=');
                if (!node)
                        return (0);
                free(info->argv[0]);
                p = shell_string_find_char(node->str, '=');
                if (!p)
                        return (0);
                p = shell_string_duplicate(p + 1);
                if (!p)
                        return (0);
                info->argv[0] = p;
        }
        return (1);
}

/**
 * shell_replace_variables - replaces var in the tokenixed string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shell_replace_variables(shell_info_t *info)
{
        int i = 0;
        shell_list_t *node;

        for (i = 0; info->argv[i]; i++)
        {
                if (info->argv[i][0] != '$' || !info->argv[i][1])
                        continue;

                if (!shell_string_compare(info->argv[i], "$?"))
                {
                        shell_replace_string(&(info->argv[i]),
                                        shell_string_duplicate(shell_convert_number(info->status, 10, 0)));
                        continue;
                }
                if (!shell_string_compare(info->argv[i], "$$"))
                {
                        shell_replace_string(&(info->argv[i]),
                                        shell_string_duplicate(shell_convert_number(getpid(), 10, 0)));
                        continue;
                }
                node = shell_node_starts_with(info->env, &info->argv[i][1], '=');
                if (node)
                {
                        shell_replace_string(&(info->argv[i]),
                                        shell_string_duplicate(shell_string_find_char(node->str, '=') + 1));
                        continue;
                }
                shell_replace_string(&info->argv[i], shell_string_duplicate(""));
        }
        return (0);
}

/**
 * shell_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int shell_replace_string(char **old, char *new)
{
        free(*old);
        *old = new;
        return (1);
}
