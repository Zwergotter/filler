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

// void	init(t_fil *fil, int fd)
// {
// 	char *line;
// 	int i;

// 	get_next_line(fd, &line);
// 	fil->player = (line[10] == '1' ? 'O' : 'X');
// 	free(line);
// 	get_next_line(fd, &line);
// 	fil->m_col = ft_atoi(line + 8);
// 	i = 0;
// 	while (line[i + 9] != ' ')
// 		i++;
// 	fil->m_line = ft_atoi(line + i + 9);
// 	free(line);
// 	fil->map = NULL;
// 	fil->piece = NULL;
// 	fil->p_line = 0;
// 	fil->p_col = 0;
// }

void	init(t_fil *fil)
{
	char *line;
	int i;

	get_next_line(0, &line);
	fil->player = (line[10] == '1' ? 'O' : 'X');
	fil->opp = (line[10] == '1' ? 'X' : 'O');
	free(line);
	get_next_line(0, &line);
	// ft_putstr_fd("line = ", 2);
	// ft_putstr_fd(line, 2);
	// ft_putstr_fd("\n", 2);
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
	fil->mid = 0;
	fil->top_left = 0;
	fil->top_right = 0;
	fil->bot_left = 0;
	fil->bot_right = 0;	
	fil->dir = EMPTY;
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

// void	trying_to_fit(t_fil *fil, int pos)
// {
// 	if (pos )
// }

void	finding_place(t_fil *fil)
{
	int	x;
	int y;
	int pos;

	y = -fil->p_line;
	x = -fil->p_col;
	pos = (fil->end_ply ? fil->end_ply : fil->start_ply);
	// trying_to_fit(fil, pos);
	while (!(fitting(fil, x, y)) && ++y < fil->m_line)
	{
		x = -fil->p_col;
		while (!(fitting(fil, x, y)) && x < fil->m_col)
			x++;
	}
	if (fitting(fil, x, y))
	{
		ft_putnbr(y);
		ft_putchar(' ');
		ft_putnbr(x);
	}
	ft_putchar('\n');
}

// void	directions(t_fil *fil, int x, int y, int i)
// {
// 	fil->start_ply = i;

// 	if ()
// }

void	positions(t_fil *fil)
{
	int i;
	int	x;
	int y;

	i = -1;
	x = -1;
	y = 0;
	if (fil->nb == 0)
	{
		while((fil->map[++y + 4 + (y * (fil->m_line + 4))] && y <= fil->m_col))
		{
			x = -1;
			while (fil->map[++x + 4 + (y * (fil->m_line + 4))] && x < fil->m_line)
			{
				i = x + 4 + (y * (fil->m_line + 4));
				if (fil->map[i] == fil->opp && !fil->start_opp)
					fil->start_opp = i;
				if (fil->map[i] == fil->player && !fil->start_ply)
					fil->start_ply = i;
					// directions(fil, x, y, i);
			}
			fil->mid = ft_strlen(fil->map) / 2;
			fil->top_left = (2 * 4 + fil->m_col);
			fil->top_right = fil->top_left + fil->m_col - 1;
			fil->bot_left = (fil->m_line * (fil->m_col + 4)) - fil->m_col;
			fil->bot_right = fil->bot_left + fil->m_col - 1;
			return ;
		}
		// while (fil->map[++i])
		// {
		// 	if (fil->map[i] == fil->opp && !fil->start_opp)
		// 		fil->start_opp = i;
		// 	if (fil->map[i] == fil->player && !fil->start_ply)
		// 		fil->start_ply = i;
		// }
		// fil->mid = ft_strlen(fil->map) / 2;
		// fil->top_left = (2 * 4 + fil->m_col);
		// fil->top_right = fil->top_left + fil->m_col - 1;
		// fil->bot_left = (fil->m_line * (fil->m_col + 4)) - fil->m_col;
		// fil->bot_right = fil->bot_left + fil->m_col - 1;
		// return ;
	}
	while (fil->map[++i])
	{
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->opp)
			fil->end_opp = i;
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->player)
			fil->end_ply = i;
	}
	// ft_putstr_fd("\nStart pos opp is ", 2);
	// ft_putnbr_fd(fil->start_opp, 2);
	// ft_putstr_fd(" and end is ", 2);
	// ft_putnbr_fd(fil->end_opp, 2);
	// ft_putstr_fd("\nStart pos ply is  ", 2);
	// ft_putnbr_fd(fil->start_ply, 2);
	// ft_putstr_fd(" and end is ", 2);
	// ft_putnbr_fd(fil->end_ply, 2);
	// ft_putstr_fd(" \n", 2);
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

// int		main(int argc, char **argv)
// {
// 	t_fil	*fil;
// 	char	*line;
// 	int		fd;
// 	int 	i;

// 	if (argc != 2)
// 		return (0);
// 	fd = open(argv[1], O_RDONLY);
// 	if (!(fil = malloc(sizeof(t_fil))))
// 	{
// 		ft_putstr_fd("Memory allocation failed", 2);
// 		exit (0);
// 	}
// 	init(fil, fd);
// 	fil->map = ft_strdup("");
// 	while (get_next_line(fd, &line) > 0 && line[0] != 'P')
// 		fil->map = ft_strjoinfree(fil->map, line, 3);
// 	// ft_putstr("\nWe are this player: ");
// 	// ft_putchar(fil->player);
// 	// ft_putstr("\nLine is ");
// 	// ft_putnbr(fil->m_line);
// 	// ft_putstr(" and col is ");
// 	// ft_putnbr(fil->m_col);
// 	fil->p_col = ft_atoi(line + 6);
// 	i = 0;
// 	while (line[i + 7] != ' ')
// 		i++;
// 	fil->p_line = ft_atoi(line + i + 7);
// 	free(line);
// 	fil->piece = ft_strdup("");
// 	while (get_next_line(fd, &line) > 0)
// 		fil->piece = ft_strjoinfree(fil->piece, line, 3);
// 	// ft_putstr("\nLine is ");
// 	// ft_putnbr(fil->p_line);
// 	// ft_putstr(" and col is ");
// 	// ft_putnbr(fil->p_col);
// 	// ft_putstr("\nMap saved is: \n");
// 	// ft_putstr(fil->piece);
// 	finding_place(fil);
// 	close(fd);
// 	free(fil->map);
// 	free(fil->piece);
// 	free(fil);
// 	return (0);
// }
