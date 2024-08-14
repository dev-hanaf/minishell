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

int	_cd(char *path, t_env **env)
{
    char *new_path;
    char *cwd;
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