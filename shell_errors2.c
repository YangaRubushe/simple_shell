#include "shell.h"

/**
 * shell_error_ascii_to_integer - converts string to an int
 * @str: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int shell_error_ascii_to_integer(char *str)
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
 * shell_print_error - prints an error  message
 * @info: the parameter & return info struct
 * @st_err : string containing specified error type
 *
 *  Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
void shell_print_error(shell_info_t *info, char *st_err)
{
	shell_error_puts(info->fname);
	shell_error_puts(": ");
	shell_print_decimal(info->line_count, STDERR_FILENO);
	shell_error_puts(": ");
	shell_error_puts(info->argv[0]);
	shell_error_puts(": ");
	shell_error_puts(st_err);
}

/**
 * shell_print_decimal - function prints a decimal number (base 10)
 * @input: the input
 * @file_d: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int shell_print_decimal(int input, int file_d)
{
	int (*shell__putchar)(char) = shell_putchar;
	int j, count = 0;
	unsigned int num, current;

	if (file_d == STDERR_FILENO)
	{
		shell__putchar = shell_error_putchar;
	}
	if (input < 0)
	{
		num = -input;
		shell__putchar('-');
		count++;
	}
	else
		num = input;
	current = num;

	for (j = 1000000000; j > 1; j /= 10)
	{
		if (num / j)
		{
			shell__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	shell__putchar('0' + current);
	count++;

	return (count);
}

/**
 * shell_convert_number - converter function, a clone of itoa
 * @number: the number
 * @base: the base
 * @flags: argument flags
 *
 * Return: string
 */
char *shell_convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long num = number;

	if (!(flags & CONVERT_TO_UNSIGNED) && number < 0)
	{
		num = -number;
		sign = '=';
	}
	array = flags & CONVERT_TO_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
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
 * shell_remove_comments - function replaces first instance of '#' with '\0'
 * @mod: address of the string to modify
 *
 * Return: Always 0
 */
void shell_remove_comments(char *mod)
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
