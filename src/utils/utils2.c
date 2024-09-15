/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:46:12 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:23:52 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] == str2[i]) && str1[i] && str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_strlen_2d_array(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	is_whitespaces(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	ft_strcpy(char *dst, char c)
{
	*dst++ = c;
	*dst = '\0';
}

void	clean_exit(int e)
{
	close_heredoc(get_ms()->cmd);
	_free();
	_free_env();
	exit(e);
}
