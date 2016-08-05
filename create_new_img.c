#include "fdf.h"

int		create_new_img(t_wind *w, int width, int height)
{
		w->img.width = width;
		w->img.height = height;

	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	fill_3d_map(w->b, &w->img, w);
	return (0);
}

