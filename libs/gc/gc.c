/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:23:42 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/08 03:24:54 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	**get_data(void)
{
	static t_data	*head;

	return (&head);
}

void	add_list(t_data *new)
{
	t_data	*tmp;

	tmp = *get_data();
	if (!tmp)
	{
		*get_data() = new;
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

void	*_malloc(size_t size)
{
	t_data	*node;
	void	*ptr;

	node = ft_gc_lstnew(ft_calloc(1, size));
	if (!node)
		return (NULL);
	ptr = node->ptr;
	add_list(node);
	return (ptr);
}

void	_free(void)
{
	t_data	**head;
	t_data	*temp;

	head = get_data();
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
