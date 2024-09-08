RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
NAME = minishell

LIBFT = ./libs/libft
GARBAGE = ./libs/gc
GNL = libs/get_next_line

LIBS = -L$(LIBFT) -lft -L$(GARBAGE) -lgarbage

INC = -Ilibs/libft -Ilibs/gc -Iheaders
REDLINE = -lreadline

SRC =  $(wildcard src/utils/*.c) $(wildcard src/*.c) $(wildcard src/tokenizing/*.c) $(wildcard src/input_validation/*.c) $(wildcard src/builtins/*/*.c) $(wildcard src/environment/*.c) $(wildcard src/parsing/*.c) $(wildcard src/execution/*.c) $(wildcard src/expand/*.c) $(wildcard src/signals/*.c)
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
dev:
	while inotifywait -q . ; do echo -e '\n\n'; make; done
sup:
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell


.SECONDARY : $(OBJ)

header:
	@echo "$(GREEN)"
	@echo "░▒▓██████████████▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓███████▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░       "
	@echo "░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓████████▓▒░"
	@echo "$(NC)"
	@echo "$(GREEN)############################################# MINISHELL MANDATORY ######################################$(NC)\n"
