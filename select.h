/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 00:25:44 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/10 20:26:26 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <termios.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termcap.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct		s_elem
{
	char			*value;
	int				sel;
	int				y;
	int				x;
	int				pos_x;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_cont
{
	t_elem			*start;
	t_elem			*end;
	t_elem			*cur;
}					t_cont;

typedef struct		s_glob
{
	t_cont			c;
	struct termios	term;
	struct termios	old_term;
}					t_glob;

t_glob				g_all;

/*
**	select.c
*/
int					main(int ac, char **av);
void				ft_select(int fd);

/*
**	arrow.c
*/
void				move_l(char *cr);
void				move_r(char *cr);
void				move_cur(char *cr);
void				stop_z(char *cr);

/*
**	term.c
*/
void				init_term(void);
void				start_term(void);
void				close_term(void);

/*
**	print.c
*/
void				print_arg(int fd);
void				set_coor(void);
void				end_verif(char *cr, int fd);
void				del_arg(char *cr);
int					calc_x(int l, int c, t_elem *e);
void				del_arg2(t_elem *e);

/*
**	error.c
*/
void				print_error(int	e);

/*
**	utils.c
*/
int					count_max(t_elem *e);
int					ft_tputs(int c);

/*
**	init.c
*/
int					init_fd(int fd);
void				create_arg(int ac, char **av);
void				init_glob(void);

/*
**	signal.c
*/
void				ft_signal(void);
void				resize(int sig);
void				stop(int sig);
void				restart(int sig);
void				end(int sig);

#endif /* !SELECT_H */
