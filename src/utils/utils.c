/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:15:46 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/07 22:02:08 by ahanaf           ###   ########.fr       */
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
	int			i;
	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

void	free_string_array(char **arr)
{
	int				a;

	a = 0;
	while (arr[a] != 0)
	{
		free(arr[a]);
		a++;
	}
	free(arr);
}

int is_whitespaces(int c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

void ft_strcpy(char *dst, char c)
{
    *dst++ = c;
    *dst = '\0';
}
 

void print_strs(char **strs)
{
	if(!strs || !*strs)
		return;
	printf("printing strssssssssssssssss\n");
	int i=0;
	while(*strs)
	{
		printf("%d=%s\n",i++,*strs);
		strs++;
	}
}

int expand_counter(t_list *lst)
{
	if(!lst)
		return 0;
	int i = 0;
	while(lst)
	{
		char **res = catch_expand((char *)lst->content , *get_ms()->env_ld, 0, 0);
		i += ft_strlen_2d_array(res);
		lst = lst->next;
	}
	return i;
}

char **ld_to_arr_and_expand(t_list *lst)
{
	int counter = 0;
	counter = expand_counter(lst);
	if(!lst || counter == 0)
		return NULL;
	char **arr = _malloc(sizeof(char *) * (counter +  1));
	int i = 0;
	while(lst)
	{
		int j = 0;
		char **res = catch_expand((char *)lst->content , *get_ms()->env_ld, 0, 0);
		while (res[j])
		{
			arr[i] = handle_quotes(res[j]);
			i++;
			j++;
		}
		lst = lst->next;
	}
	arr[i] = NULL;
	return arr;
}
char **make_child_env(t_list *lst)
{
	int counter = 0;
	counter = expand_counter(lst);
	if(!lst || counter == 0)
		return NULL;
	char **arr = _malloc(sizeof(char *) * (counter +  1));
	int i = 0;
	while(lst)
	{
		int j = 0;
		char **res = catch_expand((char *)lst->content , *get_ms()->env_ld, 0, 0);
		while (res[j])
		{
			printf("res[j]=%s\n",res[j]);
			arr[i] = handle_quotes(res[j]);
			i++;
			j++;
		}
		lst = lst->next;
	}
	arr[i] = NULL;
	return arr;
}

