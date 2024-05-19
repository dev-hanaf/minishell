/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 00:10:17 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	if (ac != 1)
	{
		ft_putstr_fd("Accept only one argument!\n", 1);
		return (0);
	}
	/* g_minishell. */
	char *line = readline("minishell$ ");
	while (TRUE)
	{
		if (/* g_minishell. */line == NULL)
			break ;
		/*input validation*/
        /*tokeniaztion*/
		tokenization(/* g_minishell. */line);
		add_history(/* g_minishell. */line);
		free(/* g_minishell. */line);
		/* g_minishell. */line = readline("minishell$ ");
	}
	add_history(/* g_minishell. */line);
	free(/* g_minishell. */line);
	// /* g_minishell. */env = env;
	return (0);
}
