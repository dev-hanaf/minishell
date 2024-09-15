/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:53:38 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:06:12 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_next_a_word(t_tokenizer *lexer)
{
	if (lexer->next != NULL)
	{
		if (lexer->next->type != WORD)
		{
			ft_putstr_fd("syntax error\n", 2);
			return (true);
		}
	}
	else
	{
		ft_putstr_fd("syntax error\n", 2);
		return (true);
	}
	return (false);
}

bool	rederections_check(t_tokenizer *lexer, int *counter)
{
	if (lexer->type == REDIR_IN)
		return (is_next_a_word(lexer));
	else if (lexer->type == REDIR_OUT)
		return (is_next_a_word(lexer));
	else if (lexer->type == APPEND)
		return (is_next_a_word(lexer));
	else if (lexer->type == HERDOC)
	{
		if (!is_next_a_word(lexer))
		{
			*counter += 1;
			if (*counter == 17)
			{
				ft_putstr_fd("bash: maximum here-document count exceeded\n", 2);
				_free();
				_free_env();
				exit(1);
				return (true);
			}
		}
		return (is_next_a_word(lexer));
	}
	return (false);
}
