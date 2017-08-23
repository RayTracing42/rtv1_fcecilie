/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 02:31:37 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/10 16:42:24 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parsing_lights_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_string_interval() failed");
	if (error == 2)
		ft_putendl("Error : parsing_lights_by_type() failed");
	if (error == 3)
		ft_putendl("Error : parsing_lights_add_to_list() failed to allocate");
	if (error == 4)
		ft_putendl("Error : get_lights_informations() failed");
	if (error == 5)
		ft_putendl("Error : parsing_lights_add_to_list() failed");
	if (error == 6)
		ft_putendl("Error : parsing_lights_new_light() failed");
	return (-1);
}

int		parsing_lights_add_to_list(t_rt *r, t_light new)
{
	t_light *first;

	first = NULL;
	if (!r->lux)
	{
		if (!(r->lux = (t_light *)ft_memalloc(sizeof(t_light))))
			return (parsing_lights_error(3));
		*r->lux = new;
		r->lux->next = NULL;
	}
	else
	{
		first = r->lux;
		while (r->lux->next)
			r->lux = r->lux->next;
		if (!(r->lux->next = (t_light *)ft_memalloc(sizeof(t_light))))
			return (parsing_lights_error(3));
		*r->lux->next = new;
		r->lux->next->next = NULL;
		r->lux = first;
	}
	return (0);
}

int		parsing_lights_new_light(t_rt *r, char *interval, int type, int id)
{
	t_light new;

	new.type = type;
	new.id = id;
	if (get_lights_informations(&new, interval) == -1)
		return (parsing_lights_error(4));
	if (parsing_lights_add_to_list(r, new) == -1)
		return (parsing_lights_error(5));
	return (0);
}

int		parsing_lights_by_type(t_rt *r, char *file, char *start, int type)
{
	static int	id;
	int			shift;
	char		*interval;

	shift = 0;
	interval = NULL;
	while ((shift = get_string_interval(file, start, '}', &interval)) > -1)
	{
		file = file + shift;
		id++;
		if (parsing_lights_new_light(r, interval, type, id) == -1)
			return (parsing_lights_error(6));
		ft_memdel((void**)&interval);
	}
	if (shift == -1)
		return (parsing_lights_error(1));
	return (0);
}

int		parsing_lights(t_rt *r, char *file)
{
	if (parsing_lights_by_type(r, file, "light spot\n{", 1) == -1)
		return (parsing_lights_error(1));
	return (0);
}
