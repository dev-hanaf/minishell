/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 18:40:36 by ahanaf           ###   ########.fr       */
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

/* It is not required to use uppercase, but often considered as good practice.
	Enum is short for "enumerations", which means "specifically listed".	
The typedef is a keyword that is used to provide existing data types with a new name.The C typedef keyword is used to redefine the name of already existing data types.
*/
typedef enum s_bool
{
	FALSE,
	TRUE = 60
}						t_bool;

typedef enum s_type
{
	ERROR = 0,
	WORD = 1,
	PIPE = 2,
	HERDOC = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	APPEND = 6
}						t_type;

typedef struct s_tokenizer
{
	struct s_tokenizer	*prev;
	char				*value;
	int					type;
	struct s_tokenizer	*next;

}						t_tokenizer;

typedef struct s_minishell
{
	char				**env;
	char				*line;
	int					status;
}						t_minishell;

t_minishell	g_minishell;

//input_validation
void input_validation(char *line);

// tokenization
t_tokenizer				*new_token(char *value, int type);
t_tokenizer				*last_token(t_tokenizer **token);
void					add_to_back(t_tokenizer **token, t_tokenizer *new);
void					add_to_front(t_tokenizer **token, t_tokenizer *new);
int						stack_size(t_tokenizer **token);
void					tokenization(char *line);
void					display_tokens(t_tokenizer *tokens);
//builtins



#endif