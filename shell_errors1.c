#include "shell.h"

/**
 * shell_error_puts - prints an input strings
 * @str: string to be printed
 *
 * Return: NULL
 */
void shell_error_puts(char *str)
{
	int j = 0;

	if (!str)
	{
		return;
	}
	while (str[j] != '\0')
	{
		shell_error_putchar(str[j]);
		j++;
	}
}

/**
 * shell_puts_fd - prints input strings
 * @str: the string to be pointed
 * @fd: the filedescriptor to write
 *
 * Return: number of charaters put
 */
int shell_puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		j += shell_put_fd(*str++, fd);
	}
	return (j);
}

/**
 *shell_error_putchar - write character c
 * @c: The character to print
 *
 * Return: 1 - success, otherwise 1 - error
 */
int shell_error_putchar(char c)
{
	static int j;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
	{
		buf[j++] = c;
	}
	return (0);
}

/**
 * *shell_put_fd - writes character c given fd
 * @c: The character to print
 * @fd: filedescriptor to write
 *
 * Return: 1 - success, otherwise -1 - error
 */
int shell_put_fd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}
