#include "shell.h"

/**
 * shell_is_command - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, otherwise 0
 */
int shell_is_command(shell_info_t *info, char *path)
{
        struct stat st;

        (void)info;
        if (!path || stat(path, &st))
                return (0);

        if (st.st_mode & S_IFREG)
        {
                return (1);
        }
        return (0);
}

/**
 * shell_duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *shell_duplicate_chars(char *pathstr, int start, int stop)
{
        static char buf[1024];
        int i = 0, k = 0;

        for (k = 0, i = start; i < stop; i++)
                if (pathstr[i] != ':')
                        buf[k++] = pathstr[i];
        buf[k] = 0;
        return (buf);
}

/**
 * shell_find_path - finds this cmd in path string
 * @info: the info strct
 * @pathstr: the path string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *shell_find_path(shell_info_t *info, char *pathstr, char *cmd)
{
        int i = 0, curr_pos = 0;
        char *path;

        if (!pathstr)
                return (NULL);
        if ((shell_string_length(cmd) > 2) && shell_starts_with(cmd, "./"))
        {
                if (shell_is_command(info, cmd))
                        return (cmd);
        }
        while (1)
        {
                if (!pathstr[i] || pathstr[i] == ':')
                {

                        path = shell_duplicate_chars(pathstr, curr_pos, i);
                        if (!*path)

                        shell_string_concat_n(path, cmd);
                        else
                        {
                                shell_string_concat_n(path, "/");
                                shell_string_concat_n(path, cmd);
                        }
                        if (shell_is_command(info, path))
                                return (path);
                        if (!pathstr[i])
                                break;
                        curr_pos = i;
                }
                i++;
        }
        return (NULL);
}