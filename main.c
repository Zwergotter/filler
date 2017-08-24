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
	fil->m_line = ft_atoi(line + 8);
	i = 0;
	while (line[i + 9] != ' ')
		i++;
	fil->m_col = ft_atoi(line + i + 9);
	free(line);
	fil->map = NULL;
	fil->piece = NULL;
	fil->nb = 0;
	fil->start_opp = 0;
	fil->end_opp = 0;
	fil->start_ply = 0;
	fil->end_ply = 0;
	fil->p_line = 0;
	fil->p_col = 0;
	fil->cur_col = 0;
	fil->cur_line = 0;
	fil->dir = EMPTY;
	fil->dir2 = EMPTY;
}

int		fitting(t_fil *fil, int x, int y)
{
	int	i;
	int j;
	int mv_x;
	int mv_y;
	int place;

	j = 0;
	mv_x = x;
	place = 0;
	while (j < fil->p_col)
	{
		mv_y = y;
		i = 0;
		while (i < fil->p_line)
		{
			if (fil->piece[j + (i * fil->p_col)] == '*')
			{
				if (mv_x < 0 || mv_y < 0 || mv_x >= fil->m_col || mv_y >= fil->m_line || fil->map[mv_x + 4 + mv_y * (fil->m_col + 4)] == fil->opp)
					place = 2;
				if (mv_x >= 0 && mv_y >= 0 && fil->map[mv_x + 4 + mv_y * (fil->m_col + 4)] == fil->player)
					place++;
			}
			mv_y++;
			i++;
		}
		mv_x++;
		j++;
	}
	if (place == 1)
		return (1);
	return (0);
}

int	trying_to_fit(t_fil *fil)
{
	int x;
	int	y;
	int result;

	x = fil->cur_col;
	y = fil->cur_line;
	result = 1;
	if (fil->dir == DESC_RIGHT)
	{
		while (!(fitting(fil, y, x)) && y < fil->m_line && x < fil->m_col)
		{
			++x;
			if (!(fitting(fil, y, x)) && x < fil->m_col)
				y++;
		}
	}
	if (fil->dir == DESC_LEFT)
	{
		while (!(fitting(fil, y, x)) && y < fil->m_line && x > -fil->p_col)
		{
			--x;
			if (!(fitting(fil, y, x)) && x > -fil->p_col)
				y++;
		}
	}
	if (fil->dir == ASC_RIGHT)
	{
		while (!(fitting(fil, y, x)) && y > -fil->p_line && x < fil->m_col)
		{
			++x;
			if (!(fitting(fil, y, x)) && x < fil->m_col)
				y--;
		}
	}
	if (fil->dir == ASC_LEFT)
	{
		while (!(fitting(fil, y, x)) && y > -fil->p_line && x > -fil->p_col)
		{
			--x;
			if (!(fitting(fil, y, x)) && x > -fil->p_col)
				y--;
		}
	}
	if (fitting(fil, y, x))
	{
		ft_putnbr(x);
		ft_putchar(' ');
		ft_putnbr(y);
		result = 0;;
	}
	return (result);
}

void	finding_place(t_fil *fil)
{
	int x;
	int	y;
	int result;

	x = -fil->p_line;
	y = -fil->p_col;
	result = 1;
	result = trying_to_fit(fil);
	while (result && !(fitting(fil, y, x)) && ++x < fil->m_line)
	{
		y = -fil->p_col;
		while (!(fitting(fil, y, x)) && y < fil->m_col)
			y++;
	}
	if (result == 1 && fitting(fil, y, x))
	{
		ft_putnbr(x);
		ft_putchar(' ');
		ft_putnbr(y);
	}
	ft_putchar('\n');
}

int	directions(t_fil *fil, int x, int y, int i)
{
	ft_putstr_fd("\nIN DIRECTIONS\n", 2);

	if (y <= fil->m_line / 2 && x <= fil->m_col / 2)
		fil->dir2 = DESC_RIGHT;
	if (y <= fil->m_line / 2 && x > fil->m_col / 2)
		fil->dir2 = DESC_LEFT;
	if (y > fil->m_line / 2 && x <= fil->m_col / 2)
		fil->dir2 = ASC_RIGHT;
	if (y > fil->m_line / 2 && x > fil->m_col / 2)
		fil->dir2 = ASC_LEFT;
	fil->cur_col = x;
	fil->cur_line = y;
	if (!fil->nb)
		fil->dir = fil->dir2;
	if (fil->dir != fil->dir2)
		fil->dir2 = EMPTY;
	ft_putstr_fd("\nDir is ", 2);
	ft_putnbr_fd(fil->dir, 2);
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
		while (fil->map[x + 4 + (y * (fil->m_col + 4))] && y < fil->m_line)
		{
			while (fil->map[x + 4 + (y * (fil->m_col + 4))] && x < fil->m_col)
			{
				i = x + 4 + (y * (fil->m_col + 4));
				if (fil->map[i] == fil->opp && !fil->start_opp)
					fil->start_opp = i;
				if (fil->map[i] == fil->player && !fil->start_ply)
					fil->start_ply = directions(fil, x, y, i);
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
			fil->end_opp = i;
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->player)
			fil->end_ply = directions(fil, x, y, i);
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
	int 	nb;

	nb = 0;
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
		if (nb)
			get_next_line(0, &line);
		fil->nb = nb;
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
		free(fil->piece);
		// i = open("lili", O_WRONLY | O_APPEND);
		// ft_putstr_fd(fil->map, i);
		// ft_putstr_fd("\n\n", i);
		// close(i);
		fil->map2 = fil->map;
		nb = 1;
	}
	free(fil);
	return (0);
}
