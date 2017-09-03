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

void	init(t_fil *fil)
{
	char *line;
	int i;

	get_next_line(0, &line);
	fil->player = (line[10] == '1' ? 'O' : 'X');
	fil->opp = (line[10] == '1' ? 'X' : 'O');
	free(line);
	get_next_line(0, &line);
	ft_putstr_fd("line = ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	fil->m_line = ft_atoi(line + 8);
	i = 0;
	while (line[i + 9] != ' ')
		i++;
	fil->m_col = ft_atoi(line + i + 9);
	free(line);
	fil->map = NULL;
	fil->map2 = NULL;
	fil->piece = NULL;
	fil->nb = 0;
	fil->p_line = 0;
	fil->p_col = 0;
	fil->start_xopp = 0;
	fil->start_yopp = 0;
	fil->high_x = 0;
	fil->high_y = 0;
	fil->end_xopp = 0;
	fil->end_yopp = 0;
	fil->start_ply = 0;
	fil->end_ply = 0;
	fil->cur_line = 0;
	fil->cur_col = 0;
	fil->dir = EMPTY;
	fil->dir2 = EMPTY;
}

void	printing(int x, int y)
{
		ft_putnbr(x);
		ft_putchar(' ');
		ft_putnbr(y);
}

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
				if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_line || mv_y >= fil->m_col || fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->opp)
					place = 2;
				if (mv_x >= 0 && mv_y >= 0 && fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
					place++;
			}
			if (fil->piece[j + (i * fil->p_col)] == '.' && fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->opp)
				close++;
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	if (place == 1 && close)
	{
		// printing(x, y);
		ft_putstr_fd("\nSUCCESS", 2);
		return (close);
	}
	return (0);
}
int		close_to_opp(t_fil *fil)
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
				if (fil->nb_opp < result)
				{
					fil->nb_opp = result;
					fil->high_x = x;
					fil->high_y = y;
				}
			}
			y++;
		}
	}
	if (fil->nb_opp)
		printing(fil->high_x, fil->high_y);
	return (fil->nb_opp);
}

int		fitting(t_fil *fil, int x, int y)
{
	int	i;//ligne
	int j;//col
	int mv_x;
	int mv_y;
	int place;

	i = 0;
	mv_x = x;
	place = 0;
	while (i < fil->p_line)
	{
		mv_y = y;
		j = 0;
		while (j < fil->p_col)
		{
			if (fil->piece[j + (i * fil->p_col)] == '*')
			{
				if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_line || mv_y >= fil->m_col || fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->opp)
					place = 2;
				if (mv_x >= 0 && mv_y >= 0 && fil->map[mv_y + 4 + mv_x * (fil->m_col + 4)] == fil->player)
					place++;
			}
			mv_y++;
			j++;
		}
		mv_x++;
		i++;
	}
	if (place == 1)
		return (1);
	return (0);
}

int	encircle(t_fil *fil)
{
	int i;
	int j;
	int x;
	int y;
	int pos;

	i = 0;
	j = 0;
	x = fil->end_xopp ? fil->end_xopp : fil->start_xopp;
	y = fil->end_yopp ? fil->end_yopp : fil->start_yopp;
	pos = y + 4 + x * (fil->m_col + 4);
	while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && j + y < fil->m_col + fil->p_col)
	{
		i = 0;
		while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && i + x < fil->m_line+ fil->p_line)
		{
			if (fitting(fil, x, y))
			{
				printing(x, y);
				ft_putstr_fd("\nIN CASE1", 2);
				return (1);
			}
			if (fitting(fil, x + i, y))
			{
				printing(x + i, y);
				ft_putstr_fd("\nIN CASE2", 2);
				return (1);
			}
			if (fitting(fil, x - i, y))
			{
				printing(x - i, y);
				ft_putstr_fd("\nIN CASE3", 2);
				return (1);
			}
			if (fitting(fil, x, y + j))
			{
				printing(x, y + j);
				ft_putstr_fd("\nIN CASE4", 2);
				return (1);
			}
			if (fitting(fil, x, y - j))
			{
				printing(x, y - j);
				ft_putstr_fd("\nIN CASE5", 2);
				return (1);
			}
			if (fitting(fil, x + i, y + j))
			{
				printing(x + i, y + j);
				ft_putstr_fd("\nIN CASE6", 2);
				return (1);
			}
			if (fitting(fil, x + i, y - j))
			{
				printing(x + i, y - j);
				ft_putstr_fd("\nIN CASE7", 2);
				return (1);
			}
			if (fitting(fil, x - i, y + j))
			{
				printing(x - i, y + j);
				ft_putstr_fd("\nIN CASE8", 2);
				return (1);
			}
			if (fitting(fil, x - i, y - j))
			{
				printing(x - i, y - j);
				ft_putstr_fd("\nIN CASE9", 2);
				return (1);
			}
			i++;
			pos = y + j + 4 + ((x + i) * (fil->m_col + 4));
		}
		j++;
		pos = y + j + 4 + ((x + i) * (fil->m_col + 4));
	}
	return (0);
}

int	trying_to_fit(t_fil *fil)
{
	int x;
	int	y;
	int result;

	x = 0;
	y = 0;
	result = 0;
	ft_putstr_fd("\nHERE", 2);
	if (fil->dir == DESC_RIGHT)
	{
		ft_putstr_fd("\nDESC_RIGHT", 2);
		while (x < fil->m_line + fil->p_line)
		{
			y = 0;
			while (y < fil->m_col + fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (x > fil->high_x || y > fil->high_y)
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
		ft_putstr_fd("\nDESC_LEFT)", 2);
		while (x < fil->m_line + fil->p_line)
		{
			y = fil->m_col + fil->p_col;
			while (y > -fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (x > fil->high_x || y < fil->high_y)
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
		ft_putstr_fd("\nASC_RIGHT", 2);
		while (x > -fil->p_line)
		{
			y = 0;
			while (y < fil->m_col + fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (x < fil->high_x || y > fil->high_y)
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
		ft_putstr_fd("\nASC_LEFT", 2);
		while (x > -fil->p_line)
		{
			y = fil->m_col + fil->p_col;
			while (y > -fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (x < fil->high_x && y < fil->high_y)
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
	if(fil->dir == EDGE)
	{
		ft_putstr_fd("\nEDGE", 2);
		x = fil->m_line / 2 - fil->p_line;		
		// while (fil->high_y == 0 && x < fil->m_line / 2 + fil->p_line)
		// {
		// 	y = fil->m_col / 2;
		// 	while (fil->high_y == 0 && y < fil->m_col + fil->p_col)
		while (x < fil->m_line / 2 + fil->p_line)
		{
			y = fil->m_col / 2;
			while (y < fil->m_col + fil->p_col)
			{
				if (fitting(fil, x, y))
				{
					if (y > fil->high_y)
					{
						ft_putstr_fd("\nPLUS", 2);
						fil->high_x = x;
						fil->high_y = y;
					}
				}
				y++;
			}
			x++;
		}
		if (!fitting(fil, fil->high_x, fil->high_y))
		{
			x = fil->m_line / 2 - fil->p_line;
			fil->high_y = fil->m_col;
			// while (fil->high_y == fil->m_col && x < fil->m_line / 2 + fil->p_line)
			// {
			// 	y = fil->m_col / 2;
			// 	while (fil->high_y == fil->m_col && y > -fil->p_col)
			while (x < fil->m_line / 2 + fil->p_line)
			{
				y = fil->m_col / 2;
				while (y > -fil->p_col)
				{
					if (fitting(fil, x, y))
					{
						if (y < fil->high_y)
						{
							ft_putstr_fd("\nEDGE minus", 2);
							fil->high_x = x;
							fil->high_y = y;
							break;
						}
					}
					y--;
				}
				x++;
			}
		}
	}
	if (fitting(fil, fil->high_x, fil->high_y))
	{
		ft_putstr_fd("\nFIRST", 2);
		printing(fil->high_x, fil->high_y);
		fil->high_x = 0;
		fil->high_y = 0;
		result = 1;
	}
	return (result);
}

void	finding_place(t_fil *fil)
{
	int	x;
	int y;
	int result;

	x = -fil->p_line;
	y = -fil->p_col;
	result = 0;
	result = trying_to_fit(fil);
	// result = result ? result : encircle(fil);
	result = result ? result : close_to_opp(fil);
	// result = close_to_opp(fil);
	result = result ? result : encircle(fil);
	if (!result)
	{
		x = -fil->p_line;
		while (!(fitting(fil, x, y)) && ++x < fil->m_line)
		{
			y = -fil->p_col;
			while (!(fitting(fil, x, y)) && y < fil->m_col)
				y++;
		}
		ft_putstr_fd("\nNOT", 2);
	}
	if (!result && fitting(fil, x, y))
		printing(x, y);
	ft_putchar('\n');
	fil->nb_opp = 0;
}

int	directions(t_fil *fil, int x, int y, int i)
{
	// ft_putstr_fd("\nIN DIRECTIONS\n", 2);
	if (x < (fil->m_line / 2) + 1 && y < (fil->m_col / 2) + 1)
		fil->dir2 = DESC_RIGHT;
	if (x < (fil->m_line / 2) + 1 && y > (fil->m_col / 2) - 1)
		fil->dir2 = DESC_LEFT;
	if (x > (fil->m_line / 2) - 1 && y < (fil->m_col / 2) + 1)
		fil->dir2 = ASC_RIGHT;
	if (x > (fil->m_line / 2) - 1 && y > (fil->m_col / 2) - 1)
		fil->dir2 = ASC_LEFT;
	fil->cur_line = x;
	fil->cur_col = y;
	if (!fil->nb)
		fil->dir = fil->dir2;
	if (fil->dir != fil->dir2)
		fil->dir2 = EDGE;
	ft_putstr_fd("\nDir is ", 2);
	ft_putnbr_fd(fil->dir, 2);
	ft_putstr_fd(" Dir2 is ", 2);
	ft_putnbr_fd(fil->dir2, 2);
	ft_putstr_fd(" \n", 2);
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
			y++;
		}
		y = 0;
		x++;
	}
	free(fil->map2);
}

int		main(void)
{
	t_fil	*fil;
	char	*line;
	int 	i;

	if (!(fil = malloc(sizeof(t_fil))))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit (0);
	}
	init(fil);
	while (1)
	{
		if (!get_next_line(0, &line)) // pas en option gros
			break ;
		if (fil->nb)
			get_next_line(0, &line);
		fil->map = ft_strdup("");
		while ((i = get_next_line(0, &line)) > 0 && line[0] != 'P')
			fil->map = ft_strjoinfree(fil->map, line, 3);
		positions(fil);
		fil->p_line = ft_atoi(line + 6);
		i = 0;
		while (line[i + 7] != ' ')
			i++;
		fil->p_col = ft_atoi(line + i + 7);
		free(line);
		i = 0;
		fil->piece = ft_strdup("");
		while (i++ < fil->p_line && get_next_line(0, &line) > 0)
			fil->piece = ft_strjoinfree(fil->piece, line, 3);
		finding_place(fil);
		// free(fil->map);
		fil->map2 = fil->map;
		free(fil->piece);
		fil->nb = 1;
	}
	free(fil);
	return (0);
}
