/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:53:58 by ahanaf            #+#    #+#             */
/*   Updated: 2023/11/27 17:18:32 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	lenght_size(long n)
{
	long	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	num;
	long	size;
	char	*str;

	num = n;
	size = lenght_size(num);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	str[size] = '\0';
	size--;
	while (size >= 0)
	{
		if (str[0] == '-' && size == 0)
			return (str);
		str[size] = (num % 10) + 48;
		num /= 10;
		size--;
	}
	return (str);
}
