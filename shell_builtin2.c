#include "shell.h"

/**
 * shell_history - display the history list.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int shell_history(shell_info_t *info)
{
	shell_print_list(info->history);
	return (0);
}

/**
 * shell_unset_alias - set alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 - success,
 *                1 - fail
 */
int shell_unset_alias(shell_info_t *info, char *str)
{
	char *a, b;
	int ret;

	a = shell_string_find_char(str, '=');
	if (!a)
	{
		return (1);
	}
	b = *a;
	*a = 0;
	ret = shell_delete_node_at_index(&(info->alias),
                        shell_get_node_index(info->alias, shell_node_starts_with(info->alias, str, -1)));
	*a = b;
	return (ret);
}

/**
 * shell_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 - success
 */
int shell_set_alias(shell_info_t *info, char *str)
{
        char *a;

        a = shell_string_find_char(str, '=');
        if (!a)
        {
                return (1);
        }
        if (!*++a)
        {
                return (shell_unset_alias(info, str));
        }

        shell_unset_alias(info, str);
        return (shell_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * shell_print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 - Success
 */
int shell_print_alias(shell_list_t *node)
{
        char *a = NULL, *b = NULL;

        if (node)
        {
                a = shell_string_find_char(node->str, '=');
                for (b = node->str; b <= a; b++)
                {
                        shell_putchar(*b);
                }
                shell_putchar('\'');
                shell_puts(a + 1);
                shell_puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * shell_alias - mimics thr alias builtin
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int shell_alias(shell_info_t *info)
{
        int j = 0;
        char *a = NULL;
        shell_list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        shell_print_alias(node);
                        node = node->next;
                }
                return (0);
        }
        for (j = 1; info->argv[j]; j++)
        {
                a = shell_string_find_char(info->argv[j], '=');
                if (a)
                {
                        shell_set_alias(info, info->argv[j]);
                }
                else
                        shell_print_alias(shell_node_starts_with(info->alias, info->argv[j], '='));
        }

        return (0);
}
