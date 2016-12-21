#include "fdf.h"

#define ButtonRelease		5
#define ButtonReleaseMask	(1L<<3)
#define MotionNotify		6
#define ButtonMotionMask	(1L<<13)
#define KeyPress			2
#define KeyPressMask		(1L<<0)
#define KeyRelease			3
#define KeyReleaseMask		(1L<<1)

void		calc_Zhigh(t_wind *w)
{
	int x;
	int y;
	int max;
	int min;

	min = 0;
	max = 1;
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line)
		{
			if (w->b.tab_int[y][x] > max)
				max = w->b.tab_int[y][x];
			if (w->b.tab_int[y][x] < min)
				min = w->b.tab_int[y][x];
			x++;
		}
		y++;
	}
	w->p.zaccentuation = 1;
	w->p.zhighest = max;
	w->p.zlowest = min;
	w->p.zmid = w->p.zlowest + ((w->p.zhighest-w->p.zlowest)/2);
}

void			def_axle_rotation(t_wind *w)
{
	w->obj.gizt.p_x.x = w->img.x_centerpoint;
	w->obj.gizt.p_x.y = w->img.y_centerpoint;
	w->obj.gizt.p_x.z = 0;
	w->obj.gizt.pd_x.x = w->img.x_centerpoint + 50;
	w->obj.gizt.pd_x.y = w->img.y_centerpoint;
	w->obj.gizt.pd_x.z = 0;
	w->obj.gizt.p_y.x = w->img.x_centerpoint;
	w->obj.gizt.p_y.y = w->img.y_centerpoint;
	w->obj.gizt.p_y.z = 0;
	w->obj.gizt.pd_y.x = w->img.x_centerpoint;
	w->obj.gizt.pd_y.y = w->img.y_centerpoint + 50;
	w->obj.gizt.pd_y.z = 0;
	w->obj.gizt.p_z.x = w->img.x_centerpoint;
	w->obj.gizt.p_z.y = w->img.y_centerpoint;
	w->obj.gizt.p_z.z = 0;
	w->obj.gizt.pd_z.x = w->img.x_centerpoint;
	w->obj.gizt.pd_z.y = w->img.y_centerpoint;
	w->obj.gizt.pd_z.z = 0 + 50;
	w->obj.gizt.t.x = 0;
	w->obj.gizt.t.y = 0;
	w->obj.gizt.t.z = 0;
	w->obj.center_rgiz.x = w->img.x_centerpoint;
	w->obj.center_rgiz.y = w->img.y_centerpoint;
	w->obj.center_rgiz.z = w->img.z_centerpoint;
}

void			def_color(t_wind *w)
{
	w->p.color.hexa_top = "0xFFFFFF"; 
	w->p.color.hexa_mid = "0x024302"; 
	w->p.color.hexa_bot = "0x432502"; 
	w->p.color.hexa_default = "0x9E11BF";
	w->p.color.hexa_bool = 0; 
}

void			def_tranrotscale_gizmo(t_wind *w)
{
	w->p.t.x = 0; 
	w->p.t.y = 0; 
	w->p.t.z = 0; 
	w->p.rot.x = 0; 
	w->p.rot.y = 0; 
	w->p.rot.z = 0; 
}

static int		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;
	w->img.margin = 100;
	w->p.graphic_mode = 2; 
	w->p.view_mode = 3; 
	w->p.help = 1;
	w->p.turntable = 0;
	w->p.space_mousemove = 0;
	w->p.m.button1 = 0; 
	w->p.m.button2 = 0;
	w->p.m.button3 = 0;
	w->p.paint = 0;
	w->p.m.mem_gizx = 0;
	w->obj.showgiz.t = 1; 
	w->obj.showgiz.r = 0;
	w->obj.showgiz.s = 0;
	w->obj.f.bol = 0; 
	w->obj.f.bolfill = 0; 
	calc_Zhigh(w);
	w->p.y_spacing = (w->img.height - w->img.margin*2)/(w->b.nbr_of_line); 
	w->p.x_spacing = (w->img.width - w->img.margin*2)/(w->b.nbr_elem_line);
	w->img.x_centerpoint = w->img.width/2;
	w->img.y_centerpoint = w->img.height/2;
	def_color(w);
	w->p.insert = 0;
	w->img.x = 0;
	w->img.y = 0;
	return (0);
}

int				fdf(char *filename)
{
	t_wind		w;

	w.width = 800;
	w.height = 600;
	w = create_new_window("42 minilibx", w.width, w.height);
	w.b.tab_int = browsefile(filename, &w.b.nbr_of_line, &w.b.nbr_elem_line);
	set_parameters(&w);
	def_axle_rotation(&w);
	def_tranrotscale_gizmo(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	mlx_mouse_hook(w.win, mousepress_function, &w); 
	mlx_hook(w.win, ButtonRelease, ButtonReleaseMask, mouseRelease_function, &w);
	mlx_hook(w.win, MotionNotify, ButtonMotionMask, mouseMotion_function, &w);
	mlx_hook(w.win, KeyPress, KeyPressMask, keypress_function, &w);
	mlx_hook(w.win, KeyRelease, KeyReleaseMask, keyRelease_function, &w);
	mlx_loop_hook(w.mlx, turntable, &w); 
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

