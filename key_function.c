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

int		keypress_function(int keycode, t_wind *w)
{
	if (keycode == EXIT)
		exit(0);
	if (keycode == KEY_W) 
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
	else if (keycode == KEY_E) 
	{
		if (w->obj.showgiz.r)
			w->obj.showgiz.r = 0;
		else
		{
			w->obj.showgiz.r = 1;
			w->obj.showgiz.t = 0;
			w->obj.showgiz.s = 0;
		}
	}
	else if (keycode == KEY_R) 
	{
		if (w->obj.showgiz.s)
			w->obj.showgiz.s = 0;
		else
		{
			w->obj.showgiz.s = 1;
			w->obj.showgiz.t = 0;
			w->obj.showgiz.r = 0;
		}
	}
	if (keycode == KEY_T) 
	{
		if (w->p.turntable)
			w->p.turntable = 0;
		else
			w->p.turntable = 1;
	}
	if (keycode == KEY_P) 
	{
		if (w->p.paint)
			w->p.paint = 0;
		else
			w->p.paint = 1;
	}
	if (keycode == SPACE)
		w->p.space_mousemove = 1;
	if (keycode == L_ARROW) 
	{
		if (w->p.rot.z >= 360 || w->p.rot.z <= -360)
			w->p.rot.z %= 360;
		if (w->p.view_mode == 2)
			w->p.rot.z += 45;
		else
			w->p.rot.z -= 5;
	}
	else if (keycode == R_ARROW) 
	{
		if (w->p.rot.z >= 360 || w->p.rot.z <= -360)
			w->p.rot.z %= 360;
		if (w->p.view_mode == 2)
			w->p.rot.z -= 45;
		else
			w->p.rot.z += 5;
	}
	else if (keycode == U_ARROW) 
	{
		if (w->p.rot.x >= 360 || w->p.rot.x <= -360)
			w->p.rot.x %= 360;
		w->p.rot.x += 5;
	}
	else if (keycode == D_ARROW) 
	{
		if (w->p.rot.x >= 360 || w->p.rot.x <= -360)
			w->p.rot.x %= 360;
		w->p.rot.x -= 5;
	}
	else if (keycode == BACKSLASH) 
	{
		if (w->p.rot.y >= 360 || w->p.rot.y <= -360)
			w->p.rot.y %= 360;
		w->p.rot.y -= 5;
	}
	else if (keycode == EXCLAMMARK) 
	{
		if (w->p.rot.y >= 360 || w->p.rot.y <= -360)
			w->p.rot.y %= 360;
		w->p.rot.y += 5;
	}
	if (keycode == INSERT) 
	{
		if (w->p.insert)
			w->p.insert = 0;
		else
			w->p.insert = 1;
	}
	if (keycode == NUM_U)
	{
		if (w->p.insert)
			w->obj.gizt.t.y -= 10;
		else
		{
			w->p.t.y -= 10;
			w->obj.gizt.t.y -= 10; 
		}
	}
	else if (keycode == NUM_D)
	{
		if (w->p.insert)
			w->obj.gizt.t.y += 10;
		else
		{
			w->p.t.y += 10;
			w->obj.gizt.t.y += 10; 
		}
	}
	else if (keycode == NUM_R)
	{
		if (w->p.insert)
			w->obj.gizt.t.x += 10;
		else
		{
			w->p.t.x += 10;
			w->obj.gizt.t.x += 10; 
		}
	}
	else if (keycode == NUM_L)
	{
		if (w->p.insert)
			w->obj.gizt.t.x -= 10;
		else
		{
			w->p.t.x -= 10;
			w->obj.gizt.t.x -= 10; 
		}
	}
	else if (keycode == NUM_1)
	{
		if (w->p.insert)
			w->obj.gizt.t.z -= 10;
		else
		{
			w->p.t.z -= 5;
			w->obj.gizt.t.z -= 5; 
		}
	}
	else if (keycode == NUM_3)
	{
		if (w->p.insert)
			w->obj.gizt.t.z += 10;
		else
		{
			w->p.t.z += 5;
			w->obj.gizt.t.z += 5; 
		}
	}
	if (keycode == ZOOM_P)
	{
		w->p.x_spacing++;
		w->p.y_spacing++;
	}
	if (keycode == ZOOM_M)
	{
		w->p.x_spacing--;
		w->p.y_spacing--;
	}
	if (keycode == PAGE_U)
	{
		w->p.zaccentuation++;
		ft_putnbr(w->p.zaccentuation);
	}
	if (keycode == PAGE_D)
	{
		w->p.zaccentuation--;
		ft_putnbr(w->p.zaccentuation);
	}
	if (keycode == KEY_1)
		w->p.graphic_mode = 1;
	else if (keycode == KEY_2)
		w->p.graphic_mode = 2;
	else if (keycode == KEY_3)
		w->p.graphic_mode = 3;
	else if (keycode == KEY_4)
		w->p.graphic_mode = 4;
	else if (keycode == KEY_I)
	{
		if (w->p.dot == 1)
			w->p.dot = 0;
		else
		{
			w->p.graphic_mode = 3;
			w->p.dot = 1;
		}
	}
	if (keycode == F1)
	{
		if (w->p.help == 1)
			w->p.help = 0;
		else
			w->p.help = 1;
	}
	else if (keycode == F2)
		w->p.view_mode = 2; 
	else if (keycode == F3)
		w->p.view_mode = 3; 
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int		keyRelease_function(int keycode, t_wind *w)
{
	if (keycode == SPACE)
		w->p.space_mousemove = 0;
	return (0);
}
