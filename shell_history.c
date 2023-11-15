#include "shell.h"

/**
 * shell_get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *shell_get_history_file(shell_info_t *info)
{
	char *buf, *dir;

	dir = shell_get_environment(info, "HOME=");
	if (!dir)
		return (NULL);
	buf =  malloc(sizeof(char) *
			(shell_string_length(dir) + shell_string_length(SHELL_HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	shell_string_copy(buf, dir);
	shell_string_concat(buf, "/");
	shell_string_concat(buf, SHELL_HISTORY_FILE);
	return (buf);
}

/**
 * shell_write_history - creates a file to an existing file
 * @info: the parameter struct
 *
 * Return: 1 success, else -1
 */
int shell_write_history(shell_info_t *info)
{
	ssize_t fd;
	char *filename = shell_get_history_file(info);
	shell_list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		shell_puts_fd(node->str, fd);
		shell_put_fd('\n', fd);
	}
	shell_put_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * shell_read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int shell_read_history(shell_info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = shell_get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			shell_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		shell_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->history_count = linecount;
	while (info->history_count-- >= SHELL_HISTORY_MAX)
		shell_delete_node_at_index(&(info->history), 0);
	shell_renumber_history(info);
	return (info->history_count);
}

/**
 * shell_build_history_list - adds entry to a history linked list
 * @info: Structure containing potentail arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int shell_build_history_list(shell_info_t *info, char *buf, int linecount)
{
	shell_list_t *node = NULL;

	if (info->history)
		node = info->history;
	shell_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * shell_renumber_history - remember the history linked list after changes
 * @info: Structure containing potentail arguments. Used to maintain
 *
 * Return: the new histcount
 */
int shell_renumber_history(shell_info_t *info)
{
	shell_list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
