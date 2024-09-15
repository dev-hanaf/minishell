/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:05 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 21:02:47 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(int new_status)
{
	get_ms()->status = new_status;
}

int	get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

void	update_underscore(t_cmd *cmd)
{
	t_list	*arg;
	char	**strs;

	while (cmd->next)
		cmd = cmd->next;
	arg = cmd->args;
	if (!arg)
		return ;
	while (arg && arg->next)
	{
		arg = arg->next;
	}
	strs = expand(*get_ms()->env_ld, (char *)arg->content);
	if (!strs || !*strs)
		return ;
	get_env_ld(get_ms()->env_ld, "_")->value = strs[ft_strlen_2d_array(strs)
	- 1];
}
