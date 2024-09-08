/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:10:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/08 07:16:14 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**init_environment(char **env)
{
	t_env	**init_env;
	size_t	i;
	t_env	*new;
	char *key;
	char *value;
	char c[2];
	int j;
	init_env = tmalloc(sizeof(t_env*));
	if (!init_env)
	{
		perror("malloc"); //TODO add the error handling function
		__exit(NULL);
	}
	*init_env = NULL;
	i = 0;
	// if (!get_env(get_ms()->env_ld, "$"))
	// {
	// 	new = new_env("$", ft_itoa_env(get_pid()));
	// 	add_to_back_env(init_env, new);
	// 	printf("i aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\n\n\n\n");
	// }
	// else
	// 	change_env(get_ms()->env_ld, "$", ft_itoa_env(get_pid()));
	while (env && env[i])
	{
		j = 0;
		key = NULL;
		value = NULL;
		while (env && env[i][j] && env[i][j] != '=')
		{
			ft_strcpy(c, env[i][j]);
			key = ft_strjoin_env(key, c);
			j++;
		}			
		if (env && env[i][j] && env[i][j] == '=')
			j++;
		while (env && env[i][j])
		{
			ft_strcpy(c, env[i][j]);
			value = ft_strjoin_env(value, c);
			j++;
		}
		new = new_env(key, value);
		add_to_back_env(init_env, new);
		i++;
	}
	return (init_env);
}
