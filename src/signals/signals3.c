/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:31 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:32 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parentsig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped) \n", 2);
	}
}

void	sighandler_parent(int sig)
{
	if (sig == SIGINT)
	{
		update_status(130);
	}
}

void	handle_parent_in_childs(void)
{
	signal(SIGINT, parentsig);
	signal(SIGQUIT, parentsig);
}

void	handle_parent_signals(void)
{
	signal(SIGINT, sighandler_parent);
	signal(SIGQUIT, SIG_IGN);
}
