/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:18:59 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/09 16:31:43 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

int	exitt(t_all *str)
{
	mlx_loop_end(str->mlx);
	return (0);
}

int	closer(int keycode, t_all *str)
{
	if (keycode == 0xff1b)
		mlx_loop_end(str->mlx);
	return (0);
}

int	zoom_or_recenter(int button, int x, int y, t_all *str)
{
	t_data	*img;
	t_data	*tmp;

	if (button == 0 || button == 2 || button == 3 || button > 5)
		return (0);
	str->center_x = str->center_x + x - str->hor / 2;
	str->center_y = str->center_y + str->vert / 2 - y;
	if (button == 5)
		str->pixel = str->pixel * 1.1;
	if (button == 4)
		str->pixel = str->pixel / 1.1;
	img = make_img(str);
	if (!img)
		mlx_loop_end(str->mlx);
	tmp = str->img;
	str->img = img;
	make_fractal(str);
	mlx_put_image_to_window(str->mlx, str->win, str->img->img, 0, 0);
	mlx_destroy_image(str->mlx, tmp->img);
	free(tmp);
	return (0);
}

void	hooks(t_all *all)
{
	mlx_hook(all->win, 2, 1L<<0, &closer, all);
	mlx_hook(all->win, 17, 0, &exitt, all);
	mlx_mouse_hook(all->win, &zoom_or_recenter, all);
	//mlx_loop_hook(all->win, //here if we want the looping c in julia)
}
