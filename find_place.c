/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_place.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:33:06 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/20 18:24:06 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

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
	ft_putstr_fd("\nPlaying O is: ", 2);
	fil->player == 'O' ? ft_putstr_fd("\033[1;36medeveze.filler\033[0m", 2)
		: ft_putstr_fd("\033[1;37mthe opponent\033[0m", 2);
	ft_putstr_fd("\nPlaying X is: ", 2);
	fil->player == 'X' ? ft_putstr_fd("\033[1;36medeveze.filler\033[0m", 2)
		: ft_putstr_fd("\033[1;37mthe opponent\033[0m", 2);
	ft_putstr_fd("\n\n", 2);
	printing(0, 0);
}

int		placing(t_fil *fil, int mv_x, int mv_y)
{
	if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_line || mv_y >= fil->m_col ||
		fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->op)
		return (2);
	if (fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
		return (1);
	return (0);
}

int		fitting(t_fil *fil, int x, int y)
{
	int place;
	int i;
	int j;
	int mv_x;
	int mv_y;

	place = 0;
	i = 0;
	mv_x = x;
	while (i < fil->p_line)
	{
		mv_y = y;
		j = 0;
		while (j < fil->p_col)
		{
			if (fil->piece[j + (i * fil->p_col)] == '*')
				place += placing(fil, mv_x, mv_y);
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	return (place);
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
		while ((fitting(fil, x, y) != 1) && ++x < fil->m_line)
		{
			y = -fil->p_col;
			while ((fitting(fil, x, y) != 1) && y < fil->m_col)
				y++;
		}
	}
	if (!result && fitting(fil, x, y) == 1)
		printing(x, y);
	if (!result && fitting(fil, x, y) != 1)
		end(fil);
	ft_putchar('\n');
	fil->nb_op = 0;
}
