NAME = ft_ssl
SRC = ./src/ft_ssl.c\
		./src/ft_md5.c\
		./src/ft_sha256.c\
		./src/tools.c
OBJ	= $(SRC:.c=.o)
# CFLAGS	=-Wall -Wextra -Werror
CFLAGS	=
P_HEADER = ./inc/ft_ssl.h
FT_LIB = ./libft/libft.a


all: $(FT_LIB) $(NAME)

$(FT_LIB): 
	@make -C  ./libft

$(OBJ): $(SRC) $(P_HEADER)


$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(FT_LIB)


clean:
	@make -C  ./libft clean
	-rm $(OBJ)

fclean: clean
	@make -C  ./libft fclean
	-rm $(NAME)

re: fclean all