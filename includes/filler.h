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

typedef struct	s_fil
{
	char		*map;
	char		*map2;
	char 		*piece;
	char		player;
	char		opp;
	int			nb;
	int			start_opp;
	int			end_opp;
	int			m_line;
	int			m_col;
	int 		p_line;
	int			p_col;
}				t_fil;

# endif
