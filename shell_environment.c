#include "shell.h"

/**
 * shell_environment - prints the current environment
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_environment(shell_info_t *info)
{
        shell_print_list_string(info->env);
        return (0);
}

/**
 * shell_get_environment - gets the value of an environ variable
 * @info: Structure containing arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *shell_get_environment(shell_info_t *info, const char *name)
{
        shell_list_t *node = info->env;
        char *a;

        while (node)
        {
                a = shell_starts_with(node->str, name);
                if (a && *a)
                {
                        return (a);
                }
                node = node->next;
        }
        return (NULL);
}

/**
 * shell_set_environment - Initialize a new envirnment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_set_environment(shell_info_t *info)
{
        if (info->argc != 3)
        {
                shell_error_puts("Incorrect number of arguments\n");
                return (1);
        }
        if (shell_set_environment_variable(info, info->argv[1], info->argv[2]))
        {
                return (0);
        }
        return (1);
}

/**
 * shell_unset_environment -  Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int shell_unset_environment(shell_info_t *info)
{
        int i;

        if (info->argc == 1)
        {
                shell_error_puts("Too few arguments.\n");
                return (1);
        }
        for (i = 1; i <= info->argc; i++)
        {
                shell_unset_environment_variable(info, info->argv[1]);
        }
        return (0);
}

/**
 * shell_populate_environment_list - populates env linked list
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_populate_environment_list(shell_info_t *info)
{
        shell_list_t *node = NULL;
        size_t j;

        for (j = 0; environ[j]; j++)
        {
                shell_add_node_end(&node, environ[j], 0);
        }
        info->env = node;
        return (0);
}
