/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_fgr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:54:02 by fcecilie          #+#    #+#             */
/*   Updated: 2017/05/02 04:04:41 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cnt_fgr(int n)
{
	int count;

	count = 0;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		count++;
	}
	count++;
	return (count);
}
