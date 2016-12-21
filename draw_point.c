#include "fdf.h"


int				hextoint(char *s)
{
	int			i;
	int			numb;
	int			tot;

	i = 0;
	if (s[i] == '0')
	{
		i++;
		if (s[i] == 'X' || s[i] == 'x')
			i++;
	}
	numb = 0;
	tot = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			numb = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			numb = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			numb = s[i] - 'A' + 10;
		else
		{
			ft_putstr("error");
			return (0);
		}
		tot = 16 * tot + numb;
		i++;
	}
	return (tot);
}

t_rgbcolor		hexatorgb(char *hexcolor)
{
	t_rgbcolor	rgbcolor;
	char		*R;
	char		*G;
	char		*B;

	B = ft_strjoin("0x", ft_strsub(hexcolor, 2, 2));
	G = ft_strjoin("0x", ft_strsub(hexcolor, 4, 2));
	R = ft_strjoin("0x", ft_strsub(hexcolor, 6, 2));
	rgbcolor.r = hextoint(R);
	rgbcolor.g = hextoint(G);
	rgbcolor.b = hextoint(B);
	return (rgbcolor);
}

char			*inttohex(int n)
{
	char		*hex;
	int			i;
	int			dizaine;

	hex = ft_strnew(4);
	i = 0;
	hex[i++] = '0';
	hex[i++] = 'x';
	dizaine = n/16;
	if (dizaine < 10)
		hex[i++] = dizaine + '0';
	else
		hex[i++] = dizaine%10 + 'A';
	n = n - (dizaine*16);
	if (n < 10)
		hex[i++] = n + '0';
	else
		hex[i++] = n%10 + 'A';
	return(hex);
}

char			*rgbtohexa(t_rgbcolor rgbcolor)
{
	char		*hexa_color;
	int			i;

	i = 0;
	hexa_color = ft_strnew(8);
	hexa_color[i++] = '0';
	hexa_color[i++] = 'x';
	hexa_color[i++] = inttohex(rgbcolor.r)[2];
	hexa_color[i++] = inttohex(rgbcolor.r)[3];
	hexa_color[i++] = inttohex(rgbcolor.g)[2];
	hexa_color[i++] = inttohex(rgbcolor.g)[3];
	hexa_color[i++] = inttohex(rgbcolor.b)[2];
	hexa_color[i++] = inttohex(rgbcolor.b)[3];
	return (hexa_color);
}

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
