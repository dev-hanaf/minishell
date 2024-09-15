/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:47 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:48 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir_to_cmd(t_cmd *cmd, t_tokenizer **tokens)
{
	t_rdr	*tmp_rdr;

	tmp_rdr = NULL;
	tmp_rdr = ft_redirnew((*tokens)->next->value, (*tokens)->type);
	ft_rdraddback(&cmd->redir, tmp_rdr);
	*tokens = (*tokens)->next->next;
}

int	check_redir(t_tokenizer *tokens)
{
	if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
		|| tokens->type == HERDOC || tokens->type == APPEND)
		return (1);
	return (0);
}

t_cmd	*parse_cmds(t_tokenizer *tokens, t_cmd *curr_cmd)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	curr_cmd = cmd;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			curr_cmd = new_cmd();
			add_to_back_cmd(&cmd, curr_cmd);
			tokens = tokens->next;
			continue ;
		}
		if (check_redir(tokens))
		{
			add_redir_to_cmd(curr_cmd, &tokens);
			continue ;
		}
		ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
		tokens = tokens->next;
	}
	get_ms()->cmd = cmd;
	if (handle_heredoc(cmd))
		return (NULL);
	return (cmd);
}
