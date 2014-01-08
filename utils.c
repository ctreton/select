/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:12:08 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 02:11:15 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"
#include "libft/libft.h"

int			count_max()
{
	int		max;
	t_elem	*e;

	e = g_all.c.start;
	max = 0;
	while (e)
	{
		if ((int)ft_strlen(e->value) > max)
			max = (int)ft_strlen(e->value);
		e = e->next;
	}
	return (max + 1);
}

int			ft_tputs(int c)
{
	ft_putchar(c);
	return (1);
}
