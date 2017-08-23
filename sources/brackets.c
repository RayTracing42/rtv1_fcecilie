/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 00:33:47 by fcecilie          #+#    #+#             */
/*   Updated: 2017/06/30 02:20:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		brackets_error(int error)
{
	if (error == 1)
		ft_putendl("Error : brackets() failed to allocate 'order'");
	if (error == 2)
	{
		ft_putstr("Error : brackets() failed when check order of apparition");
		ft_putendl("of brackets");
	}
	if (error == 3)
		ft_putendl("Error : brackets() failed when check number of brackets");
	return (-1);
}

int		par_verification(char c, int *par, char *order, int *d)
{
	if (c == '(')
	{
		order[*d] = '(';
		*d = *d + 1;
		*par = *par + 1;
	}
	if (c == ')')
	{
		if (order[*d - 1] != '(')
			return (-1);
		order[*d - 1] = '\0';
		order[*d] = '\0';
		*d = *d - 1;
		*par = *par - 1;
	}
	return (0);
}

int		cro_verification(char c, int *cro, char *order, int *d)
{
	if (c == '[')
	{
		order[*d] = '[';
		*d = *d + 1;
		*cro = *cro + 1;
	}
	if (c == ']')
	{
		if (order[*d - 1] != '[')
			return (-1);
		order[*d - 1] = '\0';
		order[*d] = '\0';
		*d = *d - 1;
		*cro = *cro - 1;
	}
	return (0);
}

int		aco_verification(char c, int *aco, char *order, int *d)
{
	if (c == '{')
	{
		order[*d] = '{';
		*d = *d + 1;
		*aco = *aco + 1;
	}
	if (c == '}')
	{
		if (order[*d - 1] != '{')
			return (-1);
		order[*d - 1] = '\0';
		order[*d] = '\0';
		*d = *d - 1;
		*aco = *aco - 1;
	}
	return (0);
}

int		brackets(char *str)
{
	int		n;
	int		d;
	int		brack[3];
	char	*order;

	n = 0;
	d = 0;
	brack[0] = 0;
	brack[1] = 0;
	brack[2] = 0;
	if (!(order = (char *)ft_memalloc(ft_strlen(str) + 1)))
		return (brackets_error(1));
	while (str[n])
	{
		if (par_verification(str[n], &brack[0], order, &d) == -1
			|| cro_verification(str[n], &brack[1], order, &d) == -1
			|| aco_verification(str[n], &brack[2], order, &d) == -1)
			return (brackets_error(2));
		n++;
	}
	if (brack[0] != 0 || brack[1] != 0 || brack[2] != 0)
		return (brackets_error(3));
	ft_memdel((void**)&order);
	return (0);
}
