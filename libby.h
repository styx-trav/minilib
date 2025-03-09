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

typedef struct s_cpx
{
	double	real;
	double	img;
}			t_cpx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_data;

typedef struct s_all
{
	int		center_x;
	int		center_y;
	double	pixel;
	int		vert;
	int		hor;
	void	*mlx;
	void	*win;
	t_data	*img;
	t_cpx	*c;
	double	cap;
	int		end;
	void	(*fractal)(t_cpx *, t_cpx *);
}			t_all;

//colors.c
int		get_blue(int color, int shade);
int		get_green(int color, int shade);
int		get_red(int color, int shade);
int		get_color(int scale);
void	my_mlx_pixel_put(t_all *str, int x, int y, int color);

//hooks.c
void	hooks(t_all *all);
int		closer(int keycode, t_all *str);
int		exitt(t_all *str);
int		zoom_or_recenter(int button, int x, int y, t_all *str);

//utils.c
t_cpx	*add(t_cpx *z, t_cpx *c);
t_cpx	*square(t_cpx *z);
double	c_abs(t_cpx *z);
t_data	*make_img(t_all *str);

//make_fr.c
void	b_ship(t_cpx *z, t_cpx *c);
void	mandel(t_cpx *z, t_cpx *c);
void	julia(t_cpx *z, t_cpx *c);
int		is_stable(double x, double y, t_all *str);
void	make_fractal(t_all *str);

//parsing.c
int		parsing(t_all *str, int argc, char **argv);

//parsing_utils.c
int		parsing_check(t_all *str);
double	get_double(char *value);
void	print_parsing(void);
void	print(char *str);

//parsing_utils_2.c
int		found(char *str, char *find);
char	*get_var(char *s);
#endif
