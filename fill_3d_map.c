#include "fdf.h"

static t_point		get_iso_point(int x, int y, t_wind *w)
{
	t_point p;
	p.x = ((x - y) * (w->p.size_square/2) + w->img.start_x) + w->p.t.x;
	p.y = ((x + y) * (w->p.angle_projpara/2) + w->img.start_y) + w->p.t.y;
	p.z = (w->b.tab_int[y][x] * (w->p.accentuation)) + w->p.t.z;
	return (p);
}

static int			checkpoint_allside_iso(int x, int y, t_wind *w)
{
	t_point			pointl;
	t_point			pointb;
	t_point			pointdiag;

	if(x>0)//Si point à gauche
	{
		pointl = get_iso_point(x-1, y, w);
		w->p.color.zd = w->b.tab_int[y][x-1];//height
		draw_line(w, w->img.point, pointl);
	}
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		pointb = get_iso_point(x, (y+1), w);
		w->p.color.zd = w->b.tab_int[y+1][x];//height
		draw_line(w, w->img.point, pointb);
	}
	if(x<(w->b.nbr_elem_line-1) && y<(w->b.nbr_of_line-1))//Si point en diagonale
	{
		pointdiag = get_iso_point(x+1, y+1, w);
		w->p.color.zd = w->b.tab_int[y+1][x+1];//height
		if (w->p.graphic_mode == 3)
		{
			draw_line(w, w->img.point, pointdiag);
		}
	}
	if (w->p.graphic_mode == 4)//Si mode fill
	{
		//pointdiag = get_iso_point(x+1, y+1, w);
		//fill_square(w->img.point, );
	}
	return (0);
}

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.accentuation);
		w->img.pointd.x = w->img.point.x - w->p.size_square;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1];//height
		draw_line(w, w->img.point, w->img.pointd);
	}
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.accentuation);
		w->img.pointd.x = w->img.point.x;
		w->img.pointd.y = w->img.point.y + w->p.angle_projpara;
		w->p.color.zd = w->b.tab_int[y+1][x];//height
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1])*(w->p.accentuation);
		w->img.pointd.x = w->img.point.x; // les sizesquare s'annule.
		w->img.pointd.y = w->img.point.y + w->p.angle_projpara;// Pour afficher remplir toutes les lignes en dessous 
		w->p.color.z = w->b.tab_int[y+1][x+1];//height
		// TRIANGULATE
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int				fill_square(t_fillsquare s, t_wind *w)
{
	t_line				v;
	t_line				v2;

	v.x = s.p.x; //left vertical side of square
	v.y = s.p.y - s.p.z;
	v.xdest = s.pd.x;
	v.ydest = s.pd.y - s.pd.z;
	v2.x = s.pr.x; //Right vertical side of square
	v2.y = s.pr.y - s.pr.z;
	v2.xdest = s.pdi.x;
	v2.ydest = s.pdi.y - s.pdi.z;
	while ((rint(v.y) < rint(v.ydest)) || (rint(v2.y) < (s.pdi.y - s.pdi.z)))
	{
		if (v.x != v.xdest)
			v.x = v.x + (v.sign_x * (v.diff_x/v.bigdiff));
		if (v.y != v.ydest)
			v.y = v.y + (v.sign_y * (v.diff_y/v.bigdiff));
		/*
		if ((s.point.y-s.point.z) < (s.pointd.y-s.pointd.z))
			s.point.y++;
		if (s.point.x > s.pointd.x)
			s.point.x--;
		if ((s.pointr.y-s.pointr.z) < (s.pointdiag.y-s.pointdiag.z))
			s.pointr.y++;
		if ((s.pointr.x) > (s.pointdiag.x))
			s.pointr.x--;
		*/
		draw_line(w, s.p, s.pr);
	}
	return (0);
}

static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;

	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		s.p = w->img.point;
		// Point à droite:
		s.pr.z = (w->b.tab_int[y][x+1])*(w->p.accentuation);
		s.pr.x = w->img.point.x + w->p.size_square;
		s.pr.y = w->img.point.y;
		// Point en dessous:
		s.pd.z = (w->b.tab_int[y+1][x])*(w->p.accentuation);
		s.pd.x = w->img.point.x - w->p.size_square;
		s.pd.y = w->img.point.y + w->p.angle_projpara;
		// Point en diagonale:
		s.pdi.z = (w->b.tab_int[y+1][x+1])*(w->p.accentuation);
		s.pdi.x = w->img.point.x;
		s.pdi.y = w->img.point.y + w->p.angle_projpara;// Pour afficher remplir toutes les lignes en dessous
		fill_square(s, w);
	}
	return (0);
}

int			fill_3d_map_iso(t_wind *w)
{
	int		y;
	int		x;

	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	w->img.start_x = 340 + w->p.t.x; //pour centrer l'iso au milieu
	w->img.start_y = 90 + w->p.t.y; //pour centrer l'iso au milieu
	w->img.point.x = 0;
	w->img.point.y = 0;
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line)
		{
			w->img.point = get_iso_point(x, y, w);
			w->p.color.z = w->b.tab_int[y][x];//height
			checkpoint_allside_iso(x, y, w);
			x++;
		}
		y++;
	}
	return (0);
}

int			fill_3d_map(t_wind *w)
{
	int		y;
	int		x;
	int		z;
	double	start_x;

	w->img.point.x = 0;
	w->img.point.y = w->p.t.y + 120; //On centre la figure au milieu de l'axe de rotation.
	start_x = (w->b.nbr_elem_line-8)*(w->p.size_square); //Centrage de la piece peut etre mieux calculé (car en digonale)
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.angle_projpara;
		w->img.point.x = start_x + (w->p.t.x-20);
		while (x < w->b.nbr_elem_line)
		{
			z = w->b.tab_int[y][x];
			w->p.color.z = z;//height
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.accentuation);
			ft_putnbr(z);
			ft_putchar('-');
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.r_point = matrice_rotation(w->img.point, w->p.rot, w->p.r_rot);
				w->img.x_centerpoint = w->img.r_point.x;
				w->img.y_centerpoint = (w->img.r_point.y - w->img.r_point.z);
				w->img.z_centerpoint = w->img.point.y - w->img.point.z;
				ft_putstr("center point:");
				ft_putnbr(w->img.x_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.y_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.z_centerpoint);
				ft_putchar('\n');
			}
			checkpoint_allside(x, y, w);
			if (w->p.graphic_mode == 3)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
				fill_para(x, y, w);
			w->img.point.x += w->p.size_square;
			x++;
		}
		ft_putendl("|");
		y++;
	}
	return (0);
}
