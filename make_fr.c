/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:07:00 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/09 16:17:34 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libby.h"

void	b_ship(t_cpx *z, t_cpx *c)
{
	if (z->real < 0)
		z->real = -z->real;
	if (z->img < 0)
		z->img = -z->img;
	julia(z, c);
}

void	mandel(t_cpx *z, t_cpx *c)
{
	julia(z, c);
}

void	julia(t_cpx *z, t_cpx *c)
{
	z = square(z);
	z = add(z, c);
}

int	is_stable(double x, double y, t_all *str)
{
	int		n;
	t_cpx	tmp;
	double	cap;

	n = 0;
	tmp.real = (x + str->center_x) * str->pixel;
	tmp.img = (-y + str->center_y) * str->pixel;
	if (str->fractal != &julia)
	{
		str->c->real = tmp.real;
		str->c->img = tmp.img;
		tmp.real = 0;
		tmp.img = 0;
	}
	cap = c_abs(&tmp) + c_abs(str->c) + 0.5;
	while (n < str->end)
	{
		if (c_abs(&tmp) > cap)
			return (n);
		str->fractal(&tmp, str->c);
		if (n > str->end / 2)
		{
			n++;
			str->fractal(&tmp, str->c);
		}
		n++;
	}
	return (-1);
}
//max end calcs incoming, checking speed first
void	make_fractal(t_all *str)
{
	int	x;
	int	y;
	int	scale;

	x = -str->hor / 2;
	while (x < str->hor - str->hor / 2)
	{
		y = -str->vert / 2;
		while (y < str->vert - str->vert / 2)
		{
			scale = is_stable((double)x, (double)y, str);
			if (scale > 0)
			{
				scale = get_color(scale);
				my_mlx_pixel_put(str, x, y, scale);
			}
			y++;
		}
		x++;
	}
}
