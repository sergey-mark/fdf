
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
		pencil(w, pos.x, pos.y);
		i++;
	}
}
