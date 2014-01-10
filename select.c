/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 23:06:06 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/10 20:04:30 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int					main(int ac, char **av)
{
	int				fd;

	fd = 0;
	ft_signal();
	init_glob();
	if (ac < 2)
		print_error(0);
	fd = init_fd(fd);
	create_arg(ac, av);
	init_term();
	g_all.c.cur = g_all.c.start;
	ft_select(fd);
	close_term();
	return (1);
}

void				ft_select(int fd)
{
	char			cr[4] = {0};

	while (!(cr[0] == 27 && cr[1] == 0 && cr[2] == 0))
	{
		move_cur(cr);
		del_arg(cr);
		end_verif(cr, fd);
		cr[1] = 0;
		cr[2] = 0;
		print_arg(fd);
		read(0, cr, 3);
	}
}
