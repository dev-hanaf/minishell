/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:55 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 16:08:33 by ahanaf           ###   ########.fr       */
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

void	cd_change_env(t_env **env, char *save);

int change_direnv(t_env **env)
{
    char *save;
    if (get_env(env , "PWD"))
        save = cd_ft_strdup(get_env(env , "PWD"));
    else
        save = getcwd(NULL, 0);
    cd_change_env(env, save);
    free(save);
    return (0);
}

int	_cd(char **path, t_env **env)
{
    char *cwd;
    if (ft_strlen_2d_array(path) > 1)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    if (path[0])
    {
        if (path[0][0] == '\0')
        {
            cwd = getcwd(NULL, 0);
            if (!cwd)
            {
                ft_putstr_fd("minishell: cd: ..: No such file or directory\n", 2);
                return (1);
            }
            free(cwd);
            return (change_direnv(env));
        }
        if (!chdir(path[0]))
            return(change_direnv(env));
        cwd = getcwd(NULL, 0);
        if (!cwd)
        {
            ft_putstr_fd("minishell: cd: ..: No such file or directory\n", 2);
            return (1);
        }
        perror(path[0]);
        return (1);
    }
    else
    {
        if (!get_env(env, "HOME"))
        {
            ft_putstr_fd("bash: cd: HOME not set\n", 1);
            return (1);
        }
        if (!chdir(get_env(env, "HOME")))
            return(change_direnv(env));
        perror(path[0]);
        return (1);
    }
    return (0);
}