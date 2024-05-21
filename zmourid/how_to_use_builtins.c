/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_to_use_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:37:42 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 19:38:01 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (temp);
}
void builtin_commands(t_env **env, char *line)
{
	if (!*env || !line || !env)
		return;
	char *cwd;
	t_tokenizer *lexer = tokenization(line);
	t_tokenizer *token = get_token(lexer, "cd");
	// printf(RED"lexer %s\n"NC, token->value);
	if (token && ft_strncmp(token->value, "..", 2) == 0 && ft_strlen(token->value) == 2 )
	{
		printf(YELLOW"PWD-->%s\n"NC, get_env(env, "PWD"));
		printf(YELLOW"OLDPWD-->%s\n"NC, get_env(env, "OLDPWD"));
		change_env(env, "OLDPWD", get_env(env, "PWD"));
		chdir("../");
		cwd = getcwd(NULL, 0);
		printf(RED"cwd %s\n"NC,cwd);
		change_env(env, "PWD", cwd);
		
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
	}
	token = get_token(lexer, "pwd");
	if (token && ft_strncmp(token->value, "pwd", 3) == 0 /* && ft_strlen(token->value) == 3 */)
	{
		char *line = get_env(env, "PWD");
		printf("%s\n", line);		
	}

}