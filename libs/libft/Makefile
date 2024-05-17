RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

NAME = libft.a

SRC = $(wildcard *.c)
 

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc

all: header $(NAME) 

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o:%.c
	@echo "✅ $(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f $(NAME)

re :fclean all 

.SECONDARY : $(OBJ)

header:
	@echo "$(RED)"
	@echo " ██░ ██  ▄▄▄       ███▄    █  ▄▄▄        █████▒"
	@echo "▓██░ ██▒▒████▄     ██ ▀█   █ ▒████▄    ▓██   ▒ "
	@echo "▒██▀▀██░▒██  ▀█▄  ▓██  ▀█ ██▒▒██  ▀█▄  ▒████ ░ "
	@echo "░▓█ ░██ ░██▄▄▄▄██ ▓██▒  ▐▌██▒░██▄▄▄▄██ ░▓█▒  ░ "
	@echo "░▓█▒░██▓ ▓█   ▓██▒▒██░   ▓██░ ▓█   ▓██▒░▒█░    "
	@echo " ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒░   ▒ ▒  ▒▒   ▓▒█░ ▒ ░    "
	@echo " ▒ ░▒░ ░  ▒   ▒▒ ░░ ░░   ░ ▒░  ▒   ▒▒ ░ ░      "
	@echo " ░  ░░ ░  ░   ▒      ░   ░ ░   ░   ▒    ░ ░    "
	@echo " ░  ░  ░      ░  ░         ░       ░  ░        "
    
	@echo "$(NC)"  
	
	@printf "$(YELLOW)###############################LIBFT###############################$(NC)\n"