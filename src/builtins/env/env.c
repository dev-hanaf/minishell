/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:18:16 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/08 06:02:31 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    _env(t_env *env)
{
    while (env)
    {
        //TODO if env->key == ? or $ skip
        if(env->value)
        {
            printf("%s=%s\n", env->key, env->value);
        }
        env = env->next;
    }
}
