#include "fdf.h"

double		degree_to_radian(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees*(pi/180);
	return (radians);
}

t_point		matrice_rotation(t_point p, t_point angle, t_dpoint r_angle)
{
	t_point p_r;
	double	A;
	double	B;
	double	C;
	double	D;
	double	E;
	double	F;
	double	AD;
	double	BD;

	// On transforme les angles en radian:
	r_angle.x = degree_to_radian(angle.x);
	r_angle.y = degree_to_radian(angle.y);
	r_angle.z = degree_to_radian(angle.z);

	A = cos(r_angle.x);
	B = sin(r_angle.x);
	C = cos(r_angle.y);
	D = sin(r_angle.y);
	E = cos(r_angle.z);
	F = sin(r_angle.z);
	AD = A * D;
	BD = B * D;

	// On crée une matrice de 16 cases:
	float mat[16];
	mat[0] = C * E;
	mat[1] = -C * F;
	mat[2] = D;
	mat[4] = BD * E + A * F;
	mat[5] = -BD * F + A * E;
	mat[6] = -B * C;
	mat[8] = -AD * E + B * F;
	mat[9] = AD * F + B * E;
	mat[10] = A * C;

	mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
	mat[15] = 1;

	// On déduit donc la position finale des points: (tel que défini ici:)
	// http://jeux.developpez.com/faq/math/?page=transformations#Q36
	p_r.x = p.x *(mat[0]) + p.y*(mat[1]) + p.z*(mat[2]);
	p_r.y = p.x *(mat[4]) + p.y*(mat[5]) + p.z*(mat[6]);
	p_r.z = p.x *(mat[8]) + p.y*(mat[9]) + p.z*(mat[10]);
	return (p_r);
}
