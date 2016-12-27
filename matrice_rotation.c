/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:31:20 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 15:31:24 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	w->mr.mat[0] = w->mr.C * w->mr.E;
	w->mr.mat[1] = -(w->mr.C) * w->mr.F;
	w->mr.mat[2] = w->mr.D;
	w->mr.mat[4] = w->mr.BD * w->mr.E + w->mr.A * w->mr.F;
	w->mr.mat[5] = -(w->mr.BD) * w->mr.F + w->mr.A * w->mr.E;
	w->mr.mat[6] = -(w->mr.B) * w->mr.C;
	w->mr.mat[8] = -(w->mr.AD) * w->mr.E + w->mr.B * w->mr.F;
	w->mr.mat[9] = w->mr.AD * w->mr.F + w->mr.B * w->mr.E;
	w->mr.mat[10] = w->mr.A * w->mr.C;
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
	w->mr.A = cos(r_angle.x);
	w->mr.B = sin(r_angle.x);
	w->mr.C = cos(r_angle.y);
	w->mr.D = sin(r_angle.y);
	w->mr.E = cos(r_angle.z);
	w->mr.F = sin(r_angle.z);
	w->mr.AD = w->mr.A * w->mr.D;
	w->mr.BD = w->mr.B * w->mr.D;
	def_matr(w);
	w->mr.p_r.x = p.x * (w->mr.mat[0]) + p.y * (w->mr.mat[1]) +
	p.z * (w->mr.mat[2]);
	w->mr.p_r.y = p.x * (w->mr.mat[4]) + p.y * (w->mr.mat[5]) +
	p.z * (w->mr.mat[6]);
	w->mr.p_r.z = p.x * (w->mr.mat[8]) + p.y * (w->mr.mat[9]) +
	p.z * (w->mr.mat[10]);
	return (w->mr.p_r);
}
