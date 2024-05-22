/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/22 06:55:27 by ahanaf           ###   ########.fr       */
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
void builtin_commands(t_env **env, char *line)
{
	if (!*env || !line || !env)
		return;
	// char *cwd;
	t_tokenizer *lexer = tokenization(line);
	t_tokenizer *token;
	// printf(RED"lexer %s\n"NC, token->value);
    // printf("char path[0]--> |%c|\n", token->value[0]);

	// if (token && ft_strncmp(token->value, "..", 2) == 0 && ft_strlen(token->value) == 2 )
	// 	_cd(token->value, env);
	token = get_token(lexer, "cd");
	if (token)
		_cd(token->value,env);
/* 	else if (!token)    //this condition to means that the input is cd --> so should change derictory to HOME
		_cd(NULL,env); */
	// token = get_token(lexer, "pwd");
	// if (token && ft_strncmp(token->value, "pwd", 3) == 0 && ft_strlen(token->value) == 3 )
	_pwd();
	token = get_token(lexer, "unset");
	if (token/*  && ft_strncmp(token->value, "unset", 5) == 0 && ft_strlen(token->value) == 5 */)
	{
		_unset(env, "LANG");
/* 		display_envirment(env);
		printf(ON_YELLOW"\n-----------------------------------------------------------------------------------------------------------------------------\n"NC);
		remove_env_element(env, "LANG");
		display_envirment(env); */

	}

}



void loop(t_env *env)
{
	char *line;
	char *prompt;
	while (TRUE)
	{
		//handle_signals();
		prompt = ft_strjoin(get_env(&env, "PWD"), "$ ");
		line = readline(prompt);
		if (line == NULL)
			break ;
		// input_validation(line);
		builtin_commands(&env, line);
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
	env = init_envirement(envp);
	loop(env);
	free_allocator();
	return (0);
}

/*	
while (env)
	{
		printf("key==>%s\nvalue==>%s\n", env->key, env->value);
		env = env->next;
	}
*/

/*
		// printf(YELLOW"PWD-->%s\n"NC, get_env(env, "PWD"));
		// printf(YELLOW"OLDPWD-->%s\n"NC, get_env(env, "OLDPWD"));
		// change_env(env, "OLDPWD", get_env(env, "PWD"));
		// chdir("../");
		// cwd = getcwd(NULL, 0);
		// printf(RED"cwd %s\n"NC,cwd);
		// change_env(env, "PWD", cwd);
		// free(cwd);
		
		
		// printf(YELLOW"get env %s\n", get_env(env, "OLDPWD"));
		// printf(ON_GREEN"OLDPWD %s\n"NC, get_env(env, "OLDPWD"));
		// printf(ON_GREEN"PWD %s\n"NC, get_env(env, "PWD"));
		// change_env(env, "OLDPWD", get_env(env, "PWD"));
		// printf(ON_BLUE"OLDPWD %s\n"NC, get_env(env, "OLDPWD"));
		// printf(ON_BLUE"PWD %s\n"NC, get_env(env, "PWD"));
		
		// printf(ON_YELLOW"PWD %s\n"NC, getenv("PWD"));

		// chdir("../");
		// printf(GREEN"env %s\n", getenv("PWD"));
		// change_env(env, "PWD", getenv("PWD"));
*/