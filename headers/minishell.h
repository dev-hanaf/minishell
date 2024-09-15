/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 01:37:26 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
//# include "header.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef __O_DIRECTORY
#  define __O_DIRECTORY 0x00100000
# endif

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
	char				*value;
	int					type;
	int					fd;
	int					mode;
	int					perm;
	int					dup;
	struct s_rdr		*next;
}						t_rdr;

typedef struct s_cmd
{
	t_list				*args;
	t_rdr				*redir;
	t_rdr				*heredoc;
	int					hrdc_fd;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_exec
{
	pid_t				*pids;
	int					pipefd[2];
	int					tmp;
	int					i;
}						t_exec;

typedef struct s_minishell
{
	char				*prompt;
	char				**env;
	struct sigaction	*old_act;
	t_env				**env_ld;
	char				*line;
	bool				execute;
	t_list				*heredoc_fds;
	int					status;
	t_cmd				*cmd;
	int					pexit;
	int					pipefd[2];
	int					pwd_islocal;
	int					oldpwd_islocal;
	char				*pwd;
	char				*oldpwd;
	char				*pwd_pwd;
	char				*oldpwd_pwd;
	char				*save_pwd;
}						t_minishell;

t_minishell				*get_ms(void);
void					loop(void);
void					init_minishell(char **envp);
/*-----------------------------Utils --------------------------*/
char					*remove_escape_character(char *str);
int						ft_strlen_2d_array(char **arr);
int						is_whitespaces(int c);
void					ft_strcpy(char *dst, char c);
void					initial_vars(void);
int						end_strs(void);
int						is_handlequotes(char q, int i, char *line);
/*----------------------------- Input Validation --------------------------*/
bool					input_validation(t_tokenizer *lexer);
bool					rederections_check(t_tokenizer *lexer, int *counter);
bool					pipes_check(t_tokenizer *lexer);
bool					check_quotes(t_tokenizer *lexer);

/*----------------------------- Syntax Analysis --------------------------*/
t_tokenizer				*new_token(char *value, int type);
t_tokenizer				*last_token(t_tokenizer **token);
void					add_to_back(t_tokenizer **token, t_tokenizer *new);
void					add_to_front(t_tokenizer **token, t_tokenizer *new);
int						stack_size(t_tokenizer **token);
t_tokenizer				*tokenization(char *line);
void					display_tokens(t_tokenizer *tokens);
void					is_redirection(t_tokenizer **lexer, char *line,
							size_t *i);
void					skip_whitespaces(char *line, size_t *i);
void					is_pipe(t_tokenizer **lexer, char *line, size_t *i);

/*----------------------------- Built-in --------------------------*/
int						_cd(char **paths, t_env **env);
int						_pwd(void);
int						_unset(t_env **env, char **variables);
int						_env(t_env *env);
int						_echo(char **argumentes);
void					__exit(char **args);
void					cd_change_env(t_env **env, char *save);

/*----------------------------- Expand --------------------------*/
typedef struct s_expand
{
	char				*line;
	int					to_expand;
	int					i;
	int					j;
	int					y;
	char				**str;
	int					x;
	char				*exp;
	char				**spilted;
	int					start;
	bool				space;
	bool				open;
	char				buffer[2];
	bool				is_first;
	int					xxx;
	int					idx;
	char				*new_exp;
	int					len;
	int					jdx;
	bool				spaces;
	bool				there_is_space;
}						t_expand;

t_expand				*var(void);
char					**expand(t_env *env, char *line);
char					**ld_to_arr_and_expand(t_list *lst);
char					**make_child_env(t_list *lst);
char					*handle_quotes(char *line);
void					add_to_back_expand(t_tokenizer **token,
							t_tokenizer *new);
bool					is_opend(char c, bool open);
int						needs_expansion(const char *line);
t_tokenizer				*new_token_expand(char *value, int type, bool expanded);
char					**catch_expand(char *line, t_env *env, int flag,
							int heredoc);
char					*expand_herdoc(t_env *env, char *line);
int						get_pid(void);
int						var_need_expansion(const char *line);
int						valid_expansion_variable(char c);
char					**ft_split_whitespaces(char *str, char *seps);
void					start_expanding(char *line, t_env *env, int flag);
bool					open_or_close(char *line);
void					whitspaces_in_var(char *exp, char *line);
/*-------------------  Initilize Envirement  ----------------*/
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
void					change_env(t_env **env, char *key, char *value);
void					remove_env_element(t_env **env, char *variable);
void					display_environment(t_env **env);
void					clean_exit(int e);
void					exiter(int e, char *str);
/*--------------cmd utils ---------------------------*/
t_cmd					*new_cmd(void);
int						cmd_nbr(t_cmd *head);
void					add_to_back_cmd(t_cmd **head, t_cmd *newCmd);
t_cmd					*get_last_cmd(t_cmd *head);
int						cmd_nbr(t_cmd *head);
char					**ld_to_arr(t_list *lst);
void					init_vars(int *is_ok, size_t *result, int *signe,
							int *i);
/*------------------------- parsing ------------------  */
t_cmd					*parse_cmds(t_tokenizer *tokens, t_cmd *curr_cmd);
int						handle_heredoc(t_cmd *cmd);
void					print_cmds(t_cmd *cmd_list);
void					print_args(t_list *arg, char *name);
/*------------------------- heredoc ------------------------  */
void					sighandler_hrdc(int sig);
void					sigherdoc(int sig);
t_rdr					*get_last_hrdc(t_rdr *redir);
char					*handle_quotes_v2(char *eof, int *expand);
int						heredoc_clean_exit(int *pipefd, int status);
int						heredoc_clean_exit2(int *pipefd, int status);
int						heredoc_parent_wait(int child, int *status);
/*t_rdr */
t_rdr					*ft_redirnew(char *value, int type);
void					ft_rdraddback(t_rdr **rdr, t_rdr *new);
void					close_heredoc(t_cmd *cmd);
/*execution  utils*/
void					update_status(int new_status);
int						get_status(int status);
int						ft_close(int fd);
pid_t					ft_fork(void);
int						*ft_pipe(int *pipefd);
int						ft_dup2(int oldfd, int newfd);
ssize_t					ft_write(int fd, const void *buf, size_t count);
int						ft_close(int fd);

int						check_ambiguous(t_rdr *redir, int *file, char **str,
							int flag);
int						handle_rdr(t_rdr *redir, int flag);
int						check_builtin(char **args, t_list *targs);
int						check_single_builtin(t_cmd *cmd);
/*execution */
void					execute_cmds(t_cmd *cmd, int nbr);
char					*get_cmd_path(char *cmd);
int						ft_strcmp(const char *s1, const char *s2);
/*signals*/
void					handle_parent_signals(void);
void					handle_child_signals(void);
void					handle_signals(void);
void					handle_parent_in_childs(void);
void					update_status(int new_status);
/*export */
void					print_export(t_env *env);
int						process_args(char *str);
void					process_nodes(t_env *env, char *arg);
int						_export(t_env **env, char **args, char **strs);
void					print_strs(char **strs);
int						get_status(int status);

#endif
