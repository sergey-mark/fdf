#include "fdf.h"

static void		update_mgizmo(t_wind *w, t_point b, t_point bd)
{
	t_point		p;
	t_point		pd;

	p.x = b.x + w->obj.gizt.t.x;
	p.y = b.y + w->obj.gizt.t.y;
	p.z = b.z + w->obj.gizt.t.z;
	pd.x = bd.x + w->obj.gizt.t.x;
	pd.y = bd.y + w->obj.gizt.t.y;
	pd.z = bd.z + w->obj.gizt.t.z;
	draw_line(w, p, pd);
}

static void		rot_gizmo(t_wind *w)
{
	t_point		p;

	p.x = w->obj.center_rgiz.x + w->obj.gizt.t.x;
	p.y = w->obj.center_rgiz.y + w->obj.gizt.t.y;
	p.z = w->obj.center_rgiz.z + w->obj.gizt.t.z;
	draw_circle(w, p, 60, "no");
}

static void		move_gizmo(t_wind *w)
{
	w->p.color.hexa_bool = 1; // We set custom color set for draw line
	update_mgizmo(w, w->obj.gizt.p_x, w->obj.gizt.pd_x);
	update_mgizmo(w, w->obj.gizt.p_y, w->obj.gizt.pd_y);
	update_mgizmo(w, w->obj.gizt.p_z, w->obj.gizt.pd_z);
	w->p.color.hexa_bool = 0; // We unset custom color set for draw line
}

int				create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	//printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	if (w->p.view_mode == 2)
	{
		if (w->p.rot.z%45 != 0)
			w->p.rot.z = 45;
		fill_3d_map(w);
	}
	if (w->p.view_mode == 3)
		fill_3d_map(w);
	if (w->obj.showgiz.t)//show Move gizmo if needed
		move_gizmo(w);
	else if (w->obj.showgiz.r)//show Rotate gizmo if needed
		rot_gizmo(w);
	help(w);
	return (0);
}

