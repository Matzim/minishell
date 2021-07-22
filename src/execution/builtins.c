#include "builtins.h"

#include <stdlib.h>

/**
** Expand the path
** @param argv Command
** @param envp Array of character pointers to the environment strings
** @return Return expanded path
*/
char *expand_path(char **argv, char **envp)
{
    if (*argv[1] == '~')
    {
        char *ptr = argv[1];
        char *home_path = get_value(envp, "HOME");
        if (ptr == NULL || home_path == NULL)
        {
            free(home_path);
            return NULL;
        }
        ptr = ft_strjoin(home_path, ptr + 1);
        if (ptr == NULL)
        {
            free(home_path);
            return NULL;
        }
        free(home_path);
        return ptr;
    }
    return ft_strdup(argv[1]);
}

/**
** Change the working directory
** @param argv Command
** @param envp Array of character pointers to the environment strings
*/
void move_to_dir(char **argv, char **envp)
{
    char *path = NULL;
    char *destination = expand_path(argv, envp);

    if (access(destination, F_OK | X_OK))
    {
        ft_putstr("minishell: cd: ");
        ft_putstr(argv[1]);
        ft_putstr(": No such file or directory\n");
    }
    else
    {
        char buf[4096] = { 0 };
        path = getcwd(buf, 4096);
        if (path == 0)
        {
            ft_putstr("mini_cd: getcwd: return an error !\n");
            free(destination);
            return;
        }
        if (chdir(destination) == -1)
        {
            ft_putstr("cd: chdir: return an error !\n");
        }
        else
        {
            setenv("OLDPWD", path, 1);
            path = getcwd(buf, 4096);
            if (path == NULL)
            {
                ft_putstr("mini_cd: getcwd: return an error !\n");
                free(destination);
                return;
            }
            setenv("PWD", path, 1);
        }
    }
    free(destination);
}

/**
** Retrieve the last directory (cd -)
** @param envp Array of character pointers to the environment strings
*/
void return_to_old_dir(char **envp)
{
    char *next_path = get_value(envp, "OLDPWD");
    char *old_dir = get_value(envp, "PWD");

    // We modify the env value of OLDPWD with the value of PWD
    setenv("OLDPWD", old_dir, 1);
    free(old_dir);
    // We move in the next_path, if is valid
    if (!access(next_path, F_OK | X_OK) && chdir(next_path) == -1)
    {
        ft_putstr("cd: chdir: return an error !\n");
    }
    else
    {
        write_str(next_path, ft_strlen(next_path));
        write_str("\n", 1);
        // If the chdir success, we modify variable PWD with $OLD_PWD
        setenv("PWD", next_path, 1);
    }
    free(next_path);
}

/**
** Change the working directory
** @param argv Command
** @param envp Array of character pointers to the environment strings
*/
void mini_cd(char **argv, char **envp)
{
    // cd without args: cd $HOME
    if (argv[1] == NULL)
    {
        char *path = NULL;
        // We modify the env value of OLDPWD with the value of PWD
        path = get_value(envp, "PWD");
        setenv("OLDPWD", path, 1);
        free(path);
        path = get_value(envp, "HOME");
        if (!access(path, F_OK | X_OK) && chdir(path) == -1)
        {
            ft_putstr("cd: chdir: return an error !\n");
        }
        else
        {
            // If the chdir success, we modify variable PWD with $HOME
            setenv("PWD", path, 1);
        }
        free(path);
    }
    // cd can only have one or less argument
    else if (argv[2] == NULL)
    {
        if (ft_strcmp(argv[1], "-"))
        {
            move_to_dir(argv, envp);
        }
        else
        {
            return_to_old_dir(envp);
        }
    }
    // Too many args for cd command
    else
    {
        ft_putstr("minishell: cd: too many arguments !\nUsage: cd <path>\n");
    }
}
