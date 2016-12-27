#ifndef FDF_H

# define FDF_H
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include "struct.h"
#include "get_next_line/get_next_line.h"
#include "keymacro.h"
#include <math.h>
#include <stdlib.h>
int				fdf(char *filename);
void			def_all_preui(t_wind *w);
t_wind			create_new_window(char *title, int width, int height);
int				**browsefile(char *filename, int *y, int *x);
int				create_new_img(t_wind *w);
int				dot_in_window(t_wind *w, int x, int y);
void			help(t_wind *w);
int				fill_3d_map(t_wind *w);
int				fill_para(int x, int y, t_wind *w);
void			draw_point(t_wind *w, int x, int y, char *hexacolor);
int				draw_line(t_wind *w, t_point point, t_point pointd);
int				dot_in_window(t_wind *w, int x, int y);
char			*get_color(t_wind *w, int z);
int				keypress_function(int keycode, t_wind *w);
void			keypress_function02(int keycode, t_wind *w);
int				key_release_function(int keycode, t_wind *w);
int				mousepress_function(int button, int x, int y, t_wind *w);
int				mouse_release_function(int button, int x, int y, t_wind *w);
int				mouse_motion_function(int x, int y, t_wind *w);
void			pencil(t_wind *w, int x, int y);
int				turntable(t_wind *w);
int				expose_hook(t_wind *w);
t_point			matrice_rotation(t_point p, t_point angle, t_dpoint r_angle, t_wind *w);
double			degree_to_radian(int degree);
void			draw_circle(t_wind *w, t_point centp, int rayon, char *hexcol);
void			draw_circlef(t_wind *w, t_point centp, int rayon, char *hexcol);
t_point			rotate_point(t_wind *w, t_point dot);
int				get_pointinbetween(t_point point, t_point pointd, t_wind *w);
t_listp_path	*ft_pathadd(t_listp_path *list, t_listp_path *elem);
t_listp_path	*ft_pathremove(t_listp_path *list);
t_listp_path	*ft_pathinit(t_line v);
char			*rgbtohexa(t_rgbcolor rgbcolor);
t_rgbcolor		hexatorgb(char *hexcolor);
t_listofnodes	*create_listofnodesperrow_fill(t_wind *w, t_listp_path *beginlst);
void			sort_listofnodes(t_listofnodes *lstnodes);
void			fill_listofnodes(t_wind *w, t_listofnodes *lstnodes);
t_line			set_parameters_tline(t_line v);
t_line			convert_3ddot_to2dline(t_point point, t_point pointd, t_wind *w);
void			set_minmaxy_lstpath(t_listp_path *lstpath, t_wind *w);

#endif
