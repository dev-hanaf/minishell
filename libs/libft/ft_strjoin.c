/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 01:43:42 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/12 02:06:26 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;//TODO make a safer strjoin
	size_t	i;
	size_t	j;

	if(!s1 && s2)
	   return ft_strdup(s2);
	if(!s2 && s1)
	   return ft_strdup(s2);
	if (s2 == NULL)
	{
		s2 = ft_allocator(sizeof(char), "s2");
		if (!s2)
			return (NULL);
		s2[0] = '\0';
	}
	if (s1 == NULL)
	{
		s1 = ft_allocator(sizeof(char), "s1");
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = ft_allocator((ft_strlen(s1) + ft_strlen(s2) + 1), "join");
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
