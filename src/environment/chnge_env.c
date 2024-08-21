/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chnge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:54:18 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 19:20:50 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    change_env(t_env **env, char *key, char *value)
{
    t_env   *temp;
    size_t  len;
    
    if (!*env || !key || !value )
        return;
    temp = *env;
    len = ft_strlen(key);
    while(temp)
    {
        if (ft_strncmp(key, temp->key, len) == 0 && len == ft_strlen(temp->key))
        {
            temp->value = ft_strdup(value);
            return;
        }
         temp =  temp->next;
    }    
}
