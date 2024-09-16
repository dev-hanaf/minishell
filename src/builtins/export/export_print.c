/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:50:23 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 22:38:41 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*sort_list(t_env *lst)
{
	char	*key;
	char	*value;
	t_env	*start;

	start = lst;
	key = NULL;
	value = NULL;
	while (lst != NULL && lst->next != NULL)
	{
		if (ft_strcmp(lst->key, lst->next->key) >= 0)
		{
			key = lst->key;
			value = lst->value;
			lst->key = lst->next->key;
			lst->value = lst->next->value;
			lst->next->key = key;
			lst->next->value = value;
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (start);
}

t_env	*clone_env(t_env *env)
{
	t_env	**new;

	new = _malloc(sizeof(t_env *));
	if (!new)
	{
		perror("malloc");
		clean_exit(1);
	}
	*new = NULL;
	while (env)
	{
		add_to_back_env(new, new_env(env->key, env->value));
		env = env->next;
	}
	return (sort_list(*new));
}

void	print_export(t_env *env)
{
	t_env	*clone;

	clone = sort_list(clone_env(env));
	while (clone)
	{
		if (!ft_strcmp(clone->key, "$") || !ft_strcmp(clone->key, "_"))
		{
			clone = clone->next;
			continue ;
		}
		printf("declare -x %s", clone->key);
		if (clone->value)
			printf("=\"%s\"", clone->value);
		printf("\n");
		clone = clone->next;
	}
}
