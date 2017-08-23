/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_interval.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 02:58:46 by fcecilie          #+#    #+#             */
/*   Updated: 2017/06/30 02:02:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		get_string_interval_error(int error)
{
	if (error == 1)
		ft_putendl("Error : get_string_interval() failed, (null) parameters");
	if (error == 2)
		ft_putendl("Error : ft_strsub() failed");
	return (-1);
}

int		check_start_occurence(char *str, char *start)
{
	int		n;
	int		d;

	n = 0;
	while (str && str[n])
	{
		d = 0;
		while (str[n + d] == start[d])
		{
			if (start[d + 1] == '\0')
				return (n + d + 1);
			d++;
		}
		n++;
	}
	return (-1);
}

int		get_string_interval(char *str, char *start, char end, char **interval)
{
	int		len_start;
	int		len_interval;

	len_start = 0;
	len_interval = 0;
	if (!str || !start)
		return (get_string_interval_error(1));
	if ((len_start = check_start_occurence(str, start)) == -1)
		return (-2);
	len_interval = ft_strnlen(str + len_start, end);
	if (!(*interval = ft_strsub(str, len_start, len_interval)))
		return (get_string_interval_error(2));
	return (len_start + len_interval + 1);
}
