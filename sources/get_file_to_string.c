/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_to_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 00:57:00 by fcecilie          #+#    #+#             */
/*   Updated: 2017/06/30 04:40:06 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_file_to_string_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_file_to_string() failed to allocate 'buf'");
	if (error == 2)
		ft_putendl("Error : ft_realloc() failed to reallocate 'buf'");
	if (error == 3)
		ft_putendl("Error : read() failed");
	if (error == 4)
		ft_putendl("Error : ft_strdup() failed");
	return (-1);
}

int		get_file_to_string(int fd, char **file)
{
	char	*buf;
	int		readed;
	int		size;

	size = 0;
	readed = 0;
	if (!(buf = (char *)ft_memalloc(10000 + 1)))
		return (get_file_to_string_error(1));
	while ((readed = read(fd, buf + size, 10000)) > 0)
	{
		size = size + readed;
		if (!(buf = ft_realloc(buf, readed)))
			return (get_file_to_string_error(2));
	}
	if (readed < 0)
		return (get_file_to_string_error(3));
	if (!(*file = ft_strdup(buf)))
		return (get_file_to_string_error(4));
	ft_memdel((void**)&buf);
	return (0);
}
