
#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

double		degree_to_radian(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees*(pi/180);
	return (radians);
}

t_point		rotation_point(t_point A, int angle)
{
	t_point B;
	double	r_angle;
	double	my_cos;
	double	my_sin;
	//double	result;
	//double	x;
	
	ft_putstr("Ax:");
	ft_putnbr(A.x);
	ft_putstr("Ay:");
	ft_putnbr(A.y);
	ft_putstr("Az:");
	ft_putnbr(A.z);
	ft_putendl("end");
/*
	x = 1.0471;
	result = cos(x);
	printf("cos(%.4lf) = %.2lf\n", x, result);
*/

	r_angle = degree_to_radian(angle);
	ft_putstr("angle:");
	ft_putnbr(angle);
	ft_putchar('\n');
	ft_putstr("angle radians:");
	printf("r_angle = %.4lf\n", r_angle);
	my_cos = cos(r_angle);
	my_sin = sin(r_angle);
	printf("cos(%.4lf) = %.2lf\n", r_angle, my_sin);
	printf("sin(%.4lf) = %.2lf\n", r_angle, my_cos);
	
	printf("A.x * cos(r_angle) = %.4lf\n", A.x * cos(r_angle));
	printf("A.y * sin(r_angle) = %.4lf\n", A.y * sin(r_angle));
	/*
	ft_putnbr(my_cos);
	ft_putstr("-");
	ft_putnbr(my_sin);
	ft_putstr("!");
	*/
	//B.x = ((A.x - i->x_centerpoint) * cos(r_angle)) - ((A.y - i->y_centerpoint)  * sin(r_angle)); // include <math.h>
	//B.y = ((A.x - i->x_centerpoint) * sin(r_angle)) + ((A.y - i->y_centerpoint)  * cos(r_angle));
	//B.z = A.z;
	
	// Rotation axe x:
	//B.x = A.x;
	//B.y = (A.y * cos(r_angle)) - (A.z * sin(r_angle)); // include <math.h>
	//B.z = (A.y * sin(r_angle)) + (A.z * cos(r_angle));
	
	// Rotation axe y:
	//B.x = (A.x * cos(r_angle)) + (A.z * sin(r_angle)); // include <math.h>
	//B.y = A.y;
	//B.z = -(A.x * sin(r_angle)) + (A.z * cos(r_angle));
	
	// Rotation axe z:
	B.x = (A.x * cos(r_angle)) - (A.y * sin(r_angle)); // include <math.h>
	B.y = (A.x * sin(r_angle)) + (A.y * cos(r_angle));
	B.z = A.z;
	
	ft_putstr("Bx:");
	ft_putnbr(B.x);
	ft_putstr("By:");
	ft_putnbr(B.y);
	ft_putstr("Bz:");
	ft_putnbr(B.z);
	ft_putendl("end");
	return (B);
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
	size_t white;
	size_t purple;

	white = 0x00FFFFFF;
	purple = 0x00FF00FF;
	if (num1 == 10 && num2 == 10)
		*color = purple;
	else
		*color = white;
}

int			draw_line(int xdest, int ydest, t_img **i)
{ 
	float	x;
	float	y;
	int		sign_x;
	int		sign_y;
	float		bigdiff;
	float		diff_x;
	float		diff_y;

	x = (*i)->r_point.x;
	y = (*i)->r_point.y - (*i)->r_point.z;
	sign_x = get_sign(x, xdest);
	sign_y = get_sign(y, ydest);
	diff_x = get_diff(x, xdest);
	diff_y = get_diff(y, ydest);
	/*
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
	*/
	if (diff_x > diff_y)
		bigdiff = diff_x;
	else if (diff_y > diff_x)
		bigdiff = diff_y;
	else
		bigdiff = diff_y;
	/*
	ft_putstr("bigdiff : ");
	ft_putnbr(bigdiff);*/
	while (rint(x) != xdest || rint(y) != ydest)
	{
		if (x != xdest)
		{
			x = x + (sign_x * (diff_x/bigdiff));
			//printf("%.2f ", x);
		}
		if (y != ydest)
		{
			y = y + (sign_y * (diff_y/bigdiff));
			//printf("%.2f ", y);
		}
	/*ft_putchar(':');
	ft_putnbr(rint(x));
	ft_putchar(':');
	ft_putnbr(rint(y));
	ft_putchar(':');
	*/
		//mlx_pixel_put((*w)->mlx, (*w)->win, rint(x), rint(y), (*w)->point.color);
		//ft_putstr("tata");
		*((*i)->pxl_ptr+(int)((rint(y))*((*i)->size_line)+ (rint(x))*((*i)->octet_per_pixel))) = (int)"0x00FFFFFF";

		//*((*i)->pxl_ptr+(int)((rint(y)*(w->p.size_square-(z)))*(((*i)->size_line)) + (rint(x))*((*i)->octet_per_pixel))) = (int)"#00FFFFFF";
	}
	return (0);
}

int			**browsefile(char *filename, int *y, int *x)
{
	int		fd;
	int		fd1;
	char	*line;
	char	**tab;
	int		**tab_int;

	//fd = open("./test_maps/42.fdf", O_RDONLY);
	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	tab = NULL;
	tab_int = NULL;
	(*y) = 0;
	while (get_next_line(fd1, &line))
		(*y)++;
	tab_int = malloc(((*y)+1) * sizeof(int *));
	
	(*y) = 0;
	while (get_next_line(fd, &line))
	{
		ft_putendl(line);
		tab_int[(*y)] = malloc(ft_strlen(line) * sizeof(int));
		tab = ft_strsplit(line, ' ');//nbr d'elements par lignes
		(*x) = 0;
		while (tab[(*x)])
		{
			tab_int[(*y)][(*x)] = ft_atoi(tab[(*x)]);
			(*x)++;
		}
		(*y)++;
	}
	return (tab_int);
}

int			checkpoint_allside(int x, int y, t_browsefile b, t_img *i, t_wind *w)
{
	int		z_left;
	int		z_right;
	int		z_up;
	int		z_down;

	//z = b.tab_int[y][x];
	//z = z*w->p.accentuation; // Ajout du parametre d'accentuationau point d'origine.
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		z_left = (b.tab_int[y][x-1]);
		color_line(i->r_point.z, z_left, &i->point.color);
		//ft_putnbr(z_left);
		//ft_putchar('\n');
		draw_line((i->r_point.x - w->p.size_square), i->r_point.y - (z_left*w->p.accentuation), &i);
	}
	if(x<(b.nbr_elem_line-1))//Si point à droite
	{
		//ft_putendl("point à droite");
		z_right = (b.tab_int[y][x+1]);
		color_line(i->r_point.z, z_right, &i->point.color);
		//ft_putnbr(z_right);
		//ft_putchar('\n');
		draw_line(i->r_point.x + w->p.size_square, i->r_point.y - (z_right*w->p.accentuation), &i);
	}
	if(y>0)//Si point au dessus
	{
		//ft_putendl("point au dessus");
		z_up = (b.tab_int[y-1][x]);
		color_line(i->r_point.z, z_up, &i->point.color);
		//ft_putnbr(z_up);
		//ft_putchar('\n');
		draw_line((i->r_point.x + w->p.size_square), (i->r_point.y - w->p.angle_projpara - (z_up*w->p.accentuation)), &i);
	}
	if(y<(b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		z_down = (b.tab_int[y+1][x]);
		color_line(i->r_point.z, z_down, &i->point.color);
		//ft_putnbr(z_down);
		//ft_putchar('\n');
		draw_line(i->r_point.x - w->p.size_square, i->r_point.y + w->p.angle_projpara - (z_down*w->p.accentuation), &i);
	}
	return (1);
}
//int			fill_3d_map(char *pxl_ptr, int bits_per_pixel, int size_line, int x, int y, int endian_type, int type)
int			fill_3d_map(t_browsefile b, t_img *i, t_wind *w)
{
	int		y;
	int		x;
	int		z;
	int		start_x;

	ft_putendl("ok");
	i->octet_per_pixel = i->bits_per_pixel/8;
	ft_putstr("octet par pixel");
	ft_putnbr(i->octet_per_pixel);
	ft_putchar('\n');

	//*(i->pxl_ptr) = (int)"0xFFFFFF";
	//x = 0;
	//while (x < 250)
		//*(i->pxl_ptr+(x++)*(i->bits_per_pixel)) = (size_t)"0x00FFFFFF";
	//*i->pxl_ptr = (int)"0x00FFFFFF";
	i->point.x = 50;
	start_x = i->point.x;
	i->point.y = 550;
	y = b.nbr_of_line;
	y--;
	while (y >= 0)
	{
		i->point.y -= w->p.angle_projpara; // On ecarte de 25 pixels les chiffres et les lignes pour mieux voir les points ;)
		//*(i->pxl_ptr) = *(int*)"0x00FFFFFF";
		//*(i->pxl_ptr+y*(i->size_line)) = (size_t)"0x00FFFFFF";
		// Puis on décrémente pour partir du bas à gauche de l'écran pour commencer à afficher les points. (en little endian)
		start_x += w->p.size_square;
		i->point.x = start_x; //Pour créer le décalage à chaque début de ligne on met x à 25 de plus au lieu de faire partir à zéro.
		x = 0;
		while (x < b.nbr_elem_line)
		{
			z = b.tab_int[y][x];
			//i->point.z = b.tab_int[y][x];
			i->point.z = b.tab_int[y][x] * w->p.accentuation;
			ft_putnbr(z);
			ft_putchar('-');
			//color_point(z, &i->point.color);//Je colore mon point si different de zero
			//*(i->pxl_ptr+((y*w->p.size_square-(z))*(i->size_line)) + (i->point.x)*(i->bits_per_pixel)) = (int)"0x00FFFFFF";
			if (x == b.nbr_elem_line/2 && y == b.nbr_of_line/2)
			{
				i->x_centerpoint = i->point.x;
				i->y_centerpoint = i->point.y;
				ft_putstr("center point:");
				ft_putnbr(i->point.x);
				ft_putstr(":");
				ft_putnbr(i->point.y);
				ft_putchar('\n');
			}
			/*
				ft_putstr("x:");
				ft_putnbr(i->point.x);
				ft_putstr("y:");
				ft_putnbr(i->point.y);
				ft_putstr("z:");
				ft_putnbr(i->point.z);
				ft_putchar('\n');
			*/
				// On applique la rotation si on appui sur la flèche de haut ou bas
				i->r_point = rotation_point(i->point, w->p.rot_x);
			/*
				ft_putstr("rotx:");
				ft_putnbr(i->r_point.x);
				ft_putstr("roty:");
				ft_putnbr(i->r_point.y);
				ft_putstr("rotz:");
				ft_putnbr(i->r_point.z);
				ft_putchar('\n');
			*/

			if (w->p.graphic_mode == 1) // Mode point
				*((i->pxl_ptr)+((i->r_point.y - i->r_point.z)*(int)(i->size_line))+((i->r_point.x)*(i->octet_per_pixel))) = (int)"0x00FFFFFF";
			else if (w->p.graphic_mode == 2) // Mode filaire
				checkpoint_allside(x, y, b, i, w);
			else if (w->p.graphic_mode == 3) // Mode rempli
				checkpoint_allside(x, y, b, i, w);
			i->point.x += w->p.size_square;
			x++;
		}
		ft_putendl("|");
		y--;
	}
	return (0);
}

int		my_expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int		create_new_img(t_wind *w)
{
	w->img.width = 1024;
	w->img.height = 600;

	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);

	fill_3d_map(w->b, &w->img, w);
	return (0);
}

int		my_key_function(int keycode, t_wind *w)
{
	//int	x_oldcenterpoint;
	//int	y_oldcenterpoint;

	ft_putchar('\n');
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');

	// ECHAP (to quit)
	if (keycode == 65307)
		exit(0);

	// ROTATIONS:
	if (keycode == 65361 && w->img.x >= 0) // fleche gauche
		w->img.x -= 5;
	else if (keycode == 65363 && w->img.x < w->width) // fleche droite
		w->img.x += 5;
	else if (keycode == 65362 && w->img.y >= 0) // fleche haut
		w->p.rot_x += 1;
	else if (keycode == 65364 && w->img.y < w->height) // fleche bas
		w->p.rot_x -= 1;

	// DEPLACEMENT LATERAL (pan) (Pavé numérique)
	if (keycode == 65431)//haut (pav num)
		w->img.y -= 5;
	else if (keycode == 65433)//bas (pav num)
		w->img.y += 5;
	else if (keycode == 65432)//droite (pav num)
		w->img.x += 5;
	else if (keycode == 65430)//gauche (pav num)
		w->img.x -= 5;

	// ZOOM:
	if (keycode == 65451)//plus (pav num)
	{
		//w->p.accentuation++;
		w->p.size_square++; 
		w->p.angle_projpara++;
		//x_oldcenterpoint = w->img.x_centerpoint;
		//y_oldcenterpoint = w->img.y_centerpoint;
		//w->img.x += w->img.x_centerpoint - x_oldcenterpoint; // Recentrage du zoom au milieu
		//w->img.y += w->img.y_centerpoint - y_oldcenterpoint; // Recentrage du zoom au milieu
	}
	if (keycode == 65453)//moins (pav num)
	{
		//w->p.accentuation--;
		w->p.size_square--; 
		w->p.angle_projpara--;
		//w->img.x = w->img.x_centerpoint - (w->img.width/2); // Recentrage du zoom au milieu
		//w->img.y = w->img.y_centerpoint - (w->img.height/2); // Recentrage du zoom au milieu
	}

	// ACCENTUATION (Hauteur du terrain)
	if (keycode == 65365)//page up
	{
		w->p.accentuation++;
		//w->p.size_square++; 
		//w->p.angle_projpara++;
	}
	if (keycode == 65366)//page down
	{
		w->p.accentuation--;
		//w->p.size_square--; 
		//w->p.angle_projpara--;
	}

	// GRAPHIC MODES: (touche 1 à zéro)
	if (keycode == 38)//1 poitille
		w->p.graphic_mode = 1;
	else if (keycode == 233)//2 filaire (par default)
		w->p.graphic_mode = 2;
	else if (keycode == 34)//2 rempli (par default)
		w->p.graphic_mode = 3;

	//F2 Vue Parallele
	//F3 Vue Isometrique

	//Gestion des couleurs

	//1 solide de base
	//2 smooth+solide de base
	//3 smooth
	//4 filaire
	//mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	//ft_putnbr(w->point.y);
	//ft_putchar('\n');
	//ft_putnbr(w->point.x);
	//ft_putchar('\n');
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int					main(int argc, char **argv)
{
	t_wind			w;

	if (argc != 2)
		ft_putstr("usage");
	ft_putendl("fdf");
	w.mlx = mlx_init();
	w.width = 1024;
	w.height = 800;
	w.title = "42 minilibx";
	w.win = mlx_new_window(w.mlx, w.width, w.height, w.title);

	ft_putstr("degree_to_radian :");
	ft_putnbr(degree_to_radian(90));
	ft_putchar('\n');

	

	w.img.x_centerpoint = 500;
	w.img.y_centerpoint = 370;

	// Parameters:
	w.p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w.p.accentuation = 4;// On peut mettre une accentuation à 10 pour compenser les maps avec des petits chiffres ;). Default = 1
	w.p.angle_projpara = 30;
	w.p.size_square = 30;
	w.p.rot_x = 0; // Rotation x par défault

	//w.img.point.x = 50;
	//w.img.point.y = 500;
	w.img.point.color = 0xFFFFFF;

	(w.b.nbr_of_line) = 0;
	(w.b.nbr_elem_line) = 0;
	w.b.tab_int = browsefile(argv[1], &w.b.nbr_of_line, &w.b.nbr_elem_line);

	create_new_img(&w);
	//Position of image in window
	w.img.x = 0;
	w.img.y = 0;
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	//*(w.img.pxl_ptr + 32) = (int)"0x00FFFFFF";

	mlx_key_hook(w.win, my_key_function, &w);
	mlx_expose_hook(w.win, my_expose_hook, &w);
	//mlx_mouse_hook(w.win, my_mouse_function, &w);
	mlx_loop(w.mlx);
	return (0);
}
