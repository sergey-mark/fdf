#include "fdf.h"

static int			checkpoint_allside(int x, int y, t_browsefile b, t_img *i, t_wind *w)
{
	//int		z_left;
	//int		z_right;
	//int		z_up;
	int		z_down;

	//z = b.tab_int[y][x];
	//z = z*w->p.accentuation; // Ajout du parametre d'accentuationau point d'origine.
	/*
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		z_left = (b.tab_int[y][x-1]);
		color_line(i->point.z, z_left, &i->point.color);
		//ft_putnbr(z_left);
		//ft_putchar('\n');
		draw_line((i->point.x - w->p.size_square), i->point.y - (z_left*w->p.accentuation), &i, w);
	}
	if(x<(b.nbr_elem_line-1))//Si point à droite
	{
		//ft_putendl("point à droite");
		z_right = (b.tab_int[y][x+1]);
		color_line(i->point.z, z_right, &i->point.color);
		//ft_putnbr(z_right);
		//ft_putchar('\n');
		draw_line(i->point.x + w->p.size_square, i->point.y - (z_right*w->p.accentuation), &i, w);
	}
	if(y>0)//Si point au dessus
	{
		//ft_putendl("point au dessus");
		z_up = (b.tab_int[y-1][x]);
		color_line(i->point.z, z_up, &i->point.color);
		//ft_putnbr(z_up);
		//ft_putchar('\n');
		draw_line((i->point.x + w->p.size_square), (i->point.y - w->p.angle_projpara - (z_up*w->p.accentuation)), &i, w);
	}*/
	if(y<(b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		z_down = (b.tab_int[y+1][x]);
		//color_line(i->point.z, z_down, &i->point.color);
		//ft_putnbr(z_down);
		//ft_putchar('\n');
		draw_line(i->point.x - w->p.size_square, (i->point.y + w->p.angle_projpara - (z_down*w->p.accentuation)), z_down, &i, w);
	}
	return (1);
}

int			fill_3d_map(t_browsefile b, t_img *i, t_wind *w)
{
	int		y;
	int		x;
	int		z;
	int		start_x;

	ft_putendl("ok");
	i->octet_per_pixel = i->bits_per_pixel/8;
	ft_putstr("octet par pixel");
	ft_putnbr(i->octet_per_pixel);
	ft_putchar('\n');

	//*(i->pxl_ptr) = (int)"0xFFFFFF";
	//x = 0;
	//while (x < 250)
		//*(i->pxl_ptr+(x++)*(i->bits_per_pixel)) = (size_t)"0x00FFFFFF";
	//*i->pxl_ptr = (int)"0x00FFFFFF";
	i->point.x = 50;
	start_x = i->point.x;
	i->point.y = 550;
	y = b.nbr_of_line;
	y--;
	while (y >= 0)
	{
		i->point.y -= w->p.angle_projpara; // On ecarte de 25 pixels les chiffres et les lignes pour mieux voir les points ;)
		//*(i->pxl_ptr) = *(int*)"0x00FFFFFF";
		//*(i->pxl_ptr+y*(i->size_line)) = (size_t)"0x00FFFFFF";
		// Puis on décrémente pour partir du bas à gauche de l'écran pour commencer à afficher les points. (en little endian)
		start_x += w->p.size_square;
		i->point.x = start_x; //Pour créer le décalage à chaque début de ligne on met x à 25 de plus au lieu de faire partir à zéro.
		x = 0;
		while (x < b.nbr_elem_line)
		{
			z = b.tab_int[y][x];
			//i->point.z = b.tab_int[y][x];
			i->point.z = b.tab_int[y][x] * w->p.accentuation;
			ft_putnbr(z);
			ft_putchar('-');
			//color_point(z, &i->point.color);//Je colore mon point si different de zero
			//*(i->pxl_ptr+((y*w->p.size_square-(z))*(i->size_line)) + (i->point.x)*(i->bits_per_pixel)) = (int)"0x00FFFFFF";
			if (x == b.nbr_elem_line/2 && y == b.nbr_of_line/2)
			{
				i->x_centerpoint = i->point.x;
				i->y_centerpoint = i->point.y;
				ft_putstr("center point:");
				ft_putnbr(i->point.x);
				ft_putstr(":");
				ft_putnbr(i->point.y);
				ft_putchar('\n');
			}
			//i->point.y = i->point.y - i->point.z;
			/*
				ft_putstr("x:");
				ft_putnbr(i->point.x);
				ft_putstr("y:");
				ft_putnbr(i->point.y);
				ft_putstr("z:");
				ft_putnbr(i->point.z);
				ft_putchar('\n');
			*/
			/*
				ft_putstr("rotx:");
				ft_putnbr(i->r_point.x);
				ft_putstr("roty:");
				ft_putnbr(i->r_point.y);
				ft_putstr("rotz:");
				ft_putnbr(i->r_point.z);
				ft_putchar('\n');
			*/

			if (w->p.graphic_mode == 1) // Mode point
			{
				// On applique la rotation si on appui sur la flèche de haut ou bas
				i->r_point = rotation_point(i->point, w->p.rot_x);
				*((i->pxl_ptr)+((i->r_point.y - i->r_point.z)*(int)(i->size_line))+((i->r_point.x)*(i->octet_per_pixel))) = (int)"0x00FFFFFF";
			}
			else if (w->p.graphic_mode == 2) // Mode filaire
				checkpoint_allside(x, y, b, i, w);
			else if (w->p.graphic_mode == 3) // Mode rempli
				checkpoint_allside(x, y, b, i, w);
			i->point.x += w->p.size_square;
			x++;
		}
		ft_putendl("|");
		y--;
	}
	return (0);
}
