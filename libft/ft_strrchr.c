/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:59:43 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/11 14:28:01 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*temp;

	len = ft_strlen(s);
	temp = (char*)s + (char)len;
	while (len && *temp != (unsigned char)c)
	{
		len--;
		temp--;
	}
	if (*temp == (unsigned char)c)
		return (temp);
	return (NULL);
}
