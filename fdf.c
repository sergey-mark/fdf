#include "fdf.h"

static int		set_parameters(t_wind *w)
{
	w->img.width = 800;
	w->img.height = 600;

	w->img.x_centerpoint = 500;
	w->img.y_centerpoint = 370;
	w->img.z_centerpoint = 370;
	// Parameters:
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	w->p.accentuation = 1;// On peut mettre une accentuation à 10 pour compenser les maps avec des petits chiffres ;). Default = 1
	w->p.angle_projpara = 30;
	w->p.size_square = 30;
	w->p.help = 1;

	w->p.rot.x = 0; // Rotation x par défault
	w->p.rot.y = 0; // Rotation y par défault
	w->p.rot.z = 0; // Rotation z par défault

	// Color Palette:
	w->p.color.hexa_top = "0xFFFFFF"; //Blanc
	w->p.color.hexa_mid = "0x024302"; //Vert
	w->p.color.hexa_bot = "0x432502"; //Marron
	w->p.color.hexa_axle = "0x9E11BF"; //Violet
	// Color fit height level for affection
	w->p.color.topl = 10;
	w->p.color.midl = 5;
	w->p.color.lowl = 0;

	// Definition des axes de rotation:
	w->r.p_x.x = (w->width/2)-25;
	w->r.p_x.y = w->height/2;
	w->r.p_x.z = 0;
	w->r.pd_x.x = (w->width/2)+25;
	w->r.pd_x.y = w->height/2;
	w->r.pd_x.z = 0;

	w->r.p_y.x = w->width/2;
	w->r.p_y.y = (w->height/2)-25;//25px height
	w->r.p_y.z = 0;
	w->r.pd_y.x = w->width/2;
	w->r.pd_y.y = (w->height/2)+25;//25px height
	w->r.pd_y.z = 0;

	// Insert pour modifier position axe Rotation
	w->p.insert = 0;

	//Position of image in window
	w->img.x = 0;
	w->img.y = 0;
	//Padding deplacement img par décalage fleche
	w->img.padh = 0;
	w->img.padv = 0;
	w->img.point.color = 0xFFFFFF;
	return (0);
}

int				fdf(char *filename)
{
	t_wind		w;

	w.width = 800;
	w.height = 600;
	w = create_new_window("42 minilibx", w.width, w.height);
	set_parameters(&w);
	w.b.nbr_of_line = 0;
	w.b.nbr_elem_line = 0;
	w.b.tab_int = browsefile(filename, &w.b.nbr_of_line, &w.b.nbr_elem_line);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	mlx_string_put(w.mlx, w.win, 5, 20, 0xFFFFFF, "Test");
	mlx_key_hook(w.win, key_function, &w);
	//mlx_loop_hook(w.mlx, keypress_func, &w);
	//mlx_hook(w.win, 2, keypress_func, KeyReleaseMask, &w);
	mlx_mouse_hook(w.win, mouse_function, &w);
	//mlx_loop_hook(w.mlx, mouse_function, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_loop(w.mlx);
	return (0);
}

