/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:31:45 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 16:44:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_out(size_t *i, char *line, t_tokenizer **lexer)
{
	t_tokenizer	*token;

	if (line[*i + 1] != '\0' && line[*i + 1] == '<')
	{
		token = new_token("<<", HERDOC);
		add_to_back(lexer, token);
		(*i)++;
	}
	else
	{
		token = new_token("<", REDIR_IN);
		add_to_back(lexer, token);
	}
	(*i)++;
}

void	is_redirection(t_tokenizer **lexer, char *line, size_t *i)
{
	t_tokenizer	*token;

	if (line[*i] == '>')
	{
		if (line[*i + 1] != '\0' && line[*i + 1] == '>')
		{
			token = new_token(">>", APPEND);
			add_to_back(lexer, token);
			(*i)++;
		}
		else
		{
			token = new_token(">", REDIR_OUT);
			add_to_back(lexer, token);
		}
		(*i)++;
	}
	else if (line[*i] == '<')
		is_out(i, line, lexer);
}

void	skip_whitespaces(char *line, size_t *i)
{
	while (line[*i] == 32 || (line[*i] >= 9 && line[*i] <= 13))
	{
		(*i)++;
	}
}

void	is_pipe(t_tokenizer **lexer, char *line, size_t *i)
{
	t_tokenizer	*token;

	if (line[*i] == '|')
	{
		token = new_token("|", PIPE);
		add_to_back(lexer, token);
		(*i)++;
	}
}
