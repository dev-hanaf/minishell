/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:18:16 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 06:01:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_env(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "$"))
		{
			env = env->next;
			continue ;
		}
		if (env->value)
		{
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (0);
}
