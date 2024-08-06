#include "minishell.h"

bool pipes_check(t_tokenizer *lexer)
{
	if (lexer->type == PIPE)
	{
		if (lexer->prev == NULL || lexer->next == NULL)
		{
			printf("syntax error near unexpected token `|'\n");
			return (true);
		}
		else if (lexer->prev == NULL && lexer->next->type == PIPE)
		{
			printf("syntax error near unexpected token `||'\n");
			return (true);
		}
		else if (lexer->prev->type != WORD)
		{
			printf("syntax error: prev it's not a word\n");
			return (true);
		}
	}
	return (false);
}
