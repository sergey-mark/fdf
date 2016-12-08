#include "fdf.h"

static int			get_sign(int first, int second)
{
	int		sign;

	if (first > second)
		sign = -1;
	else if (first == second)
		sign = 0;
	else
		sign = 1;
	return (sign);
}

static int			get_diff(int first, int second)
{
	int		i;

	i = 0;
	if (first > second)
	{
		while (first > second)
		{
			second++;
			i++;
		}
	}
	if (first < second)
	{
		while (first < second)
		{
			first++;
			i++;
		}
	}
	return (i);
}

int			dot_in_window(t_wind *w, int x, int y)
{
	if ((x > 0 && x < w->width) && (y > 0 && y < w->height))
		return (1);
	return (0);
}

t_point		move_to(t_wind *w, t_point p, int param)
{
	int		pyx;
	int		pxy;

	pyx = w->obj.gizt.p_y.x + w->obj.gizt.t.x;
	pxy = w->obj.gizt.p_x.y + w->obj.gizt.t.y;
	if (param == 0)
	{
		p.x = p.x - pyx;
		p.y = p.y - pxy;
		p.z = p.z;
	}
	else
	{
		p.x = p.x + pyx;
		p.y = p.y + pxy;
		p.z = p.z;
	}
	return (p);
}

t_point			*ft_pointnew(int x, int y, int z)
{
	t_point		*new;

	new = malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_listp_path		*ft_pathinit(t_line v)
{
	t_listp_path	*path;

	path = malloc(sizeof(t_listp_path));
	path->p = ft_pointnew(rint(v.x), rint(v.y), rint(v.z));
	path->next = NULL;
	ft_putstr("x: ");
	ft_putnbr(path->p->x);
	ft_putstr(" y: ");
	ft_putnbr(path->p->y);
	ft_putstr(" z: ");
	ft_putnbr(path->p->z);
	ft_putchar('\n');
	return (path);
}

t_listp_path		*ft_pathadd(t_listp_path *list, t_listp_path *elem)
{
	t_listp_path	*tmp;

	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
	return (list);
}

t_listp_path		*ft_pathremove(t_listp_path *list, t_listp_path *elem)
{
	t_listp_path	*tmp;
	t_listp_path	*gap;

	tmp = list;
	while (tmp->next != elem)
		tmp = tmp->next;
	gap = tmp->next->next;
	free(tmp->next);
	tmp->next = gap;
	return (list);
}


int				get_pointinbetween(t_point point, t_point pointd, t_wind *w)
{
	int			midx;
	int			midy;
	t_line		v;

	// convert rotation of point to 2d matrice
	v.x = point.x;
	v.y = point.y - point.z;
	v.z = w->p.color.z;
	v.xdest = pointd.x;
	v.ydest = pointd.y - pointd.z;
	v.zdest = w->p.color.zd;

	midx = v.xdest + ((rint(v.x) - v.xdest)/2); // To calculate mid point of the faces (w->p.dot)
	midy = v.ydest + ((rint(v.y) - v.ydest)/2); // To calculate mid point of the faces (w->p.dot)
	/*ft_putstr("v.x");
	ft_putnbr(rint(v.x));
	ft_putstr("\n");
	ft_putstr("v.xdest");
	ft_putnbr(rint(v.xdest));
	ft_putstr("\n");
	ft_putstr("v.y");
	ft_putnbr(rint(v.y));
	ft_putstr("\n");
	ft_putstr("v.ydest");
	ft_putnbr(rint(v.ydest));
	ft_putstr("\n");
	ft_putstr("midxo");
	ft_putnbr(midx);
	ft_putstr("\n");
	ft_putstr("midy");
	ft_putnbr(midy);
	ft_putstr("\n");*/
	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.sign_z = get_sign(v.z, v.zdest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	v.diff_z = get_diff(v.z, v.zdest);
	/*
	ft_putnbr(v.sign_x);
	ft_putchar('\n');
	ft_putnbr(v.sign_y);
	ft_putchar('\n');
	ft_putnbr(v.sign_z);
	ft_putchar('\n');
	ft_putnbr(v.diff_x);
	ft_putchar('\n');
	ft_putnbr(v.diff_y);
	ft_putchar('\n');
	ft_putnbr(v.diff_z);
	ft_putchar('\n');
	ft_putstr("v.x:");
	ft_putnbr(rint(v.x));
	ft_putchar('\n');
	ft_putstr("v.y:");
	ft_putnbr(rint(v.y));
	ft_putchar('\n');
	ft_putstr("xdest:");
	ft_putnbr(v.xdest);
	ft_putchar('\n');
	ft_putstr("ydest:");
	ft_putnbr(v.ydest);
	ft_putchar('\n');*/
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	if (w->p.graphic_mode == 1)//Si mode point
	{
		if (dot_in_window(w, rint(v.x), rint(v.y)))
		{
			if (w->p.color.hexa_bool)
				draw_point(w, (int)rint(v.x), (int)rint(v.y), w->p.color.hexa_default);
			else
				draw_point(w, (int)rint(v.x), (int)rint(v.y), get_color(w, w->img.point.z));
		}
	}
	else // Si mode filaire
	{
		while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
		{/*
			ft_putstr("v.x:");
			ft_putnbr(v.x);
			ft_putchar('\n');
			ft_putstr("v.y:");
			ft_putnbr(v.y);
			ft_putchar('\n');
			ft_putstr("v.z:");
			ft_putnbr(v.z);
			ft_putchar('\n');*/
			if (v.x != v.xdest)
				v.x += (v.sign_x * (v.diff_x/v.bigdiff));
			if (v.y != v.ydest)
				v.y += (v.sign_y * (v.diff_y/v.bigdiff));
			if (v.z != v.zdest)//For height per color
				v.z += (v.sign_z * (v.diff_z/v.bigdiff));
			//check if dot in window to avoid crash
			if (dot_in_window(w, rint(v.x), rint(v.y)))
			{
				if (w->p.m.button1 == 1 && w->p.paint == 1)
				{
					ft_putendl("paint fluid");
					pencil(w, rint(v.x), rint(v.y));
				}
				else if (w->p.dot == 1)
				{
					if ((rint(v.x) == midx) && (rint(v.y) == midy))
					{
						ft_putendl("mid point");
						draw_point(w, rint(v.x), rint(v.y), get_color(w, rint(v.z)));
					}
				}
				else if (w->p.graphic_mode == 4 && w->obj.f.bol == 1)
				{
					//J'enregistre les points dans une liste de points
					if (w->obj.f.i == 0)
						w->obj.f.beginpath = ft_pathinit(v);
					else
						w->obj.f.beginpath = ft_pathadd(w->obj.f.beginpath, ft_pathinit(v));
					w->obj.f.i++;
				}
				else if (w->p.color.hexa_bool)
					draw_point(w, rint(v.x), rint(v.y), w->p.color.hexa_default);
				else
					draw_point(w, rint(v.x), rint(v.y), get_color(w, rint(v.z)));
			}
		}
	}
	return (0);
}

t_point		rotate_point(t_wind *w, t_point dot)
{
	// We do the rotation of the circle in matrice
	dot = move_to(w, dot, 0); //Move to top left of screen
	dot = matrice_rotation(dot, w->p.rot, w->p.r_rot);
	dot = move_to(w, dot, 1); //Move back
	return (dot);
}

int			draw_line(t_wind *w, t_point point, t_point pointd)
{
	//BOF Hack to have our figure turn of 45° in rotx. (to start from 0 when the figure is on side, even if we show it with a different start angle)
	w->p.rot.x += 45;
	// Do the rotation of the point
	point = rotate_point(w, point);
	pointd = rotate_point(w, pointd);
	//EOF Hack to have our figure turn of 45° in rotx. 
	w->p.rot.x -= 45;
	get_pointinbetween(point, pointd, w);
	return (0);
}
