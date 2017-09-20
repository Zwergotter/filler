/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   going_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:46:02 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 17:55:53 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

void	edge2(t_fil *fil, int x, int y)
{
	x = (fil->m_line / 2) - fil->p_line;
	while (x < fil->m_line / 2 + fil->p_line)
	{
		y = fil->m_col / 2;
		while (y < fil->m_col + fil->p_col)
		{
			if (fitting(fil, x, y) == 1)
			{
				if (y > fil->high_y)
				{
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y++;
		}
		x++;
	}
}

void	edge(t_fil *fil)
{
	int x;
	int y;

	x = fil->m_line / 2 - fil->p_line;
	fil->high_y = fil->m_col;
	while (x < fil->m_line / 2 + fil->p_line)
	{
		y = fil->m_col / 2;
		while (y > -fil->p_col)
		{
			if (fitting(fil, x, y) == 1)
			{
				if (y < fil->high_y)
				{
					fil->high_x = x;
					fil->high_y = y;
					// break;
				}
			}
			y--;
		}
		x++;
	}
	if (fitting(fil, fil->high_x, fil->high_y) != 1)
		edge2(fil, x, y);
}
