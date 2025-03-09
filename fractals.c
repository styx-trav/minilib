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

int	free_str(t_all *str)
{
	if (str->img)
	{
		mlx_destroy_image(str->mlx, str->img->img);
		free(str->img);
	}
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
	str->center_x = 0;
	str->center_y = 0;
	str->vert = 800;
	str->hor = 800;
	str->pixel = 0.005;
	str->mlx = NULL;
	str->win = NULL;
	str->img = NULL;
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

	str = make_struct();
	if (!str)
		return (0);
	if (parsing(str, argc, argv) == -1)
	{
		printf("here the fractal :: ");
		if (str->fractal == &julia)
			printf("Julia\n");
		if (str->fractal == &mandel)
			printf("Mandel\n");
		if (str->fractal == &b_ship)
			printf("Burning ship\n");
		return (free_str(str));
	}
	//return (free_str(str));
	str->mlx = mlx_init();
	if (!str->mlx)
		return (free_str(str));
	str->win = mlx_new_window(str->mlx, 800, 800, "fractals");
	if (!str->win)
		return (free_str(str));
	str->img = make_img(str);
	if (!str->img)
		return (free_str(str));
	make_fractal(str);
	mlx_put_image_to_window(str->mlx, str->win, str->img->img, 0, 0);
	hooks(str);
	mlx_loop(str->mlx);
	return (free_str(str));
}
