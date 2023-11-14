#include "shell.h"

/**
 * shell_exit - exits the shell
 * @info: Structure containg potential arguemnts. Used to maintain
 *        constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int shell_exit(shell_info_t *info)
{
        int exit;

        if (info->argv[1])
        {
                exit = shell_error_ascii_to_integer(info->argv[1]);
                if (exit == -1)
                {
                        info->status = 2;
                        shell_print_error(info, "Illegal number: ");
			shell_error_puts(info->argv[1]);
                        shell_error_putchar('\n');
                        return (1);
                }
                info->err_num = shell_error_ascii_to_integer(info->argv[1]);
                return (-2);
        }
        info->err_num = -1;
        return (-2);
}

/**
 * shell_change_directory - changes the current directory of thr process
 * @info: Structure comtaining potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int shell_change_directory(shell_info_t *info)
{
        char *c, *dir, buffer[1024];
        int chdir_ret;

        c = getcwd(buffer, 1024);
        if (!c)
                shell_puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                dir = shell_get_environment(info, "HOME=");
                if (!dir)
                        chdir_ret = /* TODO */
                                chdir((dir = shell_get_environment(info, "PWD=")) ? dir : "/");
                else
                        chdir_ret = chdir(dir);
        }
        else if (shell_string_compare(info->argv[1], "-") == 0)
        {
                if (!shell_get_environment(info, "OLDPWD="))
                {
                        shell_puts(c);
                        shell_putchar('\n');
                        return (1);
                }
                shell_puts(shell_get_environment(info, "OLDPWD=")), shell_putchar('\n');
                chdir_ret = /* TODO */
                        chdir((dir = shell_get_environment(info, "OLDPWD=")) ? dir : "/");
        }
        else
                chdir_ret = chdir(info->argv[1]);
        if (chdir_ret == -1)
        {
                shell_print_error(info, "can't cd to ");
                shell_error_puts(info->argv[1]), shell_error_putchar('\n');
        }
        else
        {
                shell_set_environment_variable(info, "OLDPWD", shell_get_environment(info, "PWD="));
                shell_set_environment_variable(info, "PWD", getcwd(buffer, 1024));
        }
        return (0);
}

/**
 * shell_help - changes the current directory
 * @info: Structure containin potential arguments.
 * Return: Always 0
 *
 */
int shell_help(shell_info_t *info)
{
        char **arg_array;

        arg_array = info->argv;
        shell_puts("help call works. Fuction not yet implemented \n");
        if (0)
                shell_puts(*arg_array);
        return (0);
}
