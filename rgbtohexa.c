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
	char		*begin;
	char		*hexpart;

	begin = ft_strnew(2);
	begin = ft_strcpy(begin, "0x");
	hexpart = ft_strsub(hexcolor, 2, 2);
	b = ft_strjoin(begin, hexpart);
	ft_strdel(&hexpart);
	hexpart = ft_strsub(hexcolor, 4, 2);
	g = ft_strjoin(begin, hexpart);
	ft_strdel(&hexpart);
	hexpart = ft_strsub(hexcolor, 6, 2);
	r = ft_strjoin(begin, hexpart);
	ft_strdel(&hexpart);
	ft_strdel(&begin);
	rgbcolor.r = hextoint(r);
	rgbcolor.g = hextoint(g);
	rgbcolor.b = hextoint(b);
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
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
	char		*r;
	char		*g;
	char		*b;

	i = 0;
	hexa_color = ft_strnew(9);
	r = inttohex(rgbcolor.r);
	g = inttohex(rgbcolor.g);
	b = inttohex(rgbcolor.b);
	hexa_color[i++] = '0';
	hexa_color[i++] = 'x';
	hexa_color[i++] = r[2];
	hexa_color[i++] = r[3];
	hexa_color[i++] = g[2];
	hexa_color[i++] = g[3];
	hexa_color[i++] = b[2];
	hexa_color[i++] = b[3];
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
	return (hexa_color);
}
