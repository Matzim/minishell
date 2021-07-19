#include "libft.h"

/**
** Concatenate two strings
*/
char *ft_strjoin(char const *s1, char const *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    size_t index = 0;

    if (str == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    while (index < len1)
    {
        str[index] = s1[index];
        index++;
    }
    index = 0;
    while (index < len2)
    {
        str[index + len1] = s2[index];
        index++;
    }
    str[index + len1] = '\0';
    return str;
}
