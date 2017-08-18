/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:15:46 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/11 21:15:11 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*temp;

	temp = (unsigned char*)s;
	while (n)
	{
		if (*temp == (unsigned char)c)
			return ((void*)temp);
		temp++;
		n--;
	}
	return (NULL);
}
