/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_function02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:41:28 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 17:12:16 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		keypress_function04(int keycode, t_wind *w)
{
	if (keycode == KEY_1)
		w->p.graphic_mode = 1;
	else if (keycode == KEY_2)
		w->p.graphic_mode = 2;
	else if (keycode == KEY_3)
		w->p.graphic_mode = 3;
	else if (keycode == KEY_4)
		w->p.graphic_mode = 4;
	if (keycode == KEY_I)
	{
		if (w->p.dot == 1)
			(w->p.dot = 0);
		else
			(w->p.dot = 1);
	}
	if (keycode == F1)
	{
		if (w->p.help == 1)
			(w->p.help = 0);
		else
			(w->p.help = 1);
	}
}

static void		keypress_function05(int keycode, t_wind *w)
{
	if (keycode == F2)
		w->p.view_mode = 2;
	else if (keycode == F3)
		w->p.view_mode = 3;
	if (keycode == PAGE_U)
		w->p.zaccentuation++;
	if (keycode == PAGE_D)
		w->p.zaccentuation--;
	if (keycode == ZOOM_P)
	{
		w->p.x_spacing++;
		w->p.y_spacing++;
	}
	else if (keycode == ZOOM_M)
	{
		w->p.x_spacing--;
		w->p.y_spacing--;
	}
}

static void		keypress_function03(int keycode, t_wind *w)
{
	if (keycode == NUM_1)
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
			(w->obj.gizt.t.z += 10);
		else
		{
			w->p.t.z += 5;
			w->obj.gizt.t.z += 5;
		}
	}
	keypress_function04(keycode, w);
	keypress_function05(keycode, w);
}

void			keypress_function02(int keycode, t_wind *w)
{
	if (keycode == NUM_U)
	{
		w->obj.gizt.t.y -= 10;
		if (!w->p.insert)
			w->p.t.y -= 10;
	}
	else if (keycode == NUM_D)
	{
		w->obj.gizt.t.y += 10;
		if (!w->p.insert)
			w->p.t.y += 10;
	}
	else if (keycode == NUM_R)
	{
		w->obj.gizt.t.x += 10;
		if (!w->p.insert)
			w->p.t.x += 10;
	}
	else if (keycode == NUM_L)
	{
		w->obj.gizt.t.x -= 10;
		if (!w->p.insert)
			w->p.t.x -= 10;
	}
	keypress_function03(keycode, w);
}
