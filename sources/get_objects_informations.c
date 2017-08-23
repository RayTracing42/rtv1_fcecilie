/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects_informations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 05:09:19 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:39:47 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_objects_informations_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_t_space() failed");
	if (error == 2)
		ft_putendl("Error : get_string_interval() failed");
	return (-1);
}

int		get_objects_informations(t_object *new, char *interval)
{
	char	*tmp;
	int		res;

	tmp = NULL;
	if (get_t_space(interval, &new->origin, "origin : (") == -1)
		return (get_objects_informations_error(1));
	if (get_t_space(interval, &new->rotation, "rotation : (") == -1)
		return (get_objects_informations_error(1));
	if (get_t_space(interval, &new->translation, "translation : (") == -1)
		return (get_objects_informations_error(1));
	if (get_t_space(interval, &new->color, "color : (") == -1)
		return (get_objects_informations_error(1));
	if ((res = get_string_interval(interval, "rayon : (", ')', &tmp)) == -1)
		return (get_objects_informations_error(2));
	new->ray = catch_value(tmp, 1);
	ft_memdel((void**)&tmp);
	return (0);
}
