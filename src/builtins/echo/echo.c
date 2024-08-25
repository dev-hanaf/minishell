/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:53:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/13 13:05:58 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	len = 0;
	// while (*s1 && ft_strchr(set, *s1))
	// 	s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	res = ft_allocator(len + 1, "strtrim");
	if (!res)
		return (0);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}

void _echo(char **argumentes)
{
    int i;
    bool lock;
    bool flag;
    bool ltrim;
    int j;
    char *res = NULL;
    flag = false;
    lock = false;
    ltrim = true;
    i = 0;
    while(argumentes && argumentes[i])
    {
        if (!ft_strncmp(argumentes[i], "-n", 2) && !flag)
        {
            j = 1;        
            while (argumentes[i][j] && argumentes[i][j] == 'n')
                j++;
            if (argumentes[i][j] == '\0')
                lock = true;
            else
            {
                res = ft_strjoin(res, argumentes[i]);
                ltrim = false;
            }
        }
        else
        {
            res = ft_strjoin(res, argumentes[i]);
            flag = true;
        }
        // if (argumentes[i + 1] && argumentes[i + 1] != NULL)
        //     printf(" ");
        i++;
    }
    if (ltrim)
        res = ft_strtrim(res, " ");
    else
        res = ft_strrtrim(res, " ");
    printf("%s", res);
    if (!lock)
        printf("\n");
}

