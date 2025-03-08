/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:50:39 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/08 19:00:55 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"
#include <stdio.h>

void	hooks(t_all *all)
{
	(void)all;
	//mlx_hook(all->win, 2, 1L<<0, &close, all);
	//mlx_hook(all->win, 17, 0, &exitt, all);
	//mlx_mouse_hook(all->win, &zoom_or_recenter, all);
	//mlx_loop_hook(all->win, //here if we want the looping c in julia)
}

int	free_str(t_all *str)
{
	if (str->current_img)
		mlx_destroy_image(str->mlx, str->current_img->img);
	if (str->win)
		mlx_destroy_window(str->mlx, str->win);
	if (str->mlx)
	{
		mlx_destroy_display(str->mlx);
		free(str->mlx);
	}
	free(str->c);
	free(str);
	return (0);
}

t_all	*make_struct(void)
{
	t_all	*str;

	str = (t_all *)malloc(sizeof(t_all));
	if (!str)
		return (NULL);
	str->c = (t_cpx *)malloc(sizeof(t_cpx));
	if (!str->c)
	{
		free(str);
		return (NULL);
	}
	str->c->real = -0.4;
	str->c->img = 0.6;
	str->center_x = 400;
	str->center_y = 400;
	str->vert = 800;
	str->hor = 800;
	str->pixel = 0.0025;
	str->mlx = NULL;
	str->win = NULL;
	str->current_img = NULL;
	//str->next_img = NULL;
	str->cap = 2;
	str->end = 100;
	str->fractal = NULL; //coud we put the equ function here instead of having separate functions for different fractals ?
	//feels like if done right the equ can just have the x and y and c and figure it out from there, no
	return (str);
}

int	main(int argc, char **argv)
{
	t_all	*str;
	//t_data	img;

	str = make_struct();
	if (!str)
		return (0);
	if (parsing(str, argc, argv) == -1)
		return (free_str(str));
	printf("result of parsing ::\nMAX_ITER=%d, CAP=%d, C_REAL=%.3f, C_IM=%.3f\n", str->end, (int)str->cap, str->c->real, str->c->img);
	return (free_str(str));
	/*str->mlx = mlx_init();
	if (!str->mlx)
		return (free_str(str));
	str->win = mlx_new_window(str->mlx, 800, 800, "fractals");
	if (!str->win)
		return (free_str(str));
	img.img = mlx_new_image(str->mlx, 800, 800);
	if (!img.img)
		return (free_str(str));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	str->current_img = &img;
	make_fractal(str);
	hooks(str);
	mlx_loop(str->mlx);
	return (free_str(str));*/
}
