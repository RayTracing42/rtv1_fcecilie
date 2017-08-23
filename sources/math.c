/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 23:58:33 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/09 18:36:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	delta(double a, double b, double c)
{
	double	d;
	double	r1;
	double	r2;

	d = (b * b) - (4 * a * c);
	if (d < 0)
		return (0);
	r1 = ((b * -1) + sqrt(d)) / (2 * a);
	if (d == 0)
		return (r1);
	r2 = ((b * -1) - sqrt(d)) / (2 * a);
	if (r1 < r2)
		return (r1);
	else
		return (r2);
}

t_space	vec_unit(t_space origin, t_space ending)
{
	t_space	unit;
	double	dist;

	unit.x = ending.x - origin.x;
	unit.y = ending.y - origin.y;
	unit.z = ending.z - origin.z;
	dist = sqrt((pow(unit.x, 2) + pow(unit.y, 2) + pow(unit.z, 2)));
	unit.x = unit.x / dist;
	unit.y = unit.y / dist;
	unit.z = unit.z / dist;
	return (unit);
}
