/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_crud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:58:47 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/07 22:01:49 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenizer	*new_token(char *value, int type)
{
	t_tokenizer	*new;

	new = _malloc(sizeof(t_tokenizer));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tokenizer	*last_token(t_tokenizer **token)
{
	t_tokenizer	*temp;

	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	add_to_back(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*temp;

	if ((*token)->value == NULL)
	{
		*token = new;
		return ;
	}
	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	add_to_front(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*tmp;

	tmp = NULL;
	tmp = *token;
	if (!new)
		return ;
	if (tmp)
		tmp->prev = new;
	new->prev = NULL;
	new->next = tmp;
	*token = new;
}

int	stack_size(t_tokenizer **token)
{
	int			size;
	t_tokenizer	*tmp;

	if (!*token)
		return (0);
	tmp = *token;
	size = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
