/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:07:32 by ahanaf            #+#    #+#             */
/*   Updated: 2023/11/28 02:30:53 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	len = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}

/*int main()
{
    char *s1 = "!,,'hello world,!'";
    
    char *set = "!',";

    printf("%s\n",ft_strtrim(s1,set));
}*/