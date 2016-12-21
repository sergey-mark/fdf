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

t_listp_path		*ft_pathremove(t_listp_path *list)
{
	t_listp_path	*tmp;
	t_listp_path	*gap;

	tmp = list;
	if (tmp->next == NULL || tmp->next->next == NULL)
		gap = NULL;
	else
		gap = tmp->next->next;
	free(tmp);
	tmp->next = gap;
	return (tmp);
}

int				get_pointinbetween(t_point point, t_point pointd, t_wind *w)
{
	int			midx;
	int			midy;
	t_line		v;

	v.x = point.x;
	v.xdest = pointd.x;
	if (w->obj.f.bolfill == 0)
	{
		v.y = point.y - point.z;
		v.z = w->p.color.z;
		v.ydest = pointd.y - pointd.z;
		v.zdest = w->p.color.zd;
	}
	else
	{
		v.y = point.y;
		v.z = point.z;
		v.ydest = pointd.y;
		v.zdest = pointd.z;
	}

	midx = v.xdest + ((rint(v.x) - v.xdest)/2); 
	midy = v.ydest + ((rint(v.y) - v.ydest)/2); 
	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.sign_z = get_sign(v.z, v.zdest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	v.diff_z = get_diff(v.z, v.zdest);
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	if (w->p.graphic_mode == 1)
	{
		if (dot_in_window(w, rint(v.x), rint(v.y)))
		{
			if (w->p.color.hexa_bool)
				draw_point(w, (int)rint(v.x), (int)rint(v.y), w->p.color.hexa_default);
			else
				draw_point(w, (int)rint(v.x), (int)rint(v.y), get_color(w, w->img.point.z));
		}
	}
	else 
	{
		while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
		{
			if (v.x != v.xdest)
				v.x += (v.sign_x * (v.diff_x/v.bigdiff));
			if (v.y != v.ydest)
				v.y += (v.sign_y * (v.diff_y/v.bigdiff));
			if (v.z != v.zdest)
				v.z += (v.sign_z * (v.diff_z/v.bigdiff));
			if (w->p.graphic_mode == 4 && w->obj.f.bol == 1)
			{
				
				if (w->obj.f.i == 0)
					w->obj.f.beginpath = ft_pathinit(v);
				else
					w->obj.f.beginpath = ft_pathadd(w->obj.f.beginpath, ft_pathinit(v));
				w->obj.f.i++;
			}
			else
			{
				
				if (dot_in_window(w, rint(v.x), rint(v.y)))
				{
					if (w->p.m.button1 == 1 && w->p.paint == 1)
					{
						pencil(w, rint(v.x), rint(v.y));
					}
					else if (w->p.dot == 1)
					{
						if ((rint(v.x) == midx) && (rint(v.y) == midy))
						{
							draw_point(w, rint(v.x), rint(v.y), get_color(w, rint(v.z)));
						}
					}
					else if (w->obj.f.bolfill == 0 && w->p.graphic_mode == 4)
						draw_point(w, rint(v.x), rint(v.y), w->p.color.hexa_top);
					else if (w->p.color.hexa_bool)
						draw_point(w, rint(v.x), rint(v.y), w->p.color.hexa_default);
					else
						draw_point(w, rint(v.x), rint(v.y), get_color(w, rint(v.z)));
				}
			}
		}
	}
	return (0);
}

t_point		rotate_point(t_wind *w, t_point dot)
{
	dot = move_to(w, dot, 0); 
	dot = matrice_rotation(dot, w->p.rot, w->p.r_rot);
	dot = move_to(w, dot, 1); 
	return (dot);
}

int			draw_line(t_wind *w, t_point point, t_point pointd)
{
	w->p.rot.x += 45;
	point = rotate_point(w, point);
	pointd = rotate_point(w, pointd);
	w->p.rot.x -= 45;
	get_pointinbetween(point, pointd, w);
	return (0);
}
