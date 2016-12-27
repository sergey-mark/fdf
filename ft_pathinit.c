/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:41:29 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 14:42:11 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point				*ft_pointnew(int x, int y, int z)
{
	t_point			*new;

	new = malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_listp_path		*ft_pathinit(t_line v)
{
	t_listp_path	*path;

	path = malloc(sizeof(t_listp_path));
	path->p = ft_pointnew(rint(v.x), rint(v.y), rint(v.z));
	path->next = NULL;
	return (path);
}

t_listp_path		*ft_pathadd(t_listp_path *list, t_listp_path *elem)
{
	t_listp_path	*tmp;

	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
	return (list);
}

t_listp_path		*ft_pathremove(t_listp_path *list)
{
	t_listp_path	*tmp;
	t_listp_path	*gap;

	tmp = list;
	if (tmp->next == NULL || tmp->next->next == NULL)
		gap = NULL;
	else
		gap = tmp->next->next;
	free(tmp);
	tmp->next = gap;
	return (tmp);
}

void				set_minmaxy_lstpath(t_listp_path *lstpath, t_wind *w)
{
	t_listp_path	*tmp;

	tmp = lstpath;
	w->obj.f.row_min = tmp->p->y;
	w->obj.f.row_max = tmp->p->y;
	while (tmp)
	{
		if (tmp->p->y < w->obj.f.row_min)
			w->obj.f.row_min = tmp->p->y;
		if (tmp->p->y > w->obj.f.row_max)
			w->obj.f.row_max = tmp->p->y;
		tmp = tmp->next;
	}
}
