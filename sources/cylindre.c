/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:14:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 14:49:08 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cylindre(t_rt *r, t_space dir)
{
	double	del[4];
	t_space	rotated_cam;
	t_space	rotated_dir;
	t_space	rotated_obj;

	rotated_dir = obj_rotate(r->obj->rotation, dir);
	rotated_cam = obj_rotate(r->obj->rotation, r->cam_pos);
	rotated_obj = obj_rotate(r->obj->rotation, r->obj->origin);
	del[0] = pow(rotated_dir.x, 2) + pow(rotated_dir.z, 2);
	del[1] = 2 * (rotated_dir.x * (rotated_cam.x - rotated_obj.x) +
			rotated_dir.z * (rotated_cam.z - rotated_obj.z));
	del[2] = (pow(rotated_cam.x - rotated_obj.x, 2) +
			pow(rotated_cam.z - rotated_obj.z, 2)) - pow(r->obj->ray, 2);
	if ((del[3] = delta(del[0], del[1], del[2])))
	{
		point_space(&r->point, r->cam_pos.x + dir.x * del[3],
				r->cam_pos.y + dir.y * del[3],
				r->cam_pos.z + dir.z * del[3]);
		point_space(&r->rotated_point, rotated_cam.x + rotated_dir.x * del[3],
				rotated_cam.y + rotated_dir.y * del[3],
				rotated_cam.z + rotated_dir.z * del[3]);
	}
	return (del[3]);
}

double	cylindre_lux(t_rt *r, t_space dir)
{
	double	del[4];
	t_space	rotated_pnt;
	t_space	rotated_dir;
	t_space	rotated_obj;

	rotated_pnt = obj_rotate(r->obj->rotation, r->point);
	rotated_obj = obj_rotate(r->obj->rotation, r->obj->origin);
	rotated_dir = obj_rotate(r->obj->rotation, dir);
	del[0] = pow(rotated_dir.x, 2) + pow(rotated_dir.z, 2);
	del[1] = 2 * (rotated_dir.x * (rotated_pnt.x - rotated_obj.x) +
			rotated_dir.z * (rotated_pnt.z - rotated_obj.z));
	del[2] = (pow(rotated_pnt.x - rotated_obj.x, 2) +
			pow(rotated_pnt.z - rotated_obj.z, 2)) - pow(r->obj->ray, 2);
	return (del[3] = delta(del[0], del[1], del[2]));
}

int		cylindre_vector(t_rt *r, t_space *vector)
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
	dist_2 = sqrt(pow(dist_1, 2) - pow(r->obj->ray, 2));
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
