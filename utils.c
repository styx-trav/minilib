/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:34:51 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/09 16:34:53 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

t_cpx	*add(t_cpx *z, t_cpx *c)
{
	z->real = z->real + c->real;
	z->img = z->img + c->img;
	return (z);
}

t_cpx	*square(t_cpx *z)
{
	double	a;
	double	b;

	a = z->real;
	b = z->img;
	z->real = a * a - b * b;
	z->img = 2 * a * b;
	return (z);
}

double	c_abs(t_cpx *z)
{
	double	res;

	res = z->real * z->real + z->img * z->img;
	res = sqrt(res);
	return (res);
}

t_data	*make_img(t_all *str)
{
	t_data	*img;

	img = (t_data *)malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(str->mlx, str->hor, str->vert);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	return (img);
}
