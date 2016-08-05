#include "fdf.h"

static double		degree_to_radian(int degrees)
{
	double	radians;
	double	pi;

	pi = 3.1415;
	radians = degrees*(pi/180);
	return (radians);
}

t_point		rotation_point(t_point A, int angle)
{
	t_point B;
	double	r_angle;
	//double»···my_cos;
	//double»···my_sin;
	//double»···result;
	//double»···x;
	/*
»···ft_putstr("Ax:");
»···ft_putnbr(A.x);
»···ft_putstr("Ay:");
»···ft_putnbr(A.y);
»···ft_putstr("Az:");
»···ft_putnbr(A.z);
»···ft_putendl("end");
»···*/
/*
 * »···x = 1.0471;
 * »···result = cos(x);
 * »···printf("cos(%.4lf) = %.2lf\n", x, result);
 * */
	r_angle = degree_to_radian(angle);
	/*
»···ft_putstr("angle:");
»···ft_putnbr(angle);
»···ft_putchar('\n');
»···ft_putstr("angle radians:");
»···printf("r_angle = %.4lf\n", r_angle);
»···my_cos = cos(r_angle);
»···my_sin = sin(r_angle);
»···printf("cos(%.4lf) = %.2lf\n", r_angle, my_sin);
»···printf("sin(%.4lf) = %.2lf\n", r_angle, my_cos);

	printf(r_angle) = %.4lf\n", A.y * sin(r_angle));
»···printf("A.z * cos(r_angle) = %.4lf\n", A.z * sin(r_angle));
»···
»···ft_putnbr(i->x_centerpoint);
»···ft_putstr("-");
»···ft_putnbr(i->y_centerpoint);
»···ft_putendl("!");
»···*/
	//B.x = ((A.x - i->x_centerpoint) * cos(r_angle)) - ((A.y - i->y_centerpoint)* sin(r_angle)); // include <math.h>
	//B.y = ((A.x - i->x_centerpoint) * sin(r_angle)) + ((A.y - i->y_centerpoint)* * cos(r_angle));
	//B.x = ((A.x) * cos(r_angle)) - ((A.y)  * sin(r_angle)); // include <math.h>
	B.x = A.x;
	B.y = ((A.y) * cos(r_angle)) - ((A.z) * sin(r_angle)); // include <math.h>
	B.z = (A.y * sin(r_angle)) + (A.z * cos(r_angle));

	// Rotation axe x:
	//B.x = A.x;
	//B.y = (A.y * cos(r_angle)) - (A.z * sin(r_angle)); // include <math.h>
	//B.z = (A.y * sin(r_angle)) + (A.z * cos(r_angle));

	// Rotation axe y:
	//B.x = (A.x * cos(r_angle)) + (A.z * sin(r_angle)); // include <math.h>
	//B.y = A.y;
	//B.z = -(A.x * sin(r_angle)) + (A.z * cos(r_angle));

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


