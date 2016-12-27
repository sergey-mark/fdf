/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbtohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:04:05 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 15:08:34 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		hextoint(char *s)
{
	int			i;
	int			numb;
	int			tot;

	i = 0;
	if ((s[i] == '0') && (s[i + 1] == 'X' || s[i + 1] == 'x'))
		i += 2;
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
			ft_putstr("error color hexa\n");
		tot = 16 * tot + numb;
		i++;
	}
	return (tot);
}

t_rgbcolor		hexatorgb(char *hexcolor)
{
	t_rgbcolor	rgbcolor;
	char		*r;
	char		*g;
	char		*b;

	b = ft_strjoin("0x", ft_strsub(hexcolor, 2, 2));
	g = ft_strjoin("0x", ft_strsub(hexcolor, 4, 2));
	r = ft_strjoin("0x", ft_strsub(hexcolor, 6, 2));
	rgbcolor.r = hextoint(r);
	rgbcolor.g = hextoint(g);
	rgbcolor.b = hextoint(b);
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
	dizaine = n / 16;
	if (dizaine < 10)
		hex[i++] = dizaine + '0';
	else
		hex[i++] = dizaine % 10 + 'A';
	n = n - (dizaine * 16);
	if (n < 10)
		hex[i++] = n + '0';
	else
		hex[i++] = n % 10 + 'A';
	return (hex);
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
