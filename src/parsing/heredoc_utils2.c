/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:32:11 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/16 09:16:30 by ahanaf           ###   ########.fr       */
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

char	*is_dq_sq(char *res, int *i, char *del, char q)
{
	char	c[2];

	(*i)++;
	while (del[*i] && del[*i] != q)
	{
		ft_strcpy(c, del[*i]);
		res = ft_strjoin(res, c);
		(*i)++;
	}
	(*i)++;
	return (res);
}

char	*is_dollar_quote(char *res, int *i, char *del, char q)
{
	int		start;
	char	*str;

	(*i)++;
	(*i)++;
	start = *i;
	while (del[*i] && del[*i] != q)
		(*i)++;
	str = ft_substr(del, start, *i - start);
	if (del[*i] == q)
		(*i)++;
	res = ft_strjoin(res, str);
	return (res);
}

char	*characters(char *res, char car)
{
	char	c[2];

	ft_strcpy(c, car);
	res = ft_strjoin(res, c);
	return (res);
}
