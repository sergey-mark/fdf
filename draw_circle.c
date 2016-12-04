
#include "fdf.h"

void			draw_circle(t_wind *w, t_point centerp, int rayon)
{
	int			i;
	double		i_rad;
	t_point		pos;

	i = 0;
	while (i < 360)
	{
		i_rad = degree_to_radian(i);
		pos.x = ((double)rayon * cos(i_rad)) + centerp.x;
		pos.y = ((double)rayon * sin(i_rad)) + centerp.y;
		pos.z = centerp.z;

		pos = rotate_point(w, pos);
		draw_point(w, pos.x, pos.y, w->p.color.hexa_default);
		//draw_point(w, pos.x, pos.y, "0xFFFFFF");
		//pencil(w, pos.x, pos.y); //Pour avoir un cercle plus epais
		i++;
	}
}
