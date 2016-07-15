
#include "fdf.h"
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
	return (0);
}

int			draw_line(t_wind **w, int z, int xdest, int ydest)
{ 
	int		i;
	int		x;
	int		y;
	int		sign_x;
	int		sign_y;
	int		nb;
	float	factor;
	int		diff_x;
	int		diff_y;

	x = (*w)->point.x;
	y = (*w)->point.y - z;
	sign_x = get_sign(x, xdest);
	sign_y = get_sign(y, ydest);
	i = 0;

	diff_x = get_diff(x, xdest);
	diff_y = get_diff(y, ydest);
	ft_putstr("draw_line");
	if (diff_x > diff_y)
	{
		ft_putstr("a");
		factor = 1/diff_x;
		ft_putstr("a");
		nb = (int)diff_x;
	}
	else
	{
		ft_putstr("a");
		factor = 1/diff_y;
		ft_putstr("a");
		nb = (int)diff_y;
	}
	/*ft_putchar('\n');
	ft_putnbr(x);
	ft_putchar(':');
	ft_putnbr(y);
	ft_putchar('\n');
	ft_putnbr(xdest);
	ft_putchar(':');
	ft_putnbr(ydest);
	ft_putchar('\n');

	ft_putnbr(sign_x);
	ft_putchar(':');
	ft_putnbr(sign_y);
	ft_putchar('\n');
	ft_putnbr(z);
	ft_putchar('\n');
	*/
	while (i < nb)
	{
		x += sign_x * factor;
		y += sign_y * factor;
		mlx_pixel_put((*w)->mlx, (*w)->win, (x/1), (y/1), (*w)->point.color);
		i++;
		/*
		ft_putnbr(y);
		ft_putchar(':');
		ft_putnbr(x);
		ft_putchar('|');*/
		//ft_putchar('\n');
	}
	return (0);
}

int			draw_semi_square(t_wind **w, int z)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	/*
	draw_line(0, -30, -30, 0);
	draw_line(-30, 0, -30, 30);
	draw_line(-30, 30, 30, 0);
	draw_line(30, 0, 0, -30);
	*/
	while (x < 30)// Creation du trait horizontale
	{
		x++;
		mlx_pixel_put((*w)->mlx, (*w)->win, ((*w)->point.x + x), ((*w)->point.y), (*w)->point.color);
	}
	x = 0;
	while (y > (-30)) //Creation du trait vertical (qui doit etre different en fonction de la hauteur !)
	{
		if (z == 0)
			x++;
		y--;
		mlx_pixel_put((*w)->mlx, (*w)->win, ((*w)->point.x + x), ((*w)->point.y + y), (*w)->point.color);
	}
	return (0);
}

//int			fill_3d_map(char *pxl_ptr, int bits_per_pixel, int size_line, int x, int y, int endian_type, int type)
int			fill_3d_map(char *filename, t_wind *w)
{
	int		fd;
	int		fd1;
	char	*line;
	int		y;
	int		x;
	int		z;/*
	int		z_left;
	int		z_right;
	int		z_up;
	int		z_down;*/
	char	**tab;
	int		**tab_int;
	int		start_x;
	int		nbr_elem_line;
	//int		nbr_of_line;

	//fd = open("./test_maps/42.fdf", O_RDONLY);
	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
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
	ft_putendl("ok");
	start_x = w->point.x;
	//nbr_of_line = y;
	y--;
	while (y >= 0)
	{
		//ft_putlstnbr(tab_int[y], x);
		w->point.y -= 30; // On ecarte de 25 pixels les chiffres et les lignes pour mieux voir les points ;)
		// Puis on décrémente pour partir du bas à gauche de l'écran pour commencer à afficher les points. (en little endian)
		nbr_elem_line = x;
		start_x += 30;
		w->point.x = start_x; //Pour créer le décalage à chaque début de ligne on met x à 25 de plus au lieu de faire partir à zéro.
		x = 0;
		while (x < nbr_elem_line)
		{
			z = tab_int[y][x];
			ft_putnbr(z);
			ft_putchar('-');
			if(z != 0)//Je colore mon point si different de zero
				w->point.color = 0x00FF00FF;
			else
				w->point.color = 0x00FFFFFF;
			mlx_pixel_put(w->mlx, w->win, w->point.x, (w->point.y - (z*10)), w->point.color);
			//draw_line(&w, z, (w->point.x - 30), (w->point.y - z));
			/*
			if(x>0)//Si point à gauche
			{
				ft_putendl("point à gauche");
				z_left = (tab_int[y][x-1]);
				ft_putnbr(z_left);
				ft_putchar('\n');
				draw_line(&w, z, (w->point.x - 30), (w->point.y - z_left));
			}
			if(x<nbr_elem_line)//Si point à droite
			{
				ft_putendl("point à droite");
				z_right = (tab_int[y][x+1]);
				ft_putnbr(z_right);
				ft_putchar('\n');
				draw_line(&w, z, w->point.x + 30, w->point.y - z_right);
			}
			if(y>0)//Si point au dessus
			{
				ft_putendl("point au dessus");
				z_up = (tab_int[y-1][x]);
				ft_putnbr(z_up);
				ft_putchar('\n');
				draw_line(&w, z, (w->point.x + 30), (w->point.y - 30 - z_up));
			}
			if(y<(nbr_of_line-1))//Si point en dessous
			{
				ft_putendl("point au dessous");
				z_down = (tab_int[y+1][x]);
				ft_putnbr(z_down);
				ft_putchar('\n');
				draw_line(&w, z, w->point.x - 30, w->point.y + 30 - z_down);
			}
			*/
			//draw_semi_square(&w, z);
			w->point.x += 30;
			x++;
		}
		ft_putendl("|");
		y--;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_wind	w;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian_type;
	//char	*pxl_ptr;

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
	fill_3d_map(argv[1], &w);
	mlx_put_image_to_window(w.mlx, w.win, img_ptr, 100, 100);
	mlx_key_hook(w.win, my_key_function, &w);
	//mlx_mouse_hook(w.win, my_mouse_function, &w);
	mlx_loop(w.mlx);
	return (0);
}
