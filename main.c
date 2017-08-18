/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:11:38 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/17 15:11:41 by edeveze          ###   ########.fr       */
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
	free(line);
	get_next_line(0, &line);
	fil->m_col = ft_atoi(line + 8);
	i = 0;
	while (line[i + 9] != ' ')
		i++;
	fil->m_line = ft_atoi(line + i + 9);
	free(line);
	fil->map = NULL;
	fil->piece = NULL;
	fil->p_line = 0;
	fil->p_col = 0;
}

int		fitting(t_fil *fil, int x, int y)
{
	int	i;
	int j;
	int mv_x;
	int mv_y;
	int crash;
	int place;

	j = 0;
	mv_y = y;
	crash = 1;
	place = 0;
	while (j < fil->p_col)
	{ 	
		mv_x = x;
		i = 0;
		while (i < fil->p_line)
		{
			if (fil->piece[i + (j * fil->p_line)] == '*' && ((mv_x < 0 || mv_y < 0) || (mv_x > fil->m_line || mv_y > fil->m_col)))
				crash++;
			if (fil->piece[i + (j * fil->p_line)] == '*' && (mv_x >= 0 && mv_y >= 0) && fil->map[mv_x + (mv_y * fil->m_line)] == fil->player)
				place++;
			mv_x++;
			i++;
		}
		mv_y++;
		j++;
	}
	if (place == 1 && crash == 1)
		return (1);
	return (0);
}

void	finding_place(t_fil *fil)
{
	int	x;
	int y;

	y = 0 - fil->p_col;
	while (!(fitting(fil, x, y)) && ++y < fil->m_col)
	{
		x = 1 - fil->p_line;
		while (!(fitting(fil, x, y)) && x < fil->m_line)
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
		fil->map = ft_strdup("");
		while (get_next_line(0, &line) > 0 && line[0] != 'P')
			fil->map = ft_strjoinfree(fil->map, line, 3);
		fil->p_col = ft_atoi(line + 6);
		i = 0;
		while (line[i + 7] != ' ')
			i++;
		fil->p_line = ft_atoi(line + i + 7);
		free(line);
		fil->piece = ft_strdup("");
		while (get_next_line(0, &line) > 0)
			fil->piece = ft_strjoinfree(fil->piece, line, 3);
		finding_place(fil);
		free(fil->map);
		free(fil->piece);
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