/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenz.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:06:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 16:50:12 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_token_type_name(int type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "ERROR";
	token_type_names[1] = "WORD";
	token_type_names[2] = "PIPE";
	token_type_names[3] = "HERDOC";
	token_type_names[4] = "REDIR_IN";
	token_type_names[5] = "REDIR_OUT";
	token_type_names[6] = "APPEND";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

char	*bool_ret(bool type)
{
	if (type)
		return ("TRUE");
	return ("FALSE");
}

void	display_tokens(t_tokenizer *tokens)
{
	t_tokenizer	*token;

	token = tokens;
	while (token)
	{
		printf("Expanded : %s\t", bool_ret(token->expanded));
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
			token->value,
			get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}
