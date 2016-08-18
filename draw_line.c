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

int			draw_line(t_wind *w, t_point point, t_point pointd)
{
	t_line	v;
	/*
	ft_putnbr(w->img.point.x);
	ft_putchar('\n');
	ft_putnbr(w->img.point.y);
	ft_putchar('\n');
	ft_putnbr(w->img.point.z);
	ft_putchar('\n');
	*/
	// NORMAL:
	/*
	x = w->img.point.x;
	y = w->img.point.y - w->img.point.z;
	xdest = w->img.pointd.x;
	ydest = w->img.pointd.y - w->img.pointd.z;
	*/
	// AVEC ROTATION:
	// On applique la rotation si on appui sur la flèche de haut ou bas
	w->img.r_point = rotation_point(point, w->p.rot, w->p.r_rot);
	v.x = w->img.r_point.x;
	v.y = w->img.r_point.y - w->img.r_point.z;

	w->img.r_pointd = rotation_point(pointd, w->p.rot, w->p.r_rot);
	v.xdest = w->img.r_pointd.x;
	v.ydest = w->img.r_pointd.y - w->img.r_pointd.z;

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
		*(w->img.pxl_ptr+(int)((rint(v.y))*(w->img.size_line)+ (rint(v.x))*(w->img.octet_per_pixel))) = (int)"0x00FFFFFF";
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
			*(w->img.pxl_ptr+(int)((rint(v.y))*(w->img.size_line)+ (rint(v.x))*(4))) = (int)"0x00FFFFFF";

		}
	}
	return (0);
}
