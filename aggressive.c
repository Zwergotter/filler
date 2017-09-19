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
// #include <fcntl.h>

int		trying(t_fil *fil, int x, int y)
{
	int	i;//ligne
	int j;//col
	int mv_x;
	int mv_y;
	int place;
	int close;

	i = 0;
	mv_x = x;
	place = 0;
	close = 0;
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
				else if (mv_x >= 0 && mv_y >= 0 && fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
					place++;
			}
			if (fil->piece[j + (i * fil->p_col)] == '.' && mv_x >= 0 && mv_y >= 0)
				if (fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->op)
					close++;
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	if (place == 1 && close)
		return (close);
	return (0);
}

int		encircle(t_fil *fil)
{
 	int	x;
	int y;
	int result;

	x = -fil->p_line;
	y = -fil->p_col;
	result = 0;
	while (++x < fil->m_line)
	{
		y = -fil->p_col;
		while (y < fil->m_col)
		{
			if ((result = trying(fil, x, y)))
			{
				if (fil->nb_op < result)
				{
					fil->nb_op = result;
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y++;
		}
	}
	if (fil->nb_op)
		printing(fil->high_x, fil->high_y);
	return (fil->nb_op);
}
