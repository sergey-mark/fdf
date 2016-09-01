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
	if (param == 0)
	{
		p.x = p.x - w->width/2;
		p.y = p.y - w->height/2;
		p.z = p.z;
	}
	else
	{
		p.x = p.x + w->width/2;
		p.y = p.y + w->height/2;
		p.z = p.z;
	}
	return (p);
}

int			draw_line(t_wind *w, t_point point, t_point pointd, int booleanrot)
{
	t_line	v;

	if (booleanrot == 0)
	{
		ft_putstr("no rotation");
		// NORMAL:
		v.x = point.x;
		v.y = point.y - point.z;
		v.xdest = pointd.x;
		v.ydest = pointd.y - pointd.z;
	}
	else
	{
		// To do rotation of the object in center
		// We center object in center of rotate_axle
		// Move figure to 0, 0 coordonate:
		point = move_to(w, point, 0);
		pointd = move_to(w, pointd, 0);

		// AVEC ROTATION:
		// On applique la rotation si on appui sur la flèche de haut ou bas
		w->img.r_point = matrice_rotation(point, w->p.rot, w->p.r_rot);
		w->img.r_pointd = matrice_rotation(pointd, w->p.rot, w->p.r_rot);

		// To do rotation of the object in center
		// Move back figure to center:
		w->img.r_point = move_to(w, w->img.r_point, 1);
		w->img.r_pointd = move_to(w, w->img.r_pointd, 1);

		v.x = w->img.r_point.x;
		v.y = w->img.r_point.y - w->img.r_point.z;
		v.xdest = w->img.r_pointd.x;
		v.ydest = w->img.r_pointd.y - w->img.r_pointd.z;
	}

	v.sign_x = get_sign(v.x, v.xdest);
	v.sign_y = get_sign(v.y, v.ydest);
	v.diff_x = get_diff(v.x, v.xdest);
	v.diff_y = get_diff(v.y, v.ydest);
	/*
	ft_putstr("x : ");
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putstr("y : ");
	ft_putnbr(y);
	ft_putchar('\n');
	ft_putstr("xdest : ");
	ft_putnbr(xdest);
	ft_putchar('\n');
	ft_putstr("ydest : ");
	ft_putnbr(ydest);
	ft_putchar('\n');
	ft_putstr("diff_x : ");
	ft_putnbr(diff_x);
	ft_putchar('\n');
	ft_putstr("diff_y : ");
	ft_putnbr(diff_y);
	ft_putchar('\n');
	ft_putstr("sign_x : ");
	ft_putnbr(sign_x);
	ft_putchar('\n');
	ft_putstr("sign_y : ");
	ft_putnbr(sign_y);
	ft_putchar('\n');
	*/
	if (v.diff_x > v.diff_y)
		v.bigdiff = v.diff_x;
	else if (v.diff_y > v.diff_x)
		v.bigdiff = v.diff_y;
	else
		v.bigdiff = v.diff_y;
	if (w->p.graphic_mode == 1) // Si mode point
	{
		if (dot_in_window(w, rint(v.x), rint(v.y)))
			*(w->img.pxl_ptr+(int)((rint(v.y))*(w->img.size_line)+ (rint(v.x))*(w->img.octet_per_pixel))) = (int)"0xFF0000";
	}
	else // Si mode filaire
	{
		while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
		{
			if (v.x != v.xdest)
				v.x = v.x + (v.sign_x * (v.diff_x/v.bigdiff));
			if (v.y != v.ydest)
				v.y = v.y + (v.sign_y * (v.diff_y/v.bigdiff));
		/*
		ft_putstr("x : ");
		ft_putnbr(rint(x));
		ft_putchar('\n');
		ft_putstr("y : ");
		ft_putnbr(rint(y));
		ft_putchar('\n');
		*/
			// check if dot is in window to reduce crash:
			if (dot_in_window(w, rint(v.x), rint(v.y)))
				*(w->img.pxl_ptr+(int)((rint(v.y))*(w->img.size_line)+ (rint(v.x))*(4))) = (int)"0x00FFFFFF";
		}
	}
	return (0);
}
