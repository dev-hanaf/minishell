/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:53:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/08 06:01:38 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		_echo(char **argumentes)
{
    int i;
    bool lock;
    bool flag;
    int j;
    flag = false;
    lock = false;
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
               ft_putstr_fd(argumentes[i],1);
                flag = true;
                if (argumentes[i + 1] && argumentes[i + 1] != NULL)
                ft_putstr_fd(" ",1);
            }
        }
        else
        {
           ft_putstr_fd(argumentes[i],1);
            flag = true;
        if (argumentes[i + 1] && argumentes[i + 1] != NULL)
            ft_putstr_fd(" ",1);
        }
        i++;
    }
    if (!lock)
	{
        ft_putstr_fd("\n",1);
	}
	return 0;
}

