#include "fdf.h"

static int		set_parameters(t_wind *w)
{
	w->img.width = 1024;
	w->img.height = 900;

	w->img.x_centerpoint = 500;
	w->img.y_centerpoint = 370;
	// Parameters:
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.view_mode = 3; // Mode para par défault (touche F2/F3 pour changer)
	w->p.accentuation = 1;// On peut mettre une accentuation à 10 pour compenser les maps avec des petits chiffres ;). Default = 1
	w->p.angle_projpara = 30;
	w->p.size_square = 30;
	w->p.rot.x = 0; // Rotation x par défault
	w->p.rot.y = 0; // Rotation x par défault
	w->p.rot.z = 0; // Rotation x par défault
	//Position of image in window
	w->img.x = 0;
	w->img.y = 0;
	w->img.point.color = 0xFFFFFF;
	return (0);
}

int				fdf(char *filename)
{
	t_wind		w;

	w.width = 1024;
	w.height = 900;
	w = create_new_window("42 minilibx", w.width, w.height);
	set_parameters(&w);
	w.b.nbr_of_line = 0;
	w.b.nbr_elem_line = 0;
	w.b.tab_int = browsefile(filename, &w.b.nbr_of_line, &w.b.nbr_elem_line);
	create_new_img(&w, w.img.width, w.img.height);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	mlx_key_hook(w.win, key_function, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	//mlx_mouse_hook(w.win, my_mouse_function, &w);
	mlx_loop(w.mlx);
	return (0);
}

