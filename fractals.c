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

void	hooks(t_all *all)
{
	mlx_hook(all->win, 2, 1L<<0, &close, all);
	mlx_hook(all->win, 17, 0, &exitt, all);
	//mlx_mouse_hook(all->win, &zoom_or_recenter, all);
	//mlx_loop_hook(all->win, //here if we want the looping c in julia)
}

t_all	*make_struct()
{
	t_all	*str;

	str = (t_all *)malloc(sizeof(t_all));
	if (!str)
		return (NULL);
	str->center_x = 400;
	str->center_y = 400;
	str->vert = 800;
	str->hor = 800;
	str->pixel = 0.0025;
	str->mlx = NULL;
	str->win = NULL;
	str->current_img = NULL;
	//str->next_img = NULL;
	str->c = NULL;
	str->cap = 2;
	str->end = 100;
	str->fractal = NULL;
	return (str);
}


