#include "fdf.h"

// Find all Events and Masks for mlx_hook()
// (for keyboard and mouse) in /usr/include/X11/X.h
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
	w->p.zaccentuation = 1;// On peut mettre accentuation à 10 pour compenser les maps avec des petits chiffres ;). Default = 1
	w->p.zhighest = max;
	w->p.zlowest = min;
	w->p.zmid = w->p.zlowest + ((w->p.zhighest-w->p.zlowest)/2);
}

void			def_axle_rotation(t_wind *w)
{
	// Definition des axes de rotation (GIZMO):
	w->obj.gizt.p_x.x = w->img.x_centerpoint;
	w->obj.gizt.p_x.y = w->img.y_centerpoint;
	w->obj.gizt.p_x.z = 0;
	w->obj.gizt.pd_x.x = w->img.x_centerpoint + 50;//50px height
	w->obj.gizt.pd_x.y = w->img.y_centerpoint;
	w->obj.gizt.pd_x.z = 0;
	//Axe rotation y
	w->obj.gizt.p_y.x = w->img.x_centerpoint;
	w->obj.gizt.p_y.y = w->img.y_centerpoint;
	w->obj.gizt.p_y.z = 0;
	w->obj.gizt.pd_y.x = w->img.x_centerpoint;
	w->obj.gizt.pd_y.y = w->img.y_centerpoint + 50;
	w->obj.gizt.pd_y.z = 0;
	//Axe rotation z
	w->obj.gizt.p_z.x = w->img.x_centerpoint;
	w->obj.gizt.p_z.y = w->img.y_centerpoint;
	w->obj.gizt.p_z.z = 0;
	w->obj.gizt.pd_z.x = w->img.x_centerpoint;
	w->obj.gizt.pd_z.y = w->img.y_centerpoint;
	w->obj.gizt.pd_z.z = 0 + 50;
	//Creation d'une position pour le deplacement du GIZMO
	//On positionne le gizmo en bas de l'écran
	w->obj.gizt.t.x = 0;
	w->obj.gizt.t.y = 0;
	//w->obj.gizt.t.y = (w->img.height/2) - w->img.margin;
	w->obj.gizt.t.z = 0;

	w->obj.center_rgiz.x = w->img.x_centerpoint;
	w->obj.center_rgiz.y = w->img.y_centerpoint;
	//w->obj.center_rgiz.z = 0;
	w->obj.center_rgiz.z = w->img.z_centerpoint;
}

void			def_color(t_wind *w)
{
	// Color Palette:
	w->p.color.hexa_top = "0xFFFFFF"; //Blanc
	w->p.color.hexa_mid = "0x024302"; //Vert
	w->p.color.hexa_bot = "0x432502"; //Marron
	w->p.color.hexa_bool = 0; //Color set or no
	w->p.color.hexa_default = "0x9E11BF"; //Violet
	ft_putstr("Zhighest:");
	ft_putnbr(w->p.zhighest);
	ft_putchar('\n');
	ft_putstr("Zlowest:");
	ft_putnbr(w->p.zlowest);
	ft_putchar('\n');
	ft_putstr("Zmid:");
	ft_putnbr(w->p.zmid);
	ft_putchar('\n');
}

void			def_tranrotscale_gizmo(t_wind *w)
{
	w->p.t.x = 0; // Position x par défault
	w->p.t.y = 0; // Position y par défault
	w->p.t.z = 0; // Position z par défault
	w->p.rot.x = 0; // Rotation x par défault
	w->p.rot.y = 0; // Rotation y par défault
	w->p.rot.z = 0; // Rotation z par défault
}

static int		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;
	w->img.margin = 100;

	// Parameters:
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.view_mode = 3; // Mode para par défault (touche F2/F3 pour changer)
	w->p.help = 1;
	w->p.turntable = 0;
	w->p.space_mousemove = 0;
	w->p.m.button1 = 0; //Mouse buttons
	w->p.m.button2 = 0;
	w->p.m.button3 = 0;
	w->p.paint = 0;
	w->p.m.mem_gizx = 0;
	w->obj.showgiz.t = 1; // show gizmos or not
	w->obj.showgiz.r = 0;
	w->obj.showgiz.s = 0;
	w->obj.f.bol = 0; // Var to know when we use fill_para func in get_pointinbetween 
	w->obj.f.bolfill = 0; //To draw_pixel in get_pointinbetween without recreate 2d matrice

	calc_Zhigh(w);
	w->p.y_spacing = (w->img.height - w->img.margin*2)/(w->b.nbr_of_line); //y spacing (height)
	w->p.x_spacing = (w->img.width - w->img.margin*2)/(w->b.nbr_elem_line);//X spacing (width)

	// Positionnement du gizmo au centre de l'objet
	w->img.x_centerpoint = w->img.width/2;//By default (its actualize after when drawing obj)
	w->img.y_centerpoint = w->img.height/2;//By default (its actualize after when drawing obj)

	def_color(w);
	w->p.insert = 0;//To modify position of rotation axle

	//Position of image in window
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
	mlx_mouse_hook(w.win, mousepress_function, &w); //mouse button press
	mlx_hook(w.win, ButtonRelease, ButtonReleaseMask, mouseRelease_function, &w);//mouse button Release
	mlx_hook(w.win, MotionNotify, ButtonMotionMask, mouseMotion_function, &w);//repetition mouse
	mlx_hook(w.win, KeyPress, KeyPressMask, keypress_function, &w);// repetition key
	mlx_hook(w.win, KeyRelease, KeyReleaseMask, keyRelease_function, &w);// release key
	mlx_loop_hook(w.mlx, turntable, &w); // When no event
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

