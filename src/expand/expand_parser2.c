/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:23:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 17:35:31 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char *exp)
{
	int		i;
	bool	spaces;

	spaces = false;
	i = 0;
	while (exp && exp[i])
	{
		if (is_whitespaces(exp[i]))
			spaces = true;
		i++;
	}
	return (spaces);
}

void	whitspaces_in_var(char *exp, char *line)
{
	var()->there_is_space = false;
	var()->spaces = is_space(exp);
	if (var()->spaces && (line[0] != '"'))
	{
		if (is_whitespaces(var()->exp[0]))
			var()->there_is_space = true;
		var()->spilted = ft_split_whitespaces(var()->exp, " \t\n\v\f\r");
		var()->x = 0;
		if (!var()->is_first && var()->there_is_space)
			var()->y++;
		while (var()->spilted[var()->x])
		{
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->spilted[var()->x]);
			if (var()->spilted[var()->x + 1] != NULL)
				var()->y++;
			if (var()->y == ALLOC)
				return ;
			var()->x++;
		}
	}
	else
		var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
	    var()->exp);
}
