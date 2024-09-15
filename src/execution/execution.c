/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:07 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 23:57:39 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:51:34 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/07 03:21:09by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "minishell.h"

void	exec_cmd(t_list *args)
{
	char	**nargs;
	char	**env;

	nargs = ld_to_arr_and_expand(args);
	if (!args || !nargs)
		clean_exit(0);
	if (check_builtin(nargs, args))
		clean_exit(get_ms()->status);
	env = env_to_arr(*get_ms()->env_ld);
	execve(get_cmd_path(nargs[0]), nargs, env);
	perror("execve");
	clean_exit(1);
}

void	exec_child(t_cmd *cmd, int in_fd, int out_fd[2])
{
	handle_child_signals();
	dup2(in_fd, STDIN_FILENO);
	ft_close(in_fd);
	dup2(out_fd[WRITE], STDOUT_FILENO);
	ft_close(out_fd[WRITE]);
	ft_close(out_fd[READ]);
	handle_rdr(cmd->redir, 1);
	exec_cmd(cmd->args);
}

// if(!cmd->next)
//    update_underscore(cmd);
t_exec	*init_exec(t_cmd *cmd)
{
	t_exec	*exec;

	if (!cmd)
		return (NULL);
	if (!cmd->next && check_single_builtin(cmd))
		return (NULL);
	exec = _malloc(sizeof(t_exec));
	exec->pids = (pid_t *)_malloc(sizeof(pid_t) * (cmd_nbr(cmd)));
	exec->pipefd[READ] = 0;
	exec->pipefd[WRITE] = 1;
	exec->tmp = STDIN_FILENO;
	exec->i = 0;
	return (exec);
}

void	wait_for_childs(t_exec *exec, int nbr)
{
	int	status;
	int	i;

	i = 0;
	while (i < nbr)
		waitpid(exec->pids[i++], &status, 0);
	update_status(get_status(status));
}

void	execute_cmds(t_cmd *cmd, int nbr)
{
	t_exec	*exec;

	exec = init_exec(cmd);
	if (exec == NULL)
		return ;
	while (cmd)
	{
		if (cmd->next)
			pipe(exec->pipefd);
		exec->pids[exec->i] = fork();
		if (exec->pids[exec->i] == CHILD)
			exec_child(cmd, exec->tmp, exec->pipefd);
		else
		{
			handle_parent_in_childs();
			ft_close(exec->pipefd[WRITE]);
			ft_close(exec->tmp);
			exec->tmp = exec->pipefd[READ];
		}
		exec->i++;
		cmd = cmd->next;
	}
	ft_close(exec->tmp);
	wait_for_childs(exec, nbr);
}
