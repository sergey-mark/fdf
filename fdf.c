#include "fdf.h"

#define ButtonRelease		5
#define ButtonReleaseMask	(1L<<3)
#define MotionNotify		6
#define ButtonMotionMask	(1L<<13)
#define KeyPress			2
#define KeyPressMask		(1L<<0)
#define KeyRelease			3
#define KeyReleaseMask		(1L<<1)

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
	w->p.y_spacing = (w->img.height - w->img.margin*2)/(w->b.nbr_of_line); 
	w->p.x_spacing = (w->img.width - w->img.margin*2)/(w->b.nbr_elem_line);
	w->img.x_centerpoint = w->img.width/2;
	w->img.y_centerpoint = w->img.height/2;
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
	def_all_preui(&w);
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

