#include "fdf.h"

#define ROTABS(rot_z) ((rot_z >= 360 || rot_z <= -360) ? rot_z %= 360 : rot_z)

static void		keypress_function01(int keycode, t_wind *w)
{
	if (keycode == KEY_W)
		(w->obj.showgiz.t) ? (w->obj.showgiz.t = 0) : (w->obj.showgiz.t = 1, w->obj.showgiz.r = 0, w->obj.showgiz.s = 0);
	else if (keycode == KEY_E) 
		(w->obj.showgiz.r) ? (w->obj.showgiz.r = 0) : (w->obj.showgiz.r = 1, w->obj.showgiz.t = 0, w->obj.showgiz.s = 0);
	else if (keycode == KEY_R) 
		(w->obj.showgiz.s) ? (w->obj.showgiz.s = 0) : (w->obj.showgiz.s = 1, w->obj.showgiz.t = 0, w->obj.showgiz.r = 0);
	if (keycode == KEY_T) 
		(w->p.turntable) ? (w->p.turntable = 0) : (w->p.turntable = 1);
	if (keycode == KEY_P) 
		(w->p.paint) ? (w->p.paint = 0): (w->p.paint = 1);
	if (keycode == SPACE)
		w->p.space_mousemove = 1;
	if (keycode == L_ARROW)
		(w->p.view_mode == 2) ? (w->p.rot.z += 45) : (w->p.rot.z -= 5);
	else if (keycode == R_ARROW)
		(w->p.view_mode == 2) ? (w->p.rot.z -= 45) : (w->p.rot.z += 5);
	else if (keycode == U_ARROW)
		w->p.rot.x += 5;
	else if (keycode == D_ARROW)
		w->p.rot.x -= 5;
	else if (keycode == BACKSLASH)
		w->p.rot.y -= 5;
	else if (keycode == EXCLAMMARK)
		w->p.rot.y += 5;
	if (keycode == INSERT)
		(w->p.insert) ? (w->p.insert = 0) : (w->p.insert = 1);
}

static void		keypress_function02(int keycode, t_wind *w)
{
	if (keycode == NUM_U)
		(w->p.insert) ? (w->obj.gizt.t.y -= 10) : (w->p.t.y -= 10, w->obj.gizt.t.y -= 10);
	else if (keycode == NUM_D)
		(w->p.insert) ? (w->obj.gizt.t.y += 10) : (w->p.t.y += 10, w->obj.gizt.t.y += 10);
	else if (keycode == NUM_R)
		(w->p.insert) ? (w->obj.gizt.t.x += 10) : (w->p.t.x += 10, w->obj.gizt.t.x += 10);
	else if (keycode == NUM_L)
		(w->p.insert) ? (w->obj.gizt.t.x -= 10) : (w->p.t.x -= 10, w->obj.gizt.t.x -= 10);
	else if (keycode == NUM_1)
		(w->p.insert) ? (w->obj.gizt.t.z -= 10) : (w->p.t.z -= 5, w->obj.gizt.t.z -= 5);
	else if (keycode == NUM_3)
		(w->p.insert) ? (w->obj.gizt.t.z += 10) : (w->p.t.z += 5, w->obj.gizt.t.z += 5);
	if (keycode == ZOOM_P)
		(w->p.x_spacing++, w->p.y_spacing++);
	if (keycode == ZOOM_M)
		(w->p.x_spacing--, w->p.y_spacing--);
	if (keycode == PAGE_U)
		w->p.zaccentuation++;
	if (keycode == PAGE_D)
		w->p.zaccentuation--;
	if (keycode == KEY_1)
		w->p.graphic_mode = 1;
	else if (keycode == KEY_2)
		w->p.graphic_mode = 2;
	else if (keycode == KEY_3)
		w->p.graphic_mode = 3;
}

static void		keypress_function03(int keycode, t_wind *w)
{
	if (keycode == KEY_4)
		w->p.graphic_mode = 4;
	else if (keycode == KEY_I)
		(w->p.dot == 1) ? (w->p.dot = 0) : (w->p.graphic_mode = 3, w->p.dot = 1);
	if (keycode == F1)
		(w->p.help == 1) ? (w->p.help = 0) : (w->p.help = 1);
	else if (keycode == F2)
		w->p.view_mode = 2; 
	else if (keycode == F3)
		w->p.view_mode = 3; 
}

int		keypress_function(int keycode, t_wind *w)
{
	if (keycode == EXIT)
		exit(0);
	ROTABS(w->p.rot.z);
	keypress_function01(keycode, w);
	keypress_function02(keycode, w);
	keypress_function03(keycode, w);
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}
