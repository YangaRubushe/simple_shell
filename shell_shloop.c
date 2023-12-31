#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(shell_info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		shell_clear_info(info);
		if (shell_interactive(info))
			shell_puts("$ ");
		shell_error_putchar(BUFFER_FLUSH);
		r = shell_get_input(info);
		if (r != -1)
		{

			shell_set_info(info, av);
			builtin_ret = shell_find_builtin(info);

			if (builtin_ret == -1)
				shell_find_command(info);
		}
		else if (shell_interactive(info))
			shell_putchar('\n');
		shell_free_info(info, 0);
	}
	shell_write_history(info);
	shell_free_info(info, 1);
	if (!shell_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * shell_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 not found, 0 successful, 1 not successful and -2 exits()
 */
int shell_find_builtin(shell_info_t *info)
{
	int i, built_in_ret = -1;
	shell_builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", shell_environment},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_set_environment},
		{"unsetenv", shell_unset_environment},
		{"cd", shell_change_directory},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (shell_string_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);

			break;
		}
	return (built_in_ret);
}

/**
 * shell_find_command - find a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void shell_find_command(shell_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!shell_is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = shell_find_path(info, shell_get_environment(info, "PATH="),
			info->argv[0]);
	if (path)
	{
		info->path = path;
		shell_fork_command(info);
	}
	else
	{
		if ((shell_interactive(info) || shell_get_environment(info, "PATH=")
					|| info->argv[0][0] == '/') && shell_is_command(info, info->argv[0]))
			shell_fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			shell_print_error(info, "not found\n");
		}
	}
}

/**
 * shell_fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void shell_fork_command(shell_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, shell_get_shell_environment(info)) == -1)
		{
			shell_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				shell_print_error(info, "Permission denied\n");
		}
	}
}
