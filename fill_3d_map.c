#include "fdf.h"

static t_point		get_iso_point(int x, int y, t_wind *w)
{
	t_point p;
	p.x = (x - y) * (w->p.size_square/2) + w->img.start_x;
	p.y = (x + y) * (w->p.angle_projpara/2) + w->img.start_y;
	p.z = w->b.tab_int[y][x] * (w->p.accentuation);
	return (p);
}

static int			checkpoint_allside_iso(int x, int y, t_wind *w)
{
	if(x>0)//Si point à gauche
	{
		//ft_putendl("gauche");
		w->img.pointd = get_iso_point(x-1, y, w);
		draw_line(w, w->img.point, w->img.pointd);
	}/*
	if(x<(w->b.nbr_elem_line-1))//Si point à droite
	{
		ft_putendl("droite");
		w->img.pointd = get_iso_point(x+1, y, w);
		draw_line(w);

	}
	if(y>0)//Si point au dessus
	{
		ft_putendl("haut");
		w->img.pointd = get_iso_point(x, y-1, w);
		draw_line(w);

	}*/
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("bas");
		w->img.pointd = get_iso_point(x, (y+1), w);
		draw_line(w, w->img.point, w->img.pointd);
	}
	if (w->p.graphic_mode == 3)
	{
		if(x<(w->b.nbr_elem_line-1) && y<(w->b.nbr_of_line-1))//Si point en diagonale
		{
			w->img.pointd = get_iso_point(x+1, y+1, w);
			draw_line(w, w->img.point, w->img.pointd);
		}
	}
	return (0);
}

static int			checkpoint_allside(int x, int y, t_wind *w)
{
	//int		z_left;
	//int		z_right;
	//int		z_up;
	//int		z_down;

	//z = b.tab_int[y][x];
	//z = z*w->p.accentuation; // Ajout du parametre d'accentuationau point d'origine.
	if(x>0)//Si point à gauche
	{
		//ft_putendl("point à gauche");
		w->img.pointd.z = (w->b.tab_int[y][x-1])*(w->p.accentuation);
		//color_line(i->point.z, z_left, &i->point.color);
		//ft_putnbr(z_left);
		//w->img.pointd = get_par_point(x-1, y, w);
		w->img.pointd.x = w->img.point.x - w->p.size_square;
		w->img.pointd.y = w->img.point.y;
		//ft_putchar('\n');
		//ft_putstr("test");
		draw_line(w, w->img.point, w->img.pointd);
		//ft_putstr("test2");
	}/*
	if(x<(b.nbr_elem_line-1))//Si point à droite
	{
		//ft_putendl("point à droite");
		z_right = (b.tab_int[y][x+1]);
		//color_line(i->point.z, z_right, &i->point.color);
		//ft_putnbr(z_right);
		//ft_putchar('\n');
		draw_line(i->point.x + w->p.size_square, i->point.y - (z_right*w->p.accentuation), &i, w);
	}
	if(y>0)//Si point au dessus
	{
		//ft_putendl("point au dessus");
		z_up = (b.tab_int[y-1][x]);
		//color_line(i->point.z, z_up, &i->point.color);
		//ft_putnbr(z_up);
		//ft_putchar('\n');
		draw_line((i->point.x + w->p.size_square), (i->point.y - w->p.angle_projpara - (z_up*w->p.accentuation)), &i, w);
	}*/
	if(y<(w->b.nbr_of_line-1))//Si point en dessous
	{
		//ft_putendl("point au dessous");
		w->img.pointd.z = (w->b.tab_int[y+1][x])*(w->p.accentuation);
		//color_line(i->point.z, z_down, &i->point.color);
		//ft_putnbr(z_down);
		//ft_putchar('\n');
		w->img.pointd.x = w->img.point.x - w->p.size_square;
		w->img.pointd.y = w->img.point.y + w->p.angle_projpara;
		//w->img.pointd = get_par_point(x, y+1, w);
		//ft_putstr("test");
		draw_line(w, w->img.point, w->img.pointd);
		//ft_putstr("testb");
		//draw_line(i->point.x - w->p.size_square, (i->point.y + w->p.angle_projpara - (z_down*w->p.accentuation)), &i, w);
	}
	return (0);
}

static int			triangulate_para(int x, int y, t_wind *w)
{
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		w->img.pointd.z = (w->b.tab_int[y+1][x+1])*(w->p.accentuation);
		w->img.pointd.x = w->img.point.x; // les sizesquare s'annule.
		w->img.pointd.y = w->img.point.y + w->p.angle_projpara;// Pour afficher remplir toutes les lignes en dessous 
		// TRIANGULATE
		draw_line(w, w->img.point, w->img.pointd);
	}
	return (0);
}

static int			fill_para(int x, int y, t_wind *w)
{
	t_point			point;
	t_point			pointright;
	t_point			pointdown;
	t_point			pointddiag;
	
	if ((x<(w->b.nbr_elem_line-1)) && (y<(w->b.nbr_of_line-1)) && (x<(w->b.nbr_elem_line-1) && (y<(w->b.nbr_of_line-1)))) //Si point à droit et en dessous et en diagonale à droite
	{
		point = w->img.point;

		// Point à droite:
		pointright.z = (w->b.tab_int[y][x+1])*(w->p.accentuation);
		pointright.x = w->img.point.x + w->p.size_square;
		pointright.y = w->img.point.y;

		// Point en dessous:
		pointdown.z = (w->b.tab_int[y+1][x])*(w->p.accentuation);
		pointdown.x = w->img.point.x - w->p.size_square;
		pointdown.y = w->img.point.y + w->p.angle_projpara;
		
		// Point en diagonale:
		pointddiag.z = (w->b.tab_int[y+1][x+1])*(w->p.accentuation);
		pointddiag.x = w->img.point.x;
		pointddiag.y = w->img.point.y + w->p.angle_projpara;// Pour afficher remplir toutes les lignes en dessous
		while (((point.y-point.z) < (pointdown.y-pointdown.z)) || ((pointright.y-pointright.z) < (pointddiag.y-pointddiag.z)))
		{
			if ((point.y-point.z) < (pointdown.y-pointdown.z))
			{
				point.x--;
				point.y++;
			}
			if ((pointright.y-pointright.z) < (pointddiag.y-pointddiag.z))
			{
				pointright.y++;
				pointright.x--;
			}
			draw_line(w, point, pointright);
		}
	}
	return (0);
}

int			fill_3d_map_iso(t_wind *w)
{
	int		y;
	int		x;
	int		color;

	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	w->img.start_x = 500; //pour centrer l'iso au milieu
	w->img.start_y = 50; //pour centrer l'iso au milieu
	w->img.point.x = 0;
	w->img.point.y = 0;
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		while (x < w->b.nbr_elem_line)
		{
			w->img.point = get_iso_point(x, y, w);
			if (w->p.graphic_mode == 1)//Mode point
			{
				color = (int)"0x00FFFFFF";
				//color = (x*255)/w->b.nbr_elem_line+(((w->b.nbr_elem_line-x)*255/w->b.nbr_elem_line)<<16)+(((y*255)/w->b.nbr_of_line)<<8);
				//*((w->img.pxl_ptr)+((w->img.point.y - w->img.point.z)*(int)(w->img.size_line))+((w->img.point.x)*(w->img.octet_per_pixel))+x) = (unsigned char *)(&color)[3-x];
				*((w->img.pxl_ptr)+((w->img.point.y - w->img.point.z)*(int)(w->img.size_line))+((w->img.point.x)*(w->img.octet_per_pixel))+x) = (int)color;
			}
			else
				checkpoint_allside_iso(x, y, w);
			x++;
		}
		y++;
	}
	return (0);
}

int			fill_3d_map(t_wind *w)
{
	int		y;
	int		x;
	int		z;
	double	start_x;
	//double	diag;

	ft_putendl("ok");
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	ft_putstr("octet par pixel");
	ft_putnbr(w->img.octet_per_pixel);
	ft_putchar('\n');

	//ft_putnbr(mode);
	//while (x < 250)
		// *(i->pxl_ptr+(x++)*(i->bits_per_pixel)) = (size_t)"0x00FFFFFF";
	w->img.point.x = 0;
	//diag = pythagor((double)w->p.size_square, (double)w->p.angle_projpara);
	//printf("%.2f", diag);
	//start_x = w->b.nbr_elem_line*diag;
	start_x = (w->b.nbr_elem_line-5)*(w->p.size_square); //Centrage de la piece peut etre mieux calculé (car en digonale)
	//start_x = 0;
	w->img.point.y = 0;
	y = 0;
	while (y < w->b.nbr_of_line)
	{
		x = 0;
		w->img.point.y += w->p.angle_projpara; // On ecarte de 25 pixels les chiffres et les lignes pour mieux voir les points ;)
		// Puis on décrémente pour partir du bas à gauche de l'écran pour commencer à afficher les points. (en little endian)
		start_x -= w->p.size_square;
		w->img.point.x = start_x; //Pour créer le décalage à chaque début de ligne on met x à 25 de plus au lieu de faire partir à zéro.
		while (x < w->b.nbr_elem_line)
		{
			z = w->b.tab_int[y][x];
			w->img.point.z = (w->b.tab_int[y][x])*(w->p.accentuation);
			//i->point.z = b.tab_int[y][x] * w->p.accentuation;
			ft_putnbr(z);
			ft_putchar('-');
			//color_point(z, &i->point.color);//Je colore mon point si different de zero
			// *(i->pxl_ptr+((y*w->p.size_square-(z))*(i->size_line)) + (i->point.x)*(i->bits_per_pixel)) = (int)"0x00FFFFFF";
			if (x == w->b.nbr_elem_line/2 && y == w->b.nbr_of_line/2)
			{
				w->img.x_centerpoint = w->img.point.x;
				w->img.y_centerpoint = w->img.point.y;
				ft_putstr("center point:");
				ft_putnbr(w->img.point.x);
				ft_putstr(":");
				ft_putnbr(w->img.point.y);
				ft_putchar('\n');
			}
			//i->point.y = i->point.y - i->point.z;
			if (w->p.graphic_mode == 1) // Mode point
			{
				w->img.r_point = rotation_point(w->img.point, w->p.rot, w->p.r_rot);
				/*
				ft_putstr("rotx:");
				ft_putnbr(w->img.r_point.x);
				ft_putstr("roty:");
				ft_putnbr(w->img.r_point.y);
				ft_putstr("rotz:");
				ft_putnbr(w->img.r_point.z);
				ft_putchar('\n');
				*/
	// On applique la rotation si on appui sur la flèche de haut ou bas
				*((w->img.pxl_ptr)+((w->img.r_point.y - w->img.r_point.z)*(int)(w->img.size_line))+((w->img.r_point.x)*(w->img.octet_per_pixel))) = (int)"0x00FFFFFF";
				//*((w->img.pxl_ptr)+((w->img.r_point.y - w->img.r_point.z)*(int)(w->img.size_line))+((w->img.r_point.x)*(w->img.octet_per_pixel))) = (int)"0x00FFFFFF";
			}
			else // Mode filaire && Triangulate && fill
			{
				//if (w->p.graphic_mode == 2)
				checkpoint_allside(x, y, w);
				if (w->p.graphic_mode == 3)
					triangulate_para(x, y, w);
				if (w->p.graphic_mode == 4)
					fill_para(x, y, w);
			}
			w->img.point.x += w->p.size_square;
			x++;
		}
		ft_putendl("|");
		y++;
	}
	return (0);
}
