


#ifndef FDF_H

# define FDF_H
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include "struct.h"
#include "get_next_line/get_next_line.h"
#include <math.h>
#include <stdlib.h>

#include <stdio.h> // A supprimer

int			fdf(char *filename);
t_wind		create_new_window(char *title, int width, int height);
int			**browsefile(char *filename, int *y, int *x);
int			create_new_img(t_wind *w);
int			dot_in_window(t_wind *w, int x, int y);
void		help(t_wind *w);
int			fill_3d_map_iso(t_wind *w);
int			fill_3d_map(t_wind *w);
void		draw_point(t_wind *w, int x, int y, char *hexcolor);
int			draw_line(t_wind *w, t_point point, t_point pointd, int boolean);
char		*get_color(t_wind *w, int height);
int			key_function(int keycode, t_wind *w);
int			expose_hook(t_wind *w);
t_point		rotation_point(t_point A, t_point angle, t_dpoint r_angle);
t_point		matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);

#endif
