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

t_minishell *get_ms(void)
{
	static t_minishell ms;
	return &ms;
}
// https://42-cursus.gitbook.io/guide/rank-03/minishell/functions

void close_heredoc(t_cmd *cmd)
{
	t_rdr *temp;
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
}


void loop()
{
	char *line;
	char *prompt = NULL;
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
			exit(130);
			_free();
		}
		else if ((line && line[0] == '\0' )|| line[0] == '\n')
			continue;
		t_tokenizer *lexer = tokenization(line);
		if (!input_validation(lexer))
		{	
			t_cmd *cmd_list = parse_cmds((lexer));
			execute_cmds(cmd_list,cmd_nbr(cmd_list));
		}
		add_history(line);
		free(line);
		_free();
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	//TODO add args check
	t_env **env;
	t_minishell *ms;
	ms = get_ms();
	if (ac > 1)
		return(1);
	if(!envp || !*envp)
		printf("error\n"); //TODO add the error handling function
	ms->env = envp;
	env = init_environment(envp);
	ms->env_ld = env;
    // add_to_back_env(ms->env_ld,new_env("Aloha","ls -la"));
	loop();
	_free_env();
	return (0);
}
