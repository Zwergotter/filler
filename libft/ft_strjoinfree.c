/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosi <cosi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 22:47:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/02 01:28:00 by cosi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int nb)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new = ft_strnew(len);
	if (new == NULL)
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strcat(new, s2);
	if (nb == 1 || nb == 3)
		free(s1);
	if (nb == 2 || nb == 3)
		free(s2);
	return (new);
}
