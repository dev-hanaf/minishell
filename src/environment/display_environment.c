/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:55:40 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 06:16:34 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_environment(t_env **env)
{
	t_env	*temp;

	if (!*env)
		return ;
	temp = *env;
	while (temp)
	{
		printf("KEY: \033[0;36m %-20s \033[0m |\t \
			VALUE: \033[0;35m %-18s \033[0m \n", temp->key,
			temp->value);
		printf("--------------------------------------------------\n");
		temp = temp->next;
	}
}
