/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 19:22:32 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/25 19:22:34 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi_base(char *str, int base)
{
	int i;
	int ret;
	int t;

	i = ft_strlen(str) - 1;
	ret = 0;
	t = 1;
	while (i >= 0)
	{
		ret += (str[i] - '0') * t;
		t *= base;
		--i;
	}
	return (ret);
}
