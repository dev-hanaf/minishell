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
#include "libft.h"

t_minishell *get_ms(void)
{
	static t_minishell ms;
	return &ms;
}


void close_heredoc(t_cmd *cmd)
{
	t_rdr *temp;
	if(!cmd)
		return;
	while(cmd)
	{
		temp = cmd->redir;
		while(temp)
		{
			if(temp->type == HERDOC && temp->fd != -1)
				close(temp->fd);
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	get_ms()->cmd = NULL;
}

void	loop(void)
{
	char	*line;
	char	*prompt;

	prompt = NULL;
	while (true)
	{
		handle_signals();
		prompt = ft_strjoin("minishell(", ft_itoa(get_ms()->status));
		prompt = ft_strjoin(prompt,")$ ");
		if(!prompt)
			printf("error\n"); //TODO add the error handling function
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			clean_exit(get_ms()->status);
		}
		else if ((line && line[0] == '\0' )|| line[0] == '\n')
			continue;
		t_tokenizer *lexer = tokenization(line);
		if (!input_validation(lexer))
		{	
			t_cmd *cmd_list = parse_cmds((lexer));
			execute_cmds(cmd_list,cmd_nbr(cmd_list));
			close_heredoc(cmd_list);
		}
		add_history(line);
		free(line);
		_free();
	}
}
void init_minishell(char **envp)
{
	t_env **env;
	t_minishell *ms;
	int shlvl;
	ms = get_ms();
	ms->env = envp;
	env = init_environment(envp);
	if (!get_env(env , "$"))
		add_to_back_env(env, new_env("$", ft_itoa_env(get_pid())));
	else
		change_env(env , "$",ft_itoa_env(get_pid()));
	ms->env_ld = env;
	if(get_env_ld(ms->env_ld, "SHLVL"))
	{
		shlvl = ft_atoi(get_env_ld(ms->env_ld, "SHLVL")->value);
		if(shlvl >= 999)
			shlvl = 1;
		else
			shlvl++;
		get_env_ld(ms->env_ld, "SHLVL")->value = ft_itoa_env(shlvl);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac > 1)
		return (1);
	init_minishell(envp);
	loop();
	_free_env();
	return (0);
}
