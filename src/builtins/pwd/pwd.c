/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:13 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/13 22:12:44 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (get_ms()->pwd_pwd)
		{
			printf("%s\n", get_ms()->pwd_pwd);
		}
		else
		{
			ft_putstr_fd("pwd: error retrieving current directory: \
					getcwd: cannot access parent directories: No such file \
					or directory\n",
				2);
		}
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
