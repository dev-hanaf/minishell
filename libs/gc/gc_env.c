/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:23:42 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/08 03:25:30 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	**get_data_env(void)
{
	static t_data	*head;

	return (&head);
}

void	add_list_env(t_data *new)
{
	t_data	*tmp;

	tmp = *get_data_env();
	if (!tmp)
	{
		*get_data_env() = new;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	*tmalloc(size_t size)
{
	t_data	*node;
	void	*ptr;

	node = ft_gc_lstnew(ft_calloc(1, size));
	if (!node)
		return (NULL);
	ptr = node->ptr;
	add_list_env(node);
	return (ptr);
}

void	_free_env(void)
{
	t_data	**head;
	t_data	*temp;

	head = get_data_env();
	if (!*head)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		free((*head)->ptr);
		free(*head);
		*head = temp;
	}
	*head = NULL;
}
