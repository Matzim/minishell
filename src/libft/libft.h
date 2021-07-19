#ifndef _LIBFT_H_
#define _LIBFT_H_

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 128

void ft_putstr(char *str);
size_t ft_strlen(const char *str);
int ft_strcmp(char *s1, char *s2);
char *ft_strdup(char *src);
int ft_atoi(char *str);
char **ft_split_whitespace(char *str);
char *ft_strjoin(char const *s1, char const *s2);

#endif
