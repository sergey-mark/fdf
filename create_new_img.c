#include "fdf.h"

int		create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;

	ft_putstr("milieu:");
	ft_putnbr(w->r.p_x.y);

	// Creation of rotation axle
	draw_line(w, w->r.p_x, w->r.pd_x, 0);
	draw_line(w, w->r.p_y, w->r.pd_y, 0);

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

