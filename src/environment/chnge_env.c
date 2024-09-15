/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chnge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:54:18 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:28:08 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(t_env **env, char *key, char *value)
{
	t_env	*temp;
	size_t	len;

	if (!*env || !key)
		return ;
	temp = *env;
	len = ft_strlen(key);
	while (temp)
	{
		if (ft_strncmp(key, temp->key, len) == 0 && len == ft_strlen(temp->key))
		{
			temp->value = ft_strdup_env(value);
			return ;
		}
		temp = temp->next;
	}
}

void	check_existance(t_env **temp, char *cwd, t_env **env, char *save)
{
	if (!ft_strcmp((*temp)->key, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		(*temp)->value = ft_strdup_env(cwd);
		free(cwd);
	}
	if (!ft_strcmp((*temp)->key, "OLDPWD"))
	{
		if (!get_env(env, "PWD"))
		{
			(*temp)->key = ft_strdup_env("OLDPWD");
			(*temp)->value = NULL;
			get_ms()->oldpwd_islocal = 0;
		}
		else
			(*temp)->value = ft_strdup_env(save);
	}
}

void	cd_change_env(t_env **env, char *save)
{
	t_env	*temp;
	char	*cwd;

	cwd = NULL;
	get_ms()->pwd_pwd = NULL;
	if (!*env)
		return ;
	temp = *env;
	cwd = getcwd(NULL, 0);
	get_ms()->pwd_pwd = ft_strdup_env(cwd);
	free(cwd);
	cwd = NULL;
	get_ms()->oldpwd_islocal = 1;
	while (temp)
	{
		check_existance(&temp, cwd, env, save);
		temp = temp->next;
	}
	get_ms()->pwd_islocal = 1;
}
