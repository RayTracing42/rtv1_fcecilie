/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 04:38:02 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/09 17:06:10 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main_error(int error)
{
	if (error == 1)
		ft_putendl("Error : main() failed to allocate 'r'");
	if (error == 2)
		ft_putendl("Error : parsing() failed");
	if (error == 4)
		ft_putendl("Error : heart() failed");
	return (-1);
}

int		main(int argc, char **argv)
{
	t_rt			*r;
	t_view_plane	p;

	r = NULL;
	if (argc == 2)
	{
		if (!(r = (t_rt*)ft_memalloc(sizeof(t_rt) * (1))))
			return (main_error(1));
		r->mlx = mlx_init();
		r->win = mlx_new_window(r->mlx, 1280, 720, "RTv1");
		r->img = mlx_new_image(r->mlx, 1280, 720);
		r->add = (int*)mlx_get_data_addr(r->img, &r->bpp, &r->bpl, &r->edn);
		if (parsing(r, argv[1]) == -1)
			return (main_error(2));
		attribution(r, &p);
		if (heart(r, &p) == -1)
			return (main_error(4));
		display(r);
	}
	else
		ft_putstr("usage : ./rtv1 [scene]\n");
	return (0);
}
