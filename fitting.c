/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:11:38 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/22 15:00:45 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include <fcntl.h>

int	printing(int x, int y)
{
		ft_putnbr(x);
		ft_putchar(' ');
		ft_putnbr(y);
		return (1);
}

int		fitting(t_fil *fil, int x, int y)
{
	int	i;//ligne
	int j;//col
	int mv_x;
	int mv_y;
	int place;

	i = 0;
	mv_x = x;
	place = 0;
	while (i < fil->p_line)
	{
		mv_y = y;
		j = 0;
		while (j < fil->p_col)
		{
			if (fil->piece[j + (i * fil->p_col)] == '*')
			{
				if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_line || mv_y >= fil->m_col || fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->op)
					place = 2;
				if (mv_x >= 0 && mv_y >= 0 && fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
					place++;
			}
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	if (place == 1)
		return (1);
	return (0);
}

void	finding_place(t_fil *fil)
{
	int	x;
	int y;
	int result;

	x = fil->end_xop ? fil->end_xop: fil->start_xop;;
	y = fil->end_yop ? fil->end_yop : fil->start_yop;
	result = ((fil->m_line < 20 || fil->m_col < 20) && (fil->cur_line < x || fil->cur_col < y)) ? going_opp_direction(fil) : encircle(fil);
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
	{
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
		ft_putstr("0 0\n");
	}
	ft_putchar('\n');
	fil->nb_op = 0;
}
