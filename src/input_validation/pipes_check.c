/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:57:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 00:57:41 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipes_check(t_tokenizer *lexer)
{
	if (lexer->type == PIPE)
	{
		if (lexer->prev == NULL || lexer->next == NULL)
		{
			ft_putstr_fd("syntax error\n", 2);
			return (true);
		}
		else if (lexer->prev == NULL && lexer->next->type == PIPE)
		{
			ft_putstr_fd("syntax error\n", 2);
			return (true);
		}
		else if (lexer->prev->type != WORD)
		{
			ft_putstr_fd("syntax error\n", 2);
			return (true);
		}
	}
	return (false);
}
