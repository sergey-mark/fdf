#include "fdf.h"
/*
static void		color_line(int num1, int num2, size_t *color)
{
	size_t white;
	size_t purple;

	white = 0x00FFFFFF;
	purple = 0x00FF00FF;
	if (num1 == 10 && num2 == 10)
		*color = purple;
	else
		*color = white;
}

static void		color_point(int num, size_t *color)
  {
    if(num == 10)//Je colore mon point si different de zero
		*color = 0x00FF00FF;
	else
		*color = 0x00FFFFFF;
}
*/

// http://www.findsourcecode.com/c-programming/convert-hexadecimal-into-integer-in-c-programming/
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

t_rgbcolor			get_inbetweencolor(t_rgbcolor start, t_rgbcolor end, t_wind *w, int max)
{
	int			perc;
	t_rgbcolor	col;

	perc = (max - w->img.r_point.z)*100/max;// Calcul du pourcentage
	col.r = ((end.r - start.r)*perc/100) + start.r;// Calcul de la couleur
	col.g = ((end.g - start.g)*perc/100) + start.g;
	col.b = ((end.b - start.b)*perc/100) + start.b;
	return (col);
}

t_rgbcolor			get_color(t_wind *w)
{
	t_rgbcolor	color;
	int			z;
	int			max;

	z = w->img.r_point.z;
	w->p.color.bot = hexatorgb(w->p.color.hexa_bot);
	w->p.color.mid = hexatorgb(w->p.color.hexa_mid);
	w->p.color.top = hexatorgb(w->p.color.hexa_top);
	//if (z <= w->p.color.lowl)
		//color = hexatorgb(w->p.color.hexa_bot);
	if (z >= w->p.color.lowl && z < w->p.color.midl)
	{
		max = w->p.color.midl; //pr calcul du pourcentage max
		color = get_inbetweencolor(w->p.color.bot, w->p.color.mid, w, max);
	}
	//else if (z == w->p.color.midl)
		//color = w->p.color.hexa_mid;
	else if (z >= w->p.color.midl && z <= w->p.color.topl)
	{
		max = w->p.color.topl; //pr calcul du pourcentage max
		color = get_inbetweencolor(w->p.color.mid, w->p.color.top, w, max);
	}
	//else if (z >= w->p.color.topl)
		//color = w->p.color.hexa_top;
	return (color);
}

void			draw_point(t_wind *w, int x, int y, char *hexcolor)
{
	t_rgbcolor	rgbcolor;

	//rgbcolor = hexatorgb(hexcolor); //Get color from standard affectation
	rgbcolor = get_color(w); //Get color from color palette
	//SPLIT D'UN FORMAT CLASSIQUE DE HEXCOLOR ("0xFFFFFF") -> Attention en l'ordre est en little endian cependant! (donc inversé!) (car on est sur un x86))
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
}
