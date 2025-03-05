/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_cmplx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:13:19 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/05 12:13:20 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

double complex	equ(double complex z, double complex c)
{
	return (z * z + c);
}

int	is_stable(double complex z, double complex c, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (cabs(z) > 2)
			return (i);
		z = equ(z, c);
		i++;
	}
	return (-1);
}

int	clr_scale(double pixel, double x, double y, double complex c, int end)
{
	int	scale;
	double complex	z;

	z = CMPLX(pixel * x, pixel * y);
	scale = is_stable(z, c, end);
	return (scale);
}

int	clr(int scale, int end)
{
	//here the color work to see where we end up on the color sliding scale :: choose the order of the colors, and with end, how fast they shift;;
	return (1);
}
