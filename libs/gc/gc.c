/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:23:42 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/21 03:00:05 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	*get_data(void)
{
	static t_data	head;

	return (&head);
}

t_data	*ft_lstnew(size_t size, void *ptr, char *description)
{
	t_data		*node;
	static int	index;

	if (!ptr)
		return (NULL);
	node = (t_data *)malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->size = size;
	node->ptr = ptr;
	node->index = index;
	node->description = description;
	node->next = NULL;
	index++;
	return (node);
}

void	add_list(t_data *new)
{
	t_data	*tmp;

	tmp = get_data();
	while (tmp)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	*ft_allocator(size_t size, char *description)
{
	t_data	*node;
	void	*ptr;

	node = ft_lstnew(size, malloc(size), description);
	if (!node)
		return (NULL);
	ptr = node->ptr;
	if (get_data()->description == NULL)
	{
		get_data()->description = description;
		get_data()->size = size;
		get_data()->ptr = node->ptr;
		get_data()->next = NULL;
		free(node);
	}
	else
		add_list(node);
	return (ptr);
}

void	free_allocator(void)
{
	recursive_free(get_data());
}
