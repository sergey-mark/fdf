#include "fdf.h"

static void		update_gizmo(t_wind *w, t_point b, t_point bd)
{
	t_point		p;
	t_point		pd;

	p.x = b.x + w->r.t.x;
	p.y = b.y + w->r.t.y;
	p.z = b.z + w->r.t.z;
	pd.x = bd.x + w->r.t.x;
	pd.y = bd.y + w->r.t.y;
	pd.z = bd.z + w->r.t.z;

	draw_line(w, p, pd);
}

static void		move_gizmo(t_wind *w)
{
	w->p.color.hexa_bool = 1; // We set custom color set for draw line
	update_gizmo(w, w->r.p_x, w->r.pd_x);
	update_gizmo(w, w->r.p_y, w->r.pd_y);
	update_gizmo(w, w->r.p_z, w->r.pd_z);
	w->p.color.hexa_bool = 0; // We unset custom color set for draw line
}

int				create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	//printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;

	if (w->r.show)//show Move gizmo if needed
		move_gizmo(w);
	if (w->p.view_mode == 2)
		fill_3d_map_iso(w);
	else if (w->p.view_mode == 3)
		fill_3d_map(w);
	return (0);
}

