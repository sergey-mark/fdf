
# ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_point
{
	int			x;
	int			y;
	size_t		color;
}				t_point;

typedef struct	s_wind
{
	void		*mlx;
	void		*win;
	char		*title;
	int			width;
	int			height;
	t_point		point;
}				t_wind;

#endif

