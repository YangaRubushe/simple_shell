#include "shell.h"

/**
 * _erratoi - converts string to an int
 * @str: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int _erratoi(char *str)
{
        int j = 0;
        unsigned long int check = 0;

        if (*str == '+')
        {
                str++;
        }
        for (j = 0; str[j] != '\0'; j++)
        {
                if (str[j] >= '0' && str[j] <= '9')
                {
                        check *= 10;
                        check += (str[j] - '0');
                        if (check > INT_MAX)
                        {
                                return (-1);
                        }
                }
                else
                        return (-1);
        }
        return (check);
}

/**
 * print_error - prints an error  message
 * @info: the parameter & return info struct
 * @st_err : string containing specified error type
 *
 *  Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
void print_error(info_t *info, char *st_err)
{
        _eputs(info->fname);
        _eputs(": ");
        print_d(info->line_count, STDERR_FILENO);
        _eputs(": ");
        _eputs(info->argv[0]);
        _eputs(": ");
        _eputs(st_err);
}

/**
 * print_d - function prints a decimal number (base 10)
 * @input: the input
 * @file_d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int file_d)
{
        int (*__putchar)(char) = _putchar;
        int j, count = 0;
        unsigned int num, current;

        if (file_d == STDERR_FILENO)
        {
                __putchar = _eputchar;
        }
        if (input < 0)
        {
                num = -input;
                __putchar('-');
                count++;
        }
        else
                num = input;
        current = num;

        for (j = 1000000000; j > 1; j /= 10)
        {
                if (num / j)
                {
                        __putchar('0' + current / j);
                        count++;
                }
                current %= j;
        }
        __putchar('0' + current);
        count++;

        return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @number: the number
 * @base: the base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int number, int base, int flags)
{
        static char *array;
        static char buffer[50];
        char sign = 0;
        char *ptr;
        unsigned long num = number;

        if (!(flags & CONVERT_UNSIGNED) && number < 0)
        {
                num = -number;
                sign = '=';

        }
        array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        ptr = &buffer[49];
        *ptr = '\0';

        do {
                *--ptr = array[num % base];
                num /= base;
        } while (num != 0);

        if (sign)
        {
                *--ptr = sign;
        }
        return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @mod: address of the string to modify
 *
 * Return: Always 0
 */
void remove_comments(char *mod)
{
        int j;

        for (j = 0; mod[j] != '\0'; j++)
        {
                if (mod[j] == '#' && (!j || mod[j - 1] == ' '))
                {
                        mod[j] = '\0';
                        break;
                }
        }
}