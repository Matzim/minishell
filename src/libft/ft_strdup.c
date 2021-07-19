#include "libft.h"

/**
** Duplicate a string
*/
char *ft_strdup(char *src)
{
    size_t len = ft_strlen(src);
    size_t index = 0;
    char *ptr = (char *)malloc(sizeof(char) * (len + 1));

    if (ptr == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }
    while (index < len)
    {
        ptr[index] = src[index];
        index++;
    }
    ptr[index] = '\0';
    return ptr;
}
