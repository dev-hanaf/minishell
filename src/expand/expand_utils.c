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

bool is_opend(char c , bool open)
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
		{
			return (1); // Needs expansion
		}
		if (line[i] == '$' && !ft_isalpha(line[i + 1]))
		{
			return (0); // No expansion needed
		}
		if (hold == 0 && (line[i] == '\'' || line[i] == '\"'))
		{
			hold = line[i];
		}
		else if (hold != 0 && line[i] == hold)
		{
			hold = 0;
		}
		if (hold != '\'' && line[i] == '$')
		{
			return (1); // Needs expansion
		}
		i++;
	}
	return (0); // No expansion needed
}
