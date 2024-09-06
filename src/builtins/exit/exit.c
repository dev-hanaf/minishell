/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:16:00 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 07:22:43 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO handle these cases 
void    __exit(char **args)
{
	int num;
	if(!args)
	{
		ft_putstr_fd("exit\n",2);
		exit(0);
	}
	if(args[1] == NULL)
		num = 0;
	else if(args[2] != NULL)
	{
		ft_putstr_fd("exit\n",2);
		ft_putstr_fd("exit: too many arguments\n",2);
		return ;
	}
	else
	{
		num = ft_atoi(args[1]);
		if(num == 0 && ft_strncmp(args[1],"0",1) != 0)
		{
			ft_putstr_fd("exit\n",2);
			ft_putstr_fd("exit: numeric argument required\n",2);
			return ;
		}
	}
	ft_putstr_fd("exit\n",2);
	exit(num);
}
