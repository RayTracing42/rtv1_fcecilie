/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 05:43:00 by fcecilie          #+#    #+#             */
/*   Updated: 2017/07/13 09:54:10 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		display(t_rt *r)
{
	mlx_key_hook(r->win, hub, r);
	mlx_hook(r->win, 17, 17, leave_window, r);
	mlx_loop(r->mlx);
	return (0);
}