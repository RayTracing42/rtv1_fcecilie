/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:54:27 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 15:11:35 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		heart_view_plane_dir(t_view_plane *p, t_space *dir, int x, int y)
{
	dir->x = p->view_plane_up_left.x + (p->vec_dir_right.x * p->x_indent * x)
		- (p->vec_dir_up.x * p->y_indent * y);
	dir->y = p->view_plane_up_left.y + (p->vec_dir_right.y * p->x_indent * x)
		- (p->vec_dir_up.y * p->y_indent * y);
	dir->z = p->view_plane_up_left.z + (p->vec_dir_right.z * p->x_indent * x)
		- (p->vec_dir_up.z * p->y_indent * y);
	return (0);
}

int		heart(t_rt *r, t_view_plane *p)
{
	int		x;
	int		y;
	t_space	dir;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			heart_view_plane_dir(p, &dir, x, y);
			dir = vec_unit(r->cam_pos, dir);
			dist_camera_obj(r, dir);
			if (r->lux)
				dist_camera_lux(r);
			if (r->dist > 0)
				r->add[y * 1280 + x] = r->color.x * 0x010000 + r->color.y *
					0x0100 + r->color.z * 0x01;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(r->mlx, r->win, r->img, 0, 0);
	return (0);
}
