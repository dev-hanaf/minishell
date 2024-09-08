/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:20:14 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/08 03:25:16 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
#include "limits.h"


typedef struct s_data
{
	void			*ptr;
	struct s_data	*next;
}					t_data;


t_data				*ft_gc_lstnew(void *ptr);
void				*tmalloc(size_t size);
void				*_malloc(size_t size);
void				_free(void);
void				_free_env(void);
void				*ft_calloc(size_t nmemb, size_t size);
#endif