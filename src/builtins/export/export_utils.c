/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:39:26 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 08:50:30 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_key(char *arg, int *i)
{
	char	c[2];
	char	*key;

	key = NULL;
	while (arg && arg[*i] && arg[*i] != '=')
	{
		ft_strcpy(c, arg[*i]);
		key = ft_strjoin(key, c);
		(*i)++;
	}
	return (key);
}

char	*is_value(char *arg, int *i)
{
	char	c[2];
	char	*value;

	value = NULL;
	while (arg && arg[*i])
	{
		ft_strcpy(c, arg[*i]);
		value = ft_strjoin(value, c);
		(*i)++;
	}
	return (value);
}

void	process_args_wraper(char **strs)
{
	while (strs && *strs)
	{
		if (!process_args(*strs))
		{
			update_status(1);
			return ;
		}
		strs++;
	}
}

void	process_nodes(t_env *env, char *arg)
{
	char	*key;
	int		i;
	char	**strs;

	key = NULL;
	strs = NULL;
	i = 0;
	key = is_key(arg, &i);
	if (arg && arg[i] == '=')
		i++;
	if (!key || (key[0] == '\0' || ft_strchr(key, '$')))
		strs = expand(env, arg);
	else
	{
		strs = catch_expand(arg, env, 1, 0);
		if (strs && strs[0])
			strs[0] = handle_quotes(strs[0]);
	}
	process_args_wraper(strs);
}
