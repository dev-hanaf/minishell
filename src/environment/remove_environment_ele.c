/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_environment_ele.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:39:31 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 05:36:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_env **env, t_env *temp)
{
	t_env	*first_var;
	t_env	*last_var;

	if (temp->next && !temp->prev)
	{
		last_var = temp->next;
		temp->next = NULL;
		last_var->prev = NULL;
		*env = last_var;
	}
	else if (temp->next && temp->prev)
	{
		last_var = temp->next;
		first_var = temp->prev;
		temp->prev = NULL;
		temp->next = NULL;
		first_var->next = last_var;
		last_var->prev = first_var;
	}
	else if (!temp->next && temp->prev)
	{
		first_var = temp->prev;
		temp->prev = NULL;
		first_var->next = NULL;
	}
}

void	remove_env_element(t_env **env, char *variable)
{
	t_env	*temp;

	if (!*env || !variable)
		return ;
	if (!ft_strcmp(variable, "_") || !ft_strcmp(variable, "$"))
		return ;
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->key, variable) == 0)
		{
			delete_node(env, temp);
			break ;
		}
		temp = temp->next;
	}
}
