#include "get_environ.h"

#include "../libft/libft.h"

/**
** Verify, if the value and variable are valid
** @param value Value
** @param var Variable
*/
char *check_variable(char *value, char *var)
{
    unsigned long long index = 0;

    while (value[index] != '\0' && var[index] != '\0'
           && var[index] == value[index])
    {
        index++;
    }
    if (var[index] == '\0' && value[index] == '=')
    {
        return value;
    }
    return NULL;
}

/**
** Retrieve the value of the given variable
** @param env Array of character pointers to the environment strings
** @param var Variable
** @return Return value of the variable
*/
char *get_value(char *env[], char *var)
{
    char *value = 0;

    for (int i = 0; env[i] != NULL; i++)
    {
        value = check_variable(env[i], var);
        if (value != NULL)
        {
            value = value + (ft_strlen(var) + 1);
            return ft_strdup(value);
        }
    }
    return NULL;
}

/**
** Retrieve the value of the given variable
** @param env Array of character pointers to the environment strings
** @param var Variable
** @return Return value of the variable
*/
char *get_var(char *env[], char *var)
{
    char *value;

    for (int index = 0; env[index] != NULL; index++)
    {
        value = check_variable(env[index], var);
        if (value != NULL)
        {
            return ft_strdup(value);
        }
    }
    return NULL;
}

/**
** Display environ
** @parma env Array of character pointers to the environment strings
*/
void print_env(char **env)
{
    for (; *env != NULL; env++)
    {
        ft_putstr(*env);
        ft_putstr("\n");
    }
}
