/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_camera_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:58:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 15:26:41 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		dist_camera_obj_choice(t_rt *r, t_space dir)
{
	double	dist;

	dist = 0;
	if (r->obj->type == 1)
		dist = plan(r, dir);
	if (r->obj->type == 2)
		dist = sphere(r, dir);
	if (r->obj->type == 3)
		dist = cone(r, dir);
	if (r->obj->type == 4)
		dist = cylindre(r, dir);
	if (dist != 0)
		return (dist);
	return (0);
}

int		dist_camera_obj(t_rt *r, t_space dir)
{
	t_object	*first;
	t_space		tmp_point;
	t_space		tmp_rotated_point;
	double		dist;

	first = r->obj;
	r->dist = 0;
	while (r->obj != NULL)
	{
		dist = dist_camera_obj_choice(r, dir);
		if (dist > 0 && ((r->dist == 0) || (r->dist > 0 && dist < r->dist)))
		{
			tmp_point = r->point;
			tmp_rotated_point = r->rotated_point;
			r->dist = dist;
			r->id = r->obj->id;
			point_space(&r->color, r->obj->color.x, r->obj->color.y,
					r->obj->color.z);
		}
		r->obj = r->obj->next;
	}
	r->obj = first;
	r->point = tmp_point;
	r->rotated_point = tmp_rotated_point;
	return (0);
}
