/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:37:30 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/16 01:23:42 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/25 09:20:50 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*get_ms(void)
{
	static t_minishell	ms;

	return (&ms);
}

void	close_heredoc(t_cmd *cmd)
{
	t_rdr	*temp;

	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd->redir;
		while (temp)
		{
			if (temp->type == HERDOC && temp->fd != -1)
				close(temp->fd);
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	get_ms()->cmd = NULL;
}

void	run_minishell(t_tokenizer *lexer)
{
	t_cmd	*cmd_list;

	cmd_list = parse_cmds(lexer, NULL);
	execute_cmds(cmd_list, cmd_nbr(cmd_list));
	close_heredoc(cmd_list);
}

void	loop(void)
{
	char		*line;
	char		*prompt;
	t_tokenizer	*lexer;

	prompt = NULL;
	while (true)
	{
		get_ms()->cmd = NULL;
		handle_signals();
		prompt = "$>";
		line = readline(prompt);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			clean_exit(get_ms()->status);
		}
		else if ((line && line[0] == '\0') || line[0] == '\n')
			continue ;
		lexer = tokenization(line);
		if (!input_validation(lexer))
			run_minishell(lexer);
		add_history(line);
		free(line);
		_free();
	}
}

void	init_minishell(char **envp)
{
	t_env		**env;
	t_minishell	*ms;
	int			shlvl;

	env = NULL;
	ms = get_ms();
	ms->env = envp;
	env = init_environment(envp);
	if (!get_env(env, "$"))
		add_to_back_env(env, new_env("$", ft_itoa_env(get_pid())));
	else
		change_env(env, "$", ft_itoa_env(get_pid()));
	ms->env_ld = env;
	if (get_env_ld(ms->env_ld, "SHLVL"))
	{
		shlvl = ft_atoi(get_env_ld(ms->env_ld, "SHLVL")->value);
		if (shlvl >= 999)
			shlvl = 1;
		else
			shlvl++;
		get_env_ld(ms->env_ld, "SHLVL")->value = ft_itoa_env(shlvl);
	}
}
