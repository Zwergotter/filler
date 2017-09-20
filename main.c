/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:11:38 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/19 15:02:57 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include <fcntl.h>

void	put_map(t_fil *f)
{
	int		i;
	int		j;
	char	*map;

	(void)map;
	(void)j;
	i = 4;
	while (f->map[i])
	{
		if (i % (4 + f->m_col) == 0)
		{
			ft_putchar_fd('\n', 2);
			i += 4;
		}
		if (f->map[i] == f->player)
			ft_putstr_fd("\033[46m \033[0m", 2);
		else if (f->map[i] == '.')
			ft_putstr_fd("\033[44m \033[0m", 2);
		else
			ft_putstr_fd("\033[47m \033[0m", 2);
		++i;
	}
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);
	usleep(20000);
}

void	init_values(t_fil *fil)
{
	fil->map = NULL;
	fil->map2 = NULL;
	fil->piece = NULL;
	fil->nb = 0;
	fil->p_line = 0;
	fil->p_col = 0;
	fil->start_xop = 0;
	fil->start_yop = 0;
	fil->high_x = 0;
	fil->high_y = 0;
	fil->end_xop = 0;
	fil->end_yop = 0;
	fil->start_ply = 0;
	fil->end_ply = 0;
	fil->cur_line = 0;
	fil->cur_col = 0;
	fil->close = 0;
	fil->dir = EMPTY;
	fil->dir2 = EMPTY;
}

void	init(t_fil *fil)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	fil->player = (line[10] == '1' ? 'O' : 'X');
	fil->op = (line[10] == '1' ? 'X' : 'O');
	free(line);
	get_next_line(0, &line);
	fil->m_line = ft_atoi(line + 8);
	i = 0;
	while (line[i + 9] != ' ')
		i++;
	fil->m_col = ft_atoi(line + i + 9);
	free(line);
	init_values(fil);
}

void	filler(t_fil *fil, char *line)
{
	int	i;

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
	fil->map2 = fil->map;
	put_map(fil);
	free(fil->piece);
	fil->nb = 1;
}

int		main(void)
{
	t_fil	*fil;
	char	*line;

	if (!(fil = malloc(sizeof(t_fil))))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit(0);
	}
	init(fil);
	while (1)
	{
		if (!get_next_line(0, &line))
			break ;
		free(line);
		if (fil->nb)
		{
			get_next_line(0, &line);
			free(line);
		}
		filler(fil, line);
	}
	free(fil);
	return (0);
}
