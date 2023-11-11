#include "shell.h"

/**
 * shell_string_length - return the length
 * @s: the string
 *
 * Return: length of string
 */
int shell_string_length(char *s)
{
        int i = 0;

        if (!s)
                return (0);

        while (*s++)
                i++;
        return (i);
}

/**
 * shell_string_compare - performs lexicogarphic
 * @s1: the 1st str
 * @s2: the 2rd str
 *
 * Return: - if s1 < s2, otherwise + and 0 if  s1 == s2
 */
int shell_string_compare(char *s1, char *s2)
{
        while (*s1 && *s2)
        {
                if (*s1 != *s2)
                        return (*s1 - *s2);
                s1++;
                s2++;
        }
        if (*s1 == *s2)
                return (0);
        else
                return (*s1 < *s2 ? -1 : 1);
}

/**
 * shell_starts_with - checks id needle stats
 * @haystack: string to search
 * @needle: the substring
 *
 * Return: address of next char
 */
char *shell_starts_with(const char *haystack, const char *needle)
{
        while (*needle)
                if (*needle++ != *haystack++)
                        return (NULL);
        return ((char *)haystack);
}

/**
 * shell_string_concat - concatenates 2 string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *shell_string_concat(char *dest, char *src)
{
        char *ret = dest;

        while (*dest)
                dest++;
        while (*src)
                *dest++ = *src++;
        *dest = *src;
        return (ret);
}