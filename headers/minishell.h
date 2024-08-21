/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/18 05:21:22 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "header.h"
# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

/* It is not required to use uppercase, but often considered as good practice.
	Enum is short for "enumerations", which means "specifically listed".	
The typedef is a keyword that is used to provide existing data types with a new name.The C typedef keyword is used to redefine the name of already existing data types.
*/

enum					e_type
{
	ERROR,
	WORD,
	PIPE,
	HERDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND
};
# define WRITE 1
# define READ 0
# define CHILD 0

typedef struct s_tokenizer
{
	struct s_tokenizer	*prev;
	char				*value;
	int					type;
	struct s_tokenizer	*next;

}						t_tokenizer;

typedef struct s_env
{
	struct s_env		*next;
	char				*key;
	char				*value;
	struct s_env		*prev;
}						t_env;

typedef struct s_minishell
{
	char 				*prompt;
	char				**env;
	char				*line;
	int					status;
}						t_minishell;

extern t_minishell		g_minishell;

// TODO replace the lists in t_cmd by this 
typedef struct s_rdr
{
    t_list *redir;
    int type;
    struct s_rdr *next;
} t_rdr;
typedef struct s_cmd 
{
    t_list *args;
    t_list *redir_in;
    t_list *redir_out;
    struct s_cmd *next;
} t_cmd;


/*-----------------------------Utils --------------------------*/
int						ft_strlen_2d_array(char **arr);
void					free_string_array(char **arr);
int 					is_whitespaces(int c);
void 					ft_strcpy(char *dst, char c);

/*----------------------------- Input Validation --------------------------*/
void					input_validation(t_tokenizer *lexer);
bool					rederections_check(t_tokenizer *lexer);
bool 					pipes_check(t_tokenizer *lexer);
bool 					forbidden_inputs(t_tokenizer *lexer);
bool    				check_quotes(t_tokenizer *lexer);

/*----------------------------- Syntax Analysis --------------------------*/
t_tokenizer				*new_token(char *value, int type);
t_tokenizer				*last_token(t_tokenizer **token);
void					add_to_back(t_tokenizer **token, t_tokenizer *new);
void					add_to_front(t_tokenizer **token, t_tokenizer *new);
int						stack_size(t_tokenizer **token);
t_tokenizer				*tokenization(char *line);
void					display_tokens(t_tokenizer *tokens);

/*----------------------------- Built-in --------------------------*/
int						_cd(char *path, t_env **env);
int 					_pwd(void);
int 					_unset(t_env **env, char *variable);
void    				_env(t_env *env);
void 					_echo(char **argumentes);

/*----------------------------- Expand --------------------------*/
typedef struct s_expand
{
	char	*line;
	int 	to_expand;
	int		i;
	int		j;
	int		y;
	char	**str;
	int		exp_cmpt;
	char	*exp;
	char	**spilted;
	int 	start;
	bool	space;
	bool 	open;
	char	buffer[2];
}		t_expand;

t_tokenizer 			*expand_lexer(t_env *env, t_tokenizer **lexer);
char 					**expand(t_env *env,char *line, int enable);
char					*handle_quotes(char *line);
void					add_to_back_expand(t_tokenizer **token, t_tokenizer *new);
bool					 is_opend(char c , bool open);
int						needs_expansion(const char *line);

/*----------------------------- Initilize Envirement --------------------------*/
t_env					*new_env(char *key, char *value);
t_env					*last_env(t_env **env);
void					add_to_back_env(t_env **env, t_env *new);
void					add_to_front_env(t_env **env, t_env *new);
int						stack_size_env(t_env **env);
t_env					*init_environment(char **env);
char					*get_env(t_env **env, char *key);
void    				change_env(t_env **env, char *key, char *value);
void    				remove_env_element(t_env **env, char *variable);
// void					display_envirment(t_env **env);


#endif