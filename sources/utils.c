/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 01:55:17 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/09 17:25:45 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		point_space(t_space *n, double x, double y, double z)
{
	if (n != NULL)
	{
		n->x = x;
		n->y = y;
		n->z = z;
	}
	else
		return (-2);
	return (0);
}

int		catch_value(char *str, int nb)
{
	int		n;
	int		d;
	int		res;

	n = 0;
	d = 0;
	res = 0;
	while (str && str[n])
	{
		if (ft_isdigit(str[n]) || (str[n] == '-' && str[n + 1] >= '0'
					&& str[n + 1] <= '9'))
		{
			d++;
			if (d == nb)
				res = ft_atoi(&str[n]);
			while (str[n] && ft_strchr("-0123456789", str[n]))
				n++;
		}
		else
			n++;
		if (d == nb)
			return (res);
	}
	return (0);
}

int		get_t_space(char *interval, t_space *space, char *start)
{
	char	*tmp;

	tmp = NULL;
	if (get_string_interval(interval, start, ')', &tmp) == -1)
	{
		ft_putendl("Error : get_string_interval() failed");
		return (-1);
	}
	space->x = catch_value(tmp, 1);
	space->y = catch_value(tmp, 2);
	space->z = catch_value(tmp, 3);
	ft_memdel((void**)&tmp);
	return (0);
}
