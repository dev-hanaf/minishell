#include "minishell.h"

int forbidden_inputs(t_tokenizer *lexer)
{
	char 		*forbidden;
	size_t 		i;
	forbidden = "()&|;";
	i = 0;
	if (lexer->value[0] == '\'' || lexer->value[0] == '"')
		return (0);
	while (forbidden[i]) 
	{
		if (ft_strchr(lexer->value, (int)forbidden[i]))
		{
			printf("syntax error\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
