/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:01:12 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 16:45:34 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define ROTABS(rot_z) ((rot_z >= 360 || rot_z <= -360) ? rot_z %= 360 : rot_z)

static void		keypress_function_giz(int keycode, t_wind *w)
{
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
}

static void		keypress_function00(int keycode, t_wind *w)
{
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
	if (keycode == INSERT)
	{
		if (w->p.insert)
			w->p.insert = 0;
		else
			w->p.insert = 1;
	}
}

static void		keypress_function01(int keycode, t_wind *w)
{
	if (keycode == L_ARROW)
	{
		if (w->p.view_mode == 2)
			w->p.rot.z += 45;
		else
			w->p.rot.z -= 5;
	}
	else if (keycode == R_ARROW)
	{
		if (w->p.view_mode == 2)
			w->p.rot.z -= 45;
		else
			w->p.rot.z += 5;
	}
	else if (keycode == U_ARROW)
		w->p.rot.x += 5;
	else if (keycode == D_ARROW)
		w->p.rot.x -= 5;
	else if (keycode == BACKSLASH)
		w->p.rot.y -= 5;
	else if (keycode == EXCLAMMARK)
		w->p.rot.y += 5;
}

int				keypress_function(int keycode, t_wind *w)
{
	if (keycode == EXIT)
		exit(0);
	ROTABS(w->p.rot.z);
	keypress_function_giz(keycode, w);
	keypress_function00(keycode, w);
	keypress_function01(keycode, w);
	keypress_function02(keycode, w);
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
