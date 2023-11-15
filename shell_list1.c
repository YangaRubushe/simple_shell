#include "shell.h"

/**
 * shell_add_node - adds a node
 * @head: address of pointer
 * @str: str field
 * @num: node index
 *
 * Return: size of list
 */
shell_list_t *shell_add_node(shell_list_t **head, const char *str, int num)
{
	shell_list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(shell_list_t));
	if (!new_head)
		return (NULL);
	shell_memory_set((void *)new_head, 0, sizeof(shell_list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = shell_string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * shell_add_node_end - adds a node to the end
 * @head: address pf pointer to head node
 * @str: str field
 * @num: node index
 *
 * Return: size of the list
 */
shell_list_t *shell_add_node_end(shell_list_t **head, const char *str, int num)
{
	shell_list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(shell_list_t));
	if (!new_node)
		return (NULL);
	shell_memory_set((void *)new_node, 0, sizeof(shell_list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = shell_string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * shell_print_list_string - prints only str element
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t shell_print_list_string(const shell_list_t *h)
{
	size_t i = 0;

	while (h)
	{
		shell_puts(h->str ? h->str : "(nil)");
		shell_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * shell_delete_node_at_index - deletes nodes
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 success, 0 failure
 */
int shell_delete_node_at_index(shell_list_t **head, unsigned int index)
{
	shell_list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * shell_free_list - frees all nodes
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void shell_free_list(shell_list_t **head_ptr)
{
	shell_list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
