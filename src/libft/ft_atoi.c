#include "libft.h"

/**
** Convert a string to an integer
** @param str String to convert
** @return Integer
*/
int ft_atoi(char *str)
{
    int result = 0;
    int sign = 1;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
        {
            return result * sign;
        }
        else
        {
            result *= 10;
            result += *str - '0';
        }
        str++;
    }
    return result * sign;
}
