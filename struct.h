
# ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_rgbcolor
{
	int				r;
	int				g;
	int				b;
}					t_rgbcolor;

typedef struct		s_line
{
	float			x;
	float			y;
	int				xdest;
	int				ydest;
	int				sign_x;
	int				sign_y;
	float			bigdiff;
	float			diff_x;
	float			diff_y;
}					t_line;

typedef struct		s_dpoint
{
	double			x;
	double			y;
	double			z;
}					t_dpoint;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	size_t			color;
}					t_point;

typedef struct		s_fillsquare
{
	t_point			point;
	t_point			pointr;
	t_point			pointd;
	t_point			pointdd;
}					t_fillsquare;

typedef struct		s_browsefile
{
	int				**tab_int;
	int				nbr_of_line; //nbr of line
	int				nbr_elem_line; //nbr elem on line
}					t_browsefile;

typedef struct		s_img
{
	void			*ptr_img;
	int				x; //position of img
	int				y;
	int				start_x; //depart print ds img
	int				start_y;
	int				width;
	int				height;
	int				padh;
	int				padv;
	int				x_centerpoint;
	int				y_centerpoint;
	int				z_centerpoint;
	char			*pxl_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				octet_per_pixel;
	int				endian_type;
	t_point			point;//point
	t_point			pointd;//point destination
	t_point			r_point; //apres rotation
	t_point			r_pointd; //apres rotation
}					t_img;

typedef struct		s_params
{
	int				accentuation; //hauteur relief
	int				angle_projpara; //zoom y
	int				size_square; //zoom x
	t_point			rot; //angle de rotation
	t_dpoint		r_rot; //angle de rotation radian
	int				graphic_mode; //Mode dot/wireframe/fill
	int				view_mode; //Mode para/iso
	int				dot; //point centre carre
	int				insert;
	int				help;
}					t_params;

typedef struct		s_rotaxle
{
	t_point			p_x;
	t_point			pd_x;
	t_point			p_y;
	t_point			pd_y;
	t_point			oldp_x;
	t_point			oldp_y;
}					t_rotaxle;

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
	t_rotaxle		r;
}					t_wind;

#endif

