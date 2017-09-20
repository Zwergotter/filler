/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:14:02 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/17 15:14:05 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/includes/libft.h"
# include <stdio.h>

typedef enum		e_dir
{
	EMPTY, DESC_RIGHT, DESC_LEFT, ASC_RIGHT, ASC_LEFT, EDGE
}					t_dir;

typedef struct		s_fil
{
	char			*map;
	char			*map2;
	char			*piece;
	char			player;
	char			op;
	int				nb;
	int				m_line;
	int				m_col;
	int				p_line;
	int				p_col;
	int				cur_line;
	int				cur_col;
	int				start_xop;
	int				start_yop;
	int				start_xply;
	int				start_yply;
	int				end_xop;
	int				end_yop;
	int				start_ply;
	int				end_ply;
	int				high_x;
	int				high_y;
	int				nb_op;
	int				close;
	t_dir			dir;
	t_dir			dir2;
}					t_fil;

void				positions(t_fil *fil);

int					printing(int x, int y);
int					placing(t_fil *fil, int mv_x, int mv_y);
int					fitting(t_fil *fil, int x, int y);
void				finding_place(t_fil *fil);

int					encircle(t_fil *fil);

int					which_direction(t_fil *fil);
void				edge(t_fil *fil);

int					going_opp_direction(t_fil *fil);

#endif
