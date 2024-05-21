/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/21 02:34:15 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
# include "colors.h"

/* It is not required to use uppercase, but often considered as good practice.
	Enum is short for "enumerations", which means "specifically listed".	
The typedef is a keyword that is used to provide existing data types with a new name.The C typedef keyword is used to redefine the name of already existing data types.
*/
enum s_bool
{
	FALSE,
	TRUE = 60
};

enum s_type
{
	ERROR = 0,
	WORD = 1,
	PIPE = 2,
	HERDOC = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	APPEND = 6
};

typedef struct s_tokenizer
{
	struct s_tokenizer	*prev;
	char				*value;
	int					type;
	struct s_tokenizer	*next;

}						t_tokenizer;

typedef struct s_env
{
	struct s_env	*next;
	char		 	*key;
	char 			*value;
	struct s_env	*prev;
}				t_env;

typedef struct s_minishell
{
	char				**env;
	char				*line;
	int					status;
}						t_minishell;

extern t_minishell	g_minishell;

/*----------------------------- Input Validation --------------------------*/
void input_validation(char *line);

/*----------------------------- Syntax Analysis --------------------------*/
t_tokenizer				*new_token(char *value, int type);
t_tokenizer				*last_token(t_tokenizer **token);
void					add_to_back(t_tokenizer **token, t_tokenizer *new);
void					add_to_front(t_tokenizer **token, t_tokenizer *new);
int						stack_size(t_tokenizer **token);
void					tokenization(char *line);
void					display_tokens(t_tokenizer *tokens);

/*----------------------------- Built-in --------------------------*/
void _cd(char *cmd);

/*----------------------------- Initilize Envirement --------------------------*/
t_env	*new_env(char *key, char *value);
t_env	*last_env(t_env **env);
void	add_to_back_env(t_env **env, t_env *new);
void	add_to_front_env(t_env **env, t_env *new);
int		stack_size_env(t_env **env);
t_env 	*init_envirement(char **env);

#endif