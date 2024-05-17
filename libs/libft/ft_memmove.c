/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 02:08:52 by ahanaf            #+#    #+#             */
/*   Updated: 2023/11/27 17:27:59 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*c_src;
	char	*c_dest;
	size_t	i;

	if (dest == src)
		return (dest);
	c_src = (char *)src;
	c_dest = (char *)dest;
	i = 0;
	if (c_dest > c_src)
		while (n-- > 0)
			c_dest[n] = c_src[n];
	else
	{
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (dest);
}
