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


typedef struct	s_fil
{
	char		*map;
	char		*map2;
	char 		*piece;
	char		player;
	char 		opp;
	int			nb;
	int			m_line;
	int			m_col;
	int 		p_line;
	int			p_col;
	int 		cur_line;
	int			cur_col;
	int			start_xopp;
	int			start_yopp;
	int			end_xopp;
	int			end_yopp;
	int			start_ply;
	int			end_ply;
	int			high_x;
	int			high_y;
	int			nb_opp;
	t_dir		dir;
	t_dir		dir2;
}				t_fil;

# endif
