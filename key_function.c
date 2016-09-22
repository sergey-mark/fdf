#include "fdf.h"

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int		key_function(int keycode, t_wind *w)
{
	w->p.keypress = 1;
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	// ECHAP (to quit)
	if (keycode == 65307)
		exit(0);
	// ROTATION:
	if (keycode == 65361) // fleche gauche
	{
		if (w->p.insert)
		{
			w->r.p_y.x -= 10;
			w->r.pd_y.x -= 10;
			w->r.p_x.x -= 10;
			w->r.pd_x.x -= 10;
		}
		else
		{
			w->p.rot.z -= 5;
			ft_putstr("roty:");
			ft_putnbr(w->p.rot.y);
			ft_putchar('\n');
		}
	}
	else if (keycode == 65363) // fleche droite
	{
		if (w->p.insert)
		{
			w->r.p_y.x += 10;
			w->r.pd_y.x += 10;
			w->r.p_x.x += 10;
			w->r.pd_x.x += 10;
		}
		else
		{
			w->p.rot.z += 5;
			ft_putstr("roty:");
			ft_putnbr(w->p.rot.y);
			ft_putchar('\n');
		}
	}
	else if (keycode == 65362) // fleche haut
	{
		if (w->p.insert)
		{
			w->r.p_y.y -= 10;
			w->r.pd_y.y -= 10;
			w->r.p_x.y -= 10;
			w->r.pd_x.y -= 10;
		}
		else
		{
			//w->p.keycode = 65362;
			w->p.rot.x += 5;
			ft_putstr("rotx:");
			ft_putnbr(w->p.rot.x);
			ft_putchar('\n');
		}
	}
	else if (keycode == 65364) // fleche bas
	{
		if (w->p.insert)
		{
			w->r.p_x.y += 10;
			w->r.pd_x.y += 10;
			w->r.p_y.y += 10;
			w->r.pd_y.y += 10;
		}
		else
		{
			w->p.rot.x -= 5;
			ft_putstr("rotx:");
			ft_putnbr(w->p.rot.x);
			ft_putchar('\n');
		}
	}
	// MODIFICATION POINT DE ROTATION
	if (keycode == 65379) // Touche Insert
	{
		if (w->p.insert)
			w->p.insert = 0;
		else
		{
			w->p.insert = 1;
			//Memorise previous RotationCenter while press insert (to move RoationCenter)
			w->r.oldp_y.x = w->r.p_y.x;
			w->r.oldp_x.y = w->r.p_x.y;
		}
	}
	// DEPLACEMENT LATERAL (pan) (Pavé numérique)
	if (keycode == 65431)//haut (pav num)
		w->img.padv -= 10;
	else if (keycode == 65433)//bas (pav num)
		w->img.padv += 10;
	else if (keycode == 65432)//droite (pav num)
		w->img.padh += 10;
	else if (keycode == 65430)//gauche (pav num)
		w->img.padh -= 10;
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
	{
		w->p.accentuation++;
		//ft_putnbr(w->p.accentuation);
	}
	if (keycode == 65366)//page down
	{
		w->p.accentuation--;
		//ft_putnbr(w->p.accentuation);
	}
	// GRAPHIC MODES: (touche 1 à zéro)
	if (keycode == 38)//1 poitille
	{
		ft_putendl("mode point");
		w->p.graphic_mode = 1;
	}
	else if (keycode == 233)//2 filaire (par default)
	{
		ft_putendl("mode filaire");
		w->p.graphic_mode = 2;
	}
	else if (keycode == 34)//3 triangulate
	{
		ft_putendl("mode triangulate");
		w->p.graphic_mode = 3;
	}
	else if (keycode == 39)//4 rempli
	{
		ft_putendl("mode fill");
		w->p.graphic_mode = 4;
	}
	else if (keycode == 105)// i pour afficher point
	{
		ft_putendl("point");
		if (w->p.dot == 1)
			w->p.dot = 0;
		else
			w->p.dot = 1;
	}
	// VUE
	if (keycode == 65470)//F1 HELP
	{
		if (w->p.help == 1)
			w->p.help = 0;
		else
			w->p.help = 1;
	}
	else if (keycode == 65471)//F2 Vue Isometrique
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	else if (keycode == 65472)//F3 Vue Parallèle
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
	// COULEURS
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
/*
int	pencil(int x, int y, t_wind *w)
{
	ft_putstr("test");
	draw_point(w, x, y, "0xFFFFFF");
	ft_putstr("test2");
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
*/
int		keypress_func(t_wind *w)
{
	w->p.keypress = 0;
	if (w->p.keycode == 65362)
	{
			w->p.rot.x += 5;
			ft_putstr("rotx:");
			ft_putnbr(w->p.rot.x);
			ft_putchar('\n');
	}
	return (0);
}

int		mouse_function(int button, int x, int y, t_wind *w)
{
	ft_putnbr(w->point.x);
	ft_putchar('\n');
	ft_putendl("button:");
	ft_putnbr(button);
	ft_putchar('\n');
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	
	//mlx_destroy_image(w->mlx, w->img.ptr_img);
	//create_new_img(w);
	//if (button == 1)
		//mlx_loop_hook(w->mlx, pencil(), &w);

	draw_point(w, x, y, "0xFFFFFF");

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
