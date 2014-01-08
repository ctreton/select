/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:08:51 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 02:34:13 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/ioctl.h>
#include <termcap.h>
#include "select.h"
#include "libft/libft.h"

void		print_arg(int fd)
{
	t_elem	*e;
	int		step;

	e = g_all.c.start;
	step = count_max();
	tputs(tgetstr("cl", NULL), 1, ft_tputs);
	while (e)
	{
		tputs(tgoto(tgetstr("cm", NULL), (e->x * step), e->y), 1, ft_tputs);
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

void		set_coor(void)
{
	int		i;
	t_elem	*e;
	struct ttysize	ts;

	i = 0;
	e = g_all.c.start;
	ioctl(0, TIOCGSIZE, &ts);
	while (e)
	{
		e->y = (i % ts.ts_lines);
		e->x = (i / ts.ts_lines);
		i++;
		e = e->next;
	}
}

void		end_verif(char *cr, int fd)
{
	t_elem	*e;

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

void		del_arg(char *cr)
{
	t_elem	*e;
	t_elem	*prev;
	t_elem	*next;

	e = g_all.c.cur;
	if ((cr[0] == 126 || cr[0] == 127) && cr[1] == 0 && cr[2] == 0)
	{
		next = e->next;
		prev = e->prev;
		if (e == g_all.c.start && e == g_all.c.end)
			print_error(3);
		if (e == g_all.c.start)
		{
			next->prev = NULL;
			g_all.c.start = next;
			g_all.c.cur = next;
		}
		else if (e == g_all.c.end)
		{
			prev->next = NULL;
			g_all.c.end = prev;
			g_all.c.cur = prev;
		}
		else
		{
			prev->next = next;
			next->prev = prev;
			g_all.c.cur = next;
		}
		free(e);
		e = NULL;
		set_coor();
	}
}
