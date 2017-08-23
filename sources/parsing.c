/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 04:16:40 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 16:56:09 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parsing_error(int error)
{
	if (error == 1)
		ft_putendl("Error : open() failed to open the scene");
	if (error == 2)
		ft_putendl("Error : get_file_to_string() failed");
	if (error == 3)
		ft_putendl("Error : brackets() failed");
	if (error == 4)
		ft_putendl("Error : parsing_objects() failed");
	if (error == 5)
		ft_putendl("Error : parsing_lights() failed");
	if (error == 6)
		ft_putendl("Error : close() failed");
	if (error == 7)
		ft_putendl("Error : scene is not a valid scene");
	if (error == 8)
		ft_putendl("Error : parsing_camera() failed");
	return (-1);
}

int		parsing(t_rt *r, char *argv)
{
	int		fd;
	char	*file;

	file = NULL;
	if (!(ft_strstr(argv, ".rtv1")))
		return (parsing_error(7));
	if ((fd = open(argv, O_RDONLY)) == -1)
		return (parsing_error(1));
	if (get_file_to_string(fd, &file) == -1)
		return (parsing_error(2));
	if (brackets(file) == -1)
		return (parsing_error(3));
	if (parsing_camera(r, file) == -1)
		return (parsing_error(8));
	if (parsing_objects(r, file) == -1)
		return (parsing_error(4));
	if (parsing_lights(r, file) == -1)
		return (parsing_error(5));
	if (close(fd) == -1)
		return (parsing_error(6));
	ft_memdel((void **)&file);
	return (0);
}
