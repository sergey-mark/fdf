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

int			draw_line(int xdest, int ydest, int zdest, t_img **i, t_wind *w)
{ 
	float	x;
	float	y;
	int		sign_x;
	int		sign_y;
	float		bigdiff;
	float		diff_x;
	float		diff_y;
	t_point		destp;

	// On applique la rotation si on appui sur la flèche de haut ou bas
	(*i)->r_point = rotation_point((*i)->point, w->p.rot_x);
	x = (*i)->r_point.x;
	y = (*i)->r_point.y - (*i)->point.z;
	//y = (*i)->r_point.y;

	ft_putnbr(zdest);
	destp.x = xdest;
	destp.y = ydest;
	destp.z = 0;
	destp = rotation_point(destp, w->p.rot_x);
	xdest = destp.x;
	//ydest = destp.y - (destp.z*w->p.accentuation);
	ydest = destp.y;

	
	//*((*i)->pxl_ptr+(int)((rint(y))*((*i)->size_line)+ (rint(x))*((*i)->octet_per_pixel))) = (int)"0x00FFFFFF";
	//*((*i)->pxl_ptr+(int)((rint(ydest))*((*i)->size_line)+ (rint(xdest))*((*i)->octet_per_pixel))) = (int)"0x00FFFFFF";

	sign_x = get_sign(x, xdest);
	sign_y = get_sign(y, ydest);
	diff_x = get_diff(x, xdest);
	diff_y = get_diff(y, ydest);
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
	if (diff_x > diff_y)
		bigdiff = diff_x;
	else if (diff_y > diff_x)
		bigdiff = diff_y;
	else
		bigdiff = diff_y;
	/*
	ft_putstr("bigdiff : ");
	ft_putnbr(bigdiff);*/
	while (rint(x) != xdest || rint(y) != ydest)
	{
		if (x != xdest)
		{
			x = x + (sign_x * (diff_x/bigdiff));
			//printf("%.2f ", x);
		}
		if (y != ydest)
		{
			y = y + (sign_y * (diff_y/bigdiff));
			//printf("%.2f ", y);
		}
	/*ft_putchar(':');
	ft_putnbr(rint(x));
	ft_putchar(':');
	ft_putnbr(rint(y));
	ft_putchar(':');
	*/
		//mlx_pixel_put((*w)->mlx, (*w)->win, rint(x), rint(y), (*w)->point.color);
		//ft_putstr("tata");
		*((*i)->pxl_ptr+(int)((rint(y))*((*i)->size_line)+ (rint(x))*((*i)->octet_per_pixel))) = (int)"0x00FFFFFF";

		//*((*i)->pxl_ptr+(int)((rint(y)*(w->p.size_square-(z)))*(((*i)->size_line)) + (rint(x))*((*i)->octet_per_pixel))) = (int)"#00FFFFFF";
	}
	return (0);
}
