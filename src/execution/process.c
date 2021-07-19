#include "process.h"

/**
** Free the array
** @param array Array of string
*/
void free_tab(char **array)
{
    if (array == NULL)
    {
        return;
    }
    for (size_t index = 0; array[index] != NULL; index++)
    {
        free(array[index]);
    }
    free(array);
}

/**
** Count character separator in the string
** @param str String
** @param sep Character separator
** @return Return count
*/
unsigned int count_separator(char *str, char sep)
{
    unsigned int nb_words = 0;
    char status = 1;

    while (*str)
    {
        if (*str == sep)
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
        str++;
    }
    return nb_words;
}

/**
** Split the string on separator
** @param str String
** @param sep Separator character
*/
char **split(char *str, char sep)
{
    // Count words
    unsigned int nb_words = count_separator(str, sep);
    char **ptr_str = malloc(sizeof(char *) * (nb_words + 1));

    if (!ptr_str)
        return 0;
    nb_words = 0;
    while (*str != '\0')
    {
        unsigned int len = 0;
        char *ptr = str;
        while (*str != '\0' && *str != sep)
        {
            str++;
            len++;
        }
        if (len > 0)
        {
            char *p = malloc(sizeof(char) * (len + 1));
            if (p == NULL)
                return 0;
            unsigned int index = 0;
            // Copy the word
            while (index < len)
            {
                p[index] = ptr[index];
                index++;
            }
            p[index] = '\0';
            ptr_str[nb_words] = p;
            nb_words++;
        }
        if (*str != '\0')
        {
            str++;
        }
    }
    ptr_str[nb_words] = 0;
    return ptr_str;
}

/**
** Concatenate two strings with a given character between them
*/
char *ft_join_c(char *str1, char *str2, char join)
{
    size_t len1 = ft_strlen(str1);
    size_t len2 = ft_strlen(str2);
    char *new_str = (char *)malloc(len1 + len2 + 2);
    size_t index = 0;

    if (new_str == NULL)
    {
        write_str("Not enough memory !\n", 20);
        exit(1);
    }
    while (index < len1)
    {
        new_str[index] = str1[index];
        index++;
    }
    new_str[index] = join;
    index = 0;
    while (index < len2)
    {
        new_str[len1 + index + 1] = str2[index];
        index++;
    }
    new_str[len1 + index + 1] = '\0';
    return new_str;
}

/**
**
*/
void new_command(char *argv[], char *envp[], char *all_path[])
{
    char *path = NULL;
    int res = 1;

    for (char **tmp = all_path; *tmp != NULL; tmp++)
    {
        path = ft_join_c(*tmp, argv[0], '/');
        if (!access(path, F_OK | X_OK))
        {
            break;
        }
        free(path);
        path = 0;
    }
    free_tab(all_path);
    if (path != NULL)
    {
        res = execve(path, argv, envp);
        if (res == -1)
        {
            write_str("execve: error with this command !\n", 34);
        }
        free(path);
    }
    else
    {
        free(path);
        if (!access(argv[0], F_OK | X_OK))
        {
            res = execve(argv[0], argv, envp);
            if (res == -1)
            {
                write_str("minishell: ", 11);
                ft_putstr(argv[0]);
                write_str(": command not found\n", 21);
            }
        }
        else
        {
            write_str("minishell: ", 11);
            ft_putstr(argv[0]);
            write_str(": command not found\n", 21);
        }
    }
}

/**
** Launch a command
** @param argv Command
** @param envp Array of character pointers to the environment strings
*/
void lauch_process(char *argv[], char *envp[])
{
    pid_t w, children = fork();
    int status = 0;

    if (children == -1)
    {
        write_str("launch_process: fork() return an error !\n", 41);
        exit(2);
    }
    if (children == 0)
    {
        char *tmp = get_value(envp, "PATH");
        if (tmp == NULL)
        {
            ft_putstr("launch_process: The var PATH is not found !\n");
            exit(1);
        }
        char **ptr = split(tmp, ':');
        if (ptr == NULL)
        {
            exit(1);
        }
        free(tmp);
        new_command(argv, envp, ptr);
        exit(1);
    }
    else
    {
        w = waitpid(children, &status, 0);
        if (w == -1)
        {
            write_str("launch_process: waitpid() return an error !\n", 44);
            exit(2);
        }
    }
}

/**
** Execute the command
** @param argv Command
** @param envp Array of character pointers to the environment strings
** @param stop Return code of the exit builtin
*/
int execute_line(char *argv[], char *envp[], int *stop)
{
    int echo = 1;

    // Select the builtin
    if (ft_strcmp(argv[0], "cd") == 0)
    {
        mini_cd(argv, envp);
    }
    else if (ft_strcmp(argv[0], "echo") == 0)
    {
        while (argv[echo] != 0 && argv[echo + 1] != 0)
        {
            ft_putstr(argv[echo++]);
            write_str(" ", 1);
        }
        if (argv[echo] != 0)
        {
            ft_putstr(argv[echo++]);
            write_str("\n", 1);
        }
    }
    else if (ft_strcmp(argv[0], "env") == 0)
    {
        print_env(envp);
    }
    else if (ft_strcmp(argv[0], "exit") == 0)
    {
        if (argv[1] == 0)
        {
            *stop = 0;
            return 0;
        }
        else if (argv[2] == 0)
        {
            *stop = 0;
            return ft_atoi(argv[1]);
        }
        else
        {
            write_str("minishell: exit: too many arguments !\n", 38);
        }
    }
    else
    {
        lauch_process(argv, envp);
    }
    return 1;
}
