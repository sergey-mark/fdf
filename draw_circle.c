
#include "fdf.h"

void			draw_circle(t_wind *w, t_point centerp, int rayon, char *hexa_color)
{
	int			i;
	double		i_rad;
	t_point		pos;

	i = 0;
	if (ft_strcmp(hexa_color, "no") == 0)
		hexa_color = w->p.color.hexa_default;
	while (i < 360)
	{
		i_rad = degree_to_radian(i);
		pos.x = ((double)rayon * cos(i_rad)) + centerp.x;
		pos.y = ((double)rayon * sin(i_rad)) + centerp.y;
		pos.z = centerp.z;
		draw_point(w, pos.x, pos.y, hexa_color);
		i++;
	}
}

void			draw_circle_fill(t_wind *w, t_point centerp, int rayon, char *hexa_color)
{
	int			r;

	r = 0;
	while (r < rayon)
		draw_circle(w, centerp, r++, hexa_color);
}
