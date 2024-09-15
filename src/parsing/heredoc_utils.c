/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:39 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:40 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdr	*get_last_hrdc(t_rdr *redir)
{
	t_rdr	*last;

	last = NULL;
	if (!redir)
		return (NULL);
	while (redir)
	{
		if (redir->type == HERDOC)
			last = redir;
		redir = redir->next;
	}
	return (last);
}

char	*handle_quotes_v2(char *eof, int *expand)
{
	if (ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
		*expand = 1;
	return (handle_quotes(eof));
}

int	heredoc_clean_exit(int *pipefd, int status)
{
	close_heredoc(get_ms()->cmd);
	close(pipefd[WRITE]);
	close(pipefd[READ]);
	clean_exit(status);
	return (1);
}

int	heredoc_clean_exit2(int *pipefd, int status)
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
	return (*status);
}
