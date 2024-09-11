/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:53:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 05:47:57 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newline_n(char **argumentes, int i, bool *lock, bool *flag)
{
	int	j;

	j = 1;
	while (argumentes[i][j] && argumentes[i][j] == 'n')
		j++;
	if (argumentes[i][j] == '\0')
		*lock = true;
	else
	{
		ft_putstr_fd(argumentes[i], 1);
		*flag = true;
		if (argumentes[i + 1] && argumentes[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
}

int	_echo(char **argumentes)
{
	int		i;
	bool	lock;
	bool	flag;

	flag = false;
	lock = false;
	i = 0;
	while (argumentes && argumentes[i])
	{
		if (!ft_strncmp(argumentes[i], "-n", 2) && !flag)
			newline_n(argumentes, i, &lock, &flag);
		else
		{
			ft_putstr_fd(argumentes[i], 1);
			flag = true;
			if (argumentes[i + 1] && argumentes[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (!lock)
		ft_putstr_fd("\n", 1);
	return (0);
}
