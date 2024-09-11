#include "minishell.h"

bool is_next_a_word(t_tokenizer *lexer)
{
    if (lexer->next != NULL)
    {
        if (lexer->next->type != WORD)
        {
            printf("syntax error:next it's not a word\n");
            return (true);
        }
    }
    else
    {
        printf("syntax error:near unexpected token `newline'\n");
        return (true);
    }
    return (false);
}

bool	rederections_check(t_tokenizer *lexer)
{
	if (lexer->type == REDIR_IN)
	{
        return (is_next_a_word(lexer));
	}
	else if (lexer->type == REDIR_OUT)
	{
        return (is_next_a_word(lexer));
	}
	else if (lexer->type == APPEND)
	{
        return (is_next_a_word(lexer));
	}
	else if (lexer->type == HERDOC)
	{
		//TODO count 16 herdoc and remove it from tokenizer
        return (is_next_a_word(lexer));
	}
	return (false);
}