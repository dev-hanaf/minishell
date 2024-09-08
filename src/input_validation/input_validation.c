/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:43:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/31 15:47:25 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input_validation(t_tokenizer *lexer)
{	
	if (!lexer || lexer->type == ERROR)
		return true;

	while (lexer)
	{
		if (check_quotes(lexer))
		{
			printf("syntax error unclosed quotes\n");
			update_status(2);
			// exit(241) ;
			return true;
		}
		else if (forbidden_inputs(lexer))
		{
			update_status(2);
			return true;
		}
		else if (rederections_check(lexer))
		{
			update_status(2);
			return true;
		}
		else if(pipes_check(lexer))
		{
			update_status(2);
			return true ;
		}
		lexer = lexer->next;
	}
	return false;
}
