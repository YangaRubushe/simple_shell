#include "shell.h"

/**
 * shell_interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, otherwise 0
 */
int shell_interactive(shell_info_t *info)
{
        return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * shell_is_delimiter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int shell_is_delimiter(char c, char *delim)
{
        while (*delim)
                if (*delim++ == c)
                        return (1);
        return (0);
}

/**
 * shell_is_alpha - chaeck for alphabetic character
 * @c: the character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int shell_is_alpha(int c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

/**
 * shell_ascii_to_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int shell_ascii_to_integer(char *s)
{
        int i, sign = 1, flag = 0, output;
        unsigned int result = 0;

        for (i = 0; s[i] != '\0' && flag != 2; i++)
        {
                if (s[i] == '-')
                        sign *= -1;

                if (s[i] >= '0' && s[i] <= '9')
                {
                        flag = 1;
                        result *= 10;
                        result += (s[i] - '0');
                }
                else if (flag == 1)
                        flag = 2;
        }

        if  (sign == -1)
                output = -result;
        else
                output = result;

        return (output);
}