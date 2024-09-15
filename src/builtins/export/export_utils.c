/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:39:26 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/14 22:47:16 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_key(char *arg, int *i, char *key)
{
	char	c[2];

	while (arg && arg[*i] && arg[*i] != '=')
	{
		ft_strcpy(c, arg[*i]);
		key = ft_strjoin(key, c);
		(*i)++;
	}
}

void	id_value(char *arg, int *i, char *value)
{
	char	c[2];

	while (arg && arg[*i])
	{
		ft_strcpy(c, arg[*i]);
		value = ft_strjoin(value, c);
		(*i)++;
	}
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
	char	*value;
	int		i;
	char	**strs;

	key = NULL;
	value = NULL;
	strs = NULL;
	i = 0;
	is_key(arg, &i, key);
	if (arg && arg[i] == '=')
		i++;
	id_value(arg, &i, value);
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
