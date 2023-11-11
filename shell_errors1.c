#include "shell.h"

/**
 * _eputs - prints an input strings
 * @str: string to be printed
 *
 * Return: NULL
 */
void _eputs(char *str)
{
        int j = 0;


        if (!str)
        {
                return;
        }
        while (str[j] != '\0')
        {
                _eputchar(str[j]);
                j++;
        }
}

/**
 * _putsfd - prints input strings
 * @str: the string to be pointed
 * @fd: the filedescriptor to write
 *
 * Return: number of charaters put
 */
int _putsfd(char *str, int fd)
{
        int j = 0;

        if (!str)
        {
                return (0);
        }
        while (*str)
        {
                j += _putfd(*str++, fd);
        }
        return (j);
}

/**
 *_eputchar - write character c
 * @c: The character to print
 *
 * Return: 1 - success, otherwise 1 - error
 */
int _eputchar(char c)
{
        static int j;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
        {
                write(2, buf, j);
                j = 0;
        }
        if (c != BUF_FLUSH)
        {
                buf[j++] = c;
        }
        return (0);
}

/**
 * *_putfd - writes character c given fd
 * @c: The character to print
 * @fd: filedescriptor to write
 *
 * Return: 1 - success, otherwise -1 - error
 */
int _putfd(char c, int fd)
{
        static int j;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
        {
                write(fd, buf, j);
                j = 0;
        }
        if (c != BUF_FLUSH)
        {
                buf[j++] = c;
        }
        return (1);
}