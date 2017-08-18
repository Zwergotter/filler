/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:04:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/01/02 20:14:00 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *s2;

	if (s == NULL)
		return (NULL);
	s2 = (char*)s;
	while (*s2 != '\0' && *s2 != (unsigned char)c)
		s2++;
	if (*s2 == (unsigned char)c)
		return (s2);
	return (NULL);
}
