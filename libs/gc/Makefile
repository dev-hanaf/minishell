CC  = cc
CFLAGS = -Wall -Wextra -Werror 
AR = ar -rcs
SRC = gc.c	 gc_env.c utils.c

OBJ = $(SRC:.c=.o)

NAME = libgarbage.a

all: $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY: $(OBJ)