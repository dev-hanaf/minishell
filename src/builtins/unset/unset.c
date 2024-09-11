/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 06:50:22 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 05:27:14 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_unset(t_env **env, char **variables)
{
	if (!*env || !variables)
	{
		return (0);
	}
	while (*variables)
	{
		remove_env_element(env, *variables);
		variables++;
	}
	return (0);
}
