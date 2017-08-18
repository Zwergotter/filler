/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 13:59:08 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 00:49:24 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	if (*little == '\0')
		return ((char*)big);
	while (*big && n >= ft_strlen(little))
	{
		if (ft_strnequ(big, little, ft_strlen(little)))
			return ((char*)big);
		big++;
		n--;
	}
	return (NULL);
}
