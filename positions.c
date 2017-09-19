/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 14:52:15 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 14:52:20 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include <fcntl.h>

int		directions(t_fil *fil, int x, int y, int i)
{
	if (x <= fil->m_line / 2 && y <= fil->m_col / 2)
		fil->dir2 = DESC_RIGHT;
	if (x <= fil->m_line / 2 && y > fil->m_col / 2)
		fil->dir2 = DESC_LEFT;
	if (x > fil->m_line / 2 && y <= fil->m_col / 2)
		fil->dir2 = ASC_RIGHT;
	if (x > fil->m_line / 2 && y > fil->m_col / 2)
		fil->dir2 = ASC_LEFT;
	fil->cur_line = x;
	fil->cur_col = y;
	if (!fil->nb)
	{
		fil->start_xop = x;
		fil->start_yop = y;
		fil->dir = fil->dir2;
	}
	if (fil->dir != fil->dir2 && (fil->m_col < 20 || fil->m_line < 20) &&
		(fil->start_xply > fil->start_xop || fil->start_yply > fil->start_yop))
		fil->dir2 = EDGE;
	fil->dir = fil->dir2;
	return (i);
}

void	first_time(t_fil *fil, int x, int y)
{
	int i;

	i = 0;
	while (x < fil->m_line && fil->map[y + 4 + (x * (fil->m_col + 4))])
	{
		while (y < fil->m_col && fil->map[y + 4 + (x * (fil->m_col + 4))])
		{
			i = y + 4 + (x * (fil->m_col + 4));
			if (fil->map[i] == fil->op && !fil->start_xop)
			{
				fil->start_xop = x;
				fil->start_yop = y;
			}
			if (fil->map[i] == fil->player && !fil->start_ply)
				fil->start_ply = directions(fil, x, y, i);
			y++;
		}
		y = 0;
		x++;
	}
}

void	new_piece(t_fil *fil, int x, int y)
{
	int i;

	i = 0;
	while (x < fil->m_line && fil->map[y + 4 + (x * (fil->m_col + 4))])
	{
		while (y < fil->m_col && fil->map[y + 4 + (x * (fil->m_col + 4))])
		{
			i = y + 4 + (x * (fil->m_col + 4));
			if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->op)
			{
				fil->end_xop = x;
				fil->end_yop = y;
			}
			if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->player)
				fil->end_ply = directions(fil, x, y, i);
			y++;
		}
		y = 0;
		x++;
	}
}

void	positions(t_fil *fil)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	if (fil->nb == 0)
	{
		first_time(fil, x, y);
		return ;
	}
	new_piece(fil, x, y);
	free(fil->map2);
}
