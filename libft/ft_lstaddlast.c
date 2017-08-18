/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 07:15:38 by edeveze           #+#    #+#             */
/*   Updated: 2016/11/19 07:26:08 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddlast(t_list **begin, t_list *new)
{
	t_list	*lst;

	lst = *begin;
	if (lst == 0)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}
