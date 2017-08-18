/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:52:39 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/15 12:23:17 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (src > dst)
		return (ft_memcpy(dst, src, len));
	else
	{
		d = d + (len - 1);
		s = s + (len - 1);
		while (len)
		{
			*d-- = *s--;
			len--;
		}
	}
	return (dst);
}
