/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:39:47 by ahanaf            #+#    #+#             */
/*   Updated: 2023/11/28 03:15:01 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = NULL;
	while (i <= len)
	{
		if (s[i] == (char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (ptr != NULL)
		return (ptr);
	else
		return (NULL);
}
