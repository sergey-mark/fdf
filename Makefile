

NAME=fdf
SRC=	main.c \
		fdf.c
OBJ=${SRC:.c=.o}
LIB= -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra #Linux
#FLAG=-Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit #MAC

all: $(NAME)

$(NAME):	$(SRC)
	make -C libft
	make -C minilibx
	gcc $(FLAG) -o $(NAME) $(SRC) $(LIB) $(LIB2) $(LIB3)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
