/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:22:07 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 11:30:55 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_escape_character(char *exp)
{
	var()->idx = 0;
	var()->jdx = 0;
	var()->len = 0;
	if (!exp)
		return (NULL);
	while (exp[var()->idx])
	{
		if (exp[var()->idx] == '"' || exp[var()->idx] == '\'')
			var()->len++;
		var()->len++;
		var()->idx++;
	}
	var()->new_exp = _malloc(sizeof(char) * (var()->len + 1));
	if (var()->new_exp == NULL)
		exiter(1, "malloc");
	var()->idx = -1;
	while (exp[++var()->idx])
	{
		if (exp[var()->idx] == '"' || exp[var()->idx] == '\'')
			var()->new_exp[var()->jdx++] = ESCAPE;
		var()->new_exp[var()->jdx] = exp[var()->idx];
		var()->jdx++;
	}
	var()->new_exp[var()->jdx] = '\0';
	return (var()->new_exp);
}

void	ft_skip(char *line, int *i)
{
	if (line[*i] && line[*i] == '$')
		(*i)++;
	else if (line[*i] && line[*i] == '?')
		(*i)++;
	else if (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	else if (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
}

void	expansion_valid(char *line, int *i, t_env **env, int flag)
{
	int		start;
	char	*y;

	start = *i;
	y = var()->str[var()->y];
	ft_skip(line, i);
	var()->exp = ft_substr(line, start, *i - start);
	var()->exp = get_env(env, var()->exp);
	var()->exp = add_escape_character(var()->exp);
	if (var()->exp)
	{
		if (flag)
		{
			y = ft_strjoin(y, var()->exp);
			var()->str[var()->y] = y;
		}
		else
			whitspaces_in_var(var()->exp, line);
	}
}

void	start_expanding(char *line, t_env *env, int flag)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && var_need_expansion(line))
		{
			var()->is_first = !var()->xxx;
			i++;
			expansion_valid(line, &i, &env, flag);
			var()->xxx++;
			continue ;
		}
		else
		{
			ft_strcpy(var()->buffer, line[i]);
			temp = ft_strjoin(var()->str[var()->y], var()->buffer);
			var()->str[var()->y] = temp;
			var()->xxx++;
		}
		if (line[i] != '\0')
			i++;
	}
}

bool	open_or_close(char *line)
{
	char	to_find;
	int		i;

	i = var()->i;
	to_find = 0;
	while (line && line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && !to_find)
		{
			to_find = line[i];
			i++;
		}
		while (line[i] && line[i] != to_find && to_find)
		{
			i++;
			var()->i = i;
		}
		if (to_find == '\'')
			return (false);
		else if (to_find == '"')
			return (true);
		if (line[i] != '\0')
			i++;
	}
	return (true);
}
