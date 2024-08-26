/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_new_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:05:52 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 02:08:30 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = ft_allocator(sizeof(t_env), "new_env");
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*last_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	add_to_back_env(t_env **env, t_env *new)
{
	t_env	*temp;

	if ((*env) == NULL)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	add_to_front_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = *env;
	if (!new)
		return ;
	if (tmp)
		tmp->prev = new;
	new->prev = NULL;
	new->next = tmp;
	*env = new;
}

int	env_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	if (!env)
		return (0);
	size = 0;
	while (env != NULL)
	{
		env = env->next;
		size++;
	}
	return (size);
}
