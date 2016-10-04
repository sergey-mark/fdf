UNAME := $(shell uname)

NAME=fdf
SRC=	main.c \
		fdf.c \
		help.c \
		create_new_window.c \
		create_new_img.c \
		browsefile.c \
		get_next_line/get_next_line.c \
		matrice_rotation.c \
		rotation_point.c \
		fill_3d_map.c \
		draw_point.c \
		draw_line.c \
		key_function.c
OBJ=${SRC:.c=.o}
LIB= -L libft -lft

ifeq ($(UNAME), Darwin) # MAC :
LIB2= -L minilibx -lmlx
LIB3= -framework OpenGL -framework AppKit
#LIB2= -L./minilibx_macos/
FLAG= -Wall -Werror -Wextra
#FLAG= -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME), Linux) # LINUX :
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
endif

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
