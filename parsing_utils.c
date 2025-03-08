/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:30:01 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/08 21:30:04 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

void	print(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	print_parsing(void)
{
	print("Hi ! Looks like there was an issue with your parameters.\n\n");
	print("These are the options available to you ::\n\n");
	print("-- FRACTAL=J/j/M/m/B/b, for Julia/Mandelbrot/Burning ship;\n");
	print("-- C_REAL=double(.), for the real value of c;\n");
	print("-- C_IM=double(.), for the imaginary value of c;\n");
	print("-- MAX_ITER=int, for the max amount of iterations at each coord;\n");
	print("-- CAP=int, for the accuracy of the result;\n");
	print("\nPlease try again !\n");
}

static double	find_float(char *value, int i, double res, double sign)
{
	double	tmp;

	tmp = res;
	while (i != 0 && value[i - 1] != '.')
	{
		tmp = tmp * 0.1;
		i--;
	}
	if (i != -1)
		res = tmp;
	return (res * sign);
}

double	get_double(char *value)
{
	double	res;
	double	sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (value[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((value[i] >= '0' && value[i] <= '9') || value[i] == '.')
	{
		if (value[i] != '.')
			res = res * 10 + value[i] - '0';
		i++;
	}
	res = find_float(value, i, res, sign);
	return (res);
}

int	parsing_check(t_all *str)
{
	(void)str;
	//if (!str->fractal)
		//return (-1);
	return (0);
}
