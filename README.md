#fdf
This project consist to create graphically the schematic representation of a ground in relief.

# COMPILATION ON MAC
gcc -o $(NAME) $(SRC) -lmlx -framework OpenGL -framework AppKit

# COMPILATION ON LINUX with X11 and Xext dependencies.
Minilibx have two dependencies: X11 and Xext:

sudo apt-get install libx11-dev

sudo apt-get install libxext-dev

You should now found all the file under 

/usr/include/X11/

For an eventual problem of use of strlcpy:

- just comment the line int the file ./minilibx/mlx_xpm.c and uncomment the line just over it that use strcpy.

That's it !

You can run your project on Linux.

Ps: To compile your project under linux please create two libs in your Makefile as follow:

LIB2= -L minilibx -lmlx

LIB3= -L /usr/include/X11/ -lXext -lX11


Then compile with sources:

gcc $(FLAG) -o $(NAME) $(SRC) $(LIB) $(LIB2) $(LIB3)
