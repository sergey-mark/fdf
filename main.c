
#include "fdf.h"

int main()
{
	void *mlx;
	void *win;

	ft_putendl("fdf");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
	mlx_loop(mlx);
	return (0);
}

