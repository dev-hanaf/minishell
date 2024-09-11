/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 07:37:10 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/11 07:37:37 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_back_expand(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*temp;

	if ((*token)->value == NULL && (*token)->type == ERROR)
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

bool	is_opend(char c, bool open)
{
	if (c == '"' && !open)
	{
		open = true;
	}
	else if (c == '"' && open)
	{
		open = false;
	}
	return (open);
}

int	needs_expansion(const char *line)
{
	int		i;
	char	hold;

	i = 0;
	hold = 0;
	while (line && line[i])
	{
		if (line[0] == '$' && line[1] == '\0')
			return (0);
		if (hold == 0 && (line[i] == '\'' || line[i] == '\"'))
			hold = line[i];
		else if (hold != 0 && line[i] == hold)
			hold = 0;
		if (hold != '\'' && line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	var_need_expansion(const char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i])
			{
				if (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?'
					|| line[i] == '$')
					return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

t_tokenizer	*new_token_expand(char *value, int type, bool expanded)
{
	t_tokenizer	*new;

	new = _malloc(sizeof(t_tokenizer));
	if (!new)
		return (NULL);
	new->value = value;
	new->expanded = expanded;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
