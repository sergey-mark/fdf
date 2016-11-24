#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.zhighest);
		w->img.pointd.x = w->img.point.x - w->p.x_spacing;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1];//height
		/*
		ft_putendl("Check de tout les points in allside:");
		ft_putnbr(w->img.point.x);
		ft_putchar('\n');
		ft_putnbr(w->img.point.y);
		ft_putchar('\n');
		ft_putnbr(w->img.point.z);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.x);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.y);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.z);
		ft_putchar('\n');*/
		draw_line(w, w->img.point, w->img.pointd);
	}
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zhighest);
		w->img.pointd.x = w->img.point.x;
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.zd = w->b.tab_int[y+1][x];//height
		/*
		ft_putendl("Check de tout les points in allside:");
		ft_putnbr(w->img.point.x);
		ft_putchar('\n');
		ft_putnbr(w->img.point.y);
		ft_putchar('\n');
		ft_putnbr(w->img.point.z);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.x);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.y);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.z);
		ft_putchar('\n');*/
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1])*(w->p.zhighest);
		w->img.pointd.x = w->img.point.x; // les sizesquare s'annule.
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous 
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
		s.pr.z = (w->b.tab_int[y][x+1])*(w->p.zhighest);
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		// Point en dessous:
		s.pd.z = (w->b.tab_int[y+1][x])*(w->p.zhighest);
		s.pd.x = w->img.point.x - w->p.x_spacing;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		// Point en diagonale:
		s.pdi.z = (w->b.tab_int[y+1][x+1])*(w->p.zhighest);
		s.pdi.x = w->img.point.x;
		s.pdi.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous
		fill_square(s, w);
	}
	return (0);
}

int			fill_3d_map(t_wind *w)
{
	int		y;
	int		x;
	int		z;
	double	start_x;
	int		largeurfigure;

	//w->img.point.y = (w->b.nbr_of_line*w->p.y_spacing)/2; //On centre la figure au milieu de l'axe de rotation.
	w->img.point.y = 0; //On centre la figure au milieu de l'axe de rotation.
	//w->img.point.y = w->p.t.y; //On centre la figure au milieu de l'axe de rotation.
	largeurfigure = (w->b.nbr_elem_line)*(w->p.x_spacing);
	start_x = (w->img.width - largeurfigure)/2; //Centrage de la piece
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.y_spacing;
		w->img.point.x = start_x; // moins la position de l'axe
		while (x < w->b.nbr_elem_line)
		{
			z = w->b.tab_int[y][x];
			w->p.color.z = z;//height
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.zhighest);
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
			ft_putchar('o');
			checkpoint_allside(x, y, w);
			ft_putchar('j');
			if (w->p.graphic_mode == 3)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
				fill_para(x, y, w);
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		ft_putendl("|");
		y++;
	}
	return (0);
}
