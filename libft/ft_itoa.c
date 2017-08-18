/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 22:15:18 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 06:45:34 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	size_t	len;
	int		i;
	char	*new;

	len = ft_countdigits(n);
	i = 0;
	if (!(new = ft_strnew(len)))
		return (NULL);
	if (n == 0 || n == -2147483648)
		return (n == 0 ? ft_strdup("0") : ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		new[i++] = '-';
	}
	new[len] = '\0';
	while (n > 9)
	{
		new[--len] = ((n % 10) + '0');
		n = n / 10;
	}
	new[i] = (n + '0');
	return (new);
}
