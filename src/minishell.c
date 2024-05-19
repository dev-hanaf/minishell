/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 09:43:24 by ahanaf           ###   ########.fr       */
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
	char *line = readline("minishell$ ");
	while (TRUE)
	{
		if (line == NULL)
			break ;
		/*input validation*/
		input_validation(line);
        /*tokeniaztion*/
		tokenization(line);
		add_history(line);
		free(line);
		line = readline("minishell$ ");
	}
	add_history(line);
	free(line);
	return (0);
}
