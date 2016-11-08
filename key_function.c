#include "fdf.h"

int			expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int			turntable(t_wind *w)
{
	if (w->p.turntable)
	{
		if (w->p.rot.z >= 360)
			w->p.rot.z %= 360;
		w->p.rot.z += 5;
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
		mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
		help(w);
	}
	return (0);
}

int			key_function(int keycode, t_wind *w)
{
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	// ECHAP (to quit)
	if (keycode == 65307)
		exit(0);
	//SHOW CONTROLLER:
	if (keycode == 119) // key W - Move gizmo
	{
		if (w->r.show)
			w->r.show = 0;
		else
			w->r.show = 1;
	}
	//TURN TABLE (Rotation of 3d model):
	if (keycode == 116) // key T
	{
		if (w->p.turntable)
			w->p.turntable = 0;
		else
		{
			ft_putendl("turntable on");
			w->p.turntable = 1;
		}
	}
	// ROTATION:
	if (keycode == 65361) // fleche gauche
	{
		w->p.rot.z -= 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == 65363) // fleche droite
	{
		w->p.rot.z += 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == 65362) // fleche haut
	{
		w->p.rot.x += 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == 65364) // fleche bas
	{
		w->p.rot.x -= 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == 33) //basckslash (rotate y)
	{
		w->p.rot.y -= 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	else if (keycode == 58) //exclamation point (rotate y)
	{
		w->p.rot.y += 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	// MODIFICATION POINT DE ROTATION
	if (keycode == 65379) // Touche Insert
	{
		if (w->p.insert)
			w->p.insert = 0;
		else
			w->p.insert = 1;
	}
	// DEPLACEMENT LATERAL (pan) (Pavé numérique)
	if (keycode == 65431)//haut (pav num)
	{
		if (w->p.insert)
			w->r.t.y -= 10;
		else
		{
			w->p.t.y -= 10;
			w->r.t.y -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == 65433)//bas (pav num)
	{
		if (w->p.insert)
			w->r.t.y += 10;
		else
		{
			w->p.t.y += 10;
			w->r.t.y += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == 65432)//droite (pav num)
	{
		if (w->p.insert)
			w->r.t.x += 10;
		else
		{
			w->p.t.x += 10;
			w->r.t.x += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == 65430)//gauche (pav num)
	{
		if (w->p.insert)
			w->r.t.x -= 10;
		else
		{
			w->p.t.x -= 10;
			w->r.t.x -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == 65436)//touche 1 (pav num)
	{
		if (w->p.insert)
			w->r.t.z -= 10;
		else
		{
			w->p.t.z -= 10;
			w->r.t.z -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == 65435)//touche 3 (pav num)
	{
		if (w->p.insert)
			w->r.t.z += 10;
		else
		{
			w->p.t.z += 10;
			w->r.t.z += 10; //Move the gizmo in the same time
		}
	}
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

int		keypress_function(int keycode, t_wind *w)
{
	//ft_putendl("keypress!!!");
	if (keycode != 0)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
		ft_putnbr(w->p.help);
		ft_putchar('\n');
	}
	return (0);
}
/*
int		mousepress_function(int button, int x, int y, t_wind *w)
{
	ft_putendl("mousepress!!!");
	if (button != 0)
	{
		ft_putendl("button:");
		ft_putnbr(button);
		ft_putchar('\n');
		ft_putnbr(x);
		ft_putchar('\n');
		ft_putnbr(y);
		ft_putchar('\n');
		ft_putnbr(w->p.help);
		ft_putchar('\n');
	}
	return (0);
}*/

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

	//draw_point(w, x, y, "0xFFFFFF");
	draw_point(w, x, y, 0);

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
