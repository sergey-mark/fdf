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
	
	pyx = w->r.p_y.x;
	pxy = w->r.p_x.y;
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

void		get_pointinbetween(t_line v, t_wind *w)
{
	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	if (w->p.graphic_mode == 1)//Si mode point
	{
		if (dot_in_window(w, rint(v.x), rint(v.y)))
				draw_point(w, (int)rint(v.x), (int)rint(v.y), w->p.color.hexa_bot);
	}
	else // Si mode filaire ou mode fill
	{
		while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
		{
			if (v.x != v.xdest)
				v.x = v.x + (v.sign_x * (v.diff_x/v.bigdiff));
			if (v.y != v.ydest)
				v.y = v.y + (v.sign_y * (v.diff_y/v.bigdiff));
			// check if dot is in window to reduce crash:
			if (dot_in_window(w, rint(v.x), rint(v.y)))
				draw_point(w, (int)rint(v.x), (int)rint(v.y), w->p.color.hexa_bot);
		}
	}
}

int			draw_line(t_wind *w, t_point point, t_point pointd, int booleanrot)
{
	t_line	v;
	//char	*color;

	if (booleanrot == 0) //No rotation for cursor rotation center draw
	{
		// NORMAL:
		v.x = point.x;
		v.y = point.y - point.z;
		v.xdest = pointd.x;
		v.ydest = pointd.y - pointd.z;
	}
	else
	{
		// To do rotation of the object in center, We center object in center of rotate_axle
		point = move_to(w, point, 0);
		pointd = move_to(w, pointd, 0);// Move figure(axle) to 0, 0 coordonate:

		// Rotate axle if in para mode (so 30degree inclination)
		//point = matrice_rotation(point, 30, );

		// AVEC ROTATION:
		// On applique la rotation si on appui sur la flèche de haut ou bas
		w->img.r_point = matrice_rotation(point, w->p.rot, w->p.r_rot);
		w->img.r_pointd = matrice_rotation(pointd, w->p.rot, w->p.r_rot);

		// To do rotation of the object in center
		// Move back figure(axle) to center:
		w->img.r_point = move_to(w, w->img.r_point, 1);
		w->img.r_pointd = move_to(w, w->img.r_pointd, 1);

		v.x = w->img.r_point.x;
		v.y = w->img.r_point.y - w->img.r_point.z;
		v.xdest = w->img.r_pointd.x;
		v.ydest = w->img.r_pointd.y - w->img.r_pointd.z;
	}
	get_pointinbetween(v, w);
	//color = "0x9E11BF"; //Violet
	//color = get_color(w, w->img.r_point.z);
	return (0);
}
