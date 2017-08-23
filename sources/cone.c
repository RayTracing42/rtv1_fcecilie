/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:13:51 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 15:40:11 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	del[4] = rayon;
**	del[0] = a;
**	del[1] = b;
**	del[2] = c;
**	del[3] = delta de l'ensemble;
*/

double	cone(t_rt *r, t_space dir)
{
	double	del[5];
	t_space	rotated_cam;
	t_space	rotated_dir;
	t_space	rotated_obj;

	rotated_cam = obj_rotate(r->obj->rotation, r->cam_pos);
	rotated_dir = obj_rotate(r->obj->rotation, dir);
	rotated_obj = obj_rotate(r->obj->rotation, r->obj->origin);
	del[4] = (M_PI / 2) - (r->obj->ray * M_PI / 180);
	del[0] = pow(tan(del[4]), 2) * (pow(rotated_dir.x, 2) +
			pow(rotated_dir.z, 2)) - pow(rotated_dir.y, 2);
	del[1] = pow(tan(del[4]), 2) * (2 * (rotated_cam.x - rotated_obj.x) *
			rotated_dir.x + 2 * (rotated_cam.z - rotated_obj.z) * rotated_dir.z)
			- (2 * (rotated_cam.y - rotated_obj.y) * rotated_dir.y);
	del[2] = pow(tan(del[4]), 2) * (pow(rotated_cam.x - rotated_obj.x, 2)
			+ pow(rotated_cam.z - rotated_obj.z, 2)) - pow(rotated_cam.y
			- rotated_obj.y, 2);
	if ((del[3] = delta(del[0], del[1], del[2])))
		point_space(&r->point, r->cam_pos.x + dir.x * del[3],
				r->cam_pos.y + dir.y * del[3], r->cam_pos.z + dir.z * del[3]);
	if (del[3])
		point_space(&r->rotated_point, rotated_cam.x + rotated_dir.x * del[3],
				rotated_cam.y + rotated_dir.y * del[3],
				rotated_cam.z + rotated_dir.z * del[3]);
	return (del[3]);
}

double	cone_lux(t_rt *r, t_space dir)
{
	double	del[4];
	double	ray;
	t_space	rotated_pnt;
	t_space	rotated_dir;
	t_space	rotated_obj;

	rotated_pnt = obj_rotate(r->obj->rotation, r->point);
	rotated_obj = obj_rotate(r->obj->rotation, r->obj->origin);
	rotated_dir = obj_rotate(r->obj->rotation, dir);
	ray = (M_PI / 2) - (r->obj->ray * M_PI / 180);
	del[0] = pow(tan(ray), 2) * (pow(rotated_dir.x, 2) +
			pow(rotated_dir.z, 2)) - pow(rotated_dir.y, 2);
	del[1] = pow(tan(ray), 2) * (2 * (rotated_pnt.x - rotated_obj.x) *
			rotated_dir.x + 2 * (rotated_pnt.z - rotated_obj.z) * rotated_dir.z)
			- (2 * (rotated_pnt.y - rotated_obj.y) * rotated_dir.y);
	del[2] = pow(tan(ray), 2) * (pow(rotated_pnt.x - rotated_obj.x, 2)
			+ pow(rotated_pnt.z - rotated_obj.z, 2)) - pow(rotated_pnt.y
			- rotated_obj.y, 2);
	return (del[3] = delta(del[0], del[1], del[2]));
}

int		cone_vector(t_rt *r, t_space *vector)
{
	t_space	rotated_obj;
	t_space axe_1;
	t_space axe_2;
	double	dist_1;
	double	dist_2;

	rotated_obj = obj_rotate(r->obj->rotation, r->obj->origin);
	dist_1 = sqrt(pow(r->rotated_point.x - rotated_obj.x, 2) +
			pow(r->rotated_point.y - rotated_obj.y, 2) +
			pow(r->rotated_point.z - rotated_obj.z, 2));
	dist_2 = dist_1 * 1 / cos((r->obj->ray / 2) * M_PI / 180);
	point_space(&axe_1, rotated_obj.x, rotated_obj.y + dist_2, rotated_obj.z);
	point_space(&axe_2, rotated_obj.x, rotated_obj.y - dist_2, rotated_obj.z);
	dist_1 = sqrt(pow(r->rotated_point.x - axe_1.x, 2) + pow(r->rotated_point.y
			- axe_1.y, 2) + pow(r->rotated_point.z - axe_1.z, 2));
	dist_2 = sqrt(pow(r->rotated_point.x - axe_2.x, 2) + pow(r->rotated_point.y
			- axe_2.y, 2) + pow(r->rotated_point.z - axe_2.z, 2));
	if (dist_1 < dist_2)
		*vector = vec_unit(axe_1, r->rotated_point);
	else
		*vector = vec_unit(axe_2, r->rotated_point);
	return (0);
}
