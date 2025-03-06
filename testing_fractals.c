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
#include <mlx.h>
#include <stdlib.h>

typedef struct	s_data {
  void	*img;
  char	*addr;
  int bits_per_pixel;
  int line_length;
  int endian;
}				t_data;

typedef struct  s_vars {
  void *mlx;
  void *win;
}               t_vars;

int close(int keycode, t_vars *vars)
{
  if (keycode == 0xff1b)
  {
    mlx_loop_end(vars->mlx);
  }
  return (0);
}

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char	*dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}

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

void  make_fractal(t_data *data)
{
	int	x = 0;
	int	y = 0;
	double	c = -0.08;
	double	pixel = 0.0025;
	int scale;
	printf("pixel size :: %.4f \n", pixel);
	while (x < 800)
	{
		y = 0;
		while (y < 800)
		{
		        if (fabs((double)x * pixel + (double)y * pixel) >= 2)
		          break ;
		        scale = clr_scale(pixel, (double)x, (double)y, c, 300);
			if (scale != -1)
			{
			  if (scale == 0)
			    scale = 0x00FFFFFF;
			  else if (scale == 1)
			    scale = 0x00FF0000;
			  else if (scale == 2)
			    scale = 0x0000FF00;
			  else if (scale == 3)
			    scale = 0x000000FF;
			  else if (scale > 3)
			    scale = 0x00FF00FF;
			  my_mlx_pixel_put(data, x, y, scale);
			}
			y++;
		}
		x++;
	}
}

int main(void)
{
  void  *mlx;
  t_data  img;
  void  *mlx_win;
  t_vars  vars;

  mlx = mlx_init();
  if (!mlx)
    return (0);
  mlx_win = mlx_new_window(mlx, 800, 800, "fractals");
  if (!mlx_win)
  {
    free(mlx);
    return (0);
  }
  vars.mlx = mlx;
  vars.win = mlx_win;
  img.img = mlx_new_image(mlx, 800, 800);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  make_fractal(&img);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_hook(vars.win, 2, 1L<<0, &close, &vars);
  mlx_loop(mlx);
  mlx_destroy_image(mlx, img.img);
  mlx_destroy_window(mlx, mlx_win);
  mlx_destroy_display(mlx);
  free(mlx);
}

//okay, was a little confused with the results here but they're 100% caused by the lack of imaginary values. This isn't a correct representation of the axes, because y is real and therefore all of these values should be viewed as just the one x axis :: hence it being so straight and straightforward. we'll have to decide if we want to make our own complex nums (using an easy double struct {double real; double img;}) and funcs (looking at you, equ(z, c))

//rn i'll get on the complex numbers thing
