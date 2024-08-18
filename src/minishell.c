/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 04:48:44 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

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
// void builtin_commands(t_env **env, char *line)
// {
// 	if (!env || !line || !*env) 
// 		return;
// 	t_tokenizer *lexer = tokenization(line);
// 	t_tokenizer *token;
// 	token = get_token(lexer, "cd");
// 	if (token)
// 		_cd(token->value,env);
// 	// _pwd();
// 	token = get_token(lexer, "unset");
// 	if (token/*  && ft_strncmp(token->value, "unset", 5) == 0 && ft_strlen(token->value) == 5 */)
// 	{
// 		_unset(env, "LANG");
// 	}

// }

void loop(t_env *env)
{
	char *line;
	char *prompt;
	while (true)
	{
		prompt = ft_strjoin(get_env(&env, "PWD"), "$ ");
		if(!prompt)
			printf("error\n"); //TODO add the error handling function
		line = readline(prompt);
		if (line == NULL || line[0] == '\0')
			continue;
		// builtin_commands(&env, line);
		t_tokenizer *lexer = tokenization(line);
		display_tokens(lexer);
		input_validation(lexer);
		expand_lexer(env, &lexer);
		printf(YELLOW"after epansion\n"NC);
		display_tokens(lexer);
		puts("********************\n********************");
		// printf("%s\n", expand(env," $HOME"));
		
		add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_env *env;
	
	if (ac > 1)
		return(1);
	if(!envp || !*envp)
		printf("error\n"); //TODO add the error handling function
	g_minishell.env = envp;
	env = init_environment(envp);
	loop(env);
	free_allocator();
	return (0);
}

