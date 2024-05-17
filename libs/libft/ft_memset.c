/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:17:49 by ahanaf            #+#    #+#             */
/*   Updated: 2023/11/27 18:05:34 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = (unsigned char)c;
		n--;
	}
	return (s);
}
