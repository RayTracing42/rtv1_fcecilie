/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lights_informations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 03:13:33 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:39:43 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_lights_informations_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_t_space() failed");
	return (-1);
}

int		get_lights_informations(t_light *new, char *interval)
{
	if (get_t_space(interval, &new->origin, "origin : (") == -1)
		return (get_lights_informations_error(1));
	if (get_t_space(interval, &new->color, "color : (") == -1)
		return (get_lights_informations_error(1));
	if (get_t_space(interval, &new->translation, "translation : (") == -1)
		return (get_lights_informations_error(1));
	return (0);
}
