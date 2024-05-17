/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:20:14 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/10 07:24:52 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void			*ptr;
	size_t			size;
	int				index;
	char			*description;
	struct s_data	*next;
}					t_data;

void				recursive_free(t_data *list);
void				*ft_allocator(size_t size, char *description);
void				free_allocator(void);

#endif