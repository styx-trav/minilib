/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:40:23 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/09 16:44:03 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

int	get_blue(int color, int shade)
{
	unsigned char	maker[4];

	maker[0] = ((unsigned char *)&color)[0] + shade;
	maker[1] = ((unsigned char *)&color)[1];
	maker[2] = ((unsigned char *)&color)[2];
	maker[3] = ((unsigned char *)&color)[3];
	return ((*(int *)maker));
}

int	get_green(int color, int shade)
{
	unsigned char	maker[4];

	maker[0] = ((unsigned char *)&color)[0];
	maker[1] = ((unsigned char *)&color)[1] + shade;
	maker[2] = ((unsigned char *)&color)[2];
	maker[3] = ((unsigned char *)&color)[3];
	return ((*(int *)maker));
}

int	get_red(int color, int shade)
{
	unsigned char	maker[4];

	maker[0] = ((unsigned char *)&color)[0];
	maker[1] = ((unsigned char *)&color)[1];
	maker[2] = ((unsigned char *)&color)[2] + shade;
	maker[3] = ((unsigned char *)&color)[3];
	return ((*(int *)maker));
}

int	get_color(int scale)
{
	int	color;

	color = 0x00000000;
	color = get_blue(color, scale * 5 % 255);
	color = get_green(color, scale * 2 % 255);
	color = get_red(color, scale * 3 % 255);
	return (color);
}

void	my_mlx_pixel_put(t_all *str, int x, int y, int color)
{
	char	*dst;
	t_data	*data;

	y = y + str->hor / 2;
	x = x + str->vert / 2;
	data = str->img;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
