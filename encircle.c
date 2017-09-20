/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggressive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:58:49 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/12 16:58:56 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		trying(t_fil *f, int x, int y, int place)
{
	int	i;
	int j;
	int mv_x;
	int mv_y;

	i = 0;
	mv_x = x;
	while (i < f->p_line)
	{
		mv_y = y;
		j = 0;
		while (j < f->p_col)
		{
			if (f->piece[j + (i * f->p_col)] == '*')
				place += placing(f, mv_x, mv_y);
			if (f->piece[j + (i * f->p_col)] == '.' && mv_x >= 0 && mv_y >= 0
				&& f->map[mv_y + 4 + mv_x * (f->m_col + 4)] == f->op)
				f->close++;
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	return (place);
}

int		encircle(t_fil *fil)
{
	int	x;
	int y;

	x = -fil->p_line;
	y = -fil->p_col;
	while (++x < fil->m_line)
	{
		y = -fil->p_col;
		while (y < fil->m_col)
		{
			if ((trying(fil, x, y, 0) == 1) && fil->nb_op < fil->close)
			{
				fil->nb_op = fil->close;
				fil->high_x = x;
				fil->high_y = y;
			}
			y++;
			fil->close = 0;
		}
	}
	if (fil->nb_op)
		printing(fil->high_x, fil->high_y);
	return (fil->nb_op);
}
