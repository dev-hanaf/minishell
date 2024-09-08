/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 06:50:22 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/08 07:33:46 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int _unset(t_env **env, char **variables)
{
    if (!*env || !variables)
	{
        return (0);
	}
	while(*variables)
	{
		remove_env_element(env, *variables);
		variables++;
	}
	// puts("------------------------------- new env ----------------------------");
	// _env(*env);
	//get_ms()->env_ld = env;
	// puts("------------------------------- new env ----------------------------");
	_env(*get_ms()->env_ld);
    return (0);
}
