/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 00:18:18 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 06:24:13 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;

	if ((new_elem = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
		new_elem->next = NULL;
		return (new_elem);
	}
	if ((new_elem->content = (void*)malloc(content_size)) == NULL)
		return (NULL);
	ft_memcpy(new_elem->content, content, content_size);
	new_elem->content_size = content_size;
	return (new_elem);
}
