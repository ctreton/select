/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:07:37 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 07:54:16 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <stdlib.h>
#include "select.h"

void		init_term(void)
{
	t_elem	*e;
	char	*name;

	e = g_all.c.start;
	name = getenv("TERM");
	tgetent(NULL, name);
	tcgetattr(0, &(g_all.term));
	tgetent(NULL, name);
	tcgetattr(0, &(g_all.old_term));
	g_all.term.c_lflag &= ~(ICANON | ECHO);
	g_all.term.c_cc[VMIN] = 1;
	g_all.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &(g_all.term));
	tputs(tgetstr("ti", NULL), 1, ft_tputs);
	tputs(tgetstr("vi", NULL), 1, ft_tputs);
}

void		close_term()
{
	tputs(tgetstr("cl", NULL), 1, ft_tputs);
	tputs(tgetstr("te", NULL), 1, ft_tputs);
	tputs(tgetstr("ve", NULL), 1, ft_tputs);
	g_all.term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &(g_all.term));
}
