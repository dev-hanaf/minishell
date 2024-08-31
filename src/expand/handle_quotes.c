/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 04:44:08 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/31 16:12:23 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_qquotes(char *line, char *buffer, int *i)
{
	char	c[2];

	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		ft_strcpy(c, line[*i]);
		buffer = ft_strjoin(buffer, c);
		(*i)++;
	}
	return (buffer);
}

static char	*is_squotes(char *line, char *buffer, int *i)
{
	char	c[2];

	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		ft_strcpy(c, line[*i]);
		buffer = ft_strjoin(buffer, c);
		(*i)++;
	}
	return (buffer);
}

static char	*none(char *line, char *buffer, int *i)
{
	char	c[2];

	ft_strcpy(c, line[*i]);
	buffer = ft_strjoin(buffer, c);
	return (buffer);
}

static char	*vars_init(char *buffer, char *line, int *i)
{
	*i = 0;
	if (line)
		buffer = ft_strdup("");
	return (buffer);
}

char	*handle_quotes(char *line)
{
	char	*buffer;
	int		i;

	buffer = NULL;
	buffer = vars_init(buffer, line, &i);
	while (line && line[i])
	{
		if (line[i] && line[i] == '\"')
		{
			buffer = is_qquotes(line, buffer, &i);
			if (line[i] == '\0')
				return (buffer);
		}
		else if (line[i] && line[i] == '\'')
		{
			buffer = is_squotes(line, buffer, &i);
			if (line[i] == '\0')
				return (buffer);
		}
		else
			buffer = none(line, buffer, &i);
		i++;
	}
	return (buffer);
}
