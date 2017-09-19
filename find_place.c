/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_place.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:33:06 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 18:34:09 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include <fcntl.h>

int		printing(int x, int y)
{
	ft_putnbr(x);
	ft_putchar(' ');
	ft_putnbr(y);
	return (1);
}

void	end(t_fil *fil)
{
	int x;
	int y;

	x = -1;
	ft_putstr_fd("\nLast piece is:\n", 2);
	while (++x < fil->p_line)
	{
		y = -1;
		while (++y < fil->p_col)
			ft_putchar_fd(fil->piece[y + (x * fil->p_col)], 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putchar_fd('\n', 2);
	printing(0, 0);
}

void	finding_place(t_fil *fil)
{
	int	x;
	int y;
	int result;

	x = fil->end_xop ? fil->end_xop : fil->start_xop;
	y = fil->end_yop ? fil->end_yop : fil->start_yop;
	result = ((fil->m_line < 20 || fil->m_col < 20) && (fil->cur_line < x ||
		fil->cur_col < y)) ? going_opp_direction(fil) : encircle(fil);
	result = result ? result : which_direction(fil);
	if (!result)
	{
		x = -fil->p_line;
		while (!(fitting(fil, x, y)) && ++x < fil->m_line)
		{
			y = -fil->p_col;
			while (!(fitting(fil, x, y)) && y < fil->m_col)
				y++;
		}
	}
	if (!result && fitting(fil, x, y))
		printing(x, y);
	if (!result && !fitting(fil, x, y))
		end(fil);
	ft_putchar('\n');
	fil->nb_op = 0;
}
