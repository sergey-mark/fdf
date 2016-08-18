

NAME=fdf
SRC=	main.c \
		fdf.c \
		create_new_window.c \
		create_new_img.c \
		browsefile.c \
		get_next_line/get_next_line.c \
		rotation_point.c \
		pythagor.c \
		fill_3d_map.c \
		draw_line.c \
		key_function.c
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
	gcc $(FLAG) -o $(NAME) $(SRC) -lm  $(LIB) $(LIB2) $(LIB3)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
