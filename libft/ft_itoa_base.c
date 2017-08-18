/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:01:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/12 14:47:53 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(uintmax_t number, int base, int neg)
{
	long long int	i;
	uintmax_t		save;
	char			*str;
	char			*result;

	i = 0;
	if (number == 0)
		i++;
	save = number;
	while (number > 0 && ++i)
		number = number / base;
	str = "0123456789abcdef";
	if (!(result = malloc(i + neg + 1)))
		exit(0);
	result[i + neg] = '\0';
	result[0] = '-';
	while (i--)
	{
		result[i + neg] = str[save % base];
		save = save / base;
	}
	return (result);
}
