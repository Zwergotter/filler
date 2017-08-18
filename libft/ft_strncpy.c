/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 20:44:44 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/11 17:24:47 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *temp;

	temp = dst;
	while (len > 0 && *src != '\0')
	{
		*temp++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*temp++ = '\0';
		len--;
	}
	return (dst);
}
