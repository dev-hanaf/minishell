/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chnge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:54:18 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 15:28:24 by ahanaf           ###   ########.fr       */
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

void	cd_change_env(t_env **env, char *save)
{
	t_env	*temp;
	char	*cwd;
	int flag;
	char **str;


	flag = 0;
	cwd = NULL;
	if (!*env)
		return ;
	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
		{
			if (get_env(env, "PWD"))
			{
				cwd = getcwd(NULL, 0);
				temp->value = ft_strdup_env(cwd);
				free(cwd);
			}
		}
		if (!ft_strcmp(temp->key, "OLDPWD"))
		{
			printf("PWD ==> %s\n", get_env(env, "PWD"));
			if (!get_env(env, "PWD"))
			{
				flag = 1;
				temp->key = ft_strdup_env("OLDPWD");
				temp->value = NULL;
				str = expand(*env, "$PWD");
				if(str && !str[0])//not exist
					get_ms()->pwd_islocal = 1;//pwd = 1
				else
					get_ms()->pwd_islocal = 0;
			}
			else
			{
				flag = 0;
				temp->value = ft_strdup_env(save);
			}
		}
		temp = temp->next;
	}

	str = expand(*env, "$OLDPWD");
	if(str && !str[0] && !flag)//oldpwd = NULL and flag = 1
        get_ms()->oldpwd_islocal = 1;
	else
		get_ms()->oldpwd_islocal = 0; // oldpwd = 0
}
