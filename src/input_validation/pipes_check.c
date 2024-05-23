#include "minishell.h"

int pipes_check(t_tokenizer *lexer)
{
	if (ft_strncmp(lexer->value, "|", 1) == 0 && ft_strlen(lexer->value) == 1)
	{
		if (lexer->prev == NULL || lexer->next == NULL)
		{
			printf("syntax error\n");
			return (-1);
		}
		else if (lexer->prev == NULL && lexer->next->type == PIPE)
		{
			printf("syntax error\n");
			return (-1);
		}
		else if (lexer->prev->type != WORD)
		{
			printf("syntax error\n");
			return (-1);
		}
	}
	return (0);
}
