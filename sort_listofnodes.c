#include "fdf.h"

static int				croissant(int a, int b)
{
	return (a <= b);
}

t_listp_path			*ft_sort_listp(t_listp_path *lst, int (*cmp)(int, int))
{
	t_listp_path		*tmp;
	int					mem_x;
	int					mem_z;
	int					bol;

	bol = 1, mem_x = 0, mem_z = 0;
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

void				sort_listofnodes(t_listofnodes *lstnodes)
{
	t_listofnodes	*tmp;

	tmp = lstnodes;
	while (tmp)
	{
		tmp->lstp = ft_sort_listp(tmp->lstp, croissant);
		tmp = tmp->next;
	}
}
