#include "fdf.h"

void				help(t_wind *w)
{
	if (w->p.help)
	{
		t_point		p;
		p.x = w->width - 50;
		p.y = w->height - 25;
		p.z = 0;
		mlx_string_put(w->mlx, w->win, 10, 20, 0xFFFFFF, "F1 HELP");
		mlx_string_put(w->mlx, w->win, 10, 40, 0xFFFFFF, "F2 ISO");
		mlx_string_put(w->mlx, w->win, 10, 60, 0xFFFFFF, "F3 PARA");
		mlx_string_put(w->mlx, w->win, 10, 100, 0xFFFFFF, "1 - Dot");
		mlx_string_put(w->mlx, w->win, 10, 120, 0xFFFFFF, "2 - Wireframe");
		mlx_string_put(w->mlx, w->win, 10, 140, 0xFFFFFF, "3 - Tesselate");
		mlx_string_put(w->mlx, w->win, 10, 160, 0xFFFFFF, "4 - Fill");
		mlx_string_put(w->mlx, w->win, w->width-250, 20, 0xFFFFFF, "L/R/Up/Down - Move (numpad)");
		mlx_string_put(w->mlx, w->win, w->width-250, 40, 0xFFFFFF, "L/R/Up/Down - Rotate");
		mlx_string_put(w->mlx, w->win, w->width-250, 60, 0xFFFFFF, "Pg Up/Down - High/Low");
		mlx_string_put(w->mlx, w->win, w->width-250, 80, 0xFFFFFF, "+/- Zoom (numpad)");

		mlx_string_put(w->mlx, w->win, 10, w->height-80, 0xFFFFFF, "M Leftbt - Rotate");
		mlx_string_put(w->mlx, w->win, 10, w->height-60, 0xFFFFFF, "M Leftbt+Spacebar - Translate");
		mlx_string_put(w->mlx, w->win, 10, w->height-40, 0xFFFFFF, "M Wheel+Go Up/Down - Higher/Lower");
		mlx_string_put(w->mlx, w->win, 10, w->height-20, 0xFFFFFF, "M Wheel+Go R/L - Wider/Narrower");
		mlx_string_put(w->mlx, w->win, w->width-250, w->height-80, 0xFFFFFF, "W/E/R - Gizmo");
		mlx_string_put(w->mlx, w->win, w->width-250, w->height-60, 0xFFFFFF, "P - Paint Tool");
		mlx_string_put(w->mlx, w->win, w->width-250, w->height-40, 0xFFFFFF, "T - Turntable");
		mlx_string_put(w->mlx, w->win, w->width-250, w->height-20, 0xFFFFFF, "Insert - Move Pivot Point");
		draw_circle_fill(w, p, 10, w->p.color.hexa_bot);
		p.y -= 33;
		draw_circle_fill(w, p, 10, w->p.color.hexa_mid);
		p.y -= 33;
		draw_circle_fill(w, p, 10, w->p.color.hexa_top);
	}
}
