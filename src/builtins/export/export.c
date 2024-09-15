/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:11 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 23:22:38 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_strs(char **args)
{
	int	i;
	i = 0;
	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
}
char	**export_v2(t_env *env, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		process_nodes(env, args[i]);
		i++;
	}
	return (NULL);
}

int	_export(t_env **env, char **args, char **strs)
{
	int	status;

	status = 0;
	get_ms()->status = 0;
	if (!args)
		return (0);
	args = args + 1;
	if (!args || !*args || !*strs)
	{
		print_export(*env);
	}
	export_v2(*env, args);
	return (status);
}
