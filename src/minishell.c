/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 18:40:21 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;


int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;	
	if (ac != 1)
	{
		ft_putstr_fd("Accept only one argument!\n", 1);
		return (0);
	}
	char *line;
	while (TRUE)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		/*input validation*/
		input_validation(line);
        /*tokeniaztion*/
		tokenization(line);
		add_history(line);
		free(line);
	}
	add_history(line);
	return (0);
}
