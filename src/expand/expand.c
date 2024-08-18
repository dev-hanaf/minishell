/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:07:46 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 04:45:13 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int needs_expansion(const char *line) {
    int i = 0;
    char hold = 0;

    while (line && line[i]) {
        if (line[0] == '$' && line[1] == '\0') {
            return 1; // Needs expansion
        }
        if (line[i] == '$' && !ft_isalpha(line[i + 1])) {
            return 0; // No expansion needed
        }
        if (hold == 0 && (line[i] == '\'' || line[i] == '\"')) {
            hold = line[i];
        } else if (hold != 0 && line[i] == hold) {
            hold = 0;
        }

        if (hold != '\'' && line[i] == '$') {
            return 1; // Needs expansion
        }

        i++;
    }

    return 0; // No expansion needed
}



char *catch_expand(char *line, t_env *env, int to_expand)
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
        while(line[i])
        {
            if (line[i] && to_expand  && line[i] == '$'  &&  line[i + 1] && (ft_isalnum(line[i + 1]) || line[i  + 1] == '_' ))
            {
                if (line[i + 1] && ft_isdigit(line[i + 1]))
                {
                    i += 2;
                    continue;
                }
                start = i;
                i++;
                while (line[i] &&   line[i] != '$' && (ft_isalnum(line[i]) ||  line[i] == '_' ) &&  !is_whitespaces(line[i]))
                    i++;
                exp =  ft_substr(line, start , i - start);
                exp =  get_env(&env, exp + 1);
                printf("exp ==> %s\n", exp);
                if (exp)
                    res = ft_strjoin(res, exp);
                continue;
            }
            else if (line[i] &&  line[i + 1] && ft_isdigit(line[i + 1]))
            {
                    i += 2;
                    continue;
            }
            else if (line[i]  && line[i] == '$' && line[i + 1] &&( line[i + 1] == '\'' || line[i + 1] == '\"'))
            {
                i++;
                continue;
            }
            else if (line[i] && line[i] == '$' && !ft_isalnum(line[i + 1]) )
            {
                ft_strcpy(buffer, line[i]);
                res = ft_strjoin(res, buffer);
                i++;
                continue;
            }
            else if (line[i] && line[i] == '$' && !ft_isalpha(line[i + 1]) )
            {
                i++;
                continue;
            }
            ft_strcpy(buffer, line[i]);
            res = ft_strjoin(res, buffer);
            if (line[i] == '\0')
                break;
            i++;
        }
    }
    return (res);
}


void 		expand_lexer(t_env *env, t_tokenizer **lexer)
{
    char *res;
    int to_expand = 0;
    res = NULL;
    t_tokenizer *temp = *lexer;
    while (temp)
    {
        if (temp->prev &&  temp->prev->type == HERDOC)
            return ;
        to_expand = needs_expansion(temp->value);
        printf("to_expand ==> %d\n", to_expand);
        // printf("result ==> %s\n", res);
        res = catch_expand(temp->value, env, to_expand);
        printf("after catch ==>%s\n", res);
        res = handle_quotes(res);
        if (ft_strchr(temp->value, '$'))
        {
            //TODO after export arg="ls -la"; then axpand $arg the result should be as followd ==> [ls][-la]
            //TODO after export arg="ls -la"; then axpand "$arg" the result should be as followd ==> [ls -la]
            // TODO $arg [ls][-la]
            char **str  = ft_split(res, ' ');
            if (ft_strlen_2d_array(str) > 1)
            {
                int i = 0;
                while (str && str[i])
                {
                    t_tokenizer *new = new_token(str[i], WORD);
                   add_to_back(&temp, new);
                   if (i == 0)
                        *lexer = new;
                    i++;
                }
            }
            else 
                temp->value = res;
        }
        temp = temp->next;
    }
}

char *expand(t_env *env, char *line)
{
    //TODO you dommy need to expand the line if it has $ in it
    int to_expand = 0;
    char *res;
    res = NULL;
    
    to_expand = needs_expansion(line);
    res = catch_expand(line, env, to_expand);
    res = handle_quotes(res);
    return (res);
}


//TODO echo ''''''$HOME'''''' ==> /nfs/homes/ahanaf


// TODO echo "''"''$HOME''"''" ==> ''/nfs/homes/ahanaf''


// TODO  echo ''''$HOME'"' ==> /nfs/homes/ahanaf"

// TODO  echo $"''"'''''$HOME'''''"''" ==> ''$HOME''


//TODO $USER"v" ==> ahanafv

//TODO '""$USER""'

//TODO   $+HOME =====> $+HOME 

// TODO $HOME$HOME ===> /nfs/homes/ahanaf/nfs/homes/ahanaf

// TODO $HOME$HOM ==>  /nfs/homes/ahanaf

//TODO after export arg="ls -la"; then axpand $arg the result should be as followd ==> [ls][-la]
//TODO after export arg="ls -la"; then axpand "$arg" the result should be as followd ==> [ls -la]
  