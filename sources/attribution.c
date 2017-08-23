/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 05:08:56 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:39:56 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		view_plane(t_rt *r, t_view_plane *p)
{
	p->view_plane_up_left.x = r->cam_pos.x + ((p->vec_dir.x *
		p->view_plane_size.x) + (p->vec_dir_up.x * (p->view_plane_size.y / 2)))
		- (p->vec_dir_right.x * (p->view_plane_size.z / 2));
	p->view_plane_up_left.y = r->cam_pos.y + ((p->vec_dir.y *
		p->view_plane_size.x) + (p->vec_dir_up.y * (p->view_plane_size.y / 2)))
		- (p->vec_dir_right.y * (p->view_plane_size.z / 2));
	p->view_plane_up_left.z = r->cam_pos.z + ((p->vec_dir.z *
		p->view_plane_size.x) + (p->vec_dir_up.z * (p->view_plane_size.y / 2)))
		- (p->vec_dir_right.z * (p->view_plane_size.z / 2));
	return (0);
}

int		cam_rotate(t_rt *r, t_view_plane *p)
{
	t_space	angle;

	angle.x = r->rotation.x / 180 * M_PI;
	matrice_x(&p->vec_dir, angle.x);
	matrice_x(&p->vec_dir_up, angle.x);
	matrice_x(&p->vec_dir_right, angle.x);
	angle.y = r->rotation.y / 180 * M_PI;
	matrice_y(&p->vec_dir, angle.y);
	matrice_y(&p->vec_dir_up, angle.y);
	matrice_y(&p->vec_dir_right, angle.y);
	angle.z = r->rotation.z / 180 * M_PI;
	matrice_z(&p->vec_dir, angle.z);
	matrice_z(&p->vec_dir_up, angle.z);
	matrice_z(&p->vec_dir_right, angle.z);
	return (0);
}

void	translation(t_rt *r)
{
	t_object	*first_obj;
	t_light		*first_lux;

	first_obj = r->obj;
	while (r->obj)
	{
		point_space(&r->obj->origin, r->obj->origin.x + r->obj->translation.x,
				r->obj->origin.y + r->obj->translation.y,
				r->obj->origin.z + r->obj->translation.z);
		r->obj = r->obj->next;
	}
	if (r->lux)
	{
		first_lux = r->lux;
		while (r->lux)
		{
			point_space(&r->lux->origin, r->lux->origin.x +
				r->lux->translation.x, r->lux->origin.y +
				r->lux->translation.y, r->lux->origin.z +
				r->lux->translation.z);
			r->lux = r->lux->next;
		}
		r->lux = first_lux;
	}
	r->obj = first_obj;
}

int		attribution(t_rt *r, t_view_plane *p)
{
	translation(r);
	point_space(&r->cam_pos, r->cam_pos.x + r->translation.x,
			r->cam_pos.y + r->translation.y,
			r->cam_pos.z + r->translation.z);
	point_space(&p->vec_dir, 1, 0, 0);
	point_space(&p->vec_dir_right, 0, 0, 1);
	point_space(&p->vec_dir_up, 0, 1, 0);
	point_space(&p->view_plane_size, 623, 720, 1280);
	p->x_indent = p->view_plane_size.z / 1280;
	p->y_indent = p->view_plane_size.y / 720;
	cam_rotate(r, p);
	view_plane(r, p);
	return (0);
}
