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

/*
** Searches newline in string passed as argument. Returns its position or 0.
*/

int		find_character(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (0);
}

/*
** Has as arguments buf, where we stored what was read, ret and saved.
** It stores what there is in saved in a temporary string.
** Checks if tmp exist or not, then stores in saved either saved and buf or buf.
*/

void	fill_saved(char *buf, int ret, char **saved)
{
	char		*tmp;

	buf[ret] = '\0';
	tmp = *saved;
	if (tmp)
	{
		*saved = ft_strjoin(*saved, buf);
		free(tmp);
	}
	else
		*saved = ft_strdup(buf);
}

/*
** It stores a read line from saved in line.
** Creates a int newline and a char *tmp.
** If newline = 1, nl is at the beginning. Line is created with strnew(0).
** Else, line is created with strsub starting at temp's beginning and coping it
** before newline's position.
** saved is created with strdup after newline's position.
*/

void	line_read(char **line, char **saved)
{
	int		newline;
	char	*tmp;

	tmp = *saved;
	newline = find_character(tmp) + 1;
	if (newline == 1)
		*line = ft_strnew(0);
	else
		*line = ft_strsub(tmp, 0, newline - 1);
	*saved = ft_strdup(tmp + newline);
	free(tmp);
}

/*
** Receives a file descriptor and the line where to store.
** It returns -1, 0 or 1, depending on whether an error happened, the file's
** reading has been completed or a line has been read.
** Checks errors and then reads from fd in a loop, calling fill_saved in it,
** until saved contains nothing or a newline is found.
** Checks other possible errors after reading.
** If reading is over and no newline had been found in saved, line takes saved
** value and if saved is empty so we return 0, else 1.
** Else we can call line_read and return 1.
*/

int		get_next_line(const int fd, char **line)
{
	static char	*saved = NULL;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		fill_saved(buf, ret, &saved);
		if ((saved == NULL) || ft_strchr(saved, '\n'))
			break ;
	}
	if (ret < 0 || saved == NULL)
		return (-1);
	if (ret < 1 && !ft_strchr(saved, '\n'))
	{
		*line = saved;
		if (saved == NULL || saved[0] == '\0')
			return (0);
		saved = NULL;
		return (1);
	}
	line_read(line, &saved);
	return (1);
}
