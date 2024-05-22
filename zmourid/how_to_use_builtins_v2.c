#include "minishell.h"

t_tokenizer *get_token(t_tokenizer *lexer, char *word)
{
	t_tokenizer *temp;
	temp = lexer;
	while (temp)
	{
		if (ft_strncmp(temp->value, word, 2) == 0 )
		{
			if (temp->next != NULL)
				return(temp->next);
			break;
		}
		temp = temp->next;
	}
	return (NULL);
}
void builtin_commands(t_env **env, char *line)
{
	if (!*env || !line || !env)
		return;
	// char *cwd;
	t_tokenizer *lexer = tokenization(line);
	t_tokenizer *token;
	// printf(RED"lexer %s\n"NC, token->value);
    // printf("char path[0]--> |%c|\n", token->value[0]);

	// if (token && ft_strncmp(token->value, "..", 2) == 0 && ft_strlen(token->value) == 2 )
	// 	_cd(token->value, env);
	token = get_token(lexer, "cd");
	if (token)
		_cd(token->value,env);
/* 	else if (!token)    //this condition to means that the input is cd --> so should change derictory to HOME
		_cd(NULL,env); */
	// token = get_token(lexer, "pwd");
	// if (token && ft_strncmp(token->value, "pwd", 3) == 0 && ft_strlen(token->value) == 3 )
	_pwd();
	token = get_token(lexer, "unset");
	if (token/*  && ft_strncmp(token->value, "unset", 5) == 0 && ft_strlen(token->value) == 5 */)
	{
		_unset(env, "LANG");
/* 		display_envirment(env);
		printf(ON_YELLOW"\n-----------------------------------------------------------------------------------------------------------------------------\n"NC);
		remove_env_element(env, "LANG");
		display_envirment(env); */

	}

}