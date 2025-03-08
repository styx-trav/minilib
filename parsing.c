/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:34:06 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/08 21:20:24 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

static int	assign_max(t_all *str, char *value, int type)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	if (value[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (value[i] >= '0' && value[i] <= '9')
	{
		res = res * 10 + value[i] - '0';
		i++;
	}
	if (res < 0)
		return (-1);
	if (type == 4)
		str->end = sign * res;
	if (type == 5)
		str->cap = (double)(sign * res);
	return (0);
}

static int	assign_c(t_all *str, char *value, char type)
{
	double	res;

	res = get_double(value);
	if (type == 'r')
		str->c->real = res;
	else
		str->c->img = res;
	return (0);
}

static int	get_value(char *s)
{
	//if (found(s, "FRACTAL"))
		//return (1);
	if (found(s, "C_REAL"))
		return (2);
	if (found(s, "C_IM"))
		return (3);
	if (found(s, "MAX_ITER"))
		return (4);
	if (found(s, "CAP"))
		return (5);
	return (0);
}

static int	assign_var(t_all *str, int type, char *s)
{
	char	*value;

	value = get_var(s);
	if (!value)
		return (-1);
	/*if (type == 1)
	{
		if (value[0] == 'J' || value[0] == 'j')
			str->fractal = &julia;
		else if (value[0] == 'M' || value[0] == 'm')
			str->fractal = &mandel;
		else if (value[0] == 'B' || value[0] == 'b')
			str->fractal = &burning_ship;
		else
			return (-1);
	}*/
	else if (type == 2)
		return (assign_c(str, value, 'r'));
	else if (type == 3)
		return (assign_c(str, value, 'i'));
	else if (type == 4 || type == 5)
		return (assign_max(str, value, type));
	return (0);
}

int	parsing(t_all *str, int argc, char **argv)
{
	int	i;
	int	var;

	if (argc < 2)
	{
		print_parsing();
		return (-1);
	}
	i = 1;
	while (i < argc)
	{
		var = get_value(argv[i]);
		if (!var)
		{
			print_parsing();
			return (-1);
		}
		if (assign_var(str, var, argv[i]) == -1)
		{
			print_parsing();
			return (-1);
		}
		i++;
	}
	return (parsing_check(str));
}
