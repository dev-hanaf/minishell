/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:55 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 11:05:27 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_save(t_env **env)
{
	char	*save;
	char	*temp;

	save = NULL;
	if (get_env(env, "PWD"))
		save = ft_strdup(get_env(env, "PWD"));
	else
	{
		save = getcwd(NULL, 0);
		temp = save;
		save = ft_strdup(temp);
		free(temp);
	}
	get_ms()->save_pwd = ft_strdup_env(save);
	return (save);
}

int	change_direnv(t_env **env, char *save)
{
	cd_change_env(env, save);
	return (0);
}

int	go_to_path(char *save, t_env **env, char **path, char *cwd)
{
	save = get_save(env);
	if (path[0][0] == '\0')
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_putstr_fd("minishell: cd:", 2);
			ft_putstr_fd(path[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		free(cwd);
		return (change_direnv(env, save));
	}
	if (!chdir(path[0]))
		return (change_direnv(env, save));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd :", 2);
		ft_putstr_fd(path[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (perror(path[0]), free(cwd), 1);
}

int	go_to_home(char *save, t_env **env, char **path)
{
	save = get_save(env);
	if (!get_env(env, "HOME"))
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	if (!chdir(get_env(env, "HOME")))
		return (change_direnv(env, save));
	return (perror(path[0]), 1);
}

int	_cd(char **path, t_env **env)
{
	char	*save;
	char	*cwd;

	cwd = NULL;
	save = NULL;
	if (ft_strlen_2d_array(path) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (path[0])
		return (go_to_path(save, env, path, cwd));
	else
		return (go_to_home(save, env, path));
	return (0);
}
