/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:39 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/16 09:47:12 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollars(char *del, int i, char *res)
{
	while (del && del[i])
	{
		if (del[i] && del[i + 1] && del[i] == '$' && del[i + 1] == '$')
		{
			res = characters(res, del[i]);
			res = characters(res, del[i]);
			i += 2;
			continue ;
		}
		if (del[i] == '"' || del[i] == '\'')
		{
			res = is_dq_sq(res, &i, del, del[i]);
			continue ;
		}
		if (del[i] == '$' && del[i + 1] && (del[i + 1] == '"' || del[i
					+ 1] == '\''))
		{
			res = is_dollar_quote(res, &i, del, del[i + 1]);
			continue ;
		}
		else
			res = characters(res, del[i]);
		i++;
	}
	return (res);
}

char	*handle_quotes_v2(char *eof, int *expand)
{
	char	*res;

	res = NULL;
	if (ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
		*expand = 1;
	eof = handle_dollars(eof, 0, res);
	if (!eof)
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
	dprintf(2, "status heredoc =%d\n", *status);
	return (*status);
}
