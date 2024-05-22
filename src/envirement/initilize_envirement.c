/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize_envirement.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:10:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 02:34:21 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_envirement(char **env)
{
	t_env	*init_env;
	size_t	i;
	char	**split;
	t_env	*new;

	init_env = ft_allocator(sizeof(t_env), "t_env");
	if (!init_env)
		printf("error\n"); //TODO add the error handling function
	init_env->value = NULL;
	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		new = new_env(split[0], split[1]);
		add_to_back_env(&init_env, new);
		i++;
	}
	return (init_env);
}
