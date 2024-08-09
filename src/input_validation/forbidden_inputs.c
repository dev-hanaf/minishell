#include "minishell.h"

bool forbidden_inputs(t_tokenizer *lexer)
{
	size_t 		i;
	
	i = -1;
	while(lexer->value[++i] != '\0')
	{
		if (ft_strchr(lexer->value,'\\') || ft_strchr(lexer->value,';'))
		{
			printf("syntax error:not required special character\n");
			return (true);
		}
	}
	i = -1;
	while (lexer->value[++i] != '\0')
	{
		if (lexer->value[i] == '&')
		{
			printf("syntax error:not required special character &\n");
			return (true);
		}
		if (lexer->value[i] == '(' || lexer->value[i] == ')')
		{
			printf("syntax error:non expected argument ()\n");
			return (true);
		}
	}
	return (false);
}
