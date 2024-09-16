/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:39 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/16 02:30:18 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_qquotes_heredoc(char *line, char *buffer, int *i)
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

static char	*is_squotes_heredoc(char *line, char *buffer, int *i)
{
	char	c[2];

	(*i)++;
	while (line[*i] && line[*i] != '\'' )
	{
		ft_strcpy(c, line[*i]);
		buffer = ft_strjoin(buffer, c);
		(*i)++;
	}
	return (buffer);
}

static char	*none_heredoc(char *line, char *buffer, int *i)
{
	char	c[2];

	ft_strcpy(c, line[*i]);
	buffer = ft_strjoin(buffer, c);
	return (buffer);
}

static char	*vars_init_heredoc(char *buffer, char *line, int *i)
{
	*i = 0;
	if (line)
		buffer = ft_strdup("");
	return (buffer);
}


char	*handle_quotes_herdoc(char *line)
{
	char	*buffer;
	int		i;

	buffer = NULL;
	buffer = vars_init_heredoc(buffer, line, &i);
	while (line && line[i])
	{
		if (line[i] && line[i] == '"')
		{
			buffer = is_qquotes_heredoc(line, buffer, &i);
			if (line[i] == '\0')
				return (buffer);
		}
		else if (line[i] && line[i] == '\'')
		{
			buffer = is_squotes_heredoc(line, buffer, &i);
			if (line[i] == '\0')
				return (buffer);
		}
		else
			buffer = none_heredoc(line, buffer, &i);
		i++;
	}
	return (buffer);
}

char *handle_dollars(char *del)
{
	int	i;
	char	c[2];
	char *res;
	char 	q;
	int start;
	 
	i = 0;
	res = NULL;
	while (del && del[i])
	{
		if (del[i] == '"')
		{
			i++;
			while (del[i] && del[i] != '"')
			{
				ft_strcpy(c, del[i]);
				res = ft_strjoin(res, c);
				i++;
			}
			i++;
			continue;
		}
		if (del[i] == '\'')
		{
			i++;
			while (del[i] && del[i] != '\'')
			{
				ft_strcpy(c, del[i]);
				res = ft_strjoin(res, c);
				i++;
			}
			i++;
			continue;
		}
		if (del[i] == '$' && del[i + 1] && (del[i + 1] == '"' || del[i + 1] == '\''))
		{
			i++;
			q = del[i];
			i++;
			start = i;
			while (del[i] && del[i] != q)
				i++;
			char *str = ft_substr(del, start, i -  start);
			if (del[i] == q)
				i++;
			res = ft_strjoin(res, str);
			continue;
		}
		else
		{
			ft_strcpy(c, del[i]);
			res = ft_strjoin(res, c);
		}
		i++;
	}
	printf("res--> %s\n", res);
	// printf("quotes handle res--> %s\n", handle_quotes_herdoc(res));

	return (res);
}


/* char	*handle_dollars(char *delimiter)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = _malloc((sizeof(char) * ft_strlen(delimiter) + 1));
	while (delimiter[i])
	{
		if (delimiter[i] == '$' && (delimiter[i + 1] == '\''
				&& delimiter[i + 2] == '\''))
		{
			i += 3;
			continue ;
		}
		if (delimiter[i] == '$' && (delimiter[i + 1] == '\"'
				&& delimiter[i + 2] == '\"'))
		{
			i += 3;
			continue ;
		}
		str[j++] = delimiter[i++];
	}
	str[j] = 0;
	return (str);
} */

char	*handle_quotes_v2(char *eof, int *expand)
{
	if (ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
		*expand = 1;
	eof = handle_dollars(eof);
	if(!eof)
		eof = ft_strdup("");
	return (eof);
}

int	heredoc_clean_exit(int *pipefd, int status)
{
	close(pipefd[WRITE]);
	close(pipefd[READ]);
	clean_exit(status);
	return (0);
}

int	heredoc_parent_wait(int child, int *status)
{
	handle_parent_signals();
	waitpid(child, status, 0);
	*status = get_status(*status);
	dprintf(2,"status heredoc =%d\n",*status);
	return (*status);
}
