#include "shell.h"

/**
 * shell_list_length - length of linked list
 * @h: pointer
 *
 * Return: size of list
 */
size_t shell_list_length(const shell_list_t *h)
{
        size_t i = 0;

        while (h)
        {
                h = h->next;
                i++;
        }
        return (i);
}

/**
 * shell_list_to_strings - returns array
 * @head: pointer
 *
 * Return: array
 */
char **shell_list_to_strings(shell_list_t *head)
{
        shell_list_t *node = head;
        size_t i = shell_list_length(head), j;
        char **strs;
        char *str;

        if (!head || !i)
                return (NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if (!strs)
                return (NULL);
        for (i = 0; node; node = node->next, i++)
        {
                str = malloc(shell_string_length(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = shell_string_copy(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return (strs);
}

/**
 * print_list - prints all elements
 * @h: pointer to 1st node
 *
 * Return: size of list
 */
size_t shell_print_list(const shell_list_t *h)
{
        size_t i = 0;

        while (h)
        {
                shell_puts(shell_convert_number(h->num, 10, 0));
                shell_putchar(':');
                shell_putchar(' ');
                shell_puts(h->str ? h->str : "(nil)");
                shell_puts("\n");
                h = h->next;
                i++;
        }

        return (i);
}

/**
 * shell_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character
 *
 * Return: match node or null
 */
shell_list_t *shell_node_starts_with(shell_list_t *node, char *prefix, char c)
{
        char *p = NULL;

        while (node)
        {
                p = shell_starts_with(node->str, prefix);
                if (p && ((c == -1) || (*p == c)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}

/**
 * shell_get_node_index - gets the index
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t shell_get_node_index(shell_list_t *head, shell_list_t *node)
{
        size_t i = 0;

        while (head)
        {
                if (head == node)
                        return (i);
                head = head->next;
                i++;
        }
        return (-1);
}
