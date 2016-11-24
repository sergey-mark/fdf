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
		(*y)++;
	tab_int = malloc(((*y)+1) * sizeof(int *));
	(*y) = 0;
	while (get_next_line(fd, &line))
	{
		//ft_putendl(line);
		tab_int[(*y)] = malloc(ft_strlen(line) * sizeof(int));
		tab = ft_strsplit(line, ' ');//nbr d'elements par lignes
		(*x) = 0;
		while (tab[(*x)])
		{
			tab_int[(*y)][(*x)] = ft_atoi(tab[(*x)]);
			(*x)++;
		}
		(*y)++;
	}
	return (tab_int);
}
