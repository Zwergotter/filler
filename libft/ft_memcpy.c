/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:37:42 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/11 15:44:13 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tempd;
	char	*temps;

	tempd = (char*)dst;
	temps = (char*)src;
	while (n)
	{
		*tempd++ = *temps++;
		n--;
	}
	return (dst);
}
