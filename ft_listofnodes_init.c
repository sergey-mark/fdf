#include "fdf.h"

t_listofnodes				*ft_listofnodes_init(t_listp_path *tmp)
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

t_listofnodes				*ft_listofnodes_add(t_listofnodes *list, t_listofnodes *elem)
{
	t_listofnodes			*tmp;

	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
	return (tmp);
}

void						fill_listofnodes(t_wind *w, t_listofnodes *lstnodes)
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

t_listofnodes				*create_listofnodesperrow_fill(t_wind *w, t_listp_path *beginlst, int row_min, int row_max)
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
			else if (tmp->p->y == row_min && j != 0)
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
