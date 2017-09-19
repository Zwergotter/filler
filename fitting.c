/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fitting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:28:32 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 18:34:15 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		placing(t_fil *fil, int mv_x, int mv_y)
{
	if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_line || mv_y >= fil->m_col ||
		fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->op)
		return (2);
	if (mv_x >= 0 && mv_y >= 0 &&
		fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
		return (1);
	return (0);
}

int		try(t_fil *fil, int i, int x, int y)
{
	int place;
	int j;
	int mv_x;
	int mv_y;

	place = 0;
	j = 0;
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

int		fitting(t_fil *fil, int x, int y)
{
	int	i;

	i = 0;
	if (try(fil, i, x, y) == 1)
		return (1);
	return (0);
}
