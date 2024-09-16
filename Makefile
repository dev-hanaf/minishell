CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address 
NAME = minishell

LIBFT = ./libs/libft
GARBAGE = ./libs/gc
GNL = libs/get_next_line

LIBS = -L$(LIBFT) -lft -L$(GARBAGE) -lgarbage

INC = -Ilibs/libft -Ilibs/gc -Iheaders
REDLINE = -lreadline

SRC =  src/utils/utils2.c src/utils/utils3.c src/utils/utils.c src/main.c src/minishell.c src/tokenizing/is_redir.c src/tokenizing/lexer_crud.c src/tokenizing/print_tokenz.c src/tokenizing/tokenizing.c src/input_validation/check_quotes.c src/input_validation/input_validation.c src/input_validation/pipes_check.c src/input_validation/rederections_check.c src/builtins/cd/cd.c src/builtins/echo/echo.c src/builtins/env/env.c src/builtins/exit/exit.c src/builtins/export/export.c src/builtins/export/export_print.c src/builtins/export/export_utils2.c src/builtins/export/export_utils.c src/builtins/pwd/pwd.c src/builtins/unset/unset.c src/environment/chnge_env.c src/environment/display_environment.c src/environment/env_utils.c src/environment/get_env.c src/environment/initilize_environment.c src/environment/remove_environment_ele.c src/parsing/cmd_utils.c src/parsing/heredoc.c src/parsing/heredoc_utils2.c src/parsing/heredoc_utils.c src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/t_redir.c src/execution/exec_buitins.c src/execution/exec_redirections.c src/execution/exec_utils.c src/execution/execution.c src/execution/find_path.c src/execution/ft_syscalls.c src/expand/expand.c src/expand/expand_parser2.c src/expand/expand_parser.c src/expand/expand_utils2.c src/expand/expand_utils.c src/expand/handle_quotes.c src/signals/signals2.c src/signals/signals3.c src/signals/signals.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(GARBAGE)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(REDLINE) $(INC) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(INC)  -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(GARBAGE)
	rm -rf $(OBJ)
fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(GARBAGE)
	rm -rf $(NAME)

re: fclean all

sup: all
	valgrind -s  --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
