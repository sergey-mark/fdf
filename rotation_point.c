#include "fdf.h"

static double		degree_to_radian(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees*(pi/180);
	return (radians);
}

t_point		rotation_point(t_point A, t_point angle, t_dpoint r_angle)
{
	t_point B;


	// Rotation axe x:
	r_angle.x = degree_to_radian(angle.x);
	B.x = A.x;
	B.y = ((A.y) * cos(r_angle.x)) - ((A.z) * sin(r_angle.x)); // include <math.h>
	B.z = (A.y * sin(r_angle.x)) + (A.z * cos(r_angle.x));

	// Rotation axe y:
	/*
	r_angle.y = degree_to_radian(angle.y);
	B.x = ((A.x) * cos(r_angle.y) - A.z * sin(r_angle.y)); // include <math.h>
	B.y = A.y;
	B.z = (A.x * sin(r_angle.y)) + (A.z * cos(r_angle.y));
	*/
	// Rotation axe z:
	//B.x = (A.x * cos(r_angle)) - (A.y * sin(r_angle)); // include <math.h>
	//B.y = (A.x * sin(r_angle)) + (A.y * cos(r_angle));
	//B.z = A.z;
	/*
	ft_putstr("Bx:");
	ft_putnbr(B.x);
	ft_putstr("By:");
	ft_putnbr(B.y);
»···ft_putstr("Bz:");
»···ft_putnbr(B.z);
»···ft_putendl("end");*/
	return (B);
}


