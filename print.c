/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:08:51 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/10 20:27:14 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void				print_arg(int fd)
{
	t_elem			*e;
	struct ttysize	ts;

	e = g_all.c.start;
	ioctl(0, TIOCGSIZE, &ts);
	tputs(tgetstr("cl", NULL), 1, ft_tputs);
	while (e)
	{
		if ((e->pos_x + ft_strlen(e->value)) > ts.ts_cols)
		{
			tputs(tgoto(tgetstr("cl", NULL), e->pos_x, e->y), 1, ft_tputs);
			ft_putstr_fd("pas assez de place", fd);
			return ;
		}
		tputs(tgoto(tgetstr("cm", NULL), e->pos_x, e->y), 1, ft_tputs);
		if (e == g_all.c.cur)
			tputs(tgetstr("us", NULL), 1, ft_tputs);
		if (e->sel == 1)
			tputs(tgetstr("mr", NULL), 1, ft_tputs);
		ft_putstr_fd(e->value, fd);
		tputs(tgetstr("ue", NULL), 1, ft_tputs);
		tputs(tgetstr("me", NULL), 1, ft_tputs);
		e = e->next;
	}
}

void				set_coor(void)
{
	int				i;
	t_elem			*e;
	struct ttysize	ts;

	i = 0;
	e = g_all.c.start;
	ioctl(0, TIOCGSIZE, &ts);
	while (e)
	{
		e->y = (i % ts.ts_lines);
		e->x = (i / ts.ts_lines);
		e->pos_x = calc_x(ts.ts_lines, e->x, e);
		i++;
		e = e->next;
	}
}

void				end_verif(char *cr, int fd)
{
	t_elem			*e;

	fd = 1;
	if (cr[0] == 10 && cr[1] == 0 && cr[2] == 0)
	{
		e = g_all.c.start;
		close_term();
		while (e)
		{
			if (e->sel)
			{
				ft_putstr_fd(e->value, fd);
				ft_putchar_fd(' ', fd);
			}
			e = e->next;
		}
		exit(0);
	}
}

void				del_arg(char *cr)
{
	t_elem			*e;

	e = g_all.c.cur;
	if ((cr[0] == 126 || cr[0] == 127) && cr[1] == 0 && cr[2] == 0)
	{
		del_arg2(e);
		free(e);
		e = NULL;
		set_coor();
	}
}

void				del_arg2(t_elem *e)
{
	if (e == g_all.c.start && e == g_all.c.end)
		print_error(3);
	if (e == g_all.c.start)
	{
		(e->next)->prev = NULL;
		g_all.c.start = e->next;
		g_all.c.cur = e->next;
	}
	else if (e == g_all.c.end)
	{
		(e->prev)->next = NULL;
		g_all.c.end = e->prev;
		g_all.c.cur = e->prev;
	}
	else
	{
		(e->prev)->next = e->next;
		(e->next)->prev = e->prev;
		g_all.c.cur = e->next;
	}
}
