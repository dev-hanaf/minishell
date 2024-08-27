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

t_minishell	g_minishell;
// https://42-cursus.gitbook.io/guide/rank-03/minishell/functions

t_tokenizer *get_token(t_tokenizer *lexer, char *word)
{
	t_tokenizer *temp;
	temp = lexer;
	while (temp)
	{
		if (ft_strncmp(temp->value, word, 2) == 0 )
		{
			if (temp->next != NULL)
				return(temp->next);
			break;
		}
		temp = temp->next;
	}
	return (NULL);
}
void builtin_commands(t_env **env, t_tokenizer *lexer)
{
	size_t len;
	t_tokenizer *temp;
	t_tokenizer *save;
	int counter = 0;
	int i = 0;
	char **res;
	if (!env || !lexer)
		return;
	while (lexer)
	{
		len = ft_strlen(lexer->value);
		if (!ft_strncmp(lexer->value, "cd", 2) && len == 2)
			_cd(lexer->next->value, env);
		else if (!ft_strncmp(lexer->value, "echo", 4) && len == 4)
		{
			temp = lexer->next;
			counter++;
			while(temp && temp->type == ESPACE)
				temp = temp->next;
			save = temp;
			while (temp && (temp->type == WORD || temp->type == ESPACE) )
			{
				counter++;
				temp = temp->next;
			}
			res = ft_allocator((counter + 1)  * sizeof(char *), "echo");
			temp = save;
			i = 0;
			while (temp && (temp->type == WORD || temp->type == ESPACE))
			{
				res[i] = ft_strdup(temp->value);
				// printf("%s\n", res[i]);
				i++;
				temp = temp->next;
			}
			res[i] = NULL;

			_echo(res);
			lexer = temp;
		}
		else if(!ft_strncmp(lexer->value, "env", 3) && len == 3)
			_env(*env);
		else if (!ft_strncmp(lexer->value, "unset", 5) && len == 5 && lexer->next)
		{
			_unset(env, lexer->next->value);
		}
		if (lexer)
			lexer = lexer->next;
	}	
}
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
void loop(t_env *env)
{
    printf("env - %s\n",get_env(&env, "PWD"));
	char *line;
	char *prompt;
	while (true)
	{
		//handle_signals();
		prompt = ft_strjoin("minishell", "$ ");
		if(!prompt)
			printf("error\n"); //TODO add the error handling function
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			exit(0);
			free_allocator();
		}
		else if ((line && line[0] == '\0' )|| line[0] == '\n')
			continue;
		t_tokenizer *lexer = tokenization(line);
		if (!input_validation(lexer))
		{	
			t_tokenizer *new_tokenizer =  expand_lexer(env, &lexer);
			t_cmd *cmd_list = parse_cmds((new_tokenizer));
			execute_cmds(cmd_list);
			//close_heredoc(cmd_list);
			//print_cmds(cmd_list);
			//display_tokens(new_tokenizer);
			// puts("********************\n********************");
			// printf("%s\n", expand(env," $HOME"));
			//builtin_commands(&env, new_tokenizer);
		}
			add_history(line);
		free(line);
	}
}
// TODO test builtin_commandsll
int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_env **env;
	
	if (ac > 1)
		return(1);
	if(!envp || !*envp)
		printf("error\n"); //TODO add the error handling function
	g_minishell.env = envp;
	env = init_environment(envp);
	g_minishell.env_ld = env;
    add_to_back_env(g_minishell.env_ld,new_env("Aloha",NULL));
	loop(*env);
	free_allocator();
	return (0);
}
