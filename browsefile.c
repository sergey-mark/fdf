/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browsefile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:37:09 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 16:58:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			**browsefile(char *filename, int *y, int *x)
{
	int		fd;
	int		fd1;
	char	*line;
	char	**tab;
	int		**tab_int;

	fd = open(filename, O_RDONLY);
	fd1 = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	tab = NULL;
	tab_int = NULL;
	(*y) = 0;
	while (get_next_line(fd1, &line))
	{
		ft_strdel(&line);
		(*y)++;
	}
	tab_int = malloc(((*y) + 1) * sizeof(int *));
	(*y) = 0;
	while (get_next_line(fd, &line))
	{
		tab_int[(*y)] = malloc(ft_strlen(line) * sizeof(int));
		tab = ft_strsplit(line, ' ');
		ft_strdel(&line);
		(*x) = 0;
		while (tab[(*x)])
		{
			tab_int[(*y)][(*x)] = ft_atoi(tab[(*x)]);
			ft_strdel(&tab[(*x)]);
			(*x)++;
		}
		free(tab);
		(*y)++;
	}
	close(fd);
	close(fd1);
	return (tab_int);
}
