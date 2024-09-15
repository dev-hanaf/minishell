/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:59 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 00:31:33 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	return (0);
}

// fork mode on
int	check_builtin(char **args, t_list *targs)
{
	if (!args || !*args || !is_built_in(args[0]))
		return (0);
	if (!ft_strcmp(args[0], "export"))
	{
		_export(get_ms()->env_ld, ld_to_arr(targs), ++args);
		return (1);
	}
	else if (!ft_strcmp(args[0], "echo"))
		_echo(++args);
	else if (!ft_strcmp(args[0], "pwd"))
		_pwd();
	else if (!ft_strcmp(args[0], "exit"))
	{
		get_ms()->pexit = 0;
		__exit(++args);
		return (1);
	}
	else if (!ft_strcmp(args[0], "env"))
		_env(*get_ms()->env_ld);
	else if (!ft_strcmp(args[0], "unset"))
		_unset(get_ms()->env_ld, ++args);
	get_ms()->status = 0;
	return (1);
}

void	restore_fds(int *std_in, int *std_out)
{
	ft_dup2(*std_in, STDIN_FILENO);
	ft_dup2(*std_out, STDOUT_FILENO);
	ft_close(*std_in);
	ft_close(*std_out);
}

void	builtins_roullete(char **strs, t_cmd *cmd)
{
	if (!ft_strcmp(strs[0], "echo"))
		get_ms()->status = _echo(++strs);
	else if (!ft_strcmp(strs[0], "pwd"))
		get_ms()->status = _pwd();
	else if (!ft_strcmp(strs[0], "env"))
		get_ms()->status = _env(*get_ms()->env_ld);
	else if (!ft_strcmp(strs[0], "export"))
		_export(get_ms()->env_ld, ld_to_arr(cmd->args), ++strs);
	else if (!ft_strcmp(strs[0], "unset"))
		get_ms()->status = _unset(get_ms()->env_ld, ++strs);
	else if (!ft_strcmp(strs[0], "cd"))
		get_ms()->status = _cd(++strs, get_ms()->env_ld);
}

int	check_single_builtin(t_cmd *cmd)
{
	char	**strs;
	int		std_in;
	int		std_out;

	strs = ld_to_arr_and_expand(cmd->args);
	if (!strs || !*strs || !is_built_in(strs[0]))
		return (0);
	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (handle_rdr(cmd->redir, 0) == -1)
	{
		restore_fds(&std_in, &std_out);
		get_ms()->status = 1;
		return (1);
	}
	builtins_roullete(strs, cmd);
	if (!ft_strcmp(strs[0], "exit"))
	{
		restore_fds(&std_in, &std_out);
		get_ms()->pexit = 1;
		__exit(ld_to_arr_and_expand(cmd->args->next));
	}
	restore_fds(&std_in, &std_out);
	return (1);
}
