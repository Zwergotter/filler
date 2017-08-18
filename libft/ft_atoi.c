/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:00:20 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 07:45:07 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int neg;
	int result;

	i = 0;
	result = 0;
	neg = 1;
	while (ft_iswhitespaces(str[i]))
		i++;
	if ((str[i] == '+' || str[i] == '-') && (str[i + 1] > 47 &&
				str[i + 1] < 58))
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * neg);
}
