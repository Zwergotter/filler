/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:32:13 by edeveze           #+#    #+#             */
/*   Updated: 2017/01/25 15:22:36 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_struct	*multi(t_struct **s, t_struct *e, int fd)
{
	if (*s == NULL)
	{
		if (!(*s = malloc(sizeof(t_struct))))
			return (NULL + 1);
		(*s)->fd = fd;
		(*s)->bf[0] = 0;
		(*s)->next = NULL;
	}
	e = *s;
	while (e->fd != fd)
	{
		if (!e->next)
		{
			if (!(e->next = malloc(sizeof(t_struct))))
				return (NULL + 1);
			e->next->fd = fd;
			e->next->bf[0] = 0;
			e->next->next = NULL;
		}
		e = e->next;
	}
	if (e->bf[0] == 0 && (e->ret = read(fd, e->bf, BUFF_SIZE)) == 0)
		return (0);
	e->d = 0;
	return (e);
}

int			get_next_line(const int fd, char **line)
{
	static t_struct	*s = NULL;
	t_struct		*e;

	if (line == NULL || (*line = ft_strdup("")) == 0)
		return (-1);
	if ((e = multi(&s, 0, fd)) == 0 || e == NULL + 1)
		return (e == 0 ? 0 : -1);
	while (e->d == 0)
	{
		if (e->bf[0] == 0)
			if ((e->ret = read(fd, e->bf, BUFF_SIZE)) == -1)
				return (-1);
		e->bf[e->ret] = 0;
		e->l = ft_strchr(e->bf, '\n') ? ft_strchr(e->bf, '\n') - e->bf
		: ft_strlen(e->bf);
		e->d = !e->bf[0] || ft_strchr(e->bf, '\n') ? 1 : 0;
		ft_memcpy(e->tmp, e->bf, e->l);
		e->tmp[e->l] = 0;
		if (e->bf[0] != 0)
			ft_memcpy(e->bf, e->bf + e->l + e->d, ft_strlen(e->bf) - e->l + 1);
		if (!(*line = ft_strjoinfree(*line, e->tmp, 1)))
			return (-1);
	}
	return (1);
}
