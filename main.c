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

int		close_to_opp(t_fil *fil, int x, int y)
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
		printing(x, y);
		ft_putstr_fd("\nSUCCESS", 2);
		return (1);
	}
	return (0);
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
	if (fil->map[y + 4 + (x * (fil->m_col + 4))] && fitting(fil, x, y))
	{
		printing(x, y);
		ft_putstr_fd("\nIN CASE1", 2);
		return (1);
	}
	while (fil->map[y + 4 + ((x + i) * (fil->m_col + 4))] || fil->map[y + 4 + ((x - i) * (fil->m_col + 4))]
		|| fil->map[y + 4 + ((x + i) * (fil->m_col + 4)) + (fil->m_col + 4)] || fil->map[y + 4 + ((x - i) * (fil->m_col + 4)) + (fil->m_col + 4)])
	{
		if (fil->map[y + 4 + ((x + i) * (fil->m_col + 4))] && fitting(fil, x + i, y))
		{
			printing(x + i, y);
			ft_putstr_fd("\nIN CASE2", 2);
			return (1);
		}
		if (fil->map[y + 4 + ((x - i) * (fil->m_col + 4))] && fitting(fil, x - i, y))
		{
			printing(x - i, y);
			ft_putstr_fd("\nIN CASE3", 2);
			return (1);
		}
		j = -1;
		while (++j <= i)
		{
			if (fil->map[y + j + 4 + (x * (fil->m_col + 4))] && fitting(fil, x, y + j))
			{
				printing(x, y + j);
				ft_putstr_fd("\nIN CASE4", 2);
				return (1);
			}
			if (fil->map[y - j + 4 + (x * (fil->m_col + 4))] && fitting(fil, x, y - j))
			{
				printing(x, y - j);
				ft_putstr_fd("\nIN CASE5", 2);
				return (1);
			}
			if (fil->map[y + j + 4 + ((x + i) * (fil->m_col + 4))] && fitting(fil, x + i, y + j))
			{
				printing(x + i, y + j);
				ft_putstr_fd("\nIN CASE6", 2);
				return (1);
			}
			if (fil->map[y - j + 4 + ((x + i) * (fil->m_col + 4))] && fitting(fil, x + i, y - j))
			{
				printing(x + i, y - j);
				ft_putstr_fd("\nIN CASE7", 2);
				return (1);
			}
			if (fil->map[y + j + 4 + ((x - i) * (fil->m_col + 4))] && fitting(fil, x - i, y + j))
			{
				printing(x - i, y + j);
				ft_putstr_fd("\nIN CASE8", 2);
				return (1);
			}
			if (fil->map[y - j + 4 + ((x - i) * (fil->m_col + 4))] && fitting(fil, x - i, y - j))
			{
				printing(x - i, y - j);
				ft_putstr_fd("\nIN CASE9", 2);
				return (1);
			}
		}
		i++;
	}
	ft_putstr_fd("\nNOPE", 2);
	return (0);
}

// int	encircle(t_fil *fil)
// {
// 	int i;
// 	int j;
// 	int x;
// 	int y;
// 	int pos;

// 	i = 0;
// 	j = 0;
// 	x = fil->end_xopp ? fil->end_xopp : fil->start_xopp;
// 	y = fil->end_yopp ? fil->end_yopp : fil->start_yopp;
// 	pos = y + 4 + x * (fil->m_col + 4);
// 	while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && j + fil->end_yopp < fil->m_col)
// 	{
// 		i = 0;
// 		while ((fil->map[pos] || fil->map[pos + (fil->m_col + 4)]) && i + fil->end_xopp < fil->m_line)
// 		{
// 			if (fitting(fil, x, y))
// 			{
// 				printing(x, y);
// 				ft_putstr_fd("\nIN CASE1", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x + i, y))
// 			{
// 				printing(x + i, y);
// 				ft_putstr_fd("\nIN CASE2", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x, y + j))
// 			{
// 				printing(x, y + j);
// 				ft_putstr_fd("\nIN CASE3", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x + i, y + j))
// 			{
// 				printing(x + i, y + j);
// 				ft_putstr_fd("\nIN CASE4", 2);
// 				return (1);
// 			}
// 			i++;
// 			pos = y + j + 4 + ((x + i) * (fil->m_col + 4));
// 		}
// 		j++;
// 		pos = y + j + 4 + ((x + i) * (fil->m_col + 4));
// 	}
// 	pos = y + 4 + x * (fil->m_col + 4);
// 	while ((fil->map[pos] || fil->map[pos - (fil->m_col + 4)]) && fil->end_yopp - j > -fil->p_col)
// 	{
// 		i = 0;
// 		while ((fil->map[pos] || fil->map[pos - (fil->m_col + 4)]) && fil->end_xopp - i > -fil->p_line)
// 		{
// 			if (fitting(fil, x, y))
// 			{
// 				printing(x, y);
// 				ft_putstr_fd("\nIN CASE5", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x + i, y))
// 			{
// 				printing(x + i, y);
// 				ft_putstr_fd("\nIN CASE6", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x, y + j))
// 			{
// 				printing(x, y + j);
// 				ft_putstr_fd("\nIN CASE7", 2);
// 				return (1);
// 			}
// 			if (fitting(fil, x + i, y + j))
// 			{
// 				printing(x + i, y + j);
// 				ft_putstr_fd("\nIN CASE8", 2);
// 				return (1);
// 			}
// 			i--;
// 			pos = y + j + 4 + (x + i ) * (fil->m_col + 4);
// 		}
// 		j--;
// 		pos = y + j + 4 + (x + i ) * (fil->m_col + 4);
// 	}
// 	ft_putstr_fd("\nNOPE", 2);
// 	return (0);
// }

int	trying_to_fit(t_fil *fil)
{
	int x;
	int	y;
	int result;

	x = fil->cur_line;
	y = fil->cur_col;
	result = 0;
	if (fil->dir == DESC_RIGHT)
	{
		while (!(fitting(fil, x, y)) && x < fil->m_line && y < fil->m_col)
		{
			++y;
			if (!(fitting(fil, x, y)) && y < fil->m_col)
				x++;
		}
	}
	if (fil->dir == DESC_LEFT)
	{
		while (!(fitting(fil, x, y)) && x < fil->m_line && y > -fil->p_col)
		{
			--y;
			if (!(fitting(fil, x, y)) && y > -fil->p_col)
				x++;
		}
	}
	if (fil->dir == ASC_RIGHT)
	{
		while (!(fitting(fil, x, y)) && x > -fil->p_line && y < fil->m_col)
		{
			++y;
			if (!(fitting(fil, x, y)) && y < fil->m_col)
				x--;
		}
	}
	if (fil->dir == ASC_LEFT)
	{
		while (!(fitting(fil, x, y)) && x > -fil->p_line && y > -fil->p_col)
		{
			--y;
			if (!(fitting(fil, x, y)) && y > -fil->p_col)
				x--;
		}
	}
	if (fitting(fil, x, y))
	{
		printing(x, y);
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
	if (fil->dir == fil->dir2 || !fil->nb)
		result = trying_to_fit(fil);
	result = result ? result : encircle(fil);
	if (!result)
	{
		while (!(result = close_to_opp(fil, x, y)) && ++x < fil->m_line)
		{
			y = -fil->p_col;
			while (!(result = close_to_opp(fil, x, y)) && y < fil->m_col)
				y++;
		}
	}
	if (!result)
	{
		x = -fil->p_line;
		while (!(fitting(fil, x, y)) && ++x < fil->m_line)
		{
			y = -fil->p_col;
			while (!(fitting(fil, x, y)) && y < fil->m_col)
				y++;
		}
	}
	if (!result && fitting(fil, x, y))
		printing(x, y);
	ft_putchar('\n');
}

int	directions(t_fil *fil, int x, int y, int i)
{
	// ft_putstr_fd("\nIN DIRECTIONS\n", 2);

	// if (!fil->nb || (fil->m_line > 25 && fil->m_col > 25))
	// {
		if (x <= fil->m_line / 2 && y <= fil->m_col / 2)
			fil->dir2 = DESC_RIGHT;
		if (x <= fil->m_line / 2 && y > fil->m_col / 2)
			fil->dir2 = DESC_LEFT;
		if (x > fil->m_line / 2 && y <= fil->m_col / 2)
			fil->dir2 = ASC_RIGHT;
		if (x > fil->m_line / 2 && y > fil->m_col / 2)
			fil->dir2 = ASC_LEFT;
	// }
	// else
	// {
	// 	if (fil->dir == DESC_RIGHT && x <= fil->m_line - 2 && y <= fil->m_col - 2)
	// 		fil->dir2 = DESC_RIGHT;
	// 	if (fil->dir == DESC_LEFT && x <= fil->m_line - 2 && y > 2)
	// 		fil->dir2 = DESC_LEFT;
	// 	if (fil->dir ==  ASC_RIGHT && x > 2 && y <= fil->m_col - 2)
	// 		fil->dir2 = ASC_RIGHT;
	// 	if (x > 2 && y > 2)
	// 		fil->dir2 = ASC_LEFT;
	// 		ft_putstr_fd("\nDir is ", 2);
	// ft_putnbr_fd(fil->dir, 2);
	// ft_putstr_fd(" \n", 2);
	// }
	fil->cur_line = x;
	fil->cur_col = y;
	if (!fil->nb)
		fil->dir = fil->dir2;
	if (fil->dir != fil->dir2)
		fil->dir2 = EMPTY;
	// ft_putstr_fd("\nDir is ", 2);
	// ft_putnbr_fd(fil->dir, 2);
	// ft_putstr_fd(" \n", 2);
	fil->dir = fil->dir2;
	fil->dir2 = EMPTY;
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
		while (fil->map[x + 4 + (y * (fil->m_col + 4))] && y < fil->m_line)
		{
			while (fil->map[x + 4 + (y * (fil->m_col + 4))] && x < fil->m_col)
			{
				i = x + 4 + (y * (fil->m_col + 4));
				if (fil->map[i] == fil->opp && !fil->start_xopp)
					{
						fil->start_xopp = x;
						fil->start_yopp = y;
					}
				if (fil->map[i] == fil->player && !fil->start_ply)
					fil->start_ply = directions(fil, x, y, i);
					// fil->start_ply = i;
				x++;
			}
			x = 0;
			y++;
		}
		return ;
	}
	while (fil->map[x + 4 + (y * (fil->m_col + 4))] && y < fil->m_line)
	{
		while (fil->map[x + 4 + (y * (fil->m_col + 4))] && x < fil->m_col)
		{
			i = x + 4 + (y * (fil->m_col + 4));
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->opp)
			{
				fil->end_xopp = x;
				fil->end_yopp = y;
			}
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->player)
			fil->end_ply = directions(fil, x, y, i);
			// fil->end_ply = i;
			x++;
		}
		x = 0;
		y++;
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
