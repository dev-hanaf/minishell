/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:47:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:32:09 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(int *is_ok, size_t *result, int *signe, int *i)
{
	*is_ok = 0;
	*result = 0;
	*signe = 1;
	*i = 0;
}

int	is_handlequotes(char q, int i, char *line)
{
	if (line[i] && line[i] == q && ((i != 0 && line[i - 1] != ESCAPE)
			|| i == 0))
		return (1);
	return (0);
}

void	initial_vars(void)
{
	ft_bzero(var(), sizeof(t_expand));
	var()->str = _malloc(ALLOC * sizeof(char *));
	if (!var()->str)
	{
		perror("malloc");
		return ;
	}
	while (var()->i < ALLOC)
		var()->str[(var()->i)++] = NULL;
	var()->i = 0;
}

int	end_strs(void)
{
	if (var()->y == ALLOC)
	{
		var()->str[var()->y] = NULL;
		return (1);
	}
	return (0);
}

void	exiter(int e, char *str)
{
	if (str)
		perror(str);
	_free();
	_free_env();
	exit(e);
}
