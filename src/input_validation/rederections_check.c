#include "minishell.h"


int is_next_a_word(t_tokenizer *lexer)
{
    if (lexer->next)
    {
        if (lexer->next->type != WORD)
        {
            printf("syntax error\n");
            return (-1);
        }
    }
    else
    {
        printf("syntax error\n");
        return (-1);
    }
    return (0);
}



int	rederections_check(t_tokenizer *lexer)
{
	if (ft_strncmp(lexer->value, ">", 1) == 0 && ft_strlen(lexer->value) == 1)
	{
        is_next_a_word(lexer);
	}
	else if (ft_strncmp(lexer->value, "<", 1) == 0 && ft_strlen(lexer->value) == 1)
	{
        is_next_a_word(lexer);

	}
	else if (ft_strncmp(lexer->value, ">>", 2) == 0 && ft_strlen(lexer->value) == 2)
	{
        is_next_a_word(lexer);

	}
	else if (ft_strncmp(lexer->value, "<<", 2) == 0 && ft_strlen(lexer->value) == 2)
	{
        is_next_a_word(lexer);

	}
	return (0);
}