#include "libft.h"

/**
** Output of character and strings
** @param str String to display
*/
void ft_putstr(char *str)
{
    unsigned long long len = 0;
    ssize_t offset = 0;
    ssize_t len_write = 0;

    while (*(str + len) != '\0')
    {
        len++;
    }
    while (len != 0)
    {
        len_write = write(STDOUT_FILENO, str + offset, len);
        offset += len_write;
        len -= len_write;
    }
}
