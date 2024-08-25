/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:43:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/15 17:21:48 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	input_validation(t_tokenizer *lexer)
{	
	if (!lexer)
		return true;

	lexer = remove_espace_type(lexer);
	while (lexer)
	{
		if (check_quotes(lexer))
		{
			printf("syntax error unclosed quotes\n");
			// exit(241) ;
			return true;
		}
		else if (forbidden_inputs(lexer))
			return true;
		else if (rederections_check(lexer))
			return true;
		else if(pipes_check(lexer))
			return true ;
		lexer = lexer->next;
	}
	return false;
}
