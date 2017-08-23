/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 05:47:02 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/19 05:42:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		leave_window(void)
{
	exit(-1);
	return (0);
}

int		hub(int keycode, void *param)
{
	t_rt	*r;

	r = (t_rt*)param;
	if (keycode == 53)
		leave_window();
	return (0);
}
