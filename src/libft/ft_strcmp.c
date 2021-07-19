#include "libft.h"

/**
** Compare two strings
**
** • 0, if the s1 and s2 are equal
** • a negative value if s1 is less than s2
** • a positive value if s1 is greater than s2
*/
int ft_strcmp(char *s1, char *s2)
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (int)*s1 - (int)*s2;
}
