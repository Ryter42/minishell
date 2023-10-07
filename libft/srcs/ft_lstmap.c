/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:59:48 by emoreau           #+#    #+#             */
/*   Updated: 2022/12/02 20:00:23 by emoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tnew;
	t_list	*told;

	if (!f || !lst || !del)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	tnew = new;
	told = lst;
	while (told->next)
	{
		told = told->next;
		tnew->next = ft_lstnew((*f)(told->content));
		if (!tnew->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
			tnew = tnew->next;
	}
	return (new);
}
