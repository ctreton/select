/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctreton <ctreton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 10:11:19 by ctreton           #+#    #+#             */
/*   Updated: 2014/01/08 02:07:16 by ctreton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "select.h"
#include "libft/libft.h"

void		print_error(int e)
{
	if (e == 0)
		ft_putendl_fd("usage: ft_select [arg ...]", 2);
	else if (e == 2)
	{
		close_term();
		ft_putendl_fd("open failed", 2);
	}
	else if (e == 3)
		close_term();
	exit(1);
}
