/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 07:37:57 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 21:47:48 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pid(void)
{
	int	pid;

	pid = fork();
	if (pid == CHILD)
	{
		clean_exit(0);
	}
	wait(0);
	return (pid - 2);
}

int	valid_expansion_variable(char c)
{
	if (c == '?')
		return (1);
	if (c == '$')
		return (1);
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	counter(char *str, char *seps)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str && str[i] && seps)
	{
		while (str[i] && ft_strchr(seps, str[i]))
			i++;
		if (str && str[i] && !ft_strchr(seps, str[i]))
		{
			counter++;
			while (str && str[i] && !ft_strchr(seps, str[i]))
				i++;
		}
	}
	return (counter);
}

void	start_end(char *str, char *seps, int *start, int *end)
{
	int	index;

	while (str && str[*start] && ft_strchr(seps, str[*start]))
		(*start)++;
	index = *start;
	while (str && str[index] && !ft_strchr(seps, str[index]))
	{
		(*end)++;
		index++;
	}
}

char	**ft_split_whitespaces(char *str, char *seps)
{
	int		i;
	char	**res;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	res = _malloc(sizeof(char *) * (counter(str, seps) + 1));
	if (!res)
		return (NULL);
	while (i < counter(str, seps))
	{
		start_end(str, seps, &start, &end);
		res[i] = ft_substr(str, start, (start + end) - start);
		start += end;
		end = 0;
		i++;
	}
	res[i] = NULL;
	return (res);
}
