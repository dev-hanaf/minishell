/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 05:04:41 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 02:23:33 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_split	*getter(void)
{
	static t_split	data;
	return (&data);
}

void	word_count(char *str, char c)
{
	t_split	*data;

	data = getter();
	ft_bzero(data, sizeof(t_split));
	while (str && str[data->i])
	{
		while (str[data->i] == c)
			data->i++;
		if (str[data->i] && str && str[data->i] != c)
		{
			data->wc++;
			while (str[data->i] && str && str[data->i] != c)
				data->i++;
		}
	}
}

void	get_start_end(char *str, char c)
{
	t_split	*data;
	int		index;

	data = getter();
	while (str && str[data->start] && str[data->start] == c)
		data->start++;
	index = data->start;
	while (str && str[index] && str[index] != c)
	{
		data->end++;
		index++;
	}
}

char	*get_word(char *str)
{
	t_split	*data;
	int		i;

	data = getter();
	data->word = ft_allocator((sizeof(char) * (data->end + 1)), "get_word");
	if (data->word == NULL)
		return (NULL);
	i = 0;
	while (i < data->end)
	{
		data->word[i] = str[data->start + i];
		i++;
	}
	data->word[i] = 0;
	return (data->word);
}

char	**ft_split(char *s, char c)
{
	t_split	*data;

	if (!s)
		return (NULL);
	data = getter();
	word_count(s, c);
	data->str = ft_allocator((sizeof(char *) * (data->wc + 1)), "split_2d");
	if (data->str == NULL)
		return (NULL);
	while (data->j < data->wc)
	{
		get_start_end(s, c);
		data->str[data->j] = get_word(s);
		if (data->str[data->j] == NULL)
		{
			free_allocator();
			return (NULL);
		}
		data->start += data->end;
		data->end = 0;
		data->j++;
	}
	data->str[data->j] = 0;
	return (data->str);
}
