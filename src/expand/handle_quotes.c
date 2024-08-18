/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 04:44:08 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 04:44:15 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_quotes(char *line)
{
    char *buffer = NULL;
    char c[2];
    int i = 0;
 
    while (line && line[i])
    {
        if (line[i] == '\"' )
        {
            i++;
            while (line[i] && line[i] != '\"')
            {
                ft_strcpy(c, line[i]);
                buffer  = ft_strjoin(buffer, c);
                i++;
            }
        }
        else if (line[i] == '\'')
        {
            i++;
            while (line[i] && line[i] != '\'')
            {
               ft_strcpy(c, line[i]);
                buffer  = ft_strjoin(buffer, c);
                i++;
            }
        }
        else
        {
            ft_strcpy(c, line[i]);
            buffer  = ft_strjoin(buffer, c);
        }
        i++;    
    }
    return (buffer);
}
