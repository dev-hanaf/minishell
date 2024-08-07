/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 04:57:59 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/07 04:43:06 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void expand(t_env **env, t_tokenizer *lexer)
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
} */

char *parse_expansion_command(t_env *env, char *command, int dollar_idx)
{
    int i;
    char *res;
    
    i = dollar_idx;
    while(command[i])
    {
        if((command[i] == ' ' || command[i + 1] == '\0') && (command[i - 1] != '\'' || command[i - 1] != '\"'))
        {
            res =  get_env(&env, command + (dollar_idx + 1));
            if (!res)
                return ("NULL");
            return(ft_strdup(res));         
        }
        i++;
    }
    return (NULL);
}


char *find_the_dollar(char *command, t_env *env)
{
    int i;
    int dollar_idx;
    char *res;

    res = NULL;
    i = 0;
    if (ft_strchr(command, '$'))
    {
        while(command[i])
        {
            if (command[i] == '$')
            {
                dollar_idx = i;   
                res = parse_expansion_command(env, command, dollar_idx);
            }
            i++;
        }
    }
    return (res);
}

void expand(t_env *env, t_tokenizer *lexer, char *line)
{
    char *expansion;
    t_tokenizer *temp;

    temp = lexer;
    if (!lexer)
        return ;
    while(temp && !line)
    {
        expansion =  find_the_dollar(temp->value, env);
        // printf(RED"%s\n"NC, expansion);
        if (expansion)
        {
            temp->value = expansion;
        }
        temp = temp->next;
    }
    if (line)
    {
        if (line[0] == '$')
        {
            while (env)
            {
                if (!ft_strncmp(env->key, line + 1, ft_strlen(env->key)) && ft_strlen(env->key) == ft_strlen(line + 1))
                {
                    printf("%s\n",env->value);  
                }
                env = env->next;
            }
        }
    }
}
