#include "fdf.h"

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

int		mousepress_function(int button, int x, int y, t_wind *w)
{
	w->p.m.memm_x = x;
	w->p.m.memm_y = y;
	if (button == 1)
	{
		w->p.m.button1 = 1;
		w->p.m.mem_rotz = w->p.rot.z; 
		w->p.m.mem_rotx = w->p.rot.x; 
		w->p.m.mem_posx = w->p.t.x; 
		w->p.m.mem_posy = w->p.t.y; 
		w->p.m.mem_gizx = w->obj.gizt.t.x; 
		w->p.m.mem_gizy = w->obj.gizt.t.y; 
	}
	else if (button == 2)
	{
		w->p.m.button2 = 1;
		w->p.m.mem_spacing_x = w->p.x_spacing; 
		w->p.m.mem_zaccentuation = w->p.zaccentuation; 
	}
	else if (button == 3)
		w->p.m.button3 = 1;
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int		mouseRelease_function(int button, int x, int y, t_wind *w)
{
	ft_putnbr(x);
	ft_putnbr(y);
	if (button == 1)
		w->p.m.button1 = 0;
	else if (button == 2)
		w->p.m.button2 = 0;
	else if (button == 3)
		w->p.m.button3 = 0;
	return (0);
}

static void			fc_bt1_mousemove(int x, int y, t_wind *w)
{
	int				transl_sens;

	transl_sens = 1000;

	if (w->p.space_mousemove == 1)
	{
		w->p.t.x = w->p.m.mem_posx + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)transl_sens); 
		w->p.t.y = w->p.m.mem_posy + (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)transl_sens); 
		w->obj.gizt.t.x = w->p.m.mem_gizx + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)transl_sens); 
		w->obj.gizt.t.y = w->p.m.mem_gizy + (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)transl_sens);
	}
	else
	{
		w->p.rot.z = w->p.m.mem_rotz - (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) * (float)360); 
		w->p.rot.x = w->p.m.mem_rotx - (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) * (float)360); 
	}
}

int					mouseMotion_function(int x, int y, t_wind *w)
{
	int				spacing_sens;

	spacing_sens = 25;
	if (w->p.m.button1 == 1 && w->p.paint == 1)
		pencil(w, x, y);
	if (w->p.paint == 0)
	{
		if (w->p.m.button1 == 1)
			fc_bt1_mousemove(x, y, w);
		else if (w->p.m.button2 == 1)
		{
			w->p.x_spacing = w->p.m.mem_spacing_x + (int)(((float)(x - w->p.m.memm_x)/(float)w->img.width) *(float)spacing_sens); 
			w->p.zaccentuation = w->p.m.mem_zaccentuation - (int)(((float)(y - w->p.m.memm_y)/(float)w->img.height) *(float)spacing_sens); 
		}
		mlx_destroy_image(w->mlx, w->img.ptr_img);
		create_new_img(w);
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
