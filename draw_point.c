#include "fdf.h"

char			*get_inbetweencolor(char *start_hexa, char *end_hexa, t_wind *w, int z)
{
	float		percent;
	int			min;
	int			max;
	t_rgbcolor	col;
	t_rgbcolor	start;
	t_rgbcolor	end;
	char		*hexa_color;

	start = hexatorgb(start_hexa);
	end = hexatorgb(end_hexa);
	min = w->p.color.min;
	max = w->p.color.max;
	percent = (float)(z - min)/(max-min);
	
	col.r = ((end.r - start.r)*percent) + start.r;
	col.g = ((end.g - start.g)*percent) + start.g;
	col.b = ((end.b - start.b)*percent) + start.b;
	hexa_color = rgbtohexa(col);
	return (hexa_color);
}

char			*get_color(t_wind *w, int z)
{
	char		*hexacolor;

	if (z <= w->p.zlowest)
		hexacolor = w->p.color.hexa_bot;
	else if (z > w->p.zlowest && z < w->p.zmid)
	{
		w->p.color.min = w->p.zlowest; 
		w->p.color.max = w->p.zmid; 
		hexacolor = get_inbetweencolor(w->p.color.hexa_bot, w->p.color.hexa_mid, w, z);
	}
	else if (z == w->p.zmid)
		hexacolor = w->p.color.hexa_mid;
	else if (z > w->p.zmid && z < w->p.zhighest)
	{
		w->p.color.min = w->p.zmid; 
		w->p.color.max = w->p.zhighest; 
		hexacolor = get_inbetweencolor(w->p.color.hexa_mid, w->p.color.hexa_top, w, z);
	}
	else
		hexacolor = w->p.color.hexa_top;
	return (hexacolor);
}

void			draw_point(t_wind *w, int x, int y, char *hexacolor)
{
	t_rgbcolor	rgbcolor;

	rgbcolor = hexatorgb(hexacolor); 
	
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
	
}
