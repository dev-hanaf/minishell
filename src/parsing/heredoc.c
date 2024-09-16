/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:41 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/16 02:35:35 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_and_nl(char *str, char *line)
{
	str = ft_strjoin(str, line);
	str = ft_strjoin(str, "\n");
	return (str);
}

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
				str = strjoin_and_nl(str, line);
			free(line);
		}
		free(line);
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
		heredoc_clean_exit(pipefd, 0);
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

	status = 0;
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
