
#include "fdf.h"
#include <math.h>
#include <stdio.h>

#define ACCENTUATION 10 // On peut mettre une accentuation à 10 pour compenser les maps avec des petits chiffres ;)

/*
int		my_mouse_function(int keycode, t_wind *w)
{
	ft_putnbr(w->point.x);
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	//if (keycode == 1 && w->point.x >= 0) // fleche gauche
		//ft_putendl("clic gauche");//w->point.x -= 5;
	*//*
	else if (keycode == 65363 && w->point.x < w->width) // fleche droite
		w->point.x += 5;
	else if (keycode == 65362 && w->point.x >= 0) // fleche haut
		w->point.y -= 5;
	else if (keycode == 65364 && w->point.x < w->height) // fleche bas
		w->point.y += 5;
	*/
	//ft_putnbr(w->point.y);
	//mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	/*
	return (0);
}*/

int		my_key_function(int keycode, t_wind *w)
{
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65361 && w->point.x >= 0) // fleche gauche
		w->point.x -= 5;
	else if (keycode == 65363 && w->point.x < w->width) // fleche droite
		w->point.x += 5;
	else if (keycode == 65362 && w->point.y >= 0) // fleche haut
		w->point.y -= 5;
	else if (keycode == 65364 && w->point.y < w->height) // fleche bas
		w->point.y += 5;
	mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	ft_putnbr(w->point.y);
	ft_putchar('\n');
	ft_putnbr(w->point.x);
	ft_putchar('\n');
	return (0);
}

int			get_sign(int first, int second)
{
	int		sign;

	if (first > second)
		sign = -1;
	else if (first == second)
		sign = 0;
	else
		sign = 1;
	return (sign);
}

int			get_diff(int first, int second)
{
	int		i;

	i = 0;
	if (first > second)
	{
		while (first > second)
		{
			second++;
			i++;
		}
	}
	if (first < second)
	{
		while (first < second)
		{
			first++;
			i++;
		}
	}
	return (i);
}

void		color_point(int num, size_t *color)
{
	if(num == 10)//Je colore mon point si different de zero
		*color = 0x00FF00FF;
	else
		*color = 0x00FFFFFF;
}

void		color_line(int num1, int num2, size_t *color)
{
	if (num1 == 10 && num2 == 10)
		*color = 0x00FF00FF;
	else
		*color = 0x00FFFFFF;
}

int			draw_line(t_wind **w, int z, int xdest, int ydest)
{ 
	float	x;
	float	y;
	int		sign_x;
	int		sign_y;
	float		bigdiff;
	float		diff_x;
	float		diff_y;

	x = (*w)->point.x;
	y = (*w)->point.y - z;
	sign_x = get_sign(x, xdest);
	sign_y = get_sign(y, ydest);
	diff_x = get_diff(x, xdest);
	diff_y = get_diff(y, ydest);

	ft_putstr("x : ");
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putstr("y : ");
	ft_putnbr(y);
	ft_putchar('\n');
	ft_putstr("xdest : ");
	ft_putnbr(xdest);
	ft_putchar('\n');
	ft_putstr("ydest : ");
	ft_putnbr(ydest);
	ft_putchar('\n');
	ft_putstr("diff_x : ");
	ft_putnbr(diff_x);
	ft_putchar('\n');
	ft_putstr("diff_y : ");
	ft_putnbr(diff_y);
	ft_putchar('\n');
	ft_putstr("sign_x : ");
	ft_putnbr(sign_x);
	ft_putchar('\n');
	ft_putstr("sign_y : ");
	ft_putnbr(sign_y);
	ft_putchar('\n');

		if (diff_x > diff_y)
			bigdiff = diff_x;
		else if (diff_y > diff_x)
			bigdiff = diff_y;
		else
			bigdiff = diff_y;
	ft_putstr("bigdiff : ");
	ft_putnbr(bigdiff);
	ft_putchar('\n');
	while (rint(x) != xdest || rint(y) != ydest)
	{
		if (x != xdest)
		{
			x = x + (sign_x * (diff_x/bigdiff));
			printf("%.2f ", x);
			//ft_putnbr(x);
			//ft_putchar(' ');
		}
		if (y != ydest)
		{
			y = y + (sign_y * (diff_y/bigdiff));
			//printf("%.2f", (float)((float)diff_y/(float)bigdiff));
			printf("%.2f ", y);
			//ft_putnbr(y);
			//ft_putchar(' ');
		}
		//ft_putstr("ma fin");
		//break ;
		//ft_putnbr(x);
		//ft_putchar('-');
		//ft_putnbr(y);
		//ft_putchar(' ');
		mlx_pixel_put((*w)->mlx, (*w)->win, rint(x), rint(y), (*w)->point.color);
	}
	return (0);
}

int			**browsefile(char *filename, int *nbr_of_line, int *nbr_elem_line)
{
	int		fd;
	int		fd1;
	char	*line;
	char	**tab;
	int		**tab_int;
	int		y;
	int		x;

	//fd = open("./test_maps/42.fdf", O_RDONLY);
	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	tab = NULL;
	tab_int = NULL;
	y = 0;
	while (get_next_line(fd1, &line))
		y++;
	tab_int = malloc((y+1) * sizeof(int *));
	
	y = 0;
	while (get_next_line(fd, &line))
	{
		ft_putendl(line);
		tab_int[y] = malloc(ft_strlen(line) * sizeof(int));
		tab = ft_strsplit(line, ' ');//nbr d'elements par lignes
		x = 0;
		while (tab[x])
		{
			tab_int[y][x] = ft_atoi(tab[x]);
			x++;
		}
		y++;
	}
	*nbr_of_line = y;
	*nbr_elem_line = x;
	return (tab_int);
}

int			checkpoint_allside(t_wind *w, int x, int y, int nbr_elem_line, int nbr_of_line, int **tab_int)
{
	int		z;
	int		z_left;
	int		z_right;
	int		z_up;
	int		z_down;

	z = tab_int[y][x];
	z = z*ACCENTUATION; // Ajout du parametre d'accentuationau point d'origine.
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		z_left = (tab_int[y][x-1]);
		color_line(z, z_left, &w->point.color);
		//ft_putnbr(z_left);
		//ft_putchar('\n');
		draw_line(&w, z, (w->point.x - 30), (w->point.y - (z_left*ACCENTUATION)));
	}
	if(x<(nbr_elem_line-1))//Si point à droite
	{
		//ft_putendl("point à droite");
		z_right = (tab_int[y][x+1]);
		color_line(z, z_right, &w->point.color);
		//ft_putnbr(z_right);
		//ft_putchar('\n');
		draw_line(&w, z, w->point.x + 30, w->point.y - (z_right*ACCENTUATION));
	}
	if(y>0)//Si point au dessus
	{
		//ft_putendl("point au dessus");
		z_up = (tab_int[y-1][x]);
		color_line(z, z_up, &w->point.color);
		//ft_putnbr(z_up);
		//ft_putchar('\n');
		draw_line(&w, z, (w->point.x + 30), (w->point.y - 30 - (z_up*ACCENTUATION)));
	}
	if(y<(nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		z_down = (tab_int[y+1][x]);
		color_line(z, z_down, &w->point.color);
		//ft_putnbr(z_down);
		//ft_putchar('\n');
		draw_line(&w, z, w->point.x - 30, w->point.y + 30 - (z_down*ACCENTUATION));
	}
	return (1);
}
//int			fill_3d_map(char *pxl_ptr, int bits_per_pixel, int size_line, int x, int y, int endian_type, int type)
int			fill_3d_map(int **tab_int, int nbr_of_line, int nbr_elem_line, t_wind *w)
{
	int		y;
	int		x;
	int		z;
	int		start_x;

	ft_putendl("ok");
	start_x = w->point.x;
	y = nbr_of_line;
	y--;
	while (y >= 0)
	{
		//ft_putlstnbr(tab_int[y], x);
		w->point.y -= 30; // On ecarte de 25 pixels les chiffres et les lignes pour mieux voir les points ;)
		// Puis on décrémente pour partir du bas à gauche de l'écran pour commencer à afficher les points. (en little endian)
		start_x += 30;
		w->point.x = start_x; //Pour créer le décalage à chaque début de ligne on met x à 25 de plus au lieu de faire partir à zéro.
		x = 0;
		while (x < nbr_elem_line)
		{
			z = tab_int[y][x];
			ft_putnbr(z);
			ft_putchar('-');
			color_point(z, &w->point.color);//Je colore mon point si different de zero
			mlx_pixel_put(w->mlx, w->win, w->point.x, (w->point.y - (z*ACCENTUATION)), w->point.color);
			checkpoint_allside(w, x, y, nbr_elem_line, nbr_of_line, tab_int);
			w->point.x += 30;
			x++;
		}
		ft_putendl("|");
		y--;
	}
	//draw_line(&w, z, (w->point.x - 30), (w->point.y - z + 70));
	return (0);
}

int			main(int argc, char **argv)
{
	t_wind	w;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian_type;
	int		**tab_int;
	int		nbr_of_line;
	int		nbr_elem_line;
	//char	*pxl_ptr;
	/*
	float	my_nb;
	int		ty;

	my_nb = 3.1416;
	ty = round(my_nb);
	ft_putnbr(ty);
	ft_putstr("tata");
	printf("floatx: %.2f", 3.1416);
	ft_putstr("tata");
	*/
	if (argc != 2)
		ft_putstr("usage");
	ft_putendl("fdf");
	w.mlx = mlx_init();
	w.width = 1024;
	w.height = 800;
	w.title = "42 minilibx";
	w.win = mlx_new_window(w.mlx, w.width, w.height, w.title);
	w.point.x = 50;
	w.point.y = 500;
	w.point.color = 0x00FFFFFF;

	img_ptr = mlx_new_image(w.mlx, 100, 100);
	/*pxl_ptr = */mlx_get_data_addr(&img_ptr, &bits_per_pixel, &size_line, &endian_type);
	//fill_3d_map(pxl_ptr, bits_per_pixel, size_line, 0, 0, endian_type, 1);
	tab_int = browsefile(argv[1], &nbr_of_line, &nbr_elem_line);
	fill_3d_map(tab_int, nbr_of_line, nbr_elem_line, &w);
	mlx_put_image_to_window(w.mlx, w.win, img_ptr, 100, 100);
	mlx_key_hook(w.win, my_key_function, &w);
	//mlx_mouse_hook(w.win, my_mouse_function, &w);
	mlx_loop(w.mlx);
	return (0);
}
