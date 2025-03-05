/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_fractals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:57:44 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/05 12:13:03 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

double	equ(double z, double c)
{
	return (z * z + c);
}

int	is_stable(double z, double c, int end)
{
	int	n;

	n = 0;
	while (n < end)
	{
		if (fabs(z) > 2)
			return (n);
		z = equ(z, c);
		n++;
	}
	return (-1);
}

int	clr_scale(double pixel, double x, double y, double c, int end)
{
	double	z = x * pixel + y * pixel;

	return (is_stable(z, c, end));
}

int	main(void)
{
	int	x = 0;
	int	y = 0;
	double	c = -1;
	double	pixel = 0.05;
	printf("pixel size :: %.2f \n", pixel);
	while (x < 40)
	{
		y = 0;
		while (y < 40)
		{
			printf("for (x %d, y %d), scale at %d\n", x, y, clr_scale(pixel, (double)x, (double)y, c, 1000));
			y++;
		}
		x++;
	}
}
