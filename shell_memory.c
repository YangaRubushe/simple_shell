#include "shell.h"

/**
 * shell_buffer_free - It frees a pointer
 * @ptr: address of the pointer to free
 *
 * Return: 1 - freed, othewise 0
 */
int shell_buffer_free(void **ptr)
{
        if (ptr && *ptr)
        {
                free(*ptr);
                *ptr = NULL;
                return (1);
        }
        return (0);
}