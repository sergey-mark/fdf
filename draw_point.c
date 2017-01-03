/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:52:55 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/03 17:11:48 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char			*get_inbetweencolor(char *s_hex, char *e_hex, t_wind *w, int z)
{
	float		percent;
	t_rgbcolor	col;
	t_rgbcolor	start;
	t_rgbcolor	end;

	start = hexatorgb(s_hex);
	end = hexatorgb(e_hex);
	percent = (float)(z - w->p.color.min) / (w->p.color.max - w->p.color.min);
	col.r = ((end.r - start.r) * percent) + start.r;
	col.g = ((end.g - start.g) * percent) + start.g;
	col.b = ((end.b - start.b) * percent) + start.b;
	return (rgbtohexa(col));
}

static char		*get_color_fixed_value(t_wind *w, int z)
{
	char		*hexacolor;

	hexacolor = malloc(9);
	if (z <= w->p.zlowest)
		hexacolor = ft_strcpy(hexacolor, w->p.color.hexa_bot);
	else if (z == w->p.zmid)
		hexacolor = ft_strcpy(hexacolor, w->p.color.hexa_mid);
	else
		hexacolor = ft_strcpy(hexacolor, w->p.color.hexa_top);
	return (hexacolor);
}

char			*get_color(t_wind *w, int z)
{
	char		*hexacolor;

	if (z > w->p.zlowest && z < w->p.zmid)
	{
		w->p.color.min = w->p.zlowest;
		w->p.color.max = w->p.zmid;
		hexacolor = get_inbetweencolor(w->p.color.hexa_bot,
		w->p.color.hexa_mid, w, z);
	}
	else if (z > w->p.zmid && z < w->p.zhighest)
	{
		w->p.color.min = w->p.zmid;
		w->p.color.max = w->p.zhighest;
		hexacolor = get_inbetweencolor(w->p.color.hexa_mid,
		w->p.color.hexa_top, w, z);
	}
	else
		hexacolor = get_color_fixed_value(w, z);
	return (hexacolor);
}

void			draw_point(t_wind *w, int x, int y, char *hexacolor)
{
	t_rgbcolor	rgbcolor;

	rgbcolor = hexatorgb(hexacolor);
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
}
