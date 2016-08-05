#include "fdf.h"

static void		color_point(int num, size_t *color)
  {
    if(num == 10)//Je colore mon point si different de zero
		*color = 0x00FF00FF;
	else
		*color = 0x00FFFFFF;
}

void			color_line(int num1, int num2, size_t *color)
{
	size_t white;
	size_t purple;

	white = 0x00FFFFFF;
	purple = 0x00FF00FF;
	if (num1 == 10 && num2 == 10)
		*color = purple;
	else
		*color = white;
}
