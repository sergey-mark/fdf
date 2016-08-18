#include "fdf.h"

int		create_new_img(t_wind *w, int width, int height)
{
		w->img.width = width;
		w->img.height = height;

	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);

	if (w->p.view_mode == 2)
	{
		ft_putstr("mode iso");
		fill_3d_map_iso(w);
	}
	else if (w->p.view_mode == 3)
	{
		ft_putstr("mode parallele");
		fill_3d_map(w);
	}
	return (0);
}

