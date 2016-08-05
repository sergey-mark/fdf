#include "fdf.h"

int					main(int argc, char **argv)
{
	if (argc != 2)
		ft_putstr("usage");
	else
		fdf(argv[1]);
	return (0);
}
