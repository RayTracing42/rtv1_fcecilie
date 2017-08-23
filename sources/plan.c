/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:05:26 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 15:04:12 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	plan(t_rt *r, t_space dir)
{
	double	d;

	d = -1 * ((r->obj->rotation.x * (r->cam_pos.x - r->obj->origin.x) +
				r->obj->rotation.y * (r->cam_pos.y - r->obj->origin.y) +
				r->obj->rotation.z * (r->cam_pos.z - r->obj->origin.z) + 0) /
			(r->obj->rotation.x * dir.x + r->obj->rotation.y * dir.y +
			r->obj->rotation.z * dir.z));
	if (d)
	{
		point_space(&r->point, r->cam_pos.x + dir.x * d,
				r->cam_pos.y + dir.y * d, r->cam_pos.z + dir.z * d);
		r->rotated_point = r->point;
	}
	return (d);
}

double	plan_lux(t_rt *r, t_space dir)
{
	double	d;

	d = -1 * ((r->obj->rotation.x * (r->point.x - r->obj->origin.x) +
				r->obj->rotation.y * (r->point.y - r->obj->origin.y) +
				r->obj->rotation.z * (r->point.z - r->obj->origin.z) + 0) /
			(r->obj->rotation.x * dir.x + r->obj->rotation.y * dir.y +
			r->obj->rotation.z * dir.z));
	return (d);
}

int		plan_vector(t_rt *r, t_space *vector)
{
	t_space vector_tmp_1;
	t_space vector_tmp_2;
	double	dist_1;
	double	dist_2;

	point_space(&vector_tmp_1, r->rotated_point.x + r->obj->rotation.x,
			r->rotated_point.y + r->obj->rotation.y,
			r->rotated_point.z + r->obj->rotation.z);
	point_space(&vector_tmp_2, r->rotated_point.x - r->obj->rotation.x,
			r->rotated_point.y - r->obj->rotation.y,
			r->rotated_point.z - r->obj->rotation.z);
	dist_1 = sqrt(pow(r->lux->origin.x - vector_tmp_1.x, 2) +
			pow(r->lux->origin.y - vector_tmp_1.y, 2) +
			pow(r->lux->origin.z - vector_tmp_1.z, 2));
	dist_2 = sqrt(pow(r->lux->origin.x - vector_tmp_2.x, 2) +
			pow(r->lux->origin.y - vector_tmp_2.y, 2) +
			pow(r->lux->origin.z - vector_tmp_2.z, 2));
	if (dist_1 < dist_2)
		*vector = vec_unit(r->rotated_point, vector_tmp_1);
	else
		*vector = vec_unit(r->rotated_point, vector_tmp_2);
	return (0);
}
