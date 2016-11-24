
# ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_rgbcolor
{
	int				r;
	int				g;
	int				b;
}					t_rgbcolor;

typedef struct		s_colorpalette
{
	char			*hexa_bot; //Color bottom in hexa
	char			*hexa_mid;
	char			*hexa_top;
	char			*hexa_default;
	int				hexa_bool;
	int				z;//dot height of field
	int				zd;//dot height of field dst
	int				min;//Min Level for percent of color
	int				max;//Max level
}					t_colorpalette;

typedef struct		s_mouse
{
	int				button1;// (1 pour press, 0 pour onRelease)
	int				button2;
	int				button3;
	int				memm_x; //Save mouse pos at start of the clic
	int				memm_y;
	int				mem_rotz;
}					t_mouse;

typedef struct		s_line
{
	float			x;
	float			y;
	float			z;//For height per color
	int				xdest;
	int				ydest;
	int				zdest;
	int				sign_x;
	int				sign_y;
	int				sign_z;
	float			bigdiff;
	float			diff_x;
	float			diff_y;
	float			diff_z;
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
}					t_point;

typedef struct		s_fillsquare
{
	t_point			p;
	t_point			pr;
	t_point			pd;
	t_point			pdi;
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
	int				margin;
}					t_img;

typedef struct		s_params
{
	//int				accentuation; //hauteur relief
	int				zhighest; //highest field
	int				zlowest; //lowest field
	int				zmid; //mid field
	int				x_spacing;
	int				y_spacing;
	int				z_spacing;
	t_point			t; //Translate
	t_point			rot; //angle de rotation
	t_dpoint		r_rot; //angle de rotation radian
	int				graphic_mode; //Mode dot/wireframe/fill
	int				view_mode; //Mode para/iso
	int				dot; //point centre carre
	int				insert;
	int				help;
	t_colorpalette	color;
	int				turntable;
	t_mouse			m;
	int				paint;
}					t_params;

typedef struct		s_movegizmo
{
	int				show;
	t_point			t;
	t_point			p_x; //Points to draw the axles:
	t_point			pd_x;
	t_point			p_y;
	t_point			pd_y;
	t_point			p_z;
	t_point			pd_z;
}					t_movegizmo;

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
	t_movegizmo		r;
}					t_wind;

#endif

