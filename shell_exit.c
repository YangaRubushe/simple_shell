#include "shell.h"

/**
 * *_strncpy - copies a string
 * @des: the destination string to be copied to
 * @src: the sourtce string
 * @amount: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *des, char *src, int amount)
{
        int a, b;
        char *z = des;

        a = 0;
        while (src[a] != '\0' && a < amount - 1)
        {
                des[a] = src[a];
                a++;
        }
        if (a < amount)
        {
                b = a;
                while (b < amount)
                {
                        des[b] = '\0';
                        b++;
                }
        }
        return (z);
}

/**
 * *_strncat - concatenates two string
 * @firstr: the first string
 * @src: the second string
 * @amount: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *firstr, char *src, int amount)
{
        int a, b;
        char *z = firstr;

        a = 0;
        b = 0;
        while (firstr[a] != '\0')
        {
                a++;
        }
        while (src[b] != '\0' && b < amount)
        {
                firstr[a] = src[b];
                a++;
                b++;
        }
        if (b < amount)
        {
                firstr[a] = '\0';
        }
        return (z);
}

/**
 * *_strchr - locates a character in a string
 * @str: the string to be parsed
 * @cha: the charatera to look for
 * Return: (str) a pointer to the memory area str
 */
char *_strchr(char *str, char cha)
{
        do {
                if (*str == cha)
                {
                        return (str);
                }
        } while (*str++ != '\0');

        return (NULL);
}