/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:07:46 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/14 09:18:36 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_quotes(char *line)
{
    char *buffer = NULL;
    char c[2];
    int in_dq = 0;
    int in_sq = 0;
    int i = 0;   
    while (line && line[i])
    {
        // "''"''$HOME''"''"
        if (line[i] == '\'' && !in_dq)
            in_sq = 1;
        else if(line[i] == '\"' && !in_sq)
            in_dq = 1;
        else
        {
            c[0] = line[i];
            c[1] = '\0';
            buffer  = ft_strjoin(buffer, c);
        }
        i++;
    }
    return (buffer);
}



char *catch_expand(char *line, t_env *env)
{
    int i;
    char *res;
    int start;
    char buffer[2];
    start = 0;
    res = NULL;
    char *exp = NULL;
    i = 0;
    if (line &&  ft_strchr(line, '$'))
    {
        if (line[0] == '\"' || line[0] == '$')
        {
            while(line[i])
            {
                if (line[i] == '$')
                {
                    start = i;
                    i++;
                    while (line[i] && ft_isalnum(line[i]) &&  !is_whitespaces(line[i]))
                        i++;
                    exp =  ft_substr(line, start , i - start);
                    exp =  get_env(&env, exp + 1);
                    if (exp)
                        res = ft_strjoin(res, exp);
                }
                buffer[0] = line[i];
                buffer[1] = '\0';
                res = ft_strjoin(res, buffer);
                if (line[i] == '\0')
                    break;
                i++;
            }
        }
        else if (line[0] == '\'')
            res = ft_strjoin(res, line);  
    } 
    return (res);
}


void 		expand_lexer(t_env *env, t_tokenizer *lexer)
{
    char *res;
    
    res = NULL;
    while (lexer)
    {
        res = catch_expand(lexer->value, env);
        res = handle_quotes(res);
        if (res)
            lexer->value = res;
        lexer = lexer->next;
    }
}

/* void expand(t_env *env, char *line)
{
    TODO zmourid use it
} */


//TODO echo ''''''$HOME'''''' ==> /nfs/homes/ahanaf

// TODO echo "''"''$HOME''"''" ==> ''/nfs/homes/ahanaf''