/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:44 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:55:01 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ld_to_arr(t_list *lst)
{
	char	**arr;
	int		i;

	if (!lst)
		return (NULL);
	arr = _malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		arr[i] = ft_strdup((char *)lst->content);
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	env_size_val(t_env *env)
{
	int	size;

	if (!env)
		return (0);
	size = 0;
	while (env != NULL)
	{
		env = env->next;
		if (env->value)
			size++;
	}
	return (size);
}

char	**env_to_arr(t_env *env)
{
	char	*temp;
	char	**arr;
	int		i;

	temp = NULL;
	if (!env)
		return (NULL);
	arr = _malloc(sizeof(char *) * (env_size(env) + 1));
	i = 0;
	while (env)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		temp = ft_strjoin(ft_strdup(env->key), "=");
		temp = ft_strjoin(temp, ft_strdup(env->value));
		arr[i] = temp;
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
