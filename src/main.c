/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:40:45 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/14 23:40:55 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*cwd;

	(void)av;
	if (ac > 1)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("shell-init: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: "\
		"No such file or directory\n", 2);
	}
	free(cwd);
	init_minishell(envp);
	loop();
	_free_env();
	return (0);
}
