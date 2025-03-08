/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:58:08 by naorakot          #+#    #+#             */
/*   Updated: 2025/03/08 22:01:09 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libby.h"

int	found(char *str, char *find)
{
	int	i;

	i = 0;
	while (find[i] && str[i] == find[i])
		i++;
	if (!find[i])
		return (1);
	return (0);
}

char	*get_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (NULL);
	return (&s[i + 1]);
}
