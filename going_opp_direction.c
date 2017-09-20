/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   going_opp_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:31:35 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 16:31:37 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int	looking_for(t_fil *fil, int i, int j)
{
	int x;
	int y;

	x = fil->end_xop ? fil->end_xop : fil->start_xop;
	y = fil->end_yop ? fil->end_yop : fil->start_yop;
	if (fitting(fil, x, y) == 1)
		return (printing(x, y));
	if (fitting(fil, x - i, y) == 1)
		return (printing(x - i, y));
	if (fitting(fil, x - i, y + j) == 1)
		return (printing(x - i, y + j));
	if (fitting(fil, x - i, y - j) == 1)
		return (printing(x - i, y - j));
	if (fitting(fil, x + i, y) == 1)
		return (printing(x + i, y));
	if (fitting(fil, x, y + j) == 1)
		return (printing(x, y + j));
	if (fitting(fil, x, y - j) == 1)
		return (printing(x, y - j));
	if (fitting(fil, x + i, y + j) == 1)
		return (printing(x + i, y + j));
	if (fitting(fil, x + i, y - j) == 1)
		return (printing(x + i, y - j));
	return (0);
}

int	going_opp_direction(t_fil *fil)
{
	int i;
	int j;
	int x;
	int y;
	int pos;

	j = 0;
	x = fil->end_xop ? fil->end_xop : fil->start_xop;
	y = fil->end_yop ? fil->end_yop : fil->start_yop;
	pos = y + 4 + x * (fil->m_col + 4);
	while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && j + y <
		fil->m_col + fil->p_col)
	{
		i = 0;
		while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && i + x <
			fil->m_line + fil->p_line)
		{
			if (looking_for(fil, i, j))
				return (1);
			i++;
		}
		j++;
		pos = y + j + 4 + ((x + i) * (fil->m_col + 4));
	}
	return (0);
}
