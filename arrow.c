/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:05:15 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 02:27:02 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"
#include <stdlib.h>

void		move_cur(char *cr)
{
	t_elem	*e;

	e = g_all.c.cur;
	if (cr[0] == 27 && cr[1] == 91 && cr[2] == 66)
	{
		if (g_all.c.cur == g_all.c.end)
			g_all.c.cur = g_all.c.start;
		else
			g_all.c.cur = e->next;
	}
	if (cr[0] == 27 && cr[1] == 91 && cr[2] == 65)
	{
		if (g_all.c.cur == g_all.c.start)
			g_all.c.cur = g_all.c.end;
		else
			g_all.c.cur = e->prev;
	}
	if (cr[0] == 32 && cr[1] == 0 && cr[2] == 0)
	{
		if (e->sel)
			e->sel = 0;
		else
			e->sel = 1;
	}
	move_l(cr);
}

void		move_l(char *cr)
{
	t_elem	*end;
	t_elem	*cur;
	t_elem	*e;
	int		i;

	cur = g_all.c.cur;
	e = g_all.c.cur;
	end = g_all.c.end;
	i = end->x;
	if (cr[0] == 27 && cr[1] == 91 && cr[2] == 68)
	{
		if (e->x == 0)
		{
			if (end->y < e->y)
				i--;
			while (!((e->x == i) && (e->y == cur->y)))
				e = e->next;
			g_all.c.cur = e;
		}
		else
		{
			while (!((e->x == (cur->x - 1)) && (e->y == cur->y)))
				e = e->prev;
			g_all.c.cur = e;
		}
	}
	move_r(cr);
}

void		move_r(char *cr)
{
	t_elem	*end;
	t_elem	*cur;
	t_elem	*e;

	cur = g_all.c.cur;
	e = g_all.c.cur;
	end = g_all.c.end;
	if (cr[0] == 27 && cr[1] == 91 && cr[2] == 67)
	{
		if (e->x == end->x)
		{
			while (!((e->x == 0) && (e->y == cur->y)))
				e = e->prev;
			g_all.c.cur = e;
		}
		else
		{
			e = g_all.c.end;
			while (!((e->x == (cur->x + 1)) && (e->y == cur->y))
					&& !((e->x == 0) && (e->y == cur->y)))
				e = e->prev;
			g_all.c.cur = e;
		}
	}
}

void		stop_z(char *cr)
{
	if (cr[0] == 26 && cr[1] == 0 && cr[2] == 0)
	{
		exit(30);
		g_all.term.c_cc[VSUSP] = 1;
	}
}
