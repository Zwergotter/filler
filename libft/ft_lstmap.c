/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 05:04:40 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 06:49:47 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_elem;
	t_list	*f_app;
	t_list	*tmp;

	f_app = (*f)(lst);
	if ((new_elem = ft_lstnew(f_app->content, f_app->content_size)) == NULL)
		return (NULL);
	tmp = new_elem;
	lst = lst->next;
	while (lst)
	{
		f_app = (*f)(lst);
		if (!(tmp->next = ft_lstnew(f_app->content, f_app->content_size)))
			return (NULL);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (new_elem);
}
