/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:28 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:29 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_hrdc(int sig)
{
	write(1, "\n", 1);
	clean_exit(sig + 128);
}

void	sigherdoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		close(get_ms()->pipefd[0]);
		close(get_ms()->pipefd[1]);
		clean_exit(130);
	}
}
