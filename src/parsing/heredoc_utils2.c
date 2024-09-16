/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:32:11 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 22:32:12 by zmourid          ###   ########.fr       */
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
