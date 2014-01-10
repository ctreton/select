/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 11:17:39 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/10 20:04:27 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			ft_signal(void)
{
	signal(SIGWINCH, resize);
	signal(SIGTSTP, stop);
	signal(SIGCONT, restart);
	signal(SIGINT, end);
}

void			resize(int sig)
{
	static int	fd;

	(void)sig;
	set_coor();
	if (fd == 0)
		fd = init_fd(fd);
	print_arg(fd);
}

void			stop(int sig)
{
	char		cp[2];

	cp[0] = 032;
	cp[1] = 0;
	(void)sig;
	close_term();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, cp);
}

void			restart(int sig)
{
	static int	fd;

	(void)sig;
	start_term();
	signal(SIGTSTP, stop);
	if (fd == 0)
		fd = init_fd(fd);
	print_arg(fd);
}

void			end(int sig)
{
	(void)sig;
	close_term();
	exit(1);
}
