


#ifndef FDF_H

# define FDF_H
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include "struct.h"
#include "get_next_line/get_next_line.h"
#include "keymacro.h"
#include <math.h>
#include <stdlib.h>

#include <stdio.h> // A supprimer

int				fdf(char *filename);
t_wind			create_new_window(char *title, int width, int height);
int				**browsefile(char *filename, int *y, int *x);
int				create_new_img(t_wind *w);
int				dot_in_window(t_wind *w, int x, int y);
void			help(t_wind *w);
int				fill_3d_map(t_wind *w);
void			draw_point(t_wind *w, int x, int y, char *hexacolor);
int				draw_line(t_wind *w, t_point point, t_point pointd);
int				dot_in_window(t_wind *w, int x, int y);
char			*get_color(t_wind *w, int z);
int				keypress_function(int keycode, t_wind *w);
int				keyRelease_function(int keycode, t_wind *w);
int				mousepress_function(int button, int x, int y, t_wind *w);
int				mouseRelease_function(int button, int x, int y, t_wind *w);
int				mouseMotion_function(int x, int y, t_wind *w);
void			pencil(t_wind *w, int x, int y);
int				turntable(t_wind *w);
int				expose_hook(t_wind *w);
t_point			matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);
double			degree_to_radian(int degree);
void			draw_circle(t_wind *w, t_point centerp, int rayon);
t_point			rotate_point(t_wind *w, t_point dot);
int				get_pointinbetween(t_point point, t_point pointd, t_wind *w);
t_listp_path	*ft_pathadd(t_listp_path *list, t_listp_path *elem);
t_listp_path	*ft_pathremove(t_listp_path *list);
t_listp_path	*ft_pathinit(t_line v);

#endif
