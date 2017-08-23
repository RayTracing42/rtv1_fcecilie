/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 00:33:40 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 16:01:45 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		matrice_x(t_space *m, double angle)
{
	point_space(m, m->x * 1 + m->y * 0 + m->z * 0,
		m->x * 0 + m->y * cos(angle) - m->z * sin(angle),
		m->x * 0 + m->y * sin(angle) + m->z * cos(angle));
	return (0);
}

int		matrice_y(t_space *m, double angle)
{
	point_space(m, m->x * cos(angle) + m->y * 0 + m->z * sin(angle),
		m->x * 0 + m->y * 1 + m->z * 0,
		-m->x * sin(angle) + m->y * 0 + m->z * cos(angle));
	return (0);
}

int		matrice_z(t_space *m, double angle)
{
	point_space(m, m->x * cos(angle) - m->y * sin(angle) + m->z * 0,
		m->x * sin(angle) + m->y * cos(angle) + m->z * 0,
		m->x * 0 + m->y * 0 + m->z * 1);
	return (0);
}

t_space	obj_rotate(t_space rot, t_space vec)
{
	t_space	angle;

	angle.x = rot.x / 180 * M_PI;
	matrice_x(&vec, angle.x);
	angle.y = rot.y / 180 * M_PI;
	matrice_y(&vec, angle.y);
	angle.z = rot.z / 180 * M_PI;
	matrice_z(&vec, angle.z);
	return (vec);
}
