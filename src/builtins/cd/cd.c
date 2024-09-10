/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:55 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/10 03:30:15 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* https://linuxize.com/post/linux-cd-command/ */
/* 
cd is not a command, it's built into your shell. This is necessary because your current working directory is controlled by the PWD environment variable named after the pwd or "print working directory" command.
The environment variables of a parent process cannot be changed by a child process. So if your shell ran /bin/cd which changed PWD it would only affect /bin/cd and anything it ran. It would not change the shell's PWD.
Some systems, like OS X and CentOS, map the cd man page to builtin which lists all the shell built ins and lets you know you should look at your shell's man page.
 */

/*perror ==> file not found && permission denied */
/* oldpwd is not set && home is not set  */

int change_direnv(t_env **env, char *save)
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (get_env(env, "PWD"))
        change_env(env, "PWD", cwd);
    if (get_env(env, "OLDPWD"))
        change_env(env, "OLDPWD", save);
    free(cwd);
    return (0);
}

int	_cd(char **path, t_env **env)
{
    char *save;
    if (ft_strlen_2d_array(path) > 1)
    {
        ft_putstr_fd("minishell: cd: too many arguments", 2);
        return (1);
    }
    if (path[0])
    {
        save = getcwd(NULL, 0);
        if (!ft_strcmp(path[0],"-"))
        {
            printf(GREEN"from - \n"NC);
            // if (!get_env(env, "OLDPWD"))
            // {
            //     ft_putstr_fd("bash: cd: OLDPWD not set\n", 1);
            //     return (1);
            // }
            // if (!chdir(get_env(env, "OLDPWD")))
            //     return(change_direnv(env, save));
            return (0);
        }
        else if (!chdir(path[0]))
            return(change_direnv(env, save));
        perror(path[0]);
        return (1);
    }
    else
    {
        save= getcwd(NULL, 0);
        if (!get_env(env, "HOME"))
        {
            ft_putstr_fd("bash: cd: HOME not set\n", 1);
            return (1);
        }
        if (!chdir(get_env(env, "HOME")))
            return(change_direnv(env, save));
        perror(path[0]);
        return (1);
    }
    free(save);
    return (0);
}