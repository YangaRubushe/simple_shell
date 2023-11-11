#include "shell.h"

/**
 * shell_string_copy - copies
 * @dest : destination
 * @src: source
 *
 * Return: pointer
 */
char *shell_string_copy(char *dest, char *src)
{
        int i = 0;

        if (dest == src || src == 0)
                return (dest);
        while (src[i])
        {
                dest[i] = src[i];
                i++;
        }
        dest[i] = 0;
        return (dest);
}

/**
 * shell_string_duplicate - duplicates a string
 * @str: string
 *
 * Return: pointer to the duplicated string
 */
char *shell_string_duplicate(const char *str)
{
        int length = 0;
        char *ret;

        if (str == NULL)
                return (NULL);
        while (*str++)
                length++;
        ret =  malloc(sizeof(char) * (length + 1));
        if (!ret)
                return (NULL);
        for (length++; length--;)
                ret[length] = *--str;
        return (ret);
}

/**
 * shell_puts - prints an input
 * @str: string
 *
 * Return: Nothing
 */
void shell_puts(char *str)
{
        int i = 0;

        if (!str)
                return;
        while (str[i] != '\0')
        {
                shell_putchar(str[i]);
                i++;
        }
}

/**
 * shell_putchar - writes
 * @c: charater
 *
 * Return: 1 success
 * -1 error
 */
int shell_putchar(char c)
{
        static int i;
        static char buf[WRITE_BUFFER_SIZE];

        if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
        {
                write(1, buf, i);
                i = 0;
        }
        if (c != BUFFER_FLUSH)
                buf[i++] = c;
        return (1);
}