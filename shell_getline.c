#include "shell.h"

/**
 * shell_input_buf - buffers
 * @para: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t shell_input_buf(shell_info_t *para, char **buf, size_t *length)
{
        ssize_t a = 0;
        size_t len_pa = 0;

        if (!*length) /* if nothing lest in the buffer, fill it */
        {
                free(*buf);
                *buf = NULL;
                signal(SIGINT, shell_signal_interrupt_handler);
#if USE_GETLINE
                a = shell_get_line(buf, &len_pa, stdin);
#else
                a = shell_get_line(para, buf, &len_pa);
#endif
                if (a > 0)
                {
                        if ((*buf)[a - 1] == '\n')
                        {
                                (*buf)[a - 1] = '\0';
                                a--;
                        }
                        para->linecount_flag = 1;
                        shell_remove_comments(*buf);
                        shell_build_history_list(para, *buf, para->history_count++);
                        {
                                *length = a;
                                para->cmd_buffer = buf;
                        }
                }
        }
        return (a);
}

/**
 * shell_get_input - gets a (line) - (the newline)
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t shell_get_input(shell_info_t *info)
{
        static char *cha_buf;
        static size_t a;
        static size_t b;
        static size_t length;
        ssize_t c = 0;
        char **buff_pa = &(info->arg), *pa;

        shell_putchar(BUFFER_FLUSH);
        c = shell_get_input(info, &cha_buf, &length);
        if (c == -1)
                return (-1);
        if (length)
        {
                b = a;
                pa = cha_buf + a;

                shell_check_command_chain(info, cha_buf, &b, a, length);
                while (b < length)
                {
                        if (shell_is_command_chain(info, cha_buf, &b))
                                break;
                        b++;
                }

                a = b + 1;
                if (a >= length)
                {
                        a = length = 0;
                        info->cmd_buffer_type = COMMAND_NORMAL;
                }

                *buff_pa = pa;
                return (shell_string_length(pa));
        }
        *buff_pa = cha_buf;
        return (c);
}

/**
 * shell_read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @s: size
 *
 * Return: a
 */
ssize_t shell_read_buf(shell_info_t *info, char *buff, size_t *s)
{
        ssize_t a = 0;

        if (*s)
        {
                return (0);
        }

        a = read(info->read_fd, buff, READ_BUFFER_SIZE);
        if (a >= 0)
        {
                *s = a;
        }
        return (a);
}

/**
 * shell_get_line - gets the next line
 * @info: parameter struct
 * @ptr: address of pointer
 * @len : size of preallocated
 *
 * Return: s
 */
int shell_get_line(shell_info_t *info, char **ptr, size_t *len)
{
        static char buf[READ_BUFFER_SIZE];
        static size_t a, length;
        size_t t;
        ssize_t r = 0, s = 0;
        char *pa = NULL, *new_pa = NULL, *c;

        pa = *ptr;
        if (pa && len)
        {
                s = *len;
        }
        if (a == length)
        {
                a = length = 0;
        }

        r = shell_read_buf(info, buf, &length);
        if (r == -1 || (r == 0 && length == 0))
        {
                return (-1);
        }

        c = shell_string_find_char(buf + a, '\n');
        t = c ? 1 + (unsigned int)(c - buf) : length;
        new_pa = shell_reallocate(pa, s, s ? s + t : t + 1);
        if (!new_pa)
                return (pa ? free(pa), -1 : -1);
        if (s)
                shell_string_concat_n(new_pa, buf + a, t - a);
        else
                shell_string_copy_n(new_pa, buf + a, t - a + 1);

        s += t - a;
        a = t;
        pa = new_pa;

        if (len)
                *len = s;
        *ptr = pa;
        return (s);
}

/**
 * shell_siginal_interrupt_handler - blocks copy
 * @sign_num: the signal number
 *
 * Return: void
 */
void shell_siginal_interrupt_handler(__attribute__((unused))int sign_num)
{
        shell_puts("\n");
        shell_puts("$ ");
        shell_putchar(BUFFER_FLUSH);
}
