/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_para.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:21:23 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/10 15:10:32 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			rec_allppsquareface(t_wind *w, int x, int y, t_fillsquare s)
{
	w->obj.f.i = 0;
	w->p.color.z = w->b.tab_int[y][x + 1];
	w->p.color.zd = w->b.tab_int[y][x];
	draw_line(w, s.pr, s.p);
	w->p.color.z = w->b.tab_int[y][x];
	w->p.color.zd = w->b.tab_int[y + 1][x];
	draw_line(w, s.p, s.pd);
	w->p.color.z = w->b.tab_int[y + 1][x];
	w->p.color.zd = w->b.tab_int[y + 1][x + 1];
	draw_line(w, s.pd, s.pdi);
	w->p.color.z = w->b.tab_int[y + 1][x + 1];
	w->p.color.zd = w->b.tab_int[y][x + 1];
	draw_line(w, s.pdi, s.pr);
}

static t_fillsquare	set_square_dot_for_face(int x, int y, t_wind *w)
{
	t_fillsquare	s;

	s.pr.x = w->img.point.x + w->p.x_spacing;
	s.pr.y = w->img.point.y;
	s.pr.z = (w->b.tab_int[y][x + 1] + w->p.t.z) * (w->p.zaccentuation);
	s.p = w->img.point;
	s.pd.x = w->img.point.x;
	s.pd.y = w->img.point.y + w->p.y_spacing;
	s.pd.z = (w->b.tab_int[y + 1][x] + w->p.t.z) * (w->p.zaccentuation);
	s.pdi.x = w->img.point.x + w->p.x_spacing;
	s.pdi.y = w->img.point.y + w->p.y_spacing;
	s.pdi.z = (w->b.tab_int[y + 1][x + 1] + w->p.t.z) *
	(w->p.zaccentuation);
	return (s);
}

int					fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;

	w->obj.f.bol = 1;
	if ((x < (w->b.nbr_elem_line - 1)) && (y < (w->b.nbr_of_line - 1))
	&& (x < (w->b.nbr_elem_line - 1) && (y < (w->b.nbr_of_line - 1))))
	{
		s = set_square_dot_for_face(x, y, w);
		rec_allppsquareface(w, x, y, s);
		set_minmaxy_lstpath(w->obj.f.beginpath, w);
		create_listofnodesperrow_fill(w, w->obj.f.beginpath);
		ft_freepath(w->obj.f.beginpath);
		sort_listofnodes(w->obj.f.lstnodesbeg);
		fill_listofnodes(w, w->obj.f.lstnodesbeg);
		ft_listofnodes_free(w->obj.f.lstnodesbeg);
	}
	w->obj.f.bol = 0;
	return (0);
}
