/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libby.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:19:28 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/05 12:20:37 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBY_H
# define LIBBY_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
//# include <stdio.h>

typedef struct  s_cpx
{
  double  real;
  double  img;
}               t_cpx;

typedef struct	s_data {
  void	*img;
  char	*addr;
  int bits_per_pixel;
  int line_length;
  int endian;
}				t_data;

typedef struct  s_all
{
  int center_x;
  int center_y;
  double  pixel;
  int vert;
  int hor;
  void  *mlx;
  void  *win;
  t_data  *current_img;
  //t_data  *new_img;
  t_cpx *c;
  double  cap;
  int end;
  void  (*fractal)(struct s_all *);
}             t_all;

/*//color utils
int get_blue(int color, int shade);
int get_green(int color, int shade);
int get_red(int color, int shade);

//for now, getting just the blue shade variations (monochromatic)
int get_color(int scale, int shade);

//hook funcs
int close(int keycode, t_vars *vars);
int exitt(t_vars *vars);

//pixel put and complex utils
void  my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_cpx *add(t_cpx *z, t_cpx *c);
t_cpx *square(t_cpx *z);
t_cpx *c_equ(t_cpx *z, t_cpx *c);
double  c_abs(t_cpx *z);

//main equation call functions (here julia/mandel)
int is_stable(t_cpx *z, t_cpx *c, int end, double cap);
int	clr_scale(double pixel, double x, double y, t_cpx *c, int end, double cap);*/

//parsing.c
int	parsing(t_all *str, int argc, char **argv);

//parsing_utils.c
int	parsing_check(t_all *str);
double	get_double(char *value);
void	print_parsing(void);
void	print(char *str);

//parsing_utils_2.c
int	found(char *str, char *find);
char	*get_var(char *s);
#endif
