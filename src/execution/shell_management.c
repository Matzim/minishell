#include "shell_management.h"

#include <stdio.h>

#include "../libft/libft.h"

/**
** This function start the shell with the given environment
** @param environ Array of character pointers to the environment strings
*/
int start_shell(char **environ)
{
    int status = 0;
    int stop = 1;
    struct vector *vect = vector_init(VECTOR_SIZE);
    struct s_history *hist = init_history(MAX_HISTORY);

    while (stop)
    {
        char *input = get_user_line(vect, hist, environ);
        char **argv = ft_split_whitespace(input);

        write_str("\n", 1);
        if (argv != NULL && *argv != NULL)
        {
            // Launch a process
            status = execute_line(argv, environ, &stop);
            vector_clear(vect);
        }
        free_tab(argv);
    }
    vector_free(vect);
    free_history(hist);
    return status;
}

/**
** Setup termios structure
** @param origine Saved termios struct
** @param environ Array of character pointers to the environment strings
*/
int setup_shell(struct termios origin, char **environ)
{
    struct termios raw = origin;

    raw.c_iflag &= ~(BRKINT | IXON | ICRNL | ISTRIP | INPCK);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    {
        ft_putstr("setup_shell: tcsetattr\n");
        return 1;
    }
    int res = start_shell(environ);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin) == -1)
    {
        ft_putstr("setup_shell: tcsetattr\n");
        return 1;
    }
    return res;
}
