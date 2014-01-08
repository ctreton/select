/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 11:17:39 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 07:53:00 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termcap.h>
#include "select.h"
#include "libft/libft.h"

void		ft_signal(void)
{
	signal(SIGWINCH, resize);
//	signal(SIGTSTP, SIG_DFL);
	signal(SIGTSTP, stop);
	signal(SIGCONT, restart);
}

void		resize(int sig)
{
	int		fd;

	fd = sig;
	set_coor();
	fd = init_fd(fd);
	print_arg(fd);
}

void		stop(int sig)
{
//	if (sig == SIGTSTP)
//	{
		(void)sig;
		tputs(tgetstr("cl", NULL), 1, ft_tputs);
		tputs(tgetstr("te", NULL), 1, ft_tputs);
		tputs(tgetstr("ve", NULL), 1, ft_tputs);
		g_all.term.c_lflag = (ICANON | ECHO);
//		close_term();
//		signal(SIGCONT, restart);
//		raise(SIGTSTP);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
		tcsetattr(0, TCSADRAIN, &(g_all.term));
//		tcsetattr(0, 0, &(g_all.term));
//	}
}

void		restart(int sig)
{
	int		fd;

	(void)sig;
//	ft_signal();
	signal(SIGTSTP, stop);
//	init_term();
	g_all.term.c_lflag &= ~(ICANON | ECHO);
	tputs(tgetstr("ti", NULL), 1, ft_tputs);
	tputs(tgetstr("vi", NULL), 1, ft_tputs);
	tcsetattr(0, TCSADRAIN, &(g_all.term));
	fd = init_fd(fd);
	print_arg(fd);
	ft_select(fd);
//	signal(SIGCONT, SIG_DFL);
//	ioctl(0, TIOCSTI, g_all.term.c_cc[VSUSP]);
}
