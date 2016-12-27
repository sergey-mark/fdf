/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:21:30 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 15:00:16 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define W 0xFFFFFF

static void			color_palette_ui(t_wind *w)
{
	t_point		p;

	p.x = w->width - 50;
	p.y = w->height - 25;
	p.z = 0;
	draw_circlef(w, p, 10, w->p.color.hexa_bot);
	p.y -= 33;
	draw_circlef(w, p, 10, w->p.color.hexa_mid);
	p.y -= 33;
	draw_circlef(w, p, 10, w->p.color.hexa_top);
}

static void			right_legend(t_wind *w)
{
	int				rm;

	rm = w->width - 320;
	mlx_string_put(w->mlx, w->win, rm, 20, W, "L/R/Up/Down - Move (numpad)");
	mlx_string_put(w->mlx, w->win, rm, 40, W, "L/R/Up/Down - Rotate");
	mlx_string_put(w->mlx, w->win, rm, 60, W, "Pg Up/Down - High/Low");
	mlx_string_put(w->mlx, w->win, rm, 80, W, "+/- Zoom (numpad)");
	mlx_string_put(w->mlx, w->win, rm, w->height - 90, W, "W/E/R - Gizmo");
	mlx_string_put(w->mlx, w->win, rm, w->height - 70, W, "P - Paint Tool");
	mlx_string_put(w->mlx, w->win, rm, w->height - 50, W, "T - Turntable");
	mlx_string_put(w->mlx, w->win, rm, w->height - 30, W,
	"Insert - Move Pivot Point");
}

void				help(t_wind *w)
{
	if (w->p.help)
	{
		mlx_string_put(w->mlx, w->win, 10, 20, W, "F1 HELP");
		mlx_string_put(w->mlx, w->win, 10, 40, W, "F2 ISO");
		mlx_string_put(w->mlx, w->win, 10, 60, W, "F3 PARA");
		mlx_string_put(w->mlx, w->win, 10, 80, W, "1 - Dot");
		mlx_string_put(w->mlx, w->win, 10, 120, W, "2 - Wireframe");
		mlx_string_put(w->mlx, w->win, 10, 140, W, "3 - Tesselate");
		mlx_string_put(w->mlx, w->win, 10, 160, W, "4 - Fill");
		mlx_string_put(w->mlx, w->win, 10, w->height - 90, W,
		"M Leftbt - Rotate");
		mlx_string_put(w->mlx, w->win, 10, w->height - 70, W,
		"M Leftbt+Spacebar - Translate");
		mlx_string_put(w->mlx, w->win, 10, w->height - 50, W,
		"M Wheel+Go Up/Down - Higher/Lower");
		mlx_string_put(w->mlx, w->win, 10, w->height - 30, W,
		"M Wheel+Go R/L - Wider/Narrower");
		right_legend(w);
		color_palette_ui(w);
	}
}
