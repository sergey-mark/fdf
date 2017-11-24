/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_all_preui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:41:01 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 13:48:47 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		calc_zhigh(t_wind *w)
{
	int		x;
	int		y;
	int		max;
	int		min;

	min = 0;
	max = 1;
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line)
		{
			if (w->b.tab_int[y][x] > max)
				max = w->b.tab_int[y][x];
			if (w->b.tab_int[y][x] < min)
				min = w->b.tab_int[y][x];
			x++;
		}
		y++;
	}
	w->p.zaccentuation = 1;
	w->p.zhighest = max;
	w->p.zlowest = min;
	w->p.zmid = w->p.zlowest + ((w->p.zhighest - w->p.zlowest) / 2);
}

void		def_axle_rotation(t_wind *w)
{
	w->obj.gizt.p_x.x = w->img.x_centerpoint;
	w->obj.gizt.p_x.y = w->img.y_centerpoint;
	w->obj.gizt.p_x.z = 0;
	w->obj.gizt.pd_x.x = w->img.x_centerpoint + 50;
	w->obj.gizt.pd_x.y = w->img.y_centerpoint;
	w->obj.gizt.pd_x.z = 0;
	w->obj.gizt.p_y.x = w->img.x_centerpoint;
	w->obj.gizt.p_y.y = w->img.y_centerpoint;
	w->obj.gizt.p_y.z = 0;
	w->obj.gizt.pd_y.x = w->img.x_centerpoint;
	w->obj.gizt.pd_y.y = w->img.y_centerpoint + 50;
	w->obj.gizt.pd_y.z = 0;
	w->obj.gizt.p_z.x = w->img.x_centerpoint;
	w->obj.gizt.p_z.y = w->img.y_centerpoint;
	w->obj.gizt.p_z.z = 0;
	w->obj.gizt.pd_z.x = w->img.x_centerpoint;
	w->obj.gizt.pd_z.y = w->img.y_centerpoint;
	w->obj.gizt.pd_z.z = 0 + 50;
	w->obj.gizt.t.x = 0;
	w->obj.gizt.t.y = 0;
	w->obj.gizt.t.z = 0;
	w->obj.center_rgiz.x = w->img.x_centerpoint;
	w->obj.center_rgiz.y = w->img.y_centerpoint;
	w->obj.center_rgiz.z = w->img.z_centerpoint;
}

void		def_color(t_wind *w)
{
	w->p.color.hexa_top = "0xFFFFFF";
	w->p.color.hexa_mid = "0x024302";
	w->p.color.hexa_bot = "0x432502";
	w->p.color.hexa_default = "0x9E11BF";
	w->p.color.hexa_bool = 0;
}

void		def_tranrotscale_gizmo(t_wind *w)
{
	w->p.t.x = 0;
	w->p.t.y = 0;
	w->p.t.z = 0;
	w->p.rot.x = 0;
	w->p.rot.y = 0;
	w->p.rot.z = 0;
}

void		def_all_preui(t_wind *w)
{
	def_axle_rotation(w);
	def_tranrotscale_gizmo(w);
	def_color(w);
	calc_zhigh(w);
}
