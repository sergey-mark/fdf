UNAME := $(shell uname)

NAME=fdf
SRC=	get_next_line/get_next_line.c \
		src/main.c \
		src/fdf.c \
		src/def_all_preui.c \
		src/help.c \
		src/create_new_window.c \
		src/create_new_img.c \
		src/browsefile.c \
		src/matrice_rotation.c \
		src/fill_3d_map.c \
		src/fill_para.c \
		src/draw_point.c \
		src/draw_line.c \
		src/key_function.c \
		src/keypress_function02.c \
		src/mouse_function.c \
		src/expose_hook.c \
		src/rgbtohexa.c \
		src/ft_pathinit.c \
		src/ft_listofnodes_init.c \
		src/sort_listofnodes.c \
		src/set_parameters_tline.c \
		src/ft_listofnode_free.c \
		src/draw_circle.c
OBJ=${SRC:.c=.o}

ifeq ($(UNAME), Darwin) # MAC
MINILIBX= make -C minilibx_macos
LIB= -lm -L libft -lft
LIB2= -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include
LIB3= -lmlx -framework OpenGL -framework AppKit
FLAG= -Wall -Werror -Wextra
KEY= 1
endif
ifeq ($(UNAME), Linux) # LINUX
MINILIBX= make -C minilibx
LIB= -lm -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
KEY= 2
endif

all:	$(NAME)

$(NAME):	$(SRC)
	make -C libft
	$(MINILIBX)
	gcc $(FLAG) -o $(NAME) $(SRC) $(LIB) $(LIB2) $(LIB3) -D MACROKEY=$(KEY)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
