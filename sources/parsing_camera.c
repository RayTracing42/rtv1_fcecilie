/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 05:02:24 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:39:40 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parsing_camera_error(int error)
{
	if (error == 1)
		ft_putendl("Error : no valid camera on this scene");
	if (error == 21)
		ft_putendl("Error : get_t_space() failed");
	return (-1);
}

int		parsing_camera(t_rt *r, char *file)
{
	char	*interval;

	interval = NULL;
	if (get_string_interval(file, "camera\n{", '}', &interval) < 0)
		return (parsing_camera_error(1));
	if (get_t_space(interval, &r->cam_pos, "origin : (") == -1)
		return (parsing_camera_error(2));
	if (get_t_space(interval, &r->rotation, "rotation : (") == -1)
		return (parsing_camera_error(2));
	if (get_t_space(interval, &r->translation, "translation : (") == -1)
		return (parsing_camera_error(2));
	ft_memdel((void**)&interval);
	return (0);
}
