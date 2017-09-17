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

void	touching(t_fil *fil, int x, int y)
{
	char c;

	c = (fil->map[y + 4 + (x * (fil->m_col + 4))] == fil->player ? fil->opp : fil->player);
	if (fil->map[y + 4 + ((x + 1) * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 + ((x - 1) * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 + 1 + (x * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 - 1 + (x * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 + 1 + ((x + 1) * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 + 1 + ((x - 1) * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 - 1 + ((x + 1) * (fil->m_col + 4))] == c)
		fil->touch++;
	if (fil->map[y + 4 - 1 + ((x - 1) * (fil->m_col + 4))] == c)
		fil->touch++;
}

int	directions(t_fil *fil, int x, int y, int i)
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
		fil->start_xopp = x;
		fil->start_yopp = y;
		fil->dir = fil->dir2;
	}
	if (fil->dir != fil->dir2 && (fil->m_col < 20 || fil->m_line < 20) 
		&& (fil->start_xply > fil->start_xopp || fil->start_yply > fil->start_yopp))
		fil->dir2 = EDGE;
	fil->dir = fil->dir2;
	return (i);
}

void	positions(t_fil *fil)
{
	int i;
	int	x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	if (fil->nb == 0)
	{
		while (x < fil->m_line && fil->map[y + 4 + (x * (fil->m_col + 4))])
		{
			while (y < fil->m_col && fil->map[y + 4 + (x * (fil->m_col + 4))])
			{
				i = y + 4 + (x * (fil->m_col + 4));
				if (fil->map[i] == fil->opp && !fil->start_xopp)
				{
					fil->start_xopp = x;
					fil->start_yopp = y;
				}
				if (fil->map[i] == fil->player && !fil->start_ply)
					fil->start_ply = directions(fil, x, y, i);
				if ((fil->map[i] == fil->player || fil->map[i] == fil->opp) && !fil->touch)
					touching(fil, x, y);
				y++;
			}
			y = 0;
			x++;
		}
		return ;
	}
	while (x < fil->m_line && fil->map[y + 4 + (x * (fil->m_col + 4))])
	{
		while (y < fil->m_col && fil->map[y + 4 + (x * (fil->m_col + 4))])
		{
			i = y + 4 + (x * (fil->m_col + 4));
			if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->opp)
			{
				fil->end_xopp = x;
				fil->end_yopp = y;
			}
			if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->player)
				fil->end_ply = directions(fil, x, y, i);
			if ((fil->map[i] == fil->player || fil->map[i] == fil->opp) && !fil->touch)
				touching(fil, x, y);
			y++;
		}
		y = 0;
		x++;
	}
	free(fil->map2);
}