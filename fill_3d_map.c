#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x - w->p.x_spacing;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1] ;//height
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
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
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
		w->img.pointd.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x + w->p.x_spacing; // les sizesquare s'annule.
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous 
		w->p.color.z = w->b.tab_int[y][x];//height
		w->p.color.zd = w->b.tab_int[y+1][x+1];//height dest
		// TRIANGULATE
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}
/*
static int				fill_square(t_wind *w, t_fillsquare s)
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
	while ((rint(v.y) < rint(v.ydest)) || (rint(v2.y) < rint(v2.ydest)))
	{
		//if (v.x != v.xdest)
			//v.x = v.x + (v.sign_x * (v.diff_x/v.bigdiff));
		if (v.y != v.ydest)
			v.y = v.y + (v.sign_y * (v.diff_y/v.bigdiff));
		//if (v2.x != v2.xdest)
			//v2.x = v2.x + (v2.sign_x * (v2.diff_x/v2.bigdiff));
		if (v2.y != v2.ydest)
			v2.y = v2.y + (v2.sign_y * (v2.diff_y/v2.bigdiff));
		
		if ((s.point.y-s.point.z) < (s.pointd.y-s.pointd.z))
			s.point.y++;
		if (s.point.x > s.pointd.x)
			s.point.x--;
		if ((s.pointr.y-s.pointr.z) < (s.pointdiag.y-s.pointdiag.z))
			s.pointr.y++;
		if ((s.pointr.x) > (s.pointdiag.x))
			s.pointr.x--;
		
		draw_line(w, s.p, s.pr);
	}
	return (0);
}*/

static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;
	int				i;
	int				row_min;
	int				row_max;
	int				nodes;
	int				b;
	t_point			swap;

	//Var to know when I use fill_para function in get_pointinbetween
	w->obj.f.bol = 1;

	ft_putendl("fill para 1");
	i = 0;
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droite, actuel, et en dessous et en diagonale à droite
	{
		// Point à droite:
		s.pr.z = (w->b.tab_int[y][x+1])*(w->p.zaccentuation);
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		//Point actuel (en haut à gauche)
		s.p = w->img.point;
		// Point en dessous: (bas à gauche)
		s.pd.z = (w->b.tab_int[y+1][x])*(w->p.zaccentuation);
		s.pd.x = w->img.point.x;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		// Point en diagonale: (bas à droite)
		s.pdi.z = (w->b.tab_int[y+1][x+1])*(w->p.zaccentuation);
		s.pdi.x = w->img.point.x + w->p.x_spacing;
		s.pdi.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous
		
		ft_putendl("fill para 2");
		w->obj.f.i = 0; //initialisation de i
		w->obj.f.path = malloc(sizeof(t_point *));
		if (!w->obj.f.path)
			return (1);

		ft_putendl("fill para 2a");
		//get point line from right point to top left point
		s.v.x = s.pr.x; // Set of first line to get inbetween point
		s.v.y = s.pr.y - s.pr.z;
		s.v.z = s.pr.z;
		s.v.xdest = s.p.x;
		s.v.ydest = s.p.y - s.p.z;
		s.v.zdest = s.p.z;
		ft_putendl("fill para 2ab");
		get_pointinbetween(s.v, w);
		ft_putendl("fill para 2ac");

		ft_putendl("fill para 3");
		//get point line from top left point to bottom left point
		s.v.x = s.p.x;
		s.v.y = s.p.y - s.p.z;
		s.v.z = s.p.z;
		s.v.xdest = s.pd.x;
		s.v.ydest = s.pd.y - s.pd.z;
		s.v.zdest = s.pd.z;
		get_pointinbetween(s.v, w);

		//get point line from bottom left point to bottom right
		s.v.x = s.pd.x;
		s.v.y = s.pd.y - s.pd.z;
		s.v.z = s.pd.z;
		s.v.xdest = s.pdi.x;
		s.v.ydest = s.pdi.y - s.pdi.z;
		s.v.zdest = s.pdi.z;
		get_pointinbetween(s.v, w);

		//get point line from bottom right to top right
		s.v.x = s.pdi.x;
		s.v.y = s.pdi.y - s.pdi.z;
		s.v.z = s.pdi.z;
		s.v.xdest = s.pr.x;
		s.v.ydest = s.pr.y - s.pr.z;
		s.v.zdest = s.pr.z;
		get_pointinbetween(s.v, w);

		ft_putendl("fill para 5");
		// Normalement l'ensemble du path est récuppéré en liste de point.
		ft_putstr("number of point in path:\n");
		ft_putnbr(w->obj.f.i);
		ft_putstr("\n");
		// Set of Min and max for the rows
		row_min = w->obj.f.path[0].y;
		row_max = w->obj.f.path[0].y;
		while (i < w->obj.f.i)
		{
			if (w->obj.f.path[i].y < row_min)
				row_min = w->obj.f.path[i].y;
			if (w->obj.f.path[i].y > row_max)
				row_max = w->obj.f.path[i].y;
			i++;
		}
		ft_putstr("row_min:\n");
		ft_putnbr(row_min);
		ft_putstr("\n");
		ft_putstr("row_max:\n");
		ft_putnbr(row_max);
		ft_putstr("\n");

		i = 0;
		nodes = 0;
		//Get nodes for each rows
		w->obj.f.nodepath = malloc(sizeof(t_point **));
		ft_putstr("number of nodes:");
		ft_putnbr(row_max - row_min);
		ft_putstr("\n");
		while (i < (row_max - row_min))
		{
			ft_putstr("malloc\n");
			w->obj.f.nodepath[i] = malloc(sizeof(t_point *));
			ft_putstr("i:");
			ft_putnbr(i);
			ft_putstr("\n");
			i++;
		}
		//if (!w->obj.f.nodepath)
			//return (1);
		i = 0;
		while (row_min < row_max)//Tant qu'on parcours les lignes
		{
			b = 0;
			while (i < w->obj.f.i)
			{
				if (row_min == w->obj.f.path[i].y)
					w->obj.f.nodepath[nodes][b++] = w->obj.f.path[i];
				i++;
			}
			ft_putstr("row:\n");
			ft_putnbr(row_min);
			ft_putstr("\n");
			ft_putstr("nodes:\n");
			ft_putnbr(nodes);
			ft_putstr("\n");
			nodes++;
			row_min++;
		}
		//  Sort the nodes, via a simple “Bubble” sort.
		i = 0;
		while (i < nodes-1)
		{
			b = 0;
			while (w->obj.f.nodepath[i][b].x > w->obj.f.nodepath[i][b+1].x)
			{
				swap = w->obj.f.nodepath[i][b];
				w->obj.f.nodepath[i][b] = w->obj.f.nodepath[i][b+1];
				w->obj.f.nodepath[i][b+1] = swap;
				if (b > 0)
					b--;
			}
			i++;
		}

		i = 0;
		//Fill the pixels between node pairs.
		while (i < nodes-1)
		{
			b = 0;
			while (w->obj.f.nodepath[i][b].x)
			{
				while (w->obj.f.nodepath[i][b].x < w->obj.f.nodepath[i][b+1].x)
				{
					draw_point(w, w->obj.f.nodepath[i][b].x, w->obj.f.nodepath[i][b].y, get_color(w, w->obj.f.nodepath[i][b].z));
					w->obj.f.nodepath[i][b].x++;
				}
				b += 2;
			}
			i++;
		}
		//Var to know when I use fill_para function in get_pointinbetween
		w->obj.f.bol = 0;
		//fill_square(w, s);
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

	w->img.point.y = (w->b.nbr_of_line * w->p.y_spacing)/2 + w->p.t.y; //On centre la figure au milieu de l'axe de rotation.
	//w->img.point.y = 0; //On centre la figure au milieu de l'axe de rotation.
	//w->img.point.y = w->p.t.y; //On centre la figure au milieu de l'axe de rotation.
	largeurfigure = (w->b.nbr_elem_line)*(w->p.x_spacing);
	start_x = (w->img.width - largeurfigure)/2 + w->p.t.x; //Centrage de la piece
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
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.zaccentuation);
			//ft_putnbr(z);
			//ft_putchar('-');
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.r_point = matrice_rotation(w->img.point, w->p.rot, w->p.r_rot);
				w->img.x_centerpoint = w->img.r_point.x;
				w->img.y_centerpoint = (w->img.r_point.y - w->img.r_point.z);
				w->img.z_centerpoint = w->img.point.y - w->img.point.z;
				/*
				ft_putstr("center point:");
				ft_putnbr(w->img.x_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.y_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.z_centerpoint);
				ft_putchar('\n');*/
			}
			checkpoint_allside(x, y, w);
			if (w->p.graphic_mode == 3)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
				fill_para(x, y, w);
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		//ft_putendl("|");
		y++;
	}
	return (0);
}
