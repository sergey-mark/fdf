
# ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	size_t			color;
}					t_point;

typedef struct		s_browsefile
{
	int				**tab_int;
	int				nbr_of_line;
	int				nbr_elem_line;
}					t_browsefile;

typedef struct		s_img
{
	void			*ptr_img;
	int				x;
	int				y;
	int				width;
	int				height;
	int				x_centerpoint;
	int				y_centerpoint;
	char			*pxl_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				octet_per_pixel;
	int				endian_type;
	t_point			point; //avant calcul rotation
	t_point			r_point; //apres caclul rotation
}					t_img;

typedef struct		s_params
{
	int				accentuation; //hauteur relief
	int				angle_projpara; //zoom y
	int				size_square; //zoom x
	int				graphic_mode; // Mode
	int				rot_x;
	int				rot_y;
	int				rot_z;
}					t_params;

typedef struct		s_wind
{
	void			*mlx;
	void			*win;
	char			*title;
	int				width;
	int				height;
	t_point			point;
	t_img			img;
	t_browsefile	b;
	t_params		p;
}					t_wind;

#endif

