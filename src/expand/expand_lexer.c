#include "minishell.h"

void	expanded(t_tokenizer **head, char **res, t_tokenizer *lexer)
{
	t_tokenizer	*new;
	int			i;

	i = 0;
	if (!res[i])
	{
		new = new_token_expand(NULL, WORD, true);
		add_to_back_expand(head, new);
	}
	if (ft_strlen_2d_array(res) == 1)
	{
		new = new_token_expand(handle_quotes(res[i]), lexer->type, true);
		add_to_back_expand(head, new);
	}
	else
	{
		while (res[i])
		{
			new = new_token_expand(handle_quotes(res[i]), WORD, true);
			add_to_back_expand(head, new);
			i++;
		}
	}
}

void	expansion_controller(t_env *env, t_tokenizer *lexer, t_tokenizer **head)
{
	char	**res;

	res = catch_expand(lexer->value, env, 0, 0);
	expanded(head, res, lexer);
}

t_tokenizer	*expand_lexer(t_env *env, t_tokenizer **lexer)
{
	t_tokenizer	*head;
	t_tokenizer	*new;

	head = new_token_expand(NULL, 0, false);
	while (*lexer)
	{
		if ((*lexer)->prev && (*lexer)->prev->type == HERDOC)
		{
			new = new_token_expand((*lexer)->value, (*lexer)->type, false);
			add_to_back_expand(&head, new);
		}
		else
			expansion_controller(env, *lexer, &head);
		*lexer = (*lexer)->next;
	}
	return (head);
}
