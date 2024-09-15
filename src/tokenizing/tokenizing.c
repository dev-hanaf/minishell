/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:43:49 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:31:17 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_single_quote(char *line, size_t *i)
{
	(*i)++;
	while (line[*i] != '\0' && line[*i] != '\'')
	{
		(*i)++;
	}
	if (line[*i] == '\'')
		(*i) += 1;
	if (line[*i] == '\'')
		is_single_quote(line, i);
}

void	is_double_quotes(char *line, size_t *i)
{
	(*i)++;
	while (line[*i] != '\0' && line[*i] != '"')
	{
		(*i)++;
	}
	if (line[*i] == '"')
		(*i) += 1;
	if (line[*i] == '"')
		is_double_quotes(line, i);
}

void	allocate_word(size_t *i, size_t start, char *line, t_tokenizer **lexer)
{
	char		*word;
	t_tokenizer	*token;
	size_t		j;

	word = _malloc(sizeof(char) * (*i - start + 1));
	if (!word)
		exiter(1, "malloc");
	j = 0;
	while (start < *i)
		word[j++] = line[start++];
	word[j] = '\0';
	token = new_token(word, WORD);
	add_to_back(lexer, token);
}

void	is_command(t_tokenizer **lexer, char *line, size_t *i)
{
	size_t	start;

	start = *i;
	if (line[*i] != '>' && line[*i] != '<' && line[*i] != '|'
		&& !is_whitespaces(line[*i]) && line[*i] != 10 && line[*i] != '\0')
	{
		while (line[*i])
		{
			if (line[*i] == '\"')
			{
				is_double_quotes(line, i);
				continue ;
			}
			if (line[*i] == '\'')
			{
				is_single_quote(line, i);
				continue ;
			}
			if (line[*i] == '\0' || line[*i] == '>' || line[*i] == '<'
				|| line[*i] == '|' || is_whitespaces(line[*i]))
				break ;
			(*i)++;
		}
		allocate_word(i, start, line, lexer);
	}
}

t_tokenizer	*tokenization(char *line)
{
	size_t		i;
	t_tokenizer	*lexer;

	if (!line)
		return (NULL);
	i = 0;
	lexer = _malloc(sizeof(t_tokenizer));
	if (!lexer)
		exiter(1, "malloc");
	lexer->next = NULL;
	lexer->next = NULL;
	lexer->type = 0;
	lexer->value = NULL;
	while (line[i])
	{
		skip_whitespaces(line, &i);
		is_command(&lexer, line, &i);
		skip_whitespaces(line, &i);
		is_pipe(&lexer, line, &i);
		skip_whitespaces(line, &i);
		is_redirection(&lexer, line, &i);
	}
	return (lexer);
}
