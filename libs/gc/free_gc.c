/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 07:24:14 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/10 07:25:48 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	recursive_free(t_data *list)
{
	t_data	*tmp;

	free(list->ptr);
	tmp = list->next;
	if (list->index != 0)
		free(list);
	if (tmp == NULL)
		return ;
	recursive_free(tmp);
}
