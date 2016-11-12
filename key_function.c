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
	if (keycode == EXIT)
		exit(0);
	//SHOW CONTROLLER:
	if (keycode == KEY_W) // key W - Move gizmo
	{
		if (w->r.show)
			w->r.show = 0;
		else
			w->r.show = 1;
	}
	//TURN TABLE (Rotation of 3d model):
	if (keycode == KEY_T) // key T
	{
		if (w->p.turntable)
			w->p.turntable = 0;
		else
		{
			ft_putendl("turntable on");
			w->p.turntable = 1;
		}
	}
	//PAINT
	if (keycode == KEY_P) // key P
	{
		if (w->p.paint)
			w->p.paint = 0;
		else
			w->p.paint = 1;
	}
	// ROTATION:
	if (keycode == L_ARROW) // fleche gauche
	{
		w->p.rot.z -= 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == R_ARROW) // fleche droite
	{
		w->p.rot.z += 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == U_ARROW) // fleche haut
	{
		w->p.rot.x += 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == D_ARROW) // fleche bas
	{
		w->p.rot.x -= 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == BACKSLASH) //basckslash (rotate y)
	{
		w->p.rot.y -= 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	else if (keycode == EXCLAMMARK) //exclamation point (rotate y)
	{
		w->p.rot.y += 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	// MODIFICATION POINT DE ROTATION
	if (keycode == INSERT) // Touche Insert
	{
		if (w->p.insert)
			w->p.insert = 0;
		else
			w->p.insert = 1;
	}
	// DEPLACEMENT LATERAL (pan) (Pavé numérique)
	if (keycode == NUM_U)//haut (pav num)
	{
		if (w->p.insert)
			w->r.t.y -= 10;
		else
		{
			w->p.t.y -= 10;
			w->r.t.y -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_D)//bas (pav num)
	{
		if (w->p.insert)
			w->r.t.y += 10;
		else
		{
			w->p.t.y += 10;
			w->r.t.y += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_R)//droite (pav num)
	{
		if (w->p.insert)
			w->r.t.x += 10;
		else
		{
			w->p.t.x += 10;
			w->r.t.x += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_L)//gauche (pav num)
	{
		if (w->p.insert)
			w->r.t.x -= 10;
		else
		{
			w->p.t.x -= 10;
			w->r.t.x -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_1)//touche 1 (pav num)
	{
		if (w->p.insert)
			w->r.t.z -= 10;
		else
		{
			w->p.t.z -= 10;
			w->r.t.z -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_3)//touche 3 (pav num)
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
	if (keycode == ZOOM_P)//plus (pav num)
	{
		w->p.size_square++;
		w->p.angle_projpara++;
	}
	if (keycode == ZOOM_M)//moins (pav num)
	{
		w->p.size_square--;
		w->p.angle_projpara--;
	}
	// ACCENTUATION (Hauteur du terrain)
	if (keycode == PAGE_U)//page up
	{
		w->p.accentuation++;
		//ft_putnbr(w->p.accentuation);
	}
	if (keycode == PAGE_D)//page down
	{
		w->p.accentuation--;
		//ft_putnbr(w->p.accentuation);
	}
	// GRAPHIC MODES: (touche 1 à zéro)
	if (keycode == KEY_1)//1 poitille
	{
		ft_putendl("mode point");
		w->p.graphic_mode = 1;
	}
	else if (keycode == KEY_2)//2 filaire (par default)
	{
		ft_putendl("mode filaire");
		w->p.graphic_mode = 2;
	}
	else if (keycode == KEY_3)//3 triangulate
	{
		ft_putendl("mode triangulate");
		w->p.graphic_mode = 3;
	}
	else if (keycode == KEY_4)//4 rempli
	{
		ft_putendl("mode fill");
		w->p.graphic_mode = 4;
	}
	else if (keycode == KEY_I)// i pour afficher point
	{
		ft_putendl("point");
		if (w->p.dot == 1)
			w->p.dot = 0;
		else
			w->p.dot = 1;
	}
	// VUE
	if (keycode == F1)//F1 HELP
	{
		if (w->p.help == 1)
			w->p.help = 0;
		else
			w->p.help = 1;
	}
	else if (keycode == F2)//F2 Vue Isometrique
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	else if (keycode == F3)//F3 Vue Parallèle
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
	// COULEURS
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int		pencil(t_wind *w, int x, int y)
{
	int	i;
	int	j;
	int	brushsize;

	brushsize = 3;
	i = x - brushsize;
	while (i != (x+brushsize))
	{
		j = y - brushsize;
		while (j != (y+brushsize))
		{
			if (dot_in_window(w, i, j))
				draw_point(w, i, j, "0xFFFFFF");
			j++;
		}
		i++;
	}
	return (0);
}

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

int		mousepress_function(int button, int x, int y, t_wind *w)
{
	ft_putnbr(y);
	ft_putchar('\n');
	if (button == 1)
	{
		//on set le button en clic (1) (au lieu du onRelease en 0).
		w->p.m.button1 = 1;
		//J'enregistre le point x,y de part du clic, et la rotation de départ:
		w->p.m.memm_x = x;
		w->p.m.memm_y = y;
		w->p.m.mem_rotz = w->p.rot.z;
	}
	else if (button == 2)
		w->p.m.button2 = 1;
	else if (button == 3)
		w->p.m.button3 = 1;
	//mlx_destroy_image(w->mlx, w->img.ptr_img);
	//create_new_img(w);
	//if (button == 1)
		//mlx_loop_hook(w->mlx, pencil(), &w);

	//draw_point(w, x, y, "0xFFFFFF");
	//draw_point(w, x, y, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int		mouseRelease_function(int button, int x, int y, t_wind *w)
{
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	if (button == 1)
		w->p.m.button1 = 0;
	else if (button == 2)
		w->p.m.button2 = 0;
	else if (button == 3)
		w->p.m.button3 = 0;
	return (0);
}

int		mouseMotion_function(int x, int y, t_wind *w)
{
	if (w->p.m.button1 == 1 && w->p.paint == 1)
		pencil(w, x, y);
	else
	{
		if (w->p.m.button1 == 1)
			w->p.rot.z = w->p.m.mem_rotz - (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) * (float)360); //J'actualise la rotation de l'objet:
		if (w->p.m.button2 == 1)
		{
			w->p.size_square++;
			w->p.angle_projpara++;
			ft_putnbr(y);
		}
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}


