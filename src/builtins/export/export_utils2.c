/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:53:48 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/16 11:49:31 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	str_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (ft_strchr(str, '=') && str[i] == '+' && str[i + 1] == '=')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	fill_key_value(char *str, char **key, char **value, int flag)
{
	if (ft_strchr(str, '='))
	{
		*value = ft_strdup_env(ft_strchr(str, '=') + 1);
		*key = ft_substr(str, 0, ft_strchr(str, '=') - str - flag);
		return ;
	}
	*key = str;
	*value = NULL;
}

void	make_and_add(char *key, char *value, int concat)
{
	t_env	*node;

	key = ft_strdup_env(key);
	value = ft_strdup_env(value);
	node = get_env_ld(get_ms()->env_ld, key);
	if (!node)
	{
		add_to_back_env(get_ms()->env_ld, new_env(key, value));
		return ;
	}
	if (concat)
		value = ft_strjoin_env(node->value, value);
	if (node)
	{
		if (value)
			node->value = value;
		return ;
	}
	add_to_back_env(get_ms()->env_ld, new_env(key, value));
}

int	process_args(char *str)
{
	char	*key;
	char	*value;
	int		flag;

	key = NULL;
	value = NULL;
	flag = 1;
	flag = str_is_valid(str);
	if (!str)
		return (0);
	if (flag == 0)
	{
		ft_putstr_fd("ms: export: `%s': not a valid identifier\n", 2);
		ft_putstr_fd(str, 2);
		update_status(1);
		return (0);
	}
	else
	{
		fill_key_value(str, &key, &value, flag - 1);
		make_and_add(key, value, flag - 1);
	}
	return (1);
}
