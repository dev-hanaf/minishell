/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 05:58:00 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/05 12:46:40 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    check_quotes(t_tokenizer *lexer)
{
    int i;
    bool flag;
    char to_find;
    bool lock;
    
    lock = true;
    i = 0;
    flag = false;
    while (lexer->value[i])
    {
        if ((lexer->value[i] == '\'' || lexer->value[i] == '\"') && lock)
            to_find = lexer->value[i];
        if (lexer->value[i] == to_find)
        {
            lock = false;
            if (flag)
                flag = false;
            else
                flag = true;
        }        
        i++;
    }
    if (flag)
        return (true);
    return (false);
}
