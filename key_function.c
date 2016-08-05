#include "fdf.h"

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int		key_function(int keycode, t_wind *w)
{
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	// ECHAP (to quit)
	if (keycode == 65307)
		exit(0);
	// ROTATION:
	if (keycode == 65361 && w->img.x >= 0) // fleche gauche
		w->img.x -= 5;
	else if (keycode == 65363 && w->img.x < w->width) // fleche droite
		w->img.x += 5;
	else if (keycode == 65362 && w->img.y >= 0) // fleche haut
	{
		w->p.rot_x += 1;
		//w->img.y += 5;
	}
	else if (keycode == 65364 && w->img.y < w->height) // fleche bas
	{
		w->p.rot_x -= 1;
		//w->img.y -= 5;
	}
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
		w->p.size_square++;
		w->p.angle_projpara++;
	}
	if (keycode == 65453)//moins (pav num)
	{
		w->p.size_square--;
		w->p.angle_projpara--;
	}
	// ACCENTUATION (Hauteur du terrain)
	if (keycode == 65365)//page up
		w->p.accentuation++;
	if (keycode == 65366)//page down
		w->p.accentuation--;
	// GRAPHIC MODES: (touche 1 à zéro)
	if (keycode == 38)//1 poitille
		w->p.graphic_mode = 1;
	else if (keycode == 233)//2 filaire (par default)
		w->p.graphic_mode = 2;
	else if (keycode == 34)//2 rempli (par default)
		w->p.graphic_mode = 3;
	// VUE
	//F2 Vue Parallele
	//F3 Vue Isometrique
	// COULEURS
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w, w->img.width, w->img.height);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

/*
static int		my_mouse_function(int keycode, t_wind *w)
{
»···ft_putnbr(w->point.x);
»···ft_putendl("Keyevent");
»···ft_putnbr(keycode);
»···ft_putchar('\n');
	*/
	//if (keycode == 1 && w->point.x >= 0) // fleche gauche
		//ft_putendl("clic gauche");//w->point.x -= 5;
	/*
»···else if (keycode == 65363 && w->point.x < w->width) // fleche droite
»···»···w->point.x += 5;
»···else if (keycode == 65362 && w->point.x >= 0) // fleche haut
»···»···w->point.y -= 5;
»···else if (keycode == 65364 && w->point.x < w->height) // fleche bas
»···»···w->point.y += 5;
»···*/
	//ft_putnbr(w->point.y);
	//mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	/*
»···return (0);
}*/
