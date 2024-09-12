/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:41:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 15:18:23 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env **env, char *key)
{
	t_env	*temp;
	char *cwd;

	cwd = NULL;

	if (!env || !key)
		return (NULL);
	temp = *env;
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(get_ms()->status));
	/**********************************************************/
	if (!ft_strcmp(key, "PWD") && get_ms()->pwd_islocal == 1)
	{	
		cwd = getcwd(NULL, 0);
		get_ms()->pwd = ft_strdup_env(cwd);
		free(cwd);
		return (get_ms()->pwd);
	}
	if (!ft_strcmp(key, "OLDPWD") && get_ms()->oldpwd_islocal == 1)
	{
		get_ms()->oldpwd = get_ms()->pwd;
		return (get_ms()->oldpwd);
	}
	/**********************************************************/
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
	char *cwd;
	
	cwd = NULL;
	if (!env || !key)
		return (NULL);
	temp = *env;
	while (temp)
	{
		// if (!ft_strcmp(key, "?") && !ft_strcmp(temp->key, "?"))
		// {
		// 	temp->value = ft_itoa_env(get_ms()->status);
		// 	return (temp);
		// }
		/**********************************************************/
		if (!ft_strcmp(key, "PWD") && get_ms()->pwd_islocal == 1 && !ft_strcmp(temp->key, "PWD"))
		{
			cwd = getcwd(NULL, 0);
			get_ms()->pwd = ft_strdup_env(cwd);
			free(cwd);
			return (temp);
		}
		if (!ft_strcmp(key, "OLDPWD") && get_ms()->oldpwd_islocal == 1 && !ft_strcmp(temp->key, "OLDPWD"))
		{
			get_ms()->oldpwd = get_ms()->pwd;
			return (temp);
		}
		/**********************************************************/
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0
			&& ft_strlen(temp->key) == ft_strlen(key))
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}
