/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:41:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:08:08 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_pwd_old_pwd(t_env *env, char *key)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_pwd_oldpwd(t_env *env, char *key)
{
	char	*cwd;

	cwd = NULL;
	if (!ft_strcmp(key, "PWD") || !ft_strcmp(key, "OLDPWD"))
		cwd = key_pwd_old_pwd(env, key);
	if (cwd)
		return (cwd);
	if (!ft_strcmp(key, "PWD") && get_ms()->pwd_islocal == 1)
	{
		cwd = getcwd(NULL, 0);
		get_ms()->pwd = ft_strdup_env(cwd);
		free(cwd);
		return (get_ms()->pwd);
	}
	if (!ft_strcmp(key, "OLDPWD") && get_ms()->oldpwd_islocal == 1)
	{
		if (!get_ms()->pwd)
			get_ms()->oldpwd = get_ms()->save_pwd;
		else
			get_ms()->oldpwd = get_ms()->pwd;
		return (get_ms()->oldpwd);
	}
	return (NULL);
}

char	*get_env(t_env **env, char *key)
{
	t_env	*temp;
	char	*res;

	if (!env || !key)
		return (NULL);
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(get_ms()->status));
	res = get_pwd_oldpwd(*env, key);
	if (res)
		return (res);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0
			&& ft_strlen(temp->key) == ft_strlen(key))
		{
			return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_env	*get_env_ld(t_env **env, char *key)
{
	t_env	*temp;

	if (!env || !key)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0
			&& ft_strlen(temp->key) == ft_strlen(key))
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}
