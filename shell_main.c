#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 - success otherwise 1 - error
 */
int main(int ac, char **av)
{
        shell_info_t info[] = { SHELL_INFO_INIT };
        int fd = 2;

        asm ("mov %1, %0\n\t"
                "add $3,%0"
                : "=r" (fd)
                : "r" (fd));

        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                shell_error_puts(av[0]);
                                shell_error_puts(": 0: Can't open ");
                                shell_error_puts(av[1]);
                                shell_error_putchar('\n');
                                shell_error_putchar(BUFFER_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                info->read_fd = fd;
        }
        shell_populate_environment_list(info);
        shell_read_history(info);
        hsh(info, av);
        return (EXIT_SUCCESS);
}
