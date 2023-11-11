#include "shell.h"

/**
 * input_buf - buffers
 * @para: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *para, char **buf, size_t *len)
{
        ssize_t a = 0;
        size_t len_pa = 0;

        if (!*len) /* if nothing lest in the buffer, fill it */
        {
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                a = getline(buf, &len_pa, stdin);
#else
                a = _getline(para, buf, &len_pa);
#endif
                if (a > 0)
                {
                        if ((*buf)[a - 1] == '\n')
                        {
                                (*buf)[a - 1] = '\0';
                                a--;
                        }
                        para->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(para, *buf, para->histcount++);
                        {
                                *len = a;
                                para->cmd_buf = buf;
                        }
                }
        }
        return (a);
}

/**
 * get_input - gets a (line) - (the newline)
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
        static char *cha_buf;
        static size_t a;
        static size_t b;
        static size_t length;
        ssize_t c = 0;
        char **buff_pa = &(info->arg), *pa;

        _putchar(BUF_FLUSH);
        c = input_buf(info, &cha_buf, &length);
        if (c == -1)
                return (-1);
        if (length)
        {
                b = a;
                pa = cha_buf + a;

                check_chain(info, cha_buf, &b, a, length);
                while (b < length)
                {
                        if (is_chain(info, cha_buf, &b))
                                break;
                        b++;
                }

                a = b + 1;
                if (a >= length)
                {
                        a = length = 0;
                        info->cmd_buf_type = CMD_NORM;
                }

                *buff_pa = pa;
                return (_strlen(pa));
        }
        *buff_pa = cha_buf;
        return (c);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @s: size
 *
 * Return: a
 */
ssize_t read_buf(info_t *info, char *buff, size_t *s)
{
        ssize_t a = 0;

        if (*s)
        {
                return (0);
        }

        a = read(info->readfd, buff, READ_BUF_SIZE);
        if (a >= 0)
        {
                *s = a;
        }
        return (a);
}

/**
 * _getline - gets the next line
 * @info: parameter struct
 * @ptr: address of pointer
 * @len : size of preallocated
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *len)
{
        static char buf[READ_BUF_SIZE];
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

        r = read_buf(info, buf, &length);
        if (r == -1 || (r == 0 && length == 0))
        {
                return (-1);
        }

        c = _strchr(buf + a, '\n');
        t = c ? 1 + (unsigned int)(c - buf) : length;
        new_pa = _realloc(pa, s, s ? s + t : t + 1);
        if (!new_pa)
                return (pa ? free(pa), -1 : -1);
        if (s)
                _strncat(new_pa, buf + a, t - a);
        else
                _strncpy(new_pa, buf + a, t - a + 1);

        s += t - a;
        a = t;
        pa = new_pa;

        if (len)
                *len = s;
        *ptr = pa;
        return (s);
}

/**
 * sigintHandler - blocks copy
 * @sign_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sign_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}