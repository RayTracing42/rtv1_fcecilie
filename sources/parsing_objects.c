/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 02:31:36 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:39:51 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parsing_objects_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_string_interval() failed");
	if (error == 2)
		ft_putendl("Error : parsing_objects_by_type() failed");
	if (error == 3)
		ft_putendl("Error : parsing_objects_add_to_list() failed to allocate");
	if (error == 4)
		ft_putendl("Error : get_objects_informations() failed");
	if (error == 5)
		ft_putendl("Error : parsing_objects_add_to_list() failed");
	if (error == 6)
		ft_putendl("Error : parsing_objects_new_object() failed");
	if (error == 7)
		ft_putendl("Error : no valid object to display on this scene");
	return (-1);
}

int		parsing_objects_add_to_list(t_rt *r, t_object new)
{
	t_object *first;

	first = NULL;
	if (!r->obj)
	{
		if (!(r->obj = (t_object *)ft_memalloc(sizeof(t_object))))
			return (parsing_objects_error(3));
		*r->obj = new;
		r->obj->next = NULL;
	}
	else
	{
		first = r->obj;
		while (r->obj->next)
			r->obj = r->obj->next;
		if (!(r->obj->next = (t_object *)ft_memalloc(sizeof(t_object))))
			return (parsing_objects_error(3));
		*r->obj->next = new;
		r->obj->next->next = NULL;
		r->obj = first;
	}
	return (0);
}

int		parsing_objects_new_object(t_rt *r, char *interval, int type, int id)
{
	t_object new;

	new.type = type;
	new.id = id;
	if (get_objects_informations(&new, interval) == -1)
		return (parsing_objects_error(4));
	if (parsing_objects_add_to_list(r, new) == -1)
		return (parsing_objects_error(5));
	return (0);
}

int		parsing_objects_by_type(t_rt *r, char *file, char *start, int type)
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
		if (parsing_objects_new_object(r, interval, type, id) == -1)
			return (parsing_objects_error(6));
		ft_memdel((void**)&interval);
	}
	if (shift == -1)
		return (parsing_objects_error(1));
	return (0);
}

int		parsing_objects(t_rt *r, char *file)
{
	if (parsing_objects_by_type(r, file, "object plan\n{", 1) == -1)
		return (parsing_objects_error(2));
	if (parsing_objects_by_type(r, file, "object sphere\n{", 2) == -1)
		return (parsing_objects_error(2));
	if (parsing_objects_by_type(r, file, "object cone\n{", 3) == -1)
		return (parsing_objects_error(2));
	if (parsing_objects_by_type(r, file, "object cylindre\n{", 4) == -1)
		return (parsing_objects_error(2));
	if (!r->obj)
		return (parsing_objects_error(7));
	return (0);
}
