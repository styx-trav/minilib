#include <math.h>
#include <mlx.h>
#include <stdlib.h>

typedef struct s_cpx
{
  double real;
  double  img;
}               t_cpx;

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

t_cpx *add(t_cpx *z, t_cpx *c)
{
  z->real = z->real + c->real;
  z->img = z->img + c->img;
  return (z);
}

t_cpx *square(t_cpx *z)
{
  double  a = z->real;
  double  b = z->img;
  z->real = a * a - b * b;
  z->img = 2 * a * b;
  return (z);
}

t_cpx *c_equ(t_cpx *z, t_cpx *c)
{
  z = square(z);
  z = add(z, c);
  return (z);
}

double  c_abs(t_cpx *z)
{
  double  res = z->real * z->real + z->img * z->img;
  res = sqrt(res);
  return (res);
}

int is_stable(t_cpx *z, t_cpx *c, int end, double cap)
{
  int n = 0;
  
  while (n < end)
  {
    if (c_abs(z) > cap)
      return (n);
    z = c_equ(z, c);
    n++;
  }
  return (-1);
}

int	clr_scale(double pixel, double x, double y, t_cpx *c, int end, double cap)
{
	t_cpx	z;
	z.real = x * pixel;
	z.img = y * pixel;

	return (is_stable(&z, c, end, cap));
}

int get_blue(int color, int shade)
{
  unsigned char maker[4];
  
  maker[0] = ((unsigned char *)&color)[0] + shade;
  maker[1] = ((unsigned char *)&color)[1];
  maker[2] = ((unsigned char *)&color)[2];
  maker[3] = ((unsigned char *)&color)[3];
  return ((*(int *)maker));
}

int get_color(int scale, int shade)
{
  int color = 0x00000000;

  shade = 255 / shade;
  shade = shade * scale;
  color = get_blue(color, shade);
  return (color);
}
  
#include <stdio.h>
void  make_fractal(int hor, int vert, int end, double cap, t_data *img)
{
  int x = - (hor / 2);
  int y;
  double pixel = 0.005;
  int scale;
  t_cpx c;
  c.real = -0.4;
  c.img = 0.6;
  int max_scale = -1;

  while (x < hor - hor / 2)
  {
    y = -vert / 2;
    while (y < vert - vert / 2)
    {
      scale = clr_scale(pixel, (double)x, (double)y, &c, end, cap);
      if (scale > max_scale)
        max_scale = scale;
      if (scale != -1 && scale != 0)
      {
        if (scale == 0)
          scale = 0x00FFFFFF;
        else
          scale = get_color(scale, 255);
        my_mlx_pixel_put(img, x + hor / 2, y + vert / 2, scale);
      }
      y++;
    }
    x++;
  }
  printf("max_scale :: %d\n", max_scale);
}

int main(void)
{
  void  *mlx = NULL;
  t_data  img;
  void  *mlx_win = NULL;
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
  make_fractal(800, 800, 255, 2, &img);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_hook(vars.win, 2, 1L<<0, &close, &vars);
  mlx_hook(vars.win, 17, 0, &close, &vars);
  mlx_loop(mlx);
  mlx_destroy_image(mlx, img.img);
  mlx_destroy_window(mlx, mlx_win);
  mlx_destroy_display(mlx);
  free(mlx);
}

//was confused for a second but it actually looks really really promising !! still need to adjust the colors a little and play around with it, but i'm actuall really pleased :]
