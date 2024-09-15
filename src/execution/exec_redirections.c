/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:01 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 00:32:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous(t_rdr *redir, int *file, char **str, int flag)
{
	char	**strs;

	strs = expand(*get_ms()->env_ld, redir->value);
	if (ft_strlen_2d_array(strs) > 1 || !strs[0])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->value, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		if (flag)
			clean_exit(1);
		get_ms()->execute = 1;
		return (1);
	}
	*file = open(strs[0], redir->mode, redir->perm);
	*str = strs[0];
	return (0);
}

int	print_file_error(char *str, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	get_ms()->execute = 1;
	if (flag)
		clean_exit(1);
	return (-1);
}

int	handle_rdr(t_rdr *redir, int flag)
{
	int		file;
	char	*str;

	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_OUT
			|| redir->type == APPEND)
		{
			check_ambiguous(redir, &file, &str, flag);
			if (file == -1)
				return (print_file_error(str, flag));
			dup2(file, redir->dup);
			ft_close(file);
		}
		if (redir->type == HERDOC)
		{
			if (redir->fd != -1)
			{
				dup2(redir->fd, STDIN_FILENO);
				ft_close(redir->fd);
			}
		}
		redir = redir->next;
	}
	return (0);
}
