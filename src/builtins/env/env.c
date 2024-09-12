/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:18:16 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 15:09:03 by ahanaf           ###   ########.fr       */
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
		if (env->key && env->value)
			printf("%s", env->key);
		if (env->value)
		{
			printf("=%s",env->value);
	        printf("\n");
		}
		env = env->next;
	}
	return (0);
}
