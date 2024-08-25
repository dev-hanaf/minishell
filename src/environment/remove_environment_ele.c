/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_environment_ele.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:39:31 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/12 17:39:33 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_env_element(t_env **env, char *variable)
{
    t_env *temp;
    t_env *first_var;
    t_env *last_var;
    
    if (!*env || !variable)
        return ;
    temp = *env;
    while(temp)
    {
        if (ft_strncmp(temp->key,variable, ft_strlen(variable)) == 0 && ft_strlen(temp->key) == ft_strlen(variable))
        {
            if (temp->next && temp->prev)
            {
                last_var = temp->next;
                first_var = temp->prev;
                temp->prev = NULL;
                temp->next = NULL;
                first_var->next = last_var;
                last_var->prev = first_var;
            }
            else if (temp->next && !temp->prev)
            {
                printf(" i am here\n");
                // last_var = temp->next;
                // temp->next = NULL;
                // last_var->prev = NULL;
                // temp->next->prev = NULL;
                *env = temp->next;
            }
             else if (!temp->next && temp->prev)
            {
                first_var = temp->prev;
                temp->prev = NULL;
                first_var->next = NULL;
            }
            break;
        }
        temp = temp->next;
    }
}
