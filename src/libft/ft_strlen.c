#include "libft.h"

/**
** Return the length of the str
*/
size_t ft_strlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}
