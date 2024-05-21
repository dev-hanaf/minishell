/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 02:34:34 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;


void builtin_commands(char *line)
{
	if (line[0] == 'c' && line[1] == 'd')
		_cd(line);
	else if (!ft_strncmp(line, "pwd", 3))
	{
		char *line = getenv("PWD");
		printf("%s\n", line);
		// pid_t pid = fork();
		// if (pid == 0)
		// {
		//  	char *const args[] = {"pwd", NULL};
		// 	execvp("pwd", args);
		// 	exit(EXIT_SUCCESS) ;
		// }
	}
}
/*
void _cd(char *path)
	{
		path[0] = '~'
		char *new_path = strcat(getenv(HOME), &path[i + 1]);
		if (NULL)
			getenv(HOME);
		else if (patrh == "..")
		else if (patrh == ".")
		else if (patrh == "path")
		{
			acces(path, X_OK || F_OK) == 0;
			{
				chdir(path);
			}
				
		}
		else if(path == '_')
		{
			chdir(OLD_PWD);
		}
	}
*/

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	char *line;
	t_env *test =  init_envirement(env);
	while (test)
	{
		printf("key==>%s\nvalue==>%s\n", test->key, test->value);
		test = test->next;
	}
	while (TRUE)
	{
		//handle_signals();
		g_minishell.env = env;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		// input_validation(line);
		tokenization(line);
		// builtin_commands(line /*&env  lexer*/);
		add_history(line);
		free(line);
	}
	// add_history(line);
	return (0);
}
