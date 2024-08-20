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
// ''$var''
//str == "$var"$var"$var"
//char *exp = "ls -la"
// "ls -la"ls -la ls -la"ls -la"

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



char **catch_expand(char *line, t_env *env, int to_expand)
{
    int i;
    char *res;
    int start;
    char buffer[2];
    start = 0;
    res = NULL;
    char *exp = NULL;
    bool open = false;
    char **str;
    str = ft_allocator(10 * sizeof(char *), "expand");
    str[0] = NULL;
    str[1] = NULL;
    str[2] = NULL;
    str[3] = NULL;
    str[4] = NULL;
    str[5] = NULL;
    str[6] = NULL;
    str[7] = NULL;
    str[8] = NULL;
    str[9] = NULL;
    if (!str)
    {
        perror("malloc");
        return (NULL);
    }
    int exp_cmpt = 0 ; 
    i = 0;
    if (line &&  ft_strchr(line, '$'))
    {
        while(line[i])
        {
            if (line[i] == '"' && !open) {
                open = true;
            } else if (line[i] == '"' && open) {
                open = false;
            }
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
                // printf("exp ==> %s\n", exp);
                int j = 0;
                bool space = false;
                while(exp && exp[j])
                {
                    if (is_whitespaces(exp[j]))
                        space = true;
                    j++;
                }
                if (space && !open)
                {
                    char **spilted = ft_split(exp, ' ');
                    int x = 0;
                    while (spilted[x])
                    {
                        // printf(CYAN"%s\n"NC, spilted[x]);
                        str[exp_cmpt] = spilted[x];
                        exp_cmpt++;
                        x++;
                    }
                }
                else if (exp)
                {
                    // printf(CYAN"%s\n"NC, exp);
                    str[exp_cmpt] = exp;
                    // exp_cmpt++;
                }
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
                str[exp_cmpt] = ft_strjoin( str[exp_cmpt], buffer);
                i++;
                continue;
            }
            else if (line[i] && line[i] == '$' && !ft_isalpha(line[i + 1]) )
            {
                i++;
                continue;
            }
            ft_strcpy(buffer, line[i]);
            str[exp_cmpt] = ft_strjoin( str[exp_cmpt], buffer);
            if (line[i] == '\0')
                break;
            i++;
        }
    }
    str[++exp_cmpt] = NULL;
    return (str);
}

void	add_to_back_expand(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*temp;

	if ((*token)->value == NULL && (*token)->type == ERROR)
	{
		*token = new;
		return ;
	}
	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}


t_tokenizer 		*expand_lexer(t_env *env, t_tokenizer **lexer)
{
    char **res;
    int to_expand = 0;
    // res = NULL;
    t_tokenizer *temp = *lexer;
    t_tokenizer *head = new_token(NULL, 0);
    while (temp)
    {
        int i = 0;
        // printf(GREEN"*********%s************\n"NC, temp->value);
        if (temp->prev &&  temp->prev->type == HERDOC)
            return temp;
        to_expand = needs_expansion(temp->value);
        printf(RED"%d\n"NC, to_expand);
        res = catch_expand(temp->value, env, to_expand);        
        if (to_expand)
        {
            if (!res[i])
            {
                t_tokenizer *new = new_token(NULL, WORD);
                add_to_back_expand(&head, new);
            }
            while(res[i])
            {
                t_tokenizer *new = new_token(handle_quotes(res[i]), WORD);
                add_to_back_expand(&head, new);
                i++;
            }
        }
        else
        {
            if (res[0])
            {
                t_tokenizer *new = new_token(handle_quotes(res[0]), temp->type);
                add_to_back_expand(&head, new);
            }
            else 
            { 
                t_tokenizer *new = new_token(handle_quotes(temp->value), temp->type);
                add_to_back_expand(&head, new);
            }
        }
        temp = temp->next;
    }
    return (head);
}

// char *expand(t_env *env, char *line)
// {
//     //TODO you dommy need to expand the line if it has $ in it
//     int to_expand = 0;
//     char *res;
//     res = NULL;
    
//     to_expand = needs_expansion(line);
//     res = catch_expand(line, env, to_expand);
//     res = handle_quotes(res);
//     return (res);
// }

/* ''''''$HOME''''''  | "''"''$HOME''"''" | ''''$HOME'"' | $"''"'''''$HOME'''''"''" |  $USER"v" | $+HOME  | $HOME$HOME |  $HOME$HOM  */
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
  