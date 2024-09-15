/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:23:11 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 11:35:50 by ahanaf           ###   ########.fr       */
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
	if (is_whitespaces(var()->exp[0]))
		var()->there_is_space = true;
	var()->spilted = ft_split_whitespaces(var()->exp, " \t\n\v\f\r");
	var()->x = 0;
	if (!var()->is_first && var()->there_is_space)
	{
		var()->y++;
	}
}

int	splite_expanded_str(char *exp)
{
	char	*temp;
	int		len;

	len = 0;
	while (var()->spilted[var()->x])
	{
		if (end_strs())
			return (1);
		temp = ft_strjoin(var()->str[var()->y], var()->spilted[var()->x]);
		var()->str[var()->y] = temp;
		if (var()->spilted[var()->x + 1] != NULL)
			var()->y++;
		var()->x++;
	}
	if (len > 0 && is_whitespaces(exp[len - 1]))
		var()->espace_in_the_end = true;
	else
		var()->espace_in_the_end = false;
	return (0);
}

void	whitspaces_in_var(char *exp, char *line)
{
	char	*tmp;

	var()->there_is_space = false;
	var()->spaces = is_space(exp);
	if (var()->spaces && (line[0] != '"'))
	{
		is_there_is_aspace();
		if (splite_expanded_str(exp))
			return ;
	}
	else
	{
		if (var()->espace_in_the_end)
			var()->y++;
		tmp = ft_strjoin(var()->str[var()->y], var()->exp);
		var()->str[var()->y] = tmp;
	}
}

char	*expand_herdoc(t_env *env, char *line)
{
	char	**res;

	res = NULL;
	res = catch_expand(line, env, 1, 1);
	return (res[0]);
}
