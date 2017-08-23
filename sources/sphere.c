/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:13:37 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/14 17:54:50 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	sphere(t_rt *r, t_space dir)
{
	double a;
	double b;
	double c;
	double d;

	a = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
	b = 2 * (dir.x * (r->cam_pos.x - r->obj->origin.x) +
			dir.y * (r->cam_pos.y - r->obj->origin.y) +
			dir.z * (r->cam_pos.z - r->obj->origin.z));
	c = (pow(r->cam_pos.x - r->obj->origin.x, 2) +
			pow(r->cam_pos.y - r->obj->origin.y, 2) +
			pow(r->cam_pos.z - r->obj->origin.z, 2)) - pow(r->obj->ray, 2);
	d = delta(a, b, c);
	if (d)
	{
		point_space(&r->point, r->cam_pos.x + dir.x * d,
				r->cam_pos.y + dir.y * d, r->cam_pos.z + dir.z * d);
		r->rotated_point = r->point;
	}
	return (d);
}

double	sphere_lux(t_rt *r, t_space dir)
{
	double a;
	double b;
	double c;
	double d;

	a = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
	b = 2 * (dir.x * (r->point.x - r->obj->origin.x) +
			dir.y * (r->point.y - r->obj->origin.y) +
			dir.z * (r->point.z - r->obj->origin.z));
	c = (pow(r->point.x - r->obj->origin.x, 2) +
			pow(r->point.y - r->obj->origin.y, 2) +
			pow(r->point.z - r->obj->origin.z, 2)) - pow(r->obj->ray, 2);
	d = delta(a, b, c);
	return (d);
}

int		sphere_vector(t_rt *r, t_space *vector)
{
	*vector = vec_unit(r->obj->origin, r->rotated_point);
	return (0);
}
