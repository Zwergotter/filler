/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:17:58 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/17 17:18:03 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	if (*little == '\0')
		return ((char*)big);
	while (*big)
	{
		if (ft_strnequ(big, little, ft_strlen(little)))
			return ((char*)big);
		big++;
	}
	return (NULL);
}
