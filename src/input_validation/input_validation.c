/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:43:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 13:04:40 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
1. unclosed quotes.
2. misuse of redirection or pipe symbols.
 */

void	input_validation(t_tokenizer *lexer)
{	
	t_tokenizer *temp;
	if (!lexer)
		return ;
	temp = lexer;
	while (temp)
	{
		if (forbidden_inputs(temp) == -1)
			return;
		else if ( -1 == rederections_check(temp))
			return ;//TODO is i should return a status and write syntax error on stderr
		else if(-1 == pipes_check(temp))
			return ;
		temp = temp->next;
	}
	return ;
}