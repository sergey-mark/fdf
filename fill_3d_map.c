#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)
	{
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x - w->p.x_spacing;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1] ;
		draw_line(w, w->img.point, w->img.pointd);
	}
	if(y<(w->b.nbr_of_line-1))
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x;
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.zd = w->b.tab_int[y+1][x];
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) 
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x + w->p.x_spacing; 
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.z = w->b.tab_int[y][x];
		w->p.color.zd = w->b.tab_int[y+1][x+1];
		
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static t_listofnodes		*ft_listofnodes_init(t_listp_path *tmp)
{
	t_listofnodes			*lstnodes;
	t_line					v;
	t_listp_path			*elem;

	lstnodes = malloc(sizeof(t_listofnodes));
	if (!lstnodes)
		return (NULL);
	v.x = tmp->p->x;
	v.y = tmp->p->y;
	v.z = tmp->p->z;
	elem = ft_pathinit(v);
	lstnodes->lstp = elem;
	lstnodes->next = NULL;
	return (lstnodes);
}

static t_listofnodes		*ft_listofnodes_add(t_listofnodes *list, t_listofnodes *elem)
{
	t_listofnodes			*tmp;

	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
	return (tmp);
}

static void					fill_listofnodes(t_wind *w, t_listofnodes *lstnodes)
{
	int						i;
	int						j;
	t_listofnodes			*tmp;
	t_listp_path			*path;
	t_listp_path			*path2;

	i = 0;
	j = 0;
	tmp = lstnodes;
	while (tmp)
	{
		path = tmp->lstp;
		while (path->next != NULL)
		{
			path2 = path->next;
			w->obj.f.bol = 0;
			w->obj.f.bolfill = 1;
			get_pointinbetween(*path->p, *path2->p, w);
			w->obj.f.bolfill = 0;
			w->obj.f.bol = 1;
			path = path->next;
			j++;
		}
		i++;
		tmp = tmp->next;
	}
}

static t_listofnodes			*create_listofnodesperrow_fill(t_wind *w, t_listp_path *beginlst, int row_min, int row_max)
{
	t_listp_path			*tmp;
	t_listofnodes			*lstnodes;
	int						i;
	int						j;
	int						k;
	t_line					v;
	t_listp_path			*elem;
	t_listofnodes			*node;

	lstnodes = NULL;
	k = 0;
	while (row_min < (row_max+1))
	{
		tmp = beginlst;
		j = 0;
		while (tmp)
		{
			i = 0;
			if (tmp->p->y == row_min && j == 0)
			{
				if (i != 0)
				{
					node = ft_listofnodes_init(tmp);
					lstnodes = ft_listofnodes_add(w->obj.f.lstnodesbeg, node);
				}
				else
				{
					if (k == 0)
					{
						lstnodes = ft_listofnodes_init(tmp);
						w->obj.f.lstnodesbeg = lstnodes;
						k = 1;
					}
					else
					{
						lstnodes->next = ft_listofnodes_init(tmp);
						lstnodes = lstnodes->next;
					}
				}
				i++;
				j++;
			}
			else if (tmp->p->y == row_min && j != 0 && j < 50)
			{
				v.x = tmp->p->x;
				v.y = tmp->p->y;
				v.z = tmp->p->z;
				elem = ft_pathinit(v);
				lstnodes->lstp = ft_pathadd(lstnodes->lstp, elem);
				j++;
			}
			tmp = tmp->next;
		}
		row_min++;
		j++;
	}
	return (w->obj.f.lstnodesbeg);
}

static int			croissant(int a, int b)
{
	return (a <= b);
}

t_listp_path			*ft_sort_listp(t_listp_path *lst, int (*cmp)(int, int))
{
	t_listp_path		*tmp;
	int					mem_x;
	int					mem_z;
	int					bol;

	bol = 1;
	mem_x = 0;
	mem_z = 0;
	while (bol != 0)
	{
		bol = 0;
		tmp = lst;
		while (tmp->next != NULL)
		{
			if ((*cmp)((int)tmp->p->x, (int)tmp->next->p->x) == 0)
			{
				mem_x = (int)tmp->p->x;
				mem_z = (int)tmp->p->z;
				tmp->p->x = tmp->next->p->x;
				tmp->p->z = tmp->next->p->z;
				tmp->next->p->x = mem_x;
				tmp->next->p->z = mem_z;
				bol++;
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}

static void			sort_listofnodes(t_listofnodes *lstnodes)
{
	t_listofnodes	*tmp;

	tmp = lstnodes;
	while (tmp)
	{
		tmp->lstp = ft_sort_listp(tmp->lstp, croissant);
		tmp = tmp->next;
	}
}

static void			set_min_max_y(t_listp_path *lstpath, int *row_min, int *row_max)
{
	t_listp_path	*tmp;

	tmp = lstpath;
	*row_min = tmp->p->y;
	*row_max = tmp->p->y;
	while (tmp)
	{
		if (tmp->p->y < *row_min)
			*row_min = tmp->p->y;
		if (tmp->p->y > *row_max)
			*row_max = tmp->p->y;
		tmp = tmp->next;
	}
}

static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;
	int				row_min;
	int				row_max;

	w->obj.f.bol = 1;
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) 
	{
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		s.pr.z = (w->b.tab_int[y][x+1] + w->p.t.z)*(w->p.zaccentuation);
		s.p = w->img.point;
		s.pd.x = w->img.point.x;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		s.pd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		s.pdi.x = w->img.point.x + w->p.x_spacing;
		s.pdi.y = w->img.point.y + w->p.y_spacing;
		s.pdi.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->obj.f.i = 0; 
		w->p.color.z = w->b.tab_int[y][x+1];
		w->p.color.zd = w->b.tab_int[y][x];
		draw_line(w, s.pr, s.p);
		w->p.color.z = w->b.tab_int[y][x];
		w->p.color.zd = w->b.tab_int[y+1][x];
		draw_line(w, s.p, s.pd);
		w->p.color.z = w->b.tab_int[y+1][x];
		w->p.color.zd = w->b.tab_int[y+1][x+1];
		draw_line(w, s.pd, s.pdi);
		w->p.color.z = w->b.tab_int[y+1][x+1];
		w->p.color.zd = w->b.tab_int[y][x+1];
		draw_line(w, s.pdi, s.pr);
		set_min_max_y(w->obj.f.beginpath, &row_min, &row_max);
		create_listofnodesperrow_fill(w, w->obj.f.beginpath, row_min, row_max);
		sort_listofnodes(w->obj.f.lstnodesbeg);
		fill_listofnodes(w, w->obj.f.lstnodesbeg);
	}
	w->obj.f.bol = 0;
	return (0);
}

int			fill_3d_map(t_wind *w)
{
	int		y;
	int		x;
	int		z;
	double	start_x;
	int		largeurfigure;

	w->img.point.y = (w->b.nbr_of_line * w->p.y_spacing)/2 + w->p.t.y; 
	largeurfigure = (w->b.nbr_elem_line)*(w->p.x_spacing);
	start_x = (w->img.width - largeurfigure)/2 + w->p.t.x; 
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.y_spacing;
		w->img.point.x = start_x; 
		while (x < w->b.nbr_elem_line)
		{
			z = w->b.tab_int[y][x];
			w->p.color.z = z;
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.zaccentuation);
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.r_point = matrice_rotation(w->img.point, w->p.rot, w->p.r_rot);
				w->img.x_centerpoint = w->img.r_point.x;
				w->img.y_centerpoint = (w->img.r_point.y - w->img.r_point.z);
				w->img.z_centerpoint = w->img.point.y - w->img.point.z;
			}
			checkpoint_allside(x, y, w);
			if (w->p.graphic_mode == 3)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
				fill_para(x, y, w);
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		y++;
	}
	return (0);
}
