/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:43:49 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 10:21:16 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*perror() reads a the errno and convert it to human readable */
void	skip_whitespaces(char *line, size_t *i)
{
	while (line[*i] == 32 || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
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
			token = new_token(">", OUT);
			add_to_back(lexer, token);
		}
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		if (line[*i + 1] != '\0' && line[*i + 1] == '<')
		{
			token = new_token("<<", HERDOC);
			add_to_back(lexer, token);
			(*i)++;
		}
		else
		{
			token = new_token("<", IN);
			add_to_back(lexer, token);
		}
		(*i)++;
	}
}

void	is_command(t_tokenizer **lexer, char *line, size_t *i)
{
	t_tokenizer	*token;
	size_t		start;
	size_t		j;
	char		*word;

	start = *i;
	if (line[*i] != '>' && line[*i] != '<' && line[*i] != '|')
	{
		while (line[*i] != '\0' && line[*i] != '>' && line[*i] != '<'
			&& line[*i] != '|')
			(*i)++;
		word = ft_allocator(sizeof(char) * (*i - start + 1), "word");
		if (!word)
		{
			perror("malloc");
			exit(1);
		}
		j = 0;
		while (start < *i)
			word[j++] = line[start++];
		word[j] = '\0';
		token = new_token(word, WORD);
		add_to_back(lexer, token);
	}
}

void	tokenization(char *line)
{
	size_t		i;
	t_tokenizer	*lexer;
	t_tokenizer	*temp;

	i = 0;
	lexer = ft_allocator(sizeof(t_tokenizer), "lexer");
	if (!lexer)
		return ;
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
	temp = lexer;
	while (temp)
	{
		printf("value-->|%s|  type-->|%d|\n", temp->value, temp->type);
		temp = temp->next;
	}
}
