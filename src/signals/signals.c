/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:25 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:26 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	get_ms()->status = sig + 128;
}

void	handle_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigchildhandler(int sig)
{
	ft_putstr_fd("handling child", 2);
	if (sig == SIGINT)
		clean_exit(130);
	else if (sig == SIGQUIT)
		clean_exit(2);
}

void	handle_child_signals(void)
{
	signal(SIGINT, sigchildhandler);
	signal(SIGQUIT, sigchildhandler);
}
