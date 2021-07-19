#include <stdio.h>

#include "libft.h"

/**
** Auxiliary function of ft_split_whitespace that count the word of the str
** @param str String
*/
unsigned int count_words(char *str)
{
    unsigned int nb_words = 0;
    char status = 1;
    char *ptr = str;

    while (*ptr != '\0')
    {
        if (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\r')
        {
            status = 1;
        }
        else
        {
            if (status)
            {
                nb_words++;
                status = 0;
            }
        }
        ptr++;
    }
    return nb_words;
}

/**
** Returns a list of the words in the string, separated by blank characters.
** @param str String
** @return List of words
*/
char **ft_split_whitespace(char *str)
{
    unsigned int nb_words = count_words(str);

    char **tab = malloc(sizeof(char *) * (nb_words + 1));
    if (tab == NULL)
        return NULL;
    nb_words = 0;
    while (*str != '\0')
    {
        unsigned int len = 0;
        char *ptr = str;
        while (*str != '\0' && *str != ' ' && *str != '\n' && *str != '\t'
               && *str != '\r')
        {
            str++;
            len++;
        }
        if (len > 0)
        {
            char *p = (char *)malloc(sizeof(char) * (len + 1));
            if (p == NULL)
            {
                free(tab);
                return NULL;
            }
            unsigned int index = 0;
            while (index < len)
            {
                p[index] = ptr[index];
                index++;
            }
            p[index] = '\0';
            tab[nb_words] = p;
            nb_words++;
        }
        if (*str != '\0')
            str++;
    }
    tab[nb_words] = NULL;
    return tab;
}
