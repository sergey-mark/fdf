#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)
	{
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x - w->p.x_spacing;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1] ;
		draw_line(w, w->img.point, w->img.pointd);
	}
	if(y<(w->b.nbr_of_line-1))
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x;
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.zd = w->b.tab_int[y+1][x];
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1))
	&& (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1))))
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x + w->p.x_spacing; 
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.z = w->b.tab_int[y][x];
		w->p.color.zd = w->b.tab_int[y+1][x+1];
		
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static void			record_allppathsquareface(t_wind *w, int x, int y, t_fillsquare s)
{
	w->obj.f.i = 0;
	w->p.color.z = w->b.tab_int[y][x+1];
	w->p.color.zd = w->b.tab_int[y][x];
	draw_line(w, s.pr, s.p);
	w->p.color.z = w->b.tab_int[y][x];
	w->p.color.zd = w->b.tab_int[y+1][x];
	draw_line(w, s.p, s.pd);
	w->p.color.z = w->b.tab_int[y+1][x];
	w->p.color.zd = w->b.tab_int[y+1][x+1];
	draw_line(w, s.pd, s.pdi);
	w->p.color.z = w->b.tab_int[y+1][x+1];
	w->p.color.zd = w->b.tab_int[y][x+1];
	draw_line(w, s.pdi, s.pr);
}


static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;

	w->obj.f.bol = 1;
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1))
	&& (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1))))
	{
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		s.pr.z = (w->b.tab_int[y][x+1] + w->p.t.z)*(w->p.zaccentuation);
		s.p = w->img.point;
		s.pd.x = w->img.point.x;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		s.pd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		s.pdi.x = w->img.point.x + w->p.x_spacing;
		s.pdi.y = w->img.point.y + w->p.y_spacing;
		s.pdi.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		record_allppathsquareface(w, x, y, s);
		set_minmaxy_lstpath(w->obj.f.beginpath, w);
		create_listofnodesperrow_fill(w, w->obj.f.beginpath, w->obj.f.row_min, w->obj.f.row_max);
		sort_listofnodes(w->obj.f.lstnodesbeg);
		fill_listofnodes(w, w->obj.f.lstnodesbeg);
	}
	w->obj.f.bol = 0;
	return (0);
}

int			fill_3d_map(t_wind *w)
{
	int		y;
	int		x;
	double	start_x;
	int		largeurfigure;

	w->img.point.y = (w->b.nbr_of_line * w->p.y_spacing)/2 + w->p.t.y; 
	largeurfigure = (w->b.nbr_elem_line)*(w->p.x_spacing);
	start_x = (w->img.width - largeurfigure)/2 + w->p.t.x; 
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.y_spacing;
		w->img.point.x = start_x; 
		while (x < w->b.nbr_elem_line)
		{
			w->p.color.z = w->b.tab_int[y][x];
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.zaccentuation);
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.r_point = matrice_rotation(w->img.point, w->p.rot, w->p.r_rot);
				w->img.x_centerpoint = w->img.r_point.x;
				w->img.y_centerpoint = (w->img.r_point.y - w->img.r_point.z);
				w->img.z_centerpoint = w->img.point.y - w->img.point.z;
			}
			checkpoint_allside(x, y, w);
			if (w->p.graphic_mode == 3 || w->p.dot == 1)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
				fill_para(x, y, w);
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		y++;
	}
	return (0);
}
