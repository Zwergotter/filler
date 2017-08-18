/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:30:32 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/12 13:45:46 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	int				result;

	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	while (n)
	{
		if (*c1 != *c2)
		{
			result = (int)*c1 - (int)*c2;
			return (result);
		}
		c1++;
		c2++;
		n--;
	}
	return (0);
}
