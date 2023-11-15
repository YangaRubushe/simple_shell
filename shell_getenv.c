#include "shell.h"

/**
 * shell_get_shell_environment - return the string array copy of our environ
 * @info: Structure containing potentail argument. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **shell_get_shell_environment(shell_info_t *info)
{
        if (!info->environ || info->env_changed)
        {
                info->environ = shell_list_to_strings(info->env);
                info->env_changed = 0;
        }

        return (info->environ);
}

/**
 * shell_unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential argumments. Unsed to maintain
 *        constant function prototype.
 * Return: 1 delete, 0 otherwise
 * @var: the string env var property
 */
int shell_unset_environment_variable(shell_info_t *info, char *var)
{
        shell_list_t *node = info->env;
        size_t i = 0;
        char *p;

        if (!node || !var)
                return (0);

        while (node)
        {
                p = shell_starts_with(node->str, var);
                if (p && *p == '=')
                {
                        info->env_changed = shell_delete_node_at_index(&(info->env), i);
                        i = 0;
                        node = info->env;
                        continue;
                }
                node = node->next;
                i++;
        }
        return (info->env_changed);
}

/**
 * shell_set_environmnet_variable - Initialize a new environment variable,
 *           or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int shell_set_environment_variable(shell_info_t *info, char *var, char *value)
{
        char *buf = NULL;
        shell_list_t *node;
        char *p;

        if (!var || !value)
                return (0);

        buf = malloc(shell_string_length(var) + shell_string_length(value) + 2);
        if (!buf)
                return (1);
        shell_string_copy(buf, var);
        shell_string_concat(buf, "=");
        shell_string_concat(buf, value);
        node = info->env;
        while (node)
        {
                p = shell_starts_with(node->str, var);
                if (p && *p == '=')
                {
                        free(node->str);
                        node->str = buf;
                        info->env_changed = 1;
                        return (0);

                }
                node = node->next;
        }
        shell_add_node_end(&(info->env), buf, 0);
        free(buf);
        info->env_changed = 1;
        return (0);
}
