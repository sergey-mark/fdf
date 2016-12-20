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

void					pencil_fluid(t_wind *w, int x, int y)
{
	static t_point		prevp;
	t_point				currp;

	currp.x = x;
	currp.y = y;
	if (prevp.x && prevp.y && (prevp.x != x || prevp.y != y))
	{
		draw_line(w, prevp, currp);
	}
	else
		pencil(w, x, y);
	prevp.x = x; //save position of previous dot
	prevp.y = y;
}

void			pencil(t_wind *w, int x, int y)
{
	int			i;
	int			j;
	int			brushsize;

	brushsize = 1;
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
}

int		keypress_function(int keycode, t_wind *w)
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
		if (w->obj.showgiz.t)
			w->obj.showgiz.t = 0;
		else
		{
			w->obj.showgiz.t = 1;
			w->obj.showgiz.r = 0;
			w->obj.showgiz.s = 0;
		}
	}
	else if (keycode == KEY_E) // key E - Rotate gizmo
	{
		if (w->obj.showgiz.r)
			w->obj.showgiz.r = 0;
		else
		{
			ft_putstr("show rotate giz\n");
			w->obj.showgiz.r = 1;
			w->obj.showgiz.t = 0;
			w->obj.showgiz.s = 0;
		}
	}
	else if (keycode == KEY_R) // key R - Scale gizmo
	{
		if (w->obj.showgiz.s)
			w->obj.showgiz.s = 0;
		else
		{
			ft_putstr("show rotate giz\n");
			w->obj.showgiz.s = 1;
			w->obj.showgiz.t = 0;
			w->obj.showgiz.r = 0;
		}
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
	// ESPACE (to use in addition of mouse left clic to move object)
	if (keycode == SPACE)
	{
		ft_putendl("spacemove on");
		w->p.space_mousemove = 1;
	}
	// ROTATION:
	if (keycode == L_ARROW) // fleche gauche
	{
		if (w->p.rot.z >= 360 || w->p.rot.z <= -360)
			w->p.rot.z %= 360;
		w->p.rot.z -= 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == R_ARROW) // fleche droite
	{
		if (w->p.rot.z >= 360 || w->p.rot.z <= -360)
			w->p.rot.z %= 360;
		w->p.rot.z += 5;
		ft_putstr("rotz:");
		ft_putnbr(w->p.rot.z);
		ft_putchar('\n');
	}
	else if (keycode == U_ARROW) // fleche haut
	{
		if (w->p.rot.x >= 360 || w->p.rot.x <= -360)
			w->p.rot.x %= 360;
		w->p.rot.x += 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == D_ARROW) // fleche bas
	{
		if (w->p.rot.x >= 360 || w->p.rot.x <= -360)
			w->p.rot.x %= 360;
		w->p.rot.x -= 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
	}
	else if (keycode == BACKSLASH) //basckslash (rotate y)
	{
		if (w->p.rot.y >= 360 || w->p.rot.y <= -360)
			w->p.rot.y %= 360;
		w->p.rot.y -= 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	else if (keycode == EXCLAMMARK) //exclamation point (rotate y)
	{
		if (w->p.rot.y >= 360 || w->p.rot.y <= -360)
			w->p.rot.y %= 360;
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
			w->obj.gizt.t.y -= 10;
		else
		{
			w->p.t.y -= 10;
			w->obj.gizt.t.y -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_D)//bas (pav num)
	{
		if (w->p.insert)
			w->obj.gizt.t.y += 10;
		else
		{
			w->p.t.y += 10;
			w->obj.gizt.t.y += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_R)//droite (pav num)
	{
		if (w->p.insert)
			w->obj.gizt.t.x += 10;
		else
		{
			w->p.t.x += 10;
			w->obj.gizt.t.x += 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_L)//gauche (pav num)
	{
		if (w->p.insert)
			w->obj.gizt.t.x -= 10;
		else
		{
			w->p.t.x -= 10;
			w->obj.gizt.t.x -= 10; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_1)//touche 1 (pav num)
	{
		if (w->p.insert)
			w->obj.gizt.t.z -= 10;
		else
		{
			w->p.t.z -= 5;
			w->obj.gizt.t.z -= 5; //Move the gizmo in the same time
		}
	}
	else if (keycode == NUM_3)//touche 3 (pav num)
	{
		if (w->p.insert)
			w->obj.gizt.t.z += 10;
		else
		{
			w->p.t.z += 5;
			w->obj.gizt.t.z += 5; //Move the gizmo in the same time
		}
	}
	// ZOOM:
	if (keycode == ZOOM_P)//plus (pav num)
	{
		w->p.x_spacing++;
		w->p.y_spacing++;
	}
	if (keycode == ZOOM_M)//moins (pav num)
	{
		w->p.x_spacing--;
		w->p.y_spacing--;
	}
	// ACCENTUATION (Hauteur du terrain)
	if (keycode == PAGE_U)//page up
	{
		w->p.zaccentuation++;
		ft_putnbr(w->p.zaccentuation);
	}
	if (keycode == PAGE_D)//page down
	{
		w->p.zaccentuation--;
		ft_putnbr(w->p.zaccentuation);
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
		{
			w->p.graphic_mode = 3;
			w->p.dot = 1;
		}
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

int		keyRelease_function(int keycode, t_wind *w)
{
	if (keycode == SPACE)
	{
		ft_putendl("spacemove off");
		w->p.space_mousemove = 0;
	}
	return (0);
}

int		mousepress_function(int button, int x, int y, t_wind *w)
{
	//J'enregistre le point x,y de depart du clic, et la rotation de départ:
	w->p.m.memm_x = x;
	w->p.m.memm_y = y;
	if (button == 1)
	{
		w->p.m.button1 = 1;
		w->p.m.mem_rotz = w->p.rot.z; // Horizontal mouse object turn
		w->p.m.mem_rotx = w->p.rot.x; // vertical mouse object turn
		w->p.m.mem_posx = w->p.t.x; // Horizontal mouse object pos (when space key press)
		w->p.m.mem_posy = w->p.t.y; // Verticale mouse object pos
		w->p.m.mem_gizx = w->obj.gizt.t.x; // Horizontal mouse object pos (when space key press)
		w->p.m.mem_gizy = w->obj.gizt.t.y; // Verticale mouse object pos
	}
	else if (button == 2)
	{
		w->p.m.button2 = 1;
		w->p.m.mem_spacing_x = w->p.x_spacing; // Horizontale save x_spacing
		w->p.m.mem_zaccentuation = w->p.zaccentuation; // Vertical save zaccentuation
	}
	else if (button == 3)
	{
		ft_putendl("button molette:");
		ft_putnbr(button);
		w->p.m.button3 = 1;
	}
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
	int	spacing_sens;
	int	transl_sens;

	spacing_sens = 25;
	transl_sens = 1000;
	if (w->p.m.button1 == 1 && w->p.paint == 1)
		pencil(w, x, y);
	if (w->p.paint == 0)
	{
		if (w->p.m.button1 == 1)
		{
			if (w->p.space_mousemove == 1)
			{
				ft_putendl("space_mousemove");
				w->p.t.x = w->p.m.mem_posx + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)transl_sens); //J'actualise la rotation de l'objet:
				w->p.t.y = w->p.m.mem_posy + (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)transl_sens); //J'actualise la rotation de l'objet:
				w->obj.gizt.t.x = w->p.m.mem_gizx + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)transl_sens); // Deplacement du gizmo
				w->obj.gizt.t.y = w->p.m.mem_gizy + (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)transl_sens); //J'actualise la rotation de l'objet:
			}
			else
			{
				w->p.rot.z = w->p.m.mem_rotz - (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) * (float)360); //J'actualise la rotation de l'objet:
				w->p.rot.x = w->p.m.mem_rotx - (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) * (float)360); //J'actualise la rotation de l'objet vers le haut (pour permettre une rotation complete autour de l'objet avec la souris)
			}
		}
		else if (w->p.m.button2 == 1)
		{
			w->p.x_spacing = w->p.m.mem_spacing_x + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)spacing_sens); //J'actualise la rotation de l'objet:
			w->p.zaccentuation = w->p.m.mem_zaccentuation - (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)spacing_sens); //J'actualise la rotation de l'objet:
		}
		else if (w->p.m.button3 == 1)
			ft_putendl("button3");
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
