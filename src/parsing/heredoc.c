/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:41 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 00:39:36 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_while(t_rdr *heredocs, char *str, int *isexpand)
{
	char	*line;
	char	*eof;

	while (heredocs)
	{
		if (heredocs->type != HERDOC)
		{
			heredocs = get_last_hrdc(heredocs);
			continue ;
		}
		eof = handle_quotes_v2(heredocs->value, isexpand);
		while (TRUE)
		{
			line = readline(">");
			if (line == NULL || !ft_strcmp(line, eof))
				break ;
			if (get_last_hrdc(heredocs) == heredocs)
			{
				str = ft_strjoin(str, line);
				str = ft_strjoin(str, "\n");
			}
		}
		heredocs = heredocs->next;
	}
	return (str);
}

int	open_heredoc(t_rdr *heredocs, int *pipefd, int *status)
{
	char	*str;
	int		isexpand;
	int		pid;

	str = NULL;
	isexpand = 0;
	pid = fork();
	if (pid != CHILD)
		return (heredoc_parent_wait(pid, status));
	signal(SIGINT, sigherdoc);
	signal(SIGQUIT, SIG_IGN);
	str = heredoc_while(heredocs, str, &isexpand);
	if (!str)
		heredoc_clean_exit2(pipefd, 0);
	if (!isexpand)
		str = expand_herdoc(*get_ms()->env_ld, str);
	ft_write(pipefd[WRITE], str, ft_strlen(str));
	close_heredoc(get_ms()->cmd);
	return (heredoc_clean_exit(pipefd, 0));
}

int	handle_heredoc(t_cmd *cmd)
{
	int		status;
	t_rdr	*last;

	while (cmd)
	{
		last = get_last_hrdc(cmd->redir);
		if (last)
		{
			ft_pipe(get_ms()->pipefd);
			open_heredoc(cmd->redir, get_ms()->pipefd, &status);
			close(get_ms()->pipefd[WRITE]);
			if (status != 0)
			{
				close(get_ms()->pipefd[READ]);
				get_ms()->status = status;
				update_status(get_status(status));
				return (status);
			}
			last->fd = get_ms()->pipefd[READ];
		}
		cmd = cmd->next;
	}
	return (0);
}
