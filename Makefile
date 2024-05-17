RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fasanitize=address
NAME = minishell

LIBFT = ./libs/libft
GARBAGE = ./libs/garbage_collector
GNL = libs/get_next_line

LIBS = -L$(LIBFT) -lft

INC = -Ilibs/libft -Iheaders
REDLINE = -lreadline

SRC =  $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all : header $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(REDLINE) $(INC) -o $(NAME) 

%.o:%.c
	$(CC) $(CFLAGS) $(INC)  -c $< -o $@

clean:
	@make clean -C $(LIBFT)
	rm -rf $(OBJ)
fclean: clean
	@make fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.SECONDARY : $(OBJ)

header:
	@echo "$(RED)"
	@echo "   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
	@echo " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
	@echo "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "
	@echo "                                                                              ▀         ▀         "
	@echo "$(NC)"  
	@echo "$(RED)############################### MINISHELL MANDATORY ###############################$(NC)\n"
