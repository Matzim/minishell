#include <curses.h>
#include <term.h>

#include "execution/get_environ.h"
#include "execution/shell_management.h"
#include "libft/libft.h"

/**
** Main function of the shell
**
** @param argc Number of strings pointed to by argv
** @param argv List of arguments
** @param env Array of character pointers to the environment strings
** @return Return code
*/
int main(int argc, char *argv[], char *env[])
{
    // Get the array of character pointers to the environment strings
    int res = 0;
    struct termios origin;

    if (argc == 1)
    {
        if (setupterm(0, STDOUT_FILENO, 0) == ERR)
        {
            ft_putstr("main: setupterm returns an error !\n");
            exit(1);
        }
        if (tcgetattr(STDIN_FILENO, &origin) == -1)
        {
            ft_putstr("main: tcgetattr return an error !\n");
            exit(1);
        }
        res = setup_shell(origin, env);
        // Free routines of terminfo
        reset_shell_mode();
        del_curterm(cur_term);
    }
    return res;
}
