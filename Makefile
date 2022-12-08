NAME = ft_ssl
SRC = ./src/ft_ssl.c
OBJ	= $(SRC:.c=.o)
# CFLAGS	=-Wall -Wextra -Werror
CFLAGS	=
P_HEADER = ./inc/ft_ssl.h
FT_LIB = ./libft/libft.a


all: $(FT_LIB) $(NAME)

$(FT_LIB): 
	@make -C  ./libft

$(OBJ): $(SRC) $(P_HEADER)
	gcc $(CFLAGS) -c $(SRC) -o $(OBJ)
	

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(FT_LIB)


clean:
	@make -C  ./libft clean
	-rm $(OBJ)

fclean: clean
	@make -C  ./libft fclean
	-rm $(NAME)

re: fclean all