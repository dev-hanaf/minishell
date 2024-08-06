/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 04:57:59 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/06 06:19:24 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand(t_env **env, t_tokenizer *lexer)
{
    char *key;
    t_env *temp;
    
    temp = *env;
    if (lexer->type == WORD)
    {
        if (lexer->value[0] == '$')
        {
            key = get_env(env, lexer->value + 1);
            if (ft_strncmp(key, "ahanaf", ft_strlen(key)))
            {
                printf(RED"%s\n"NC, key);
            }
        }
    }
    return;
}
