/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 15:39:32 by pbillett          #+#    #+#             */
/*   Updated: 2015/12/07 15:54:47 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;

	i = 0;
	if (s1[0] == s2[i])
	{
		while (s1[i] == s2[i])
		{
			i++;
			if (s1[i] == '\0' && s2[i] == '\0')
				return (1);
		}
	}
	return (0);
}
