/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   going_mid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 17:00:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/12 17:00:51 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

void	desc_right(t_fil *fil)
{
	int x;
	int	y;

	x = 0;
	while (x < fil->m_line + fil->p_line)
	{
		y = 0;
		while (y < fil->m_col + fil->p_col)
		{
			if (fitting(fil, x, y))
			{
				if ((x >= fil->high_x || y >= fil->high_y))
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

void	desc_left(t_fil *fil)
{
	int x;
	int	y;

	x = 0;
	while (x < fil->m_line + fil->p_line)
	{
		y = fil->m_col + fil->p_col;
		while (y > -fil->p_col)
		{
			if (fitting(fil, x, y))
			{
				if ((x >= fil->high_x || y <= fil->high_y))
				{
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y--;
		}
		x++;
	}
}

void	asc_right(t_fil *fil)
{
	int x;
	int	y;

	x = fil->m_line + fil->p_line;
	while (x > -fil->p_line)
	{
		y = 0;
		while (y < fil->m_col + fil->p_col)
		{
			if (fitting(fil, x, y))
			{
				if ((x <= fil->high_x || y >= fil->high_y))
				{
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y++;
		}
		x--;
	}
}

void	asc_left(t_fil *fil)
{
	int x;
	int	y;

	x = fil->m_line + fil->p_line;
	while (x > -fil->p_line)
	{
		y = fil->m_col + fil->p_col;
		while (y > -fil->p_col)
		{
			if (fitting(fil, x, y))
			{
				if ((x <= fil->high_x || y <= fil->high_y))
				{
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y--;
		}
		x--;
	}
}

int		which_direction(t_fil *fil)
{
	int result;

	result = 0;
	if (fil->dir == DESC_RIGHT)
		desc_right(fil);
	if (fil->dir == DESC_LEFT)
		desc_left(fil);
	if (fil->dir == ASC_RIGHT)
		asc_right(fil);
	if (fil->dir == ASC_LEFT)
		asc_left(fil);
	if (fil->dir == EDGE)
		edge(fil);
	if (fitting(fil, fil->high_x, fil->high_y))
	{
		printing(fil->high_x, fil->high_y);
		fil->high_x = 0;
		fil->high_y = 0;
		result = 1;
	}
	return (result);
}
