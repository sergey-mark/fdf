/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:49:59 by pbillett          #+#    #+#             */
/*   Updated: 2017/01/10 15:50:02 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double		degree_to_radian(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees * (pi / 180);
	return (radians);
}

static void	def_matr(t_wind *w)
{
	w->mr.mat[0] = w->mr.c * w->mr.e;
	w->mr.mat[1] = -(w->mr.c) * w->mr.f;
	w->mr.mat[2] = w->mr.d;
	w->mr.mat[4] = w->mr.bd * w->mr.e + w->mr.a * w->mr.f;
	w->mr.mat[5] = -(w->mr.bd) * w->mr.f + w->mr.a * w->mr.e;
	w->mr.mat[6] = -(w->mr.b) * w->mr.c;
	w->mr.mat[8] = -(w->mr.ad) * w->mr.e + w->mr.b * w->mr.f;
	w->mr.mat[9] = w->mr.ad * w->mr.f + w->mr.b * w->mr.e;
	w->mr.mat[10] = w->mr.a * w->mr.c;
	w->mr.mat[3] = 0;
	w->mr.mat[7] = 0;
	w->mr.mat[11] = 0;
	w->mr.mat[12] = 0;
	w->mr.mat[13] = 0;
	w->mr.mat[14] = 0;
	w->mr.mat[15] = 1;
}

t_point		matrice_rotation(t_point p, t_point angle, t_dpoint r_angle,
t_wind *w)
{
	r_angle.x = degree_to_radian(angle.x);
	r_angle.y = degree_to_radian(angle.y);
	r_angle.z = degree_to_radian(angle.z);
	w->mr.a = cos(r_angle.x);
	w->mr.b = sin(r_angle.x);
	w->mr.c = cos(r_angle.y);
	w->mr.d = sin(r_angle.y);
	w->mr.e = cos(r_angle.z);
	w->mr.f = sin(r_angle.z);
	w->mr.ad = w->mr.a * w->mr.d;
	w->mr.bd = w->mr.b * w->mr.d;
	def_matr(w);
	w->mr.p_r.x = p.x * (w->mr.mat[0]) + p.y * (w->mr.mat[1]) +
	p.z * (w->mr.mat[2]);
	w->mr.p_r.y = p.x * (w->mr.mat[4]) + p.y * (w->mr.mat[5]) +
	p.z * (w->mr.mat[6]);
	w->mr.p_r.z = p.x * (w->mr.mat[8]) + p.y * (w->mr.mat[9]) +
	p.z * (w->mr.mat[10]);
	return (w->mr.p_r);
}
