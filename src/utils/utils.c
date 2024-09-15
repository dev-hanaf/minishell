/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:15:46 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:37:07 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_counter(t_list *lst)
{
	int		i;
	char	**res;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		res = catch_expand((char *)lst->content, *get_ms()->env_ld, 0, 0);
		i += ft_strlen_2d_array(res);
		lst = lst->next;
	}
	return (i);
}

char	**ld_to_arr_and_expand(t_list *lst)
{
	int		counter;
	char	**arr;
	int		i;
	int		j;
	char	**res;

	counter = 0;
	counter = expand_counter(lst);
	if (!lst || counter == 0)
		return (NULL);
	arr = _malloc(sizeof(char *) * (counter + 1));
	i = 0;
	while (lst)
	{
		j = 0;
		res = catch_expand((char *)lst->content, *get_ms()->env_ld, 0, 0);
		while (res[j])
			arr[i++] = handle_quotes(res[j++]);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**make_child_env(t_list *lst)
{
	int		counter;
	char	**arr;
	int		i;
	int		j;
	char	**res;

	counter = 0;
	counter = expand_counter(lst);
	if (!lst || counter == 0)
		return (NULL);
	arr = _malloc(sizeof(char *) * (counter + 1));
	i = 0;
	while (lst)
	{
		j = 0;
		res = catch_expand((char *)lst->content, *get_ms()->env_ld, 0, 0);
		while (res[j])
			arr[i++] = handle_quotes(res[j++]);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*remove_escape_character(char *str)
{
	int		i;
	int		len;
	int		j;
	char	*res;

	if (!str)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != ESCAPE)
			len++;
	}
	res = _malloc(sizeof(char) * (len + 1));
	if (!res)
		exiter(1, "malloc");
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ESCAPE)
			res[j++] = str[i];
	}
	return (res);
}
