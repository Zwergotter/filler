/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:34:08 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/15 12:09:52 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	len = ft_strlen(s) - 1;
	while (s[i] == 32 || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (ft_strnew(1));
	while (s[len] == 32 || s[len] == '\n' || s[len] == '\t')
		len--;
	len = len - i + 1;
	new = ft_strsub(s, i, len);
	if (new == NULL)
		return (NULL);
	return (new);
}
