/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:43:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/06 05:22:14 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	input_validation(t_tokenizer *lexer)
{	
	t_tokenizer *temp;
	if (!lexer)
		return ;
	temp = lexer;
	while (temp)
	{
		if (check_quotes(temp))
		{
			printf("syntax error unclosed quotes\n");
			return ;
		}
		else if (forbidden_inputs(temp))
			return;
		else if (rederections_check(temp))
			return ;//TODO is i should return a status and write syntax error on stderr
		else if(pipes_check(temp))
			return ;
		temp = temp->next;
	}
	return ;
}
