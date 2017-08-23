/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_camera_lux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 14:09:55 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 15:02:46 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	get_vectors(t_rt *r, t_space *obj_dir, t_space *lux_dir)
{
	t_object	*first;
	t_space		rotated_lux;

	first = r->obj;
	while (r->obj != NULL && r->id != r->obj->id)
		r->obj = r->obj->next;
	if (r->obj)
	{
		rotated_lux = obj_rotate(r->obj->rotation, r->lux->origin);
		*lux_dir = vec_unit(r->rotated_point, rotated_lux);
		if (r->obj->type == 1)
			plan_vector(r, obj_dir);
		if (r->obj->type == 2)
			sphere_vector(r, obj_dir);
		if (r->obj->type == 3)
			cone_vector(r, obj_dir);
		if (r->obj->type == 4)
			cylindre_vector(r, obj_dir);
	}
	r->obj = first;
	return (0);
}

int	dist_camera_lux_angle_vec(t_space lux_dir, t_space obj_dir, double *csns)
{
	double	csns_tmp;

	*csns = obj_dir.x * lux_dir.x + obj_dir.y * lux_dir.y + obj_dir.z *
		lux_dir.z;
	csns_tmp = (acos(*csns) * 180 / M_PI);
	*csns = ft_abs(1 - (csns_tmp * 1 / 180));
	return (0);
}

int	check_shadow_obj_2(t_rt *r, t_space lux_dir, double *delta)
{
	if (r->obj->type == 1)
		*delta = plan_lux(r, lux_dir);
	if (r->obj->type == 2)
		*delta = sphere_lux(r, lux_dir);
	if (r->obj->type == 3)
		*delta = cone_lux(r, lux_dir);
	if (r->obj->type == 4)
		*delta = cylindre_lux(r, lux_dir);
	return (0);
}

int	check_shadow_obj(t_rt *r, t_space lux_dir)
{
	t_object	*first;
	double		delta;
	double		dist;

	dist = sqrt(pow(r->point.x - r->lux->origin.x, 2) + pow(r->point.y -
				r->lux->origin.y, 2) + pow(r->point.z - r->lux->origin.z, 2));
	first = r->obj;
	while (r->obj != NULL)
	{
		if (r->obj->id == r->id)
			r->obj = r->obj->next;
		if (r->obj)
		{
			delta = 0;
			check_shadow_obj_2(r, lux_dir, &delta);
			if (delta < dist && delta > 0.000001)
			{
				r->obj = first;
				return (1);
			}
			r->obj = r->obj->next;
		}
	}
	r->obj = first;
	return (0);
}

int	dist_camera_lux(t_rt *r)
{
	t_light	*first;
	t_space	lux_dir;
	t_space	obj_dir;
	double	csns;

	r->nb_light = 1;
	csns = 1;
	first = r->lux;
	while (r->lux != NULL)
	{
		get_vectors(r, &obj_dir, &lux_dir);
		dist_camera_lux_angle_vec(lux_dir, obj_dir, &csns);
		lux_dir = vec_unit(r->point, r->lux->origin);
		if (!(check_shadow_obj(r, lux_dir) == 1))
			point_space(&r->color, r->color.x + r->lux->color.x * pow(csns, 2),
					r->color.y + r->lux->color.y * pow(csns, 2),
					r->color.z + r->lux->color.z * pow(csns, 2));
		r->nb_light++;
		r->lux = r->lux->next;
	}
	r->lux = first;
	point_space(&r->color, (int)((r->color.x / r->nb_light)),
			(int)((r->color.y / r->nb_light)),
			(int)((r->color.z / r->nb_light)));
	return (0);
}
