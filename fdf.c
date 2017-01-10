/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:17:23 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/10 16:30:43 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define BUTTONRELEASE		5
#define BUTTONRELEASEMASK	(1L<<3)
#define MOTIONNOTIFY		6
#define BUTTONMOTIONMASK	(1L<<13)
#define KEYPRESS			2
#define KEYPRESSMASK		(1L<<0)
#define KEYRELEASE			3
#define KEYRELEASEMASK		(1L<<1)

static void		set_gizmo(t_wind *w)
{
	w->p.m.mem_gizx = 0;
	w->obj.showgiz.t = 1;
	w->obj.showgiz.r = 0;
	w->obj.showgiz.s = 0;
}

static int		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;
	w->img.margin = 100;
	w->p.graphic_mode = 2;
	w->p.view_mode = 3;
	w->p.help = 1;
	w->p.turntable = 0;
	w->p.space_mousemove = 0;
	w->p.m.button1 = 0;
	w->p.m.button2 = 0;
	w->p.m.button3 = 0;
	w->p.paint = 0;
	w->p.dot = 0;
	set_gizmo(w);
	w->obj.f.bol = 0;
	w->obj.f.bolfill = 0;
	w->p.y_spacing = (w->img.height - w->img.margin * 2) / (w->b.nbr_of_line);
	w->p.x_spacing = (w->img.width - w->img.margin * 2) / (w->b.nbr_elem_line);
	w->img.x_centerpoint = w->img.width / 2;
	w->img.y_centerpoint = w->img.height / 2;
	w->p.insert = 0;
	w->img.x = 0;
	w->img.y = 0;
	return (0);
}

int				fdf(char *filename)
{
	t_wind		w;

	w.width = 800;
	w.height = 600;
	w = create_new_window("42 minilibx", w.width, w.height);
	if (browsefile(filename, &w.b.nbr_of_line, &w.b.nbr_elem_line) == NULL)
		return (0);
	else
		w.b.tab_int = browsefile(filename, &w.b.nbr_of_line,
	&w.b.nbr_elem_line);
	set_parameters(&w);
	def_all_preui(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	mlx_mouse_hook(w.win, mousepress_function, &w);
	mlx_hook(w.win, BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release_function,
	&w);
	mlx_hook(w.win, MOTIONNOTIFY, BUTTONMOTIONMASK, mouse_motion_function, &w);
	mlx_hook(w.win, KEYPRESS, KEYPRESSMASK, keypress_function, &w);
	mlx_hook(w.win, KEYRELEASE, KEYRELEASEMASK, key_release_function, &w);
	mlx_loop_hook(w.mlx, turntable, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}
