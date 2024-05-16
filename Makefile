RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fasanitize=address
NAME = minishell
INCLUDES = -Iheaders -I~/readline/include/readline -Ilibs/libft
REDLINE = -L~/readline/lib -lreadline
SRC =  $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libs/libft
	$(CC) $(CFLAGS) $(INCLUDES) $(REDLINE) $(OBJ) -o $(NAME) 

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C libs/libft
	rm -rf $(OBJ)
flcean: clean
	make fclean -C libs/libft
	rm -rf $(NAME)

re: fclean all

.SECONDARY : $(OBJ)

header:
	@echo $(RED)
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
	@echo "$(GREEN)############################### MINISHELL MANDATORY ###############################$(NC)\n"
