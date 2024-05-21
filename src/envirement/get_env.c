/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:41:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 19:11:54 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env **env, char *key)
{
	t_env	*temp;

	if (!env || !key)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
        {
        	return (temp->value);
        }
        temp = temp->next;
	}
	return ("ahanaf");
}
