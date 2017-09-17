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
// #include <fcntl.h>

int	trying_to_fit(t_fil *fil)
{
	int x;
	int	y;
	int result;

	x = 0;
	y = 0;
	result = 0;
	if (fil->dir == DESC_RIGHT)
	{
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
	if (fil->dir == DESC_LEFT)
	{
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
	if (fil->dir == ASC_RIGHT)
	{
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
	if (fil->dir == ASC_LEFT)
	{
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
	if (fil->dir == EDGE)
	{
		x = fil->m_line / 2 - fil->p_line;
		fil->high_y = fil->m_col;
		while (x < fil->m_line / 2 + fil->p_line)
		{
			y = fil->m_col / 2;
			while (y > -fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (y < fil->high_y)
					{
						fil->high_x = x;
						fil->high_y = y;
						break;
					}
				}
				y--;
			}
			x++;
		}
		if (!fitting(fil, fil->high_x, fil->high_y))
		{
			x = (fil->m_line / 2) - fil->p_line;
			while (x < fil->m_line / 2 + fil->p_line)
			{
				y = fil->m_col / 2;
				while (y < fil->m_col + fil->p_col)
				{
					if (fitting(fil, x, y))
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
	}
	if (fitting(fil, fil->high_x, fil->high_y))
	{
		printing(fil->high_x, fil->high_y);
		fil->high_x = 0;
		fil->high_y = 0;
		result = 1;
	}
	return (result);
}
