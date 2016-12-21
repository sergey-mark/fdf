#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		w->img.pointd.z = (w->b.tab_int[y][x-1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x - w->p.x_spacing;
		w->img.pointd.y = w->img.point.y;
		w->p.color.zd = w->b.tab_int[y][x-1] ;//height
		/*
		ft_putendl("Check de tout les points in allside:");
		ft_putnbr(w->img.point.x);
		ft_putchar('\n');
		ft_putnbr(w->img.point.y);
		ft_putchar('\n');
		ft_putnbr(w->img.point.z);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.x);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.y);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.z);
		ft_putchar('\n');*/
		draw_line(w, w->img.point, w->img.pointd);
	}
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		w->img.pointd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x;
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;
		w->p.color.zd = w->b.tab_int[y+1][x];//height
		/*
		ft_putendl("Check de tout les points in allside:");
		ft_putnbr(w->img.point.x);
		ft_putchar('\n');
		ft_putnbr(w->img.point.y);
		ft_putchar('\n');
		ft_putnbr(w->img.point.z);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.x);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.y);
		ft_putchar('\n');
		ft_putnbr(w->img.pointd.z);
		ft_putchar('\n');*/
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->img.pointd.x = w->img.point.x + w->p.x_spacing; // les sizesquare s'annule.
		w->img.pointd.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous 
		w->p.color.z = w->b.tab_int[y][x];//height
		w->p.color.zd = w->b.tab_int[y+1][x+1];//height dest
		// TRIANGULATE
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
/*
static void					print_listofnodes(t_listofnodes *lstnodes)
{
	int						i;
	int						j;
	t_listofnodes			*tmp;
	t_listp_path			*path;

	i = 0;
	j = 0;
	tmp = lstnodes;
	ft_putstr("print list of nodes: \n");
	while (tmp)
	{
		ft_putstr("nodes: ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr(" x:");
		ft_putnbr(tmp->lstp->p->x);
		ft_putstr(" y:");
		ft_putnbr(tmp->lstp->p->y);
		ft_putstr(" z:");
		ft_putnbr(tmp->lstp->p->z);
		ft_putchar('\n');
		
		path = tmp->lstp;
		while (path->next != NULL)
		{
			path = path->next;
			ft_putstr("||| inside node ");
			ft_putnbr(j);
			ft_putstr("}");
			ft_putstr(" x:");
			ft_putnbr(path->p->x);
			ft_putchar(' ');
			ft_putstr(" y:");
			ft_putnbr(path->p->y);
			ft_putchar(' ');
			ft_putstr(" z:");
			ft_putnbr(path->p->z);
			ft_putchar(' ');
			ft_putchar('\n');
			j++;
		}
		i++;
		tmp = tmp->next;
	}
}*/

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
	//ft_putstr("fill list of nodes: \n");
	while (tmp)
	{
		/*ft_putstr("fill nodes: ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr(" x:");
		ft_putnbr(tmp->lstp->p->x);
		ft_putstr(" y:");
		ft_putnbr(tmp->lstp->p->y);
		ft_putstr(" z:");
		ft_putnbr(tmp->lstp->p->z);
		ft_putchar('\n');
		ft_putnbr(w->p.paint);*/

		path = tmp->lstp;
		while (path->next != NULL)
		{
			//if (j == 0)
			path2 = path->next;
			/*ft_putstr("fill||| inside node ");
			ft_putnbr(j);
			ft_putstr("}");
			ft_putstr(" x:");
			ft_putnbr(path->p->x);
			ft_putchar(' ');
			ft_putstr(" y:");
			ft_putnbr(path->p->y);
			ft_putchar(' ');
			ft_putstr(" z:");
			ft_putnbr(path->p->z);
			ft_putstr(" -> ");
			ft_putstr(" x:");
			ft_putnbr(path2->p->x);
			ft_putchar(' ');
			ft_putstr(" y:");
			ft_putnbr(path2->p->y);
			ft_putchar(' ');
			ft_putstr(" z:");
			ft_putnbr(path2->p->z);
			ft_putchar('\n');*/
			// Draw_line recall get_pointinbetween() func, so we temporary set off the bol parameters to fill the surface:
			
			w->obj.f.bol = 0;
			w->obj.f.bolfill = 1;
			//if (dot_in_window(w, path->p->x, path->p->y))
			//{
					//We set pointcolor of beginning and and the end point:
					//w->p.color.z = path->p->z;
					//w->p.color.zd = path2->p->z;
					//get_pointinbetween(*path->p, *path2->p, w);
					//draw_point(w, path->p->x, path->p->y, get_color(w, path->p->z));
					get_pointinbetween(*path->p, *path2->p, w);
			//}
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
				/*ft_putnbr(tmp->p->x);
				ft_putstr(">");
				ft_putnbr(tmp->next->p->x);
				ft_putstr("\n");*/
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
		//ft_putstr("sort_listofnodes:");
		//ft_putnbr(tmp->lstp->p->y);
		//ft_putchar('\n');
		tmp->lstp = ft_sort_listp(tmp->lstp, croissant);
		tmp = tmp->next;
	}
}
/*
static void			print_listp_path(t_listp_path *lst)
{
	t_listp_path	*start;

	start = lst;
	ft_putendl("print list point path:");
	while (lst)
	{
		ft_putstr("x:");
		ft_putnbr(lst->p->x);
		ft_putstr(" y:");
		ft_putnbr(lst->p->y);
		ft_putstr(" z:");
		ft_putnbr(lst->p->z);
		ft_putchar('\n');
		lst = lst->next;
	}
	lst = start;
}*/

static void			set_min_max_y(t_listp_path *lstpath, int *row_min, int *row_max)
{
	t_listp_path	*tmp;

	// Set of Min and max for the rows
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
	}/*
	ft_putstr("row_min:\n");
	ft_putnbr(*row_min);
	ft_putstr("\n");
	ft_putstr("row_max:\n");
	ft_putnbr(*row_max);
	ft_putstr("\n");*/
}

static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;
	int				row_min;
	int				row_max;

	//Var to know when I use fill_para function in get_pointinbetween
	w->obj.f.bol = 1;

	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droite, actuel, et en dessous et en diagonale à droite
	{
		// Point à droite:
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		s.pr.z = (w->b.tab_int[y][x+1] + w->p.t.z)*(w->p.zaccentuation);
		//Point actuel (en haut à gauche)
		s.p = w->img.point;
		// Point en dessous: (bas à gauche)
		s.pd.x = w->img.point.x;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		s.pd.z = (w->b.tab_int[y+1][x] + w->p.t.z)*(w->p.zaccentuation);
		// Point en diagonale: (bas à droite)
		s.pdi.x = w->img.point.x + w->p.x_spacing;
		s.pdi.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous
		s.pdi.z = (w->b.tab_int[y+1][x+1] + w->p.t.z)*(w->p.zaccentuation);
		w->obj.f.i = 0; //initialisation de i

		 //Get list of all point(and do not print them)
		w->p.color.z = w->b.tab_int[y][x+1];  //We set color z high for draw_line
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
		// Normalement l'ensemble du path est récuppéré en liste de point.
		//print_listp_path(w->obj.f.beginpath);

		set_min_max_y(w->obj.f.beginpath, &row_min, &row_max);

		create_listofnodesperrow_fill(w, w->obj.f.beginpath, row_min, row_max);
		//ft_putstr("create_listofnodesperrow_fill done !\n");
		//print_listofnodes(w->obj.f.lstnodesbeg);
		//ft_putstr("print done !\n");
		//ft_putstr("start sort !\n");
		sort_listofnodes(w->obj.f.lstnodesbeg);
		//ft_putstr("sort done !\n");
		//ft_putstr("Finale Print !\n");
		//print_listofnodes(w->obj.f.lstnodesbeg);
		fill_listofnodes(w, w->obj.f.lstnodesbeg);
	}
	//Var to know when I use fill_para function in get_pointinbetween
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

	w->img.point.y = (w->b.nbr_of_line * w->p.y_spacing)/2 + w->p.t.y; //On centre la figure au milieu de l'axe de rotation.
	//w->img.point.y = 0; //On centre la figure au milieu de l'axe de rotation.
	//w->img.point.y = w->p.t.y; //On centre la figure au milieu de l'axe de rotation.
	largeurfigure = (w->b.nbr_elem_line)*(w->p.x_spacing);
	start_x = (w->img.width - largeurfigure)/2 + w->p.t.x; //Centrage de la piece
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.y_spacing;
		w->img.point.x = start_x; // moins la position de l'axe
		while (x < w->b.nbr_elem_line)
		{
			z = w->b.tab_int[y][x];
			w->p.color.z = z;//height
			w->img.point.z = (w->b.tab_int[y][x]+ w->p.t.z)*(w->p.zaccentuation);
			//ft_putnbr(z);
			//ft_putchar('-');
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.r_point = matrice_rotation(w->img.point, w->p.rot, w->p.r_rot);
				w->img.x_centerpoint = w->img.r_point.x;
				w->img.y_centerpoint = (w->img.r_point.y - w->img.r_point.z);
				w->img.z_centerpoint = w->img.point.y - w->img.point.z;
				/*
				ft_putstr("center point:");
				ft_putnbr(w->img.x_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.y_centerpoint);
				ft_putstr(":");
				ft_putnbr(w->img.z_centerpoint);
				ft_putchar('\n');*/
			}
			checkpoint_allside(x, y, w);
			if (w->p.graphic_mode == 3)
				triangulate_para(x, y, w);
			if (w->p.graphic_mode == 4)
			{
				fill_para(x, y, w);
				//checkpoint_allside(x, y, w); // To do the outline override
			}
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		//ft_putendl("|");
		y++;
	}
	return (0);
}
