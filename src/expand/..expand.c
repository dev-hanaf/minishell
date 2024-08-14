/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:43:38 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/12 14:53:40 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_quotes
{
    char *str;
    struct s_quotes *next;
    struct s_quotes *prev;
}   t_quotes;

t_quotes *new_node(char *s)
{
    t_quotes *new;

    new = malloc(sizeof(t_quotes));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    new->str = ft_strdup(s);
    return (new);
}

void append_node(t_quotes **head, t_quotes *new)
{
    t_quotes *tmp;

    if (!new)
        return;
    tmp = *head;
    if (!tmp->str)
    {
        (*head)= new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}



void expand(t_env *env, t_tokenizer *lexer, char *line)
{
    int i = 0;
    t_quotes *head;
    char buffer[2];
    head = new_node(NULL);
    t_quotes *new;
    (void )env;
    (void)line;
    while (lexer)
    {
        i = 0;
        while (lexer->value && lexer->value[i] && (ft_strchr(lexer->value, '\'') || ft_strchr(lexer->value, '\"') || ft_strchr(lexer->value, '$')))
        {
            if (!ft_isalnum(lexer->value[i]))
            {
                buffer[0] = lexer->value[i];
                buffer[1] = '\0';
                new = new_node(buffer);
                append_node(&head, new);
            }
            if (ft_isalnum(lexer->value[i]))
            {
                char *s = NULL;
                while(ft_isalnum(lexer->value[i]))
                {
                    buffer[0] = lexer->value[i];
                    buffer[1] = '\0';
                    s = ft_strjoin(s, buffer);
                    i++;
                }
                new = new_node(s);
                append_node(&head, new);
                if (s)
                    free(s);
                i--;
            }
            i++;
        //     if (i == (int)ft_strlen(lexer->value))
        //     {//TODO move the head from node to another node
        //         t_quotes *temp = head;
        //            while (temp)
        //             {
        //                 if (temp->str[0] == '\'' && (temp->str[0] == temp->next->str[0]))
        //                 {
        //                         if (temp->next->next)
        //                             head = temp->next->next;
        //                         else
        //                             head->next = NULL;
        //                         temp = head;
        //                 }
        //                 if (temp->next)
        //                     temp =  temp->next;
        //             }
        //     }
        }
        lexer = lexer->next;
    }
    while (head)
    {
        printf(RED"%s\n"NC, head->str);
        head = head->next;
    }
}