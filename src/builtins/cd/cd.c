/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:55 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/14 00:52:12 by ahanaf           ###   ########.fr       */
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

int	_cd(char **paths, t_env **env)
{
    char *new_path;
	char *path = paths[0];
    char *cwd;
	if(ft_strlen_2d_array(paths) > 1)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
    if (path == NULL)
    {
        change_env(env, "OLDPWD", get_env(env, "PWD"));
        chdir(getenv("HOME"));
        cwd = getcwd(NULL, 0);
        change_env(env, "PWD", cwd);
        free(cwd); 
    }
    else if (path[0] == '~')
    {
        if (ft_strlen(path) > 1)
        {
            new_path = ft_strjoin(getenv("HOME"), &path[1]);
            if (-1 == chdir(new_path))
            {
                perror(new_path);
                return (-1);
            }
            change_env(env, "OLDPWD", get_env(env, "PWD"));
            cwd = getcwd(NULL, 0);
            change_env(env, "PWD", cwd);
            free(cwd);
        }
        else
        {
            change_env(env, "OLDPWD", get_env(env, "PWD"));
            chdir(getenv("HOME"));
            cwd = getcwd(NULL, 0);
            change_env(env, "PWD", cwd);
            free(cwd);
        }
    }
    else if ( ft_strncmp(path,"..", 2) == 0 && ft_strlen(path) == 2)
    {
        change_env(env, "OLDPWD", get_env(env, "PWD"));
        chdir("../");
        cwd = getcwd(NULL, 0);
        change_env(env, "PWD", cwd);
        free(cwd);
    }
    else if ( ft_strncmp(path,".", 1) == 0 && ft_strlen(path) == 1)
    {
        change_env(env, "OLDPWD", get_env(env, "PWD"));
        chdir("./");
        cwd = getcwd(NULL, 0);
        change_env(env, "PWD", cwd);
        free(cwd);
    }
    else if (ft_strncmp(path,"-", 1) == 0 && ft_strlen(path) == 1)
    {
        char *temp = get_env(env, "OLDPWD");
        change_env(env, "OLDPWD", get_env(env, "PWD"));
        chdir(temp);
        cwd = getcwd(NULL, 0);
        change_env(env, "PWD", cwd);
        free(cwd);
    }
    else
    {
        change_env(env, "OLDPWD", get_env(env, "PWD"));
        if (chdir(path) == -1)
        {
            perror("");
            return (-1);
        }
        cwd = getcwd(NULL, 0);
        change_env(env, "PWD", cwd);
        free(cwd);
    }
    return (0);
}

/*
void _cd(char *path)
	{
		path[0] = '~'
		char *new_path = strcat(getenv(HOME), &path[i + 1]);
		if (NULL)
			getenv(HOME);
		else if (patrh == "..")
		else if (patrh == ".")
		else if (patrh == "path")
		{
			acces(path, X_OK || F_OK) == 0;
			{
				chdir(path);
			}
				
		}
		else if(path == '_')
		{
			chdir(OLD_PWD);
		}
	}
*/
