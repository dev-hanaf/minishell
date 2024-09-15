/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:43:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 11:17:10 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	update_status_and_return_true(void)
{
	update_status(2);
	return (true);
}

bool	input_validation(t_tokenizer *lexer)
{
	int	counter;

	if (!lexer || lexer->type == ERROR)
		return (true);
	counter = 0;
	while (lexer)
	{
		if (check_quotes(lexer))
		{
			ft_putstr_fd("syntax error\n", 2);
			update_status(2);
			return (true);
		}
		else if (rederections_check(lexer, &counter))
			return (update_status_and_return_true());
		else if (pipes_check(lexer))
			return (update_status_and_return_true());
		lexer = lexer->next;
	}
	return (false);
}
