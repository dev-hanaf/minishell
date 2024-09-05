/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:10:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/31 15:55:55 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**init_environment(char **env)
{
	t_env	**init_env;
	size_t	i;
	char	**split;
	t_env	*new;

	init_env = ft_allocator(sizeof(t_env*), "t_env");
	if (!init_env)
		printf("error\n"); //TODO add the error handling function
	*init_env = NULL;
	i = 0;
	new = new_env("$", ft_itoa(get_pid()));
	wait(0);
	add_to_back_env(init_env, new);
	new = new_env("?", ft_itoa(g_minishell.status));
	add_to_back_env(init_env, new);
	new = new_env("0", "minishell");
	add_to_back_env(init_env, new);
	while (env[i])
	{
		split = ft_split(env[i], '=');
		new = new_env(split[0], split[1]);
		add_to_back_env(init_env, new);
		i++;
	}

	return (init_env);
}
