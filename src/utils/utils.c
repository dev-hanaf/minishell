/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:15:46 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 04:45:17 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_2d_array(char **arr)
{
	int			i;
	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

void	free_string_array(char **arr)
{
	int				a;

	a = 0;
	while (arr[a] != 0)
	{
		free(arr[a]);
		a++;
	}
	free(arr);
}

int is_whitespaces(int c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

void ft_strcpy(char *dst, char c)
{
    *dst++ = c;
    *dst = '\0';
}
 
t_tokenizer *remove_espace_type(t_tokenizer *lexer)
{
	t_tokenizer *head;
	t_tokenizer *new;

	head = new_token(NULL, 0);
	while (lexer)
	{
		if (lexer->type != ESPACE)
		{
			new = new_token(lexer->value, lexer->type);
			add_to_back_expand(&head, new);
		}
		lexer = lexer->next;
	}
	return (head);
}

void print_strs(char **strs)
{
	if(!strs || !*strs)
		return;
	printf("printing strssssssssssssssss\n");
	int i=0;
	while(*strs)
	{
		printf("%d=%s",i++,*strs);
		strs++;
	}
}