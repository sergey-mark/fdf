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
/*
// http://stackoverflow.com/questions/3723846/convert-from-hex-color-to-rgb-struct-in-c
t_rgbcolor		color_hexatorgb(char *hexa_color)
{
	t_rgbcolor	rgbcolor;
	int			intcolor;


	intcolor = hextoint(hexa_color);
	//ft_putnbr(intcolor);
	rgbcolor.r = ((intcolor >> 16) & 0xFF)/255.0;
	rgbcolor.g = ((intcolor >> 8) & 0xFF)/255.0;
	rgbcolor.b = ((intcolor) & 0xFF)/255.0;
	return (rgbcolor);
}
*/
void			draw_point(t_wind *w, int x, int y, char *hexcolor)
{
	t_rgbcolor	rgbcolor;
	char		*R;
	char		*G;
	char		*B;

	//printf("%zx\n", hexcolor);  // prints as hex
	//SPLIT D'UN FORMAT CLASSIQUE DE HEXCOLOR ("0xFFFFFF") -> Attention en l'ordre est en little endian cependant! (donc inversé!) (car on est sur un x86))
	B = ft_strjoin("0x", ft_strsub(hexcolor, 2, 2));
	G = ft_strjoin("0x", ft_strsub(hexcolor, 4, 2));
	R = ft_strjoin("0x", ft_strsub(hexcolor, 6, 2));
	rgbcolor.r = hextoint(R);
	rgbcolor.g = hextoint(G);
	rgbcolor.b = hextoint(B);
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
}
