
#include "fdf.h"

int		my_key_function(int keycode, t_wind *w)
{
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65361 && w->point.x >= 0) // fleche gauche
		w->point.x -= 5;
	else if (keycode == 65363 && w->point.x < w->width) // fleche droite
		w->point.x += 5;
	else if (keycode == 65362 && w->point.x >= 0) // fleche haut
		w->point.y -= 5;
	else if (keycode == 65364 && w->point.x < w->height) // fleche bas
		w->point.y += 5;
	mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	return (0);
}

int		main()
{
	t_wind w;

	ft_putendl("fdf");
	w.mlx = mlx_init();
	w.width = 400;
	w.height = 400;
	w.title = "42 minilibx";
	w.win = mlx_new_window(w.mlx, w.width, w.height, w.title);

	w.point.x = 200;
	w.point.y = 200;
	w.point.color = 0x00FFFFFF;
	mlx_key_hook(w.win, my_key_function, &w);
	mlx_loop(w.mlx);
	return (0);
}

