/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/12 01:54:17 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
//# include "header.h"
# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>


# ifndef __O_DIRECTORY
#define __O_DIRECTORY     0x00100000
# endif

/* It is not required to use uppercase, but often considered as good practice.
	Enum is short for "enumerations", which means "specifically listed".
The typedef is a keyword that is used to provide existing data types with a new name.The C typedef keyword is used to redefine the name of already existing data types.
*/

# define ESCAPE 1

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

# define TRUE 1
# define WRITE 1
# define READ 0
# define CHILD 0
#define ALLOC 100

typedef struct s_tokenizer
{
	struct s_tokenizer	*prev;
	char				*value;
	bool				expanded;
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

typedef struct s_rdr
{
    char *value;
    int type;
    int fd;
	int mode;
	int perm;
	int dup;
    struct s_rdr *next;
} t_rdr;

typedef struct s_cmd
{
    t_list *args;
    t_rdr *redir;
    t_rdr *heredoc;
    int hrdc_fd;
    struct s_cmd *next;
} t_cmd;

typedef struct s_exec
{
	pid_t *pids;
	int pipefd[2];
	int tmp;
	int i;
} t_exec;

typedef struct s_minishell
{
	char 				*prompt;
	char				**env;
	struct sigaction *old_act;
	t_env               **env_ld;
	char				*line;
	bool				execute;
	t_list				*heredoc_fds;
	int					status;
	t_cmd				*cmd;
	int					pExit;
	int					pipefd[2];
}						t_minishell;

t_minishell *get_ms(void);



/*-----------------------------Utils --------------------------*/
int						ft_strlen_2d_array(char **arr);
void					free_string_array(char **arr);
int 					is_whitespaces(int c);
void 					ft_strcpy(char *dst, char c);
t_tokenizer 			*remove_espace_type(t_tokenizer *lexer);


/*----------------------------- Input Validation --------------------------*/
bool					input_validation(t_tokenizer *lexer);
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
int						_cd(char **paths, t_env **env);
int 					_pwd(void);
int 					_unset(t_env **env, char **variables);
int						_env(t_env *env);
int						_echo(char **argumentes);
void					__exit(char **args);


/*----------------------------- Expand --------------------------*/
typedef struct s_expand
{
	char	*line;
	int 	to_expand;
	int		i;
	int		j;
	int		y;
	char	**str;
	int		x;
	char	*exp;
	char	**spilted;
	int 	start;
	bool	space;
	bool 	open;
	char	buffer[2];
	bool	is_first;
	int 	xxx;
}		t_expand;


t_expand	*var(void);
t_tokenizer 			*expand_lexer(t_env *env, t_tokenizer **lexer);
char 					**expand(t_env *env, char *line);
char					**ld_to_arr_and_expand(t_list *lst);
char					**make_child_env(t_list *lst);
char					*handle_quotes(char *line);
void					add_to_back_expand(t_tokenizer **token, t_tokenizer *new);
bool					 is_opend(char c , bool open);
int						needs_expansion(const char *line);
t_tokenizer				*new_token_expand(char *value, int type, bool expanded);
char					**catch_expand(char *line, t_env *env, int flag, int heredoc);
char 					*expand_herdoc(t_env *env, char *line);
int 					get_pid(void);
int						var_need_expansion(const char *line);
int 					valid_expansion_variable(char c);
char 					**ft_split_whitespaces(char *str, char *seps);
void					start_expanding(char *line, t_env *env, int flag);
bool					open_or_close(char *line);
/*----------------------------- Initilize Envirement --------------------------*/
t_env					*new_env(char *key, char *value);
t_env					*last_env(t_env **env);
void					add_to_back_env(t_env **env, t_env *new);
void					add_to_front_env(t_env **env, t_env *new);
int						env_size(t_env *env);
char					**env_to_arr(t_env *env);
t_env					**init_environment(char **env);
char					*get_env(t_env **env, char *key);
t_env					*get_env_ld(t_env **env, char *key);
void					print_export(t_env *env);
void    				change_env(t_env **env, char *key, char *value);
void    				remove_env_element(t_env **env, char *variable);
void					display_environment(t_env **env);
void clean_exit(int e);
/*-------------------------- cmd utils --------------------------------------- */
t_cmd* new_cmd(void);
int  cmd_nbr(t_cmd *head);
void add_to_back_cmd(t_cmd **head, t_cmd *newCmd);
t_cmd *get_last_cmd(t_cmd *head);
int cmd_nbr(t_cmd *head);
char **ld_to_arr(t_list *lst);
void	init_vars(int *is_ok, long *result, int *signe, int *i);
/*------------------------- parsing -----------------------------------------  */
t_cmd *parse_cmds(t_tokenizer *tokens);
int 	handle_heredoc(t_cmd *cmd);
void print_cmds(t_cmd *cmd_list);
void print_args(t_list *arg,char *name);
/*t_rdr */
t_rdr *ft_redirnew(char *value,int type);
void ft_rdraddback(t_rdr **rdr,t_rdr *new);
void close_heredoc(t_cmd *cmd);
/*execution */
void execute_cmds(t_cmd *cmd,int nbr);
char	*get_cmd_path(char *cmd, char **env);
int	ft_strcmp(const char *s1, const char *s2);
/*signals*/
void handle_parent_signals(void);
void handle_child_signals(void);
void handle_signals(void);
void handle_parent_in_childs(void);
void update_status(int new_status);
int     _export(t_env **env,char **args);
void print_strs(char **strs);
int get_status(int status);
#endif
