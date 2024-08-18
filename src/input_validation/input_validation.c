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
			exit(241) ;
		}
		else if (forbidden_inputs(temp))
			exit(241);
		else if (rederections_check(temp))
			exit(241) ;//TODO is i should return a status and write syntax error on stderr
		else if(pipes_check(temp))
			exit(241) ;
		temp = temp->next;
	}
	return ;
}
