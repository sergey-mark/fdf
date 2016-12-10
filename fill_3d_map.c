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
/*
static int				fill_square(t_wind *w, t_fillsquare s)
{
	t_line				v;
	t_line				v2;

	v.x = s.p.x; //left vertical side of square
	v.y = s.p.y - s.p.z;
	v.xdest = s.pd.x;
	v.ydest = s.pd.y - s.pd.z;
	v2.x = s.pr.x; //Right vertical side of square
	v2.y = s.pr.y - s.pr.z;
	v2.xdest = s.pdi.x;
	v2.ydest = s.pdi.y - s.pdi.z;
	while ((rint(v.y) < rint(v.ydest)) || (rint(v2.y) < rint(v2.ydest)))
	{
		//if (v.x != v.xdest)
			//v.x = v.x + (v.sign_x * (v.diff_x/v.bigdiff));
		if (v.y != v.ydest)
			v.y = v.y + (v.sign_y * (v.diff_y/v.bigdiff));
		//if (v2.x != v2.xdest)
			//v2.x = v2.x + (v2.sign_x * (v2.diff_x/v2.bigdiff));
		if (v2.y != v2.ydest)
			v2.y = v2.y + (v2.sign_y * (v2.diff_y/v2.bigdiff));
		
		if ((s.point.y-s.point.z) < (s.pointd.y-s.pointd.z))
			s.point.y++;
		if (s.point.x > s.pointd.x)
			s.point.x--;
		if ((s.pointr.y-s.pointr.z) < (s.pointdiag.y-s.pointdiag.z))
			s.pointr.y++;
		if ((s.pointr.x) > (s.pointdiag.x))
			s.pointr.x--;
		
		draw_line(w, s.p, s.pr);
	}
	return (0);
}*/

static t_listofnodes		*ft_listofnodes_init(t_listp_path *tmp)
{
	t_listofnodes			*lstnodes;
	t_line					v;
	t_listp_path			*elem;

	//ft_putendl("init");
	lstnodes = malloc(sizeof(t_listofnodes));
	if (!lstnodes)
		return (NULL);
	
	v.x = tmp->p->x;
	v.y = tmp->p->y;
	v.z = tmp->p->z;
	elem = ft_pathinit(v);
	//ft_putendl("after path init");
	//lstnodes->lstp = malloc(sizeof(t_listp_path));
	//ft_putendl("after path init malloc");
	//lstnodes->lstp = ft_pathadd(lstnodes->lstp, elem);*/
	lstnodes->lstp = elem;
	//ft_putendl("after path add");
	lstnodes->next = NULL;
	/*ft_putendl("end init");
	ft_putstr(" x:");
	ft_putnbr(lstnodes->lstp->p->x);
	ft_putstr(" y:");
	ft_putnbr(lstnodes->lstp->p->y);
	ft_putstr(" z:");
	ft_putnbr(lstnodes->lstp->p->z);
	ft_putchar('\n');*/
	return (lstnodes);
}

static t_listofnodes		*ft_listofnodes_add(t_listofnodes *list, t_listofnodes *elem)
{
	t_listofnodes			*tmp;

	tmp = list;
	while (tmp->next != NULL)
	{
		/*ft_putendl("Add listnodes");
		ft_putstr(" x:");
		ft_putnbr(tmp->lstp->p->x);
		ft_putstr(" y:");
		ft_putnbr(tmp->lstp->p->y);
		ft_putstr(" z:");
		ft_putnbr(tmp->lstp->p->z);*/
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (tmp);
}

static void					print_listofnodes(t_listofnodes *lstnodes)
{
	int						i;
	int						j;
	t_listofnodes			*tmp;
	t_listp_path			*path;

	i = 0;
	j = 0;
	tmp = lstnodes;
		ft_putstr(" x:");
		ft_putnbr(tmp->lstp->p->x);
		ft_putstr(" y:");
		ft_putnbr(tmp->lstp->p->y);
		ft_putstr(" z:");
		ft_putnbr(tmp->lstp->p->z);
		ft_putchar('\n');

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
		ft_putstr("---------------------------------debut node");
		tmp = beginlst;
		j = 0;
		while (tmp)
		{
			i = 0;
			ft_putstr("b");
			if (tmp->p->y == row_min && j == 0)
			{
				//ft_putstr("add node:");
				ft_putnbr(row_min);
				ft_putchar('\n');
				if (i != 0)
				{
					//ft_putendl("//////////////add");
					node = ft_listofnodes_init(tmp);
					/*ft_putstr("x:");
					ft_putnbr(node->lstp->p->x);
					ft_putstr("y:");
					ft_putnbr(node->lstp->p->y);
					ft_putstr("z:");
					ft_putnbr(node->lstp->p->z);*/
					lstnodes = ft_listofnodes_add(w->obj.f.lstnodesbeg, node);
				}
				else
				{
					ft_putendl("first elem");
					if (k == 0)
					{
						ft_putendl("first time ever !");
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
				/*
				ft_putstr("x:");
				ft_putnbr(lstnodes->lstp->p->x);
				ft_putstr(" y:");
				ft_putnbr(lstnodes->lstp->p->y);
				ft_putstr(" z:");
				ft_putnbr(lstnodes->lstp->p->z);
				ft_putstr("\n");*/
				i++;
				j++;
			}
			else if (tmp->p->y == row_min && j != 0 && j < 50)
			{
				/*
				ft_putendl("inside node");
				ft_putstr("x:");
				ft_putnbr(tmp->p->x);
				ft_putstr(" y:");
				ft_putnbr(tmp->p->y);
				ft_putstr(" z:");
				ft_putnbr(tmp->p->z);
				ft_putstr("\n");*/

				//ft_putnbr(row_min);
				//ft_putstr(" : ");
				//ft_putnbr(j);
				//ft_putstr(" - ");
				v.x = tmp->p->x;
				v.y = tmp->p->y;
				v.z = tmp->p->z;
				elem = ft_pathinit(v);
				//lstnodes->lstp = lstnodes->lstp
				lstnodes->lstp = ft_pathadd(lstnodes->lstp, elem);
				//tmp = ft_pathremove(tmp);
				j++;
			}
			tmp = tmp->next;
		}
		ft_putendl("---------------------------------fin de node");

		print_listofnodes(w->obj.f.lstnodesbeg);
		row_min++;
		j++;
	}
	return (w->obj.f.lstnodesbeg);
}
/*
static int			croissant(int a, int b)
{
	return (a <= b);
}*/
/*
t_listp_path			*ft_sort_listp(t_listp_path *lst, int (*cmp)(int, int))
{
	t_listp_path		*tmp;
	int					n;
	int					bol;

	bol = 1;
	n = 0;
	while (bol != 0)
	{
		bol = 0;
		tmp = lst;
		while (tmp->next != NULL)
		{
			if ((*cmp)((int)tmp->p->x, (int)tmp->next->p->x) == 0)
			{
				n = (int)tmp->p->x;
				tmp->p->x = tmp->next->p->x;
				tmp->next->p->x = n;
				bol++;
			}
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static void			sort_listofnodes(t_listofnodes *lstnodes)
{
	t_listofnodes	*start;
	int				i;

	i = 0;
	start = lstnodes;
	while (lstnodes)
	{
		ft_putstr("sort_listofnodes:");
		ft_putnbr(i);
		ft_putchar('\n');
		lstnodes->lstp = ft_sort_listp(lstnodes->lstp, croissant);
		lstnodes = lstnodes->next;
		i++;
	}
	lstnodes = start;
}*/

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
}

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
	}
	ft_putstr("row_min:\n");
	ft_putnbr(*row_min);
	ft_putstr("\n");
	ft_putstr("row_max:\n");
	ft_putnbr(*row_max);
	ft_putstr("\n");
}

static int			fill_para(int x, int y, t_wind *w)
{
	t_fillsquare	s;
	int				row_min;
	int				row_max;
	static int		bol;

	//Var to know when I use fill_para function in get_pointinbetween
	w->obj.f.bol = 1;

	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1))) && bol <= 0) //Si point à droite, actuel, et en dessous et en diagonale à droite
	{
		bol = 0;
		// Point à droite:
		s.pr.z = (w->b.tab_int[y][x+1])*(w->p.zaccentuation);
		s.pr.x = w->img.point.x + w->p.x_spacing;
		s.pr.y = w->img.point.y;
		//Point actuel (en haut à gauche)
		s.p = w->img.point;
		// Point en dessous: (bas à gauche)
		s.pd.z = (w->b.tab_int[y+1][x])*(w->p.zaccentuation);
		s.pd.x = w->img.point.x;
		s.pd.y = w->img.point.y + w->p.y_spacing;
		// Point en diagonale: (bas à droite)
		s.pdi.z = (w->b.tab_int[y+1][x+1])*(w->p.zaccentuation);
		s.pdi.x = w->img.point.x + w->p.x_spacing;
		s.pdi.y = w->img.point.y + w->p.y_spacing;// Pour afficher remplir toutes les lignes en dessous
		w->obj.f.i = 0; //initialisation de i
		//get point line from right point to top left point
		get_pointinbetween(s.pr, s.p, w);
		get_pointinbetween(s.p, s.pd, w);
		get_pointinbetween(s.pd, s.pdi, w);
		get_pointinbetween(s.pdi, s.pr, w);
		// Normalement l'ensemble du path est récuppéré en liste de point.
		print_listp_path(w->obj.f.beginpath);

		set_min_max_y(w->obj.f.beginpath, &row_min, &row_max);

		w->obj.f.lstnodesbeg = create_listofnodesperrow_fill(w, w->obj.f.beginpath, row_min, row_max);
		ft_putstr("create_listofnodesperrow_fill done !\n");
		print_listofnodes(w->obj.f.lstnodesbeg);
		ft_putstr("print done !\n");
		bol++;
		//sort_listofnodes(w->obj.f.lstnodes);
		//ft_putstr("sort_listofnodes done !\n");
		//fill_square(w, s);
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
				fill_para(x, y, w);
			w->img.point.x += w->p.x_spacing;
			x++;
		}
		//ft_putendl("|");
		y++;
	}
	return (0);
}

/*i = 0;
		nodes = 0;
		//Get nodes for each rows
		w->obj.f.nodepath = malloc(sizeof(t_point **));
		ft_putstr("number of nodes:");
		ft_putnbr(row_max - row_min);
		ft_putstr("\n");
		while (i < (row_max - row_min))
		{
			ft_putstr("malloc\n");
			w->obj.f.nodepath[i] = malloc(sizeof(t_point *));
			ft_putstr("i:");
			ft_putnbr(i);
			ft_putstr("\n");
			i++;
		}
		//if (!w->obj.f.nodepath)
			//return (1);
		i = 0;
		while (row_min < row_max)//Tant qu'on parcours les lignes
		{
			b = 0;
			while (i < w->obj.f.i)
			{
				if (row_min == w->obj.f.path[i].y)
					w->obj.f.nodepath[nodes][b++] = w->obj.f.path[i];
				i++;
			}
			ft_putstr("row:\n");
			ft_putnbr(row_min);
			ft_putstr("\n");
			ft_putstr("nodes:\n");
			ft_putnbr(nodes);
			ft_putstr("\n");
			nodes++;
			row_min++;
		}
		//  Sort the nodes, via a simple “Bubble” sort.
		i = 0;
		while (i < nodes-1)
		{
			b = 0;
			while (w->obj.f.nodepath[i][b].x > w->obj.f.nodepath[i][b+1].x)
			{
				swap = w->obj.f.nodepath[i][b];
				w->obj.f.nodepath[i][b] = w->obj.f.nodepath[i][b+1];
				w->obj.f.nodepath[i][b+1] = swap;
				if (b > 0)
					b--;
			}
			i++;
		}

		i = 0;
		//Fill the pixels between node pairs.
		while (i < nodes-1)
		{
			b = 0;
			while (w->obj.f.nodepath[i][b].x)
			{
				while (w->obj.f.nodepath[i][b].x < w->obj.f.nodepath[i][b+1].x)
				{
					draw_point(w, w->obj.f.nodepath[i][b].x, w->obj.f.nodepath[i][b].y, get_color(w, w->obj.f.nodepath[i][b].z));
					w->obj.f.nodepath[i][b].x++;
				}
				b += 2;
			}
			i++;
		}
		*/

