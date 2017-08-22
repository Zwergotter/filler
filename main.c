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
	fil->piece = NULL;
	fil->nb = 0;
	fil->start_opp = 0;
	fil->end_opp = 0;
	fil->p_line = 0;
	fil->p_col = 0;
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

void	finding_place(t_fil *fil)
{
	int	x;
	int y;

	y = -fil->p_line;
	x = -fil->p_col;
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

void	opp_pos(t_fil *fil)
{
	int i;

	i = -1;
	if (fil->nb == 0)
	{
		while (fil->map[++i])
		{
			if (fil->map[i] == fil->opp)
			{
				fil->start_opp = i;
				return ;
			}
		}
	}
	while (fil->map[++i])
	{
		if (fil->map[i] != fil->map2[i] && fil->map[i] == fil->opp)
			fil->end_opp = i;
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
		opp_pos(fil);
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
		free(fil->piece);
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
