/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:36 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:37 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*newcmd;

	newcmd = (t_cmd *)_malloc(sizeof(t_cmd));
	if (!newcmd)
		return (NULL);
	newcmd->args = NULL;
	newcmd->next = NULL;
	newcmd->redir = NULL;
	newcmd->heredoc = NULL;
	newcmd->hrdc_fd = -1;
	return (newcmd);
}

void	add_to_back_cmd(t_cmd **head, t_cmd *newCmd)
{
	t_cmd	*temp;

	if (*head == NULL)
	{
		*head = newCmd;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newCmd;
	}
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	cmd_nbr(t_cmd *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
