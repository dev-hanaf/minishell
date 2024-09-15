/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:23:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/14 11:42:09 by ahanaf           ###   ########.fr       */
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

void	is_there_is_aspace(void)
{
	//TODO export a="a b" ==> cmd:$a"$a" ==> [a][ba b]
	//TODO export a="a b " ==> cmd:$a"$a" ==> [a][b][ab]
	if (is_whitespaces(var()->exp[0]))
		var()->there_is_space = true;
	var()->spilted = ft_split_whitespaces(var()->exp, " \t\n\v\f\r");
	var()->x = 0;
	if (!var()->is_first && var()->there_is_space)
		var()->y++;
}

void	whitspaces_in_var(char *exp, char *line)
{
	var()->there_is_space = false;
	var()->spaces = is_space(exp);
	if (var()->spaces && (line[0] != '"'))
	{
		is_there_is_aspace();
		while (var()->spilted[var()->x])
		{
			if (end_strs())
				return;
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y], var()->spilted[var()->x]);
			if (var()->spilted[var()->x + 1] != NULL)
				var()->y++;
			var()->x++;
		}
	}
	else
		var()->str[var()->y] = ft_strjoin(var()->str[var()->y], var()->exp);
}
